#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable conditionVariable;
public:
    void push(T value);
    T pop();
    bool empty() const { return queue.empty(); }
};

template <typename T>
void ThreadSafeQueue<T>::push(T value) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(std::move(value));
    conditionVariable.notify_one();
}

template <typename T>
T ThreadSafeQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    conditionVariable.wait(lock, [this] { return !queue.empty(); });
    T value = std::move(queue.front());
    queue.pop();
    return value;
}

#endif // !THREAD_SAFE_QUEUE_HPP