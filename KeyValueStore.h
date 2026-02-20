#ifndef KEYVALSTORE_KEYVALUESTORE_H
#define KEYVALSTORE_KEYVALUESTORE_H

#include <unordered_map>
#include <string>

// KeyValueStore class represents an interactive key-value database
// Supports TTL-based expiration and file persistence
class KeyValueStore {
public:
    KeyValueStore();
    ~KeyValueStore();

    // Sets a key-value pair. TTL (in seconds) is optional; 0 = permanent
    void set(const std::string &key, const std::string &value, int ttlSeconds);

    // Prints the value of a key if it exists and hasn't expired
    void get(const std::string &key);

    // Deletes a key from the store
    void del(const std::string &key);

    // Saves all keys to a file
    void save(const std::string &filename) const;

    // Loads all keys from file
    void load(const std::string &filename);
private:
    struct Entry {
        std::string value;
        std::time_t expireAt;
    };

    std::unordered_map<std::string, Entry> store;
};

#endif //KEYVALSTORE_KEYVALUESTORE_H