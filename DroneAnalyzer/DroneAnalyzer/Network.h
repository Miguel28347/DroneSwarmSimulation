#pragma once
#include "Message.h"
#include "Node.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>

class Network {
public:
    Network(double baseLatency, double jitter, double dropProbability)
        : baseLatency_(baseLatency),
        jitter_(jitter),
        dropProb_(dropProbability),
        rng_(std::random_device{}()),
        uniform01_(0.0, 1.0),
        jitterDist_(-jitter, jitter)
    {
        logFile_.open("comms_log.csv");
        logFile_ << "event,time,id,from,to,latency,dropped,payload\n";
    }

    ~Network() {
        if (logFile_.is_open()) {
            logFile_.close();
        }
    }

    Node& addNode(const std::string& name) {
        nodes_.emplace_back(name);
        nodeIndex_[name] = static_cast<int>(nodes_.size()) - 1;
        return nodes_.back();
    }

    Node* getNode(const std::string& name) {
        auto it = nodeIndex_.find(name);
        if (it == nodeIndex_.end()) return nullptr;
        return &nodes_[it->second];
    }

    // schedule a message from 'from' to 'to' at simulation time 't'
    void sendMessage(const std::string& from,
        const std::string& to,
        const std::string& payload,
        double currentTime)
    {
        Message msg;
        msg.id = nextMessageId_++;
        msg.from = from;
        msg.to = to;
        msg.payload = payload;
        msg.sendTime = currentTime;

        // Encrypt payload before placing it "on the wire"
        msg.cipherText = xorCipher(payload, encryptionKey_);

        bool drop = (uniform01_(rng_) < dropProb_);
        if (drop) {
            msg.dropped = true;
            msg.deliverTime = currentTime + sampleLatency();
            droppedMessages_.push_back(msg);

            std::cout << std::fixed << std::setprecision(3)
                << "[t=" << currentTime << "] "
                << "[DROP SCHEDULED] " << from << " -> " << to
                << "  msgId=" << msg.id
                << "  payload=<ENCRYPTED len=" << msg.cipherText.size() << ">\n";

            // LOG: record drop event
            logFile_ << "drop_scheduled,"
                << currentTime << ","
                << msg.id << ","
                << msg.from << ","
                << msg.to << ","
                << 0.0 << ","      // latency N/A at scheduling
                << 1 << ","        // dropped = 1
                << "\"" << payload << "\""
                << "\n";
        }
        else {
            msg.dropped = false;
            msg.deliverTime = currentTime + sampleLatency();
            inTransit_.push_back(msg);

            std::cout << std::fixed << std::setprecision(3)
                << "[t=" << currentTime << "] "
                << "[SEND] " << from << " -> " << to
                << "  msgId=" << msg.id
                << "  payload=<ENCRYPTED len=" << msg.cipherText.size() << ">\n";

            // LOG: record send event
            logFile_ << "send,"
                << currentTime << ","
                << msg.id << ","
                << msg.from << ","
                << msg.to << ","
                << 0.0 << ","      // latency N/A at send
                << 0 << ","        // dropped = 0
                << "\"" << payload << "\""
                << "\n";
        }
    }

    // advance simulation by dt
    void step(double currentTime) {
        // deliver messages whose time has come
        std::vector<Message> remaining;
        remaining.reserve(inTransit_.size());

        for (auto& msg : inTransit_) {
            if (msg.deliverTime <= currentTime) {
                deliver(msg, currentTime);
            }
            else {
                remaining.push_back(msg);
            }
        }

        inTransit_.swap(remaining);
    }

    // print summary at end
    void printSummary(double finalTime) const {
        std::cout << "\n=== Simulation Summary (t=" << finalTime << ") ===\n";
        std::cout << "Delivered messages: " << deliveredCount_ << "\n";
        std::cout << "Dropped messages:   " << droppedMessages_.size() << "\n";

        if (deliveredCount_ > 0) {
            double avgLatency = totalLatency_ / deliveredCount_;
            std::cout << "Average latency:    " << avgLatency << " s\n";
        }

        std::cout << "\nPer-node inbox contents:\n";
        for (const auto& node : nodes_) {
            std::cout << "Node " << node.name() << ":\n";
            for (const auto& rm : node.inbox()) {
                std::cout << "  at t=" << rm.timeReceived
                    << "  from=" << rm.from
                    << "  id=" << rm.id
                    << "  latency=" << rm.latency
                    << "  payload=\"" << rm.payload << "\"\n";
            }
        }
    }

private:
    double sampleLatency() {
        return baseLatency_ + jitterDist_(rng_);
    }

    std::string xorCipher(const std::string& text, const std::string& key) {
        std::string out = text;
        for (size_t i = 0; i < text.size(); ++i) {
            out[i] = text[i] ^ key[i % key.size()];
        }
        return out;
    }

    void deliver(Message& msg, double currentTime) {
        Node* dest = getNode(msg.to);
        if (!dest) {
            std::cout << std::fixed << std::setprecision(3)
                << "[t=" << currentTime << "] "
                << "[DELIVERY FAILED] unknown node " << msg.to
                << " for msgId=" << msg.id << "\n";
            return;
        }

        double latency = msg.deliverTime - msg.sendTime;
        deliveredCount_++;
        totalLatency_ += latency;

        // Decrypt at the destination
        std::string plaintext = xorCipher(msg.cipherText, encryptionKey_);

        dest->onMessageReceived(msg.id, msg.from, plaintext,
            msg.deliverTime, latency);

        std::cout << std::fixed << std::setprecision(3)
            << "[t=" << currentTime << "] "
            << "[DELIVER] " << msg.from << " -> " << msg.to
            << "  msgId=" << msg.id
            << "  latency=" << latency
            << "  payload=\"" << plaintext << "\"\n";

        // LOG: record delivery event
        logFile_ << "deliver,"
            << currentTime << ","
            << msg.id << ","
            << msg.from << ","
            << msg.to << ","
            << latency << ","
            << 0 << ","              // not dropped
            << "\"" << plaintext << "\""
            << "\n";
    }

    std::ofstream logFile_;

    // network parameters
    double baseLatency_;
    double jitter_;
    double dropProb_;

    // nodes
    std::vector<Node> nodes_;
    std::unordered_map<std::string, int> nodeIndex_;

    // in-flight and dropped messages
    std::vector<Message> inTransit_;
    std::vector<Message> droppedMessages_;

    int nextMessageId_ = 1;
    int deliveredCount_ = 0;
    double totalLatency_ = 0.0;

    // RNG
    std::mt19937 rng_;
    std::uniform_real_distribution<double> uniform01_;
    std::uniform_real_distribution<double> jitterDist_;

    // "encryption"
    std::string encryptionKey_ = "USMC-COMMS-KEY";
};
