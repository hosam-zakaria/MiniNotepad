#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

class FileManager {
public:
    // Save content to a file. Returns true on success.
    static bool saveToFile(const std::string& filename,
                           const std::string& content);

    // Load entire file contents into a string.
    // Sets 'success' to true if the file was read successfully.
    static std::string loadFromFile(const std::string& filename,
                                    bool& success);
};

#endif

