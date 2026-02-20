#include "KeyValueStore.h"

#include <fstream>
#include <iostream>
#include <string>

KeyValueStore::KeyValueStore() = default;
KeyValueStore::~KeyValueStore() = default;

void KeyValueStore::set(const std::string &key, const std::string &value, const int ttlSeconds) {
    Entry e;
    e.value = value;

    // Expiration time in seconds – if valid – otherwise set to 0, which is permanent
    if (ttlSeconds > 0) {
        e.expireAt = ttlSeconds + std::time(nullptr);
    } else {
        e.expireAt = 0;
    }

    // Store and print contents to console
    store[key] = e;
    std::cout << "Key: " << key << " | Value: " << value <<
        " | With expiration: " << ttlSeconds << " seconds" << std::endl;
}

void KeyValueStore::get(const std::string &key) {
    auto it = store.find(key);

    // If key not found
    if (it == store.end()) {
        std::cout << "Key not found" << std::endl;
        return;
    }

    // Check expiration
    if (it->second.expireAt != 0 && std::time(nullptr) >= it->second.expireAt) {
        store.erase(it);
        std::cout << "Key expired" << std::endl;
        return;
    }

    // Print value
    std::cout << it->second.value << std::endl;
}

void KeyValueStore::del(const std::string &key) {

    // If store contains the key, delete it, otherwise do nothing
    if (store.contains(key)) {
        std::cout << "Deleting: " << key << std::endl;
        store.erase(key);
    }
}

// Saves (key, value) pair into a file. Also saves expiration
void KeyValueStore::save(const std::string &filename) const {
    std::ofstream file(filename);
    for (auto pair : store) {
        file << pair.first << " " << pair.second.value << " " << pair.second.expireAt << std::endl;
    }
}

// Loads key, value, and expiration from file
void KeyValueStore::load(const std::string &filename) {
    std::ifstream file(filename);
    std::string key, value, expiration;
    Entry e;
    while (file >> key >> value >> expiration) {
        e.value = value;
        e.expireAt = std::stoi(expiration);
        store[key] = e;
    }
}
