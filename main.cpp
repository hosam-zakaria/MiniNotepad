#include <iostream>
#include <string>
#include <limits>
#include "TextEditor.h"
#include "KMP.h"
#include "FileManager.h"

// ── Helper Functions ─────────────────────────────────────────────

void printMenu() {
    std::cout << "\n===== Mini Text Editor =====\n";
    std::cout << "1. Write / Replace Text\n";
    std::cout << "2. Display Text\n";
    std::cout << "3. Insert Text\n";
    std::cout << "4. Delete Text\n";
    std::cout << "5. Search Text (KMP)\n";
    std::cout << "6. Save to File\n";
    std::cout << "7. Load from File\n";
    std::cout << "8. Exit\n";
    std::cout << "Choose an option: ";
}

// Safely read an integer, re-prompting on invalid input.
// Returns false if stdin reaches EOF (e.g. piped input ends).
bool readInt(const std::string& prompt, int& outValue) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> outValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        if (std::cin.eof()) return false;  // No more input available
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Read multiple lines until the user types END on its own line.
// Lines are joined with '\n' to preserve multiline structure.
std::string readMultilineText() {
    std::cout << "Enter text (type END on a new line to finish):\n";
    std::string result;
    std::string line;
    bool firstLine = true;
    while (std::getline(std::cin, line)) {
        if (line == "END") break;
        if (!firstLine) result += "\n";
        result += line;
        firstLine = false;
    }
    return result;
}

// ── Main ─────────────────────────────────────────────────────────

int main() {
    TextEditor editor;
    bool running = true;

    std::cout << "Welcome to Mini Text Editor!\n";

    while (running) {
        printMenu();

        int choice;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) break;  // End of input — exit gracefully
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number (1-8).\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string text = readMultilineText();
                editor.setText(text);
                std::cout << "Text has been set. ("
                          << text.length() << " characters)\n";
                break;
            }
            case 2: {
                editor.displayText();
                break;
            }
            case 3: {
                int index;
                if (!readInt("Enter index to insert at: ", index)) break;
                std::cout << "Enter text to insert: ";
                std::string str;
                std::getline(std::cin, str);
                editor.insertText(index, str);
                break;
            }
            case 4: {
                int index, count;
                if (!readInt("Enter starting index: ", index)) break;
                if (!readInt("Enter number of characters to delete: ", count)) break;
                editor.deleteText(index, count);
                break;
            }
            case 5: {
                if (editor.isEmpty()) {
                    std::cout << "The text buffer is empty. Nothing to search.\n";
                    break;
                }
                std::cout << "Enter pattern to search for: ";
                std::string pattern;
                std::getline(std::cin, pattern);
                if (pattern.empty()) {
                    std::cout << "Error: Pattern cannot be empty.\n";
                    break;
                }
                std::vector<int> matches = KMP::search(editor.getText(), pattern);
                if (matches.empty()) {
                    std::cout << "Pattern \"" << pattern
                              << "\" not found in the text.\n";
                } else {
                    std::cout << "Pattern \"" << pattern << "\" found "
                              << matches.size() << " time(s) at index(es): ";
                    for (size_t i = 0; i < matches.size(); i++) {
                        if (i > 0) std::cout << ", ";
                        std::cout << matches[i];
                    }
                    std::cout << "\n";
                }
                break;
            }
            case 6: {
                if (editor.isEmpty()) {
                    std::cout << "The text buffer is empty. Nothing to save.\n";
                    break;
                }
                std::cout << "Enter filename to save to: ";
                std::string filename;
                std::getline(std::cin, filename);
                if (filename.empty()) {
                    std::cout << "Error: Filename cannot be empty.\n";
                    break;
                }
                if (FileManager::saveToFile(filename, editor.getText())) {
                    std::cout << "Text saved to \"" << filename
                              << "\" successfully.\n";
                }
                break;
            }
            case 7: {
                std::cout << "Enter filename to load from: ";
                std::string filename;
                std::getline(std::cin, filename);
                if (filename.empty()) {
                    std::cout << "Error: Filename cannot be empty.\n";
                    break;
                }
                bool success;
                std::string content = FileManager::loadFromFile(filename, success);
                if (success) {
                    editor.setText(content);
                    std::cout << "Loaded " << content.length()
                              << " characters from \"" << filename << "\".\n";
                }
                break;
            }
            case 8: {
                running = false;
                std::cout << "Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid option. Please choose 1-8.\n";
                break;
            }
        }
    }

    return 0;
}
