#include <iostream>
#include <pthread.h>

// 定义一个数据结构，用于存储共享数据
struct Data {
    int value;
    pthread_rwlock_t lock; // 读写锁
};

// 读取数据的线程函数
void* reader_thread(void* arg) {
    Data* data = static_cast<Data*>(arg);

    pthread_rwlock_rdlock(&data->lock); // 获取读锁

    std::cout << "Reader thread: Reading value = " << data->value << std::endl;

    pthread_rwlock_unlock(&data->lock); // 解锁

    return nullptr;
}

// 写入数据的线程函数
void* writer_thread(void* arg) {
    Data* data = static_cast<Data*>(arg);

    pthread_rwlock_wrlock(&data->lock); // 获取写锁

    data->value++; // 修改数据

    std::cout << "Writer thread: Writing value = " << data->value << std::endl;

    pthread_rwlock_unlock(&data->lock); // 解锁

    return nullptr;
}

int main() {
    // 初始化数据结构和读写锁
    Data data;
    data.value = 0;
    pthread_rwlock_init(&data.lock, nullptr);

    // 创建读取数据的线程
    pthread_t reader;
    pthread_create(&reader, nullptr, reader_thread, &data);

    // 创建写入数据的线程
    pthread_t writer;
    pthread_create(&writer, nullptr, writer_thread, &data);

    // 等待线程结束
    pthread_join(reader, nullptr);
    pthread_join(writer, nullptr);

    // 销毁读写锁
    pthread_rwlock_destroy(&data.lock);

    return 0;
}

