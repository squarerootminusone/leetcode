#include <atomic>
#include <memory>

using Event = int;

template<typename T, std::size_t Capacity>
class ring_buffer {
public:
    bool push(const T& obj) {
        const std::size_t tail = tail_.load(std::memory_order_relaxed); // regular read
        const std::size_t head = head_.load(std::memory_order_acquire); // make sure pop executes after

        // -1 overflows to capacity
        if (tail - head == Capacity)
            return false;

        // write 
        buffer_[tail & mask_] = obj;

        tail_.store(tail + 1, std::memory_order_release);
        return true;
    }

    bool pop(T& obj) {
        const std::size_t head = head_.load(std::memory_order_relaxed);
        const std::size_t tail = tail_.load(std::memory_order_acquire);

        if (tail == head)
            return false;

        obj = buffer_[head & mask_];
        head_.store(head + 1, std::memory_order_release);
        return true;
    }

private: 
    // masking prevents head/tail wrapping
    static constexpr std::size_t mask_ = Capacity - 1;

    alignas(64) std::atomic<std::size_t> head_{0}; // where reader is
    alignas(64) std::atomic<std::size_t> tail_{0}; // where writer is
    alignas(64) std::unique_ptr<T[]> buffer_;
};

ring_buffer<Event, 1 << 16> rx;

void on_packet(const Event& e) {
    rx.push(e);
}

void process() {
    Event e;
    while(rx.pop(e)) {
        // process
    }
}