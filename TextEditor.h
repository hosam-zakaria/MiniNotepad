#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <string>

class TextEditor {
private:
    std::string text;  // The main text buffer

public:
    TextEditor();

    // Replace the entire text buffer
    void setText(const std::string& newText);

    // Get a copy of the current text
    std::string getText() const;

    // Print the text to the console with formatting
    void displayText() const;

    // Insert a string at the given index (0-based)
    void insertText(int index, const std::string& str);

    // Delete 'count' characters starting at 'index'
    void deleteText(int index, int count);

    // Check if the buffer is empty
    bool isEmpty() const;
};

#endif

