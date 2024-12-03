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