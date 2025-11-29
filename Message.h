#pragma once
#include <string>

struct Message {
    int id;
    std::string from;
    std::string to;
    std::string payload;      // plaintext (used at endpoints)
    std::string cipherText;   // what travels over the network
    double sendTime = 0.0;
    double deliverTime = 0.0;
    bool delivered = false;
    bool dropped = false;
};
