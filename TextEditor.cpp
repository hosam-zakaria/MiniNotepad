#include "TextEditor.h"
#include <iostream>

TextEditor::TextEditor() : text("") {}

void TextEditor::setText(const std::string& newText) {
    text = newText;
}

std::string TextEditor::getText() const {
    return text;
}

void TextEditor::displayText() const {
    if (text.empty()) {
        std::cout << "[The text buffer is empty]\n";
        return;
    }
    std::cout << "--- Text Content ---\n";
    std::cout << text << "\n";
    std::cout << "--- End (Length: " << text.length() << ") ---\n";
}

void TextEditor::insertText(int index, const std::string& str) {
    // Allow inserting at index == length (appending)
    if (index < 0 || index > static_cast<int>(text.length())) {
        std::cout << "Error: Index " << index
                  << " is out of range. Valid range: 0 to "
                  << text.length() << "\n";
        return;
    }
    if (str.empty()) {
        std::cout << "Nothing to insert (empty string).\n";
        return;
    }
    text.insert(index, str);
    std::cout << "Inserted \"" << str << "\" at index " << index << ".\n";
}

void TextEditor::deleteText(int index, int count) {
    if (text.empty()) {
        std::cout << "Error: Nothing to delete. The text buffer is empty.\n";
        return;
    }
    if (index < 0 || index >= static_cast<int>(text.length())) {
        std::cout << "Error: Index " << index
                  << " is out of range. Valid range: 0 to "
                  << text.length() - 1 << "\n";
        return;
    }
    if (count <= 0) {
        std::cout << "Error: Count must be a positive number.\n";
        return;
    }

    // Clamp count so we don't go past the end of the string
    int maxCount = static_cast<int>(text.length()) - index;
    if (count > maxCount) {
        std::cout << "Note: Only " << maxCount
                  << " character(s) available from index " << index
                  << ". Deleting " << maxCount << " instead of "
                  << count << ".\n";
        count = maxCount;
    }

    std::string deleted = text.substr(index, count);
    text.erase(index, count);
    std::cout << "Deleted " << count
              << " character(s): \"" << deleted << "\"\n";
}

bool TextEditor::isEmpty() const {
    return text.empty();
}

