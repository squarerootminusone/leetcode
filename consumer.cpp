struct ProtocolMessage {
    uint64_t seq_num;
    uint32_t x;
    uint32_t y;
    
    bool operator<(const ProtocolMessage& other) const {
        return seq_num < other.seq_num;
    }
};

void onUDPPacket(const char* buffer) {
    ProtocolMessage msg;
    std::memcpy(&msg, buffer, sizeof(ProtocolMessage));

    if (msg.seq_num == next_seq_number_) {
        ConsumerFunction(msg);
        next_seq_number_++;
    }
    else if (msg.seq_num > next_seq_number_) {
        buffer_.insert(msg);
        // Request recovery for the gap
        RequestTCPRecovery(next_seq_number_, msg.seq_num - next_seq_number_);
    }
    // else: duplicate/old message, ignore
}

void onTCPPacket(const char* buffer, size_t count) {
    const ProtocolMessage* messages = reinterpret_cast<const ProtocolMessage*>(buffer);
    
    for (size_t i = 0; i < count; i++) {
        ConsumerFunction(messages[i]);
        next_seq_number_++;
    }
    
    while (!buffer_.empty() && buffer_.begin()->seq_num == next_seq_number_) {
        ConsumerFunction(*buffer_.begin());
        buffer_.erase(buffer_.begin());
        next_seq_number_++;
    }
}