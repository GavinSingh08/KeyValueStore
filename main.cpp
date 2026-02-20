#include <iostream>
#include <sstream>

#include "KeyValueStore.h"

int main() {
    KeyValueStore store;
    // Load keys
    store.load("key_vals.txt");
    std::string line;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        // Read the command, key/value, optional "EX" command, and expiration from console
        std::istringstream stream(line);
        std::string command, key, value, extra, expiration;
        stream >> command >> key >> value >> extra >> expiration;

        // If user wants an expiration, read "EX" and set expiration to user input, otherwise default to 0
        if (command == "SET") {
            int ttl = 0;
            if (extra == "EX") {
                ttl = std::stoi(expiration);
            }
            store.set(key, value, ttl);
        } else if (command == "GET") {
            store.get(key);
        } else if (command == "DEL") {
            store.del(key);
        } else if (command == "EXIT") {
            break;
        } else {
            std::cout << "Unknown command\n";
        }
    }

    // Save keys
    store.save("key_vals.txt");
}