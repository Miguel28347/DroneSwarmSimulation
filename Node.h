#pragma once
#include <string>
#include <vector>

struct ReceivedMessage {
    int id;
    std::string from;
    std::string payload;
    double timeReceived;
    double latency;
};

class Node {
public:
    explicit Node(const std::string& name) : name_(name) {}

    const std::string& name() const { return name_; }

    void onMessageReceived(int id,
        const std::string& from,
        const std::string& payload,
        double timeReceived,
        double latency)
    {
        inbox_.push_back({ id, from, payload, timeReceived, latency });
    }

    const std::vector<ReceivedMessage>& inbox() const { return inbox_; }

private:
    std::string name_;
    std::vector<ReceivedMessage> inbox_;
};
