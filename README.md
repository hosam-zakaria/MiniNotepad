# Mini Text Editor

A CLI-based text editor built in C++ as a student project to practice **Object-Oriented Programming** and **Data Structures & Algorithms**.

## Features

- **Write & Display** — Enter multiline text and view the current buffer
- **Insert & Delete** — Modify text at any position with full input validation
- **KMP Search** — Find all occurrences of a pattern using the Knuth–Morris–Pratt algorithm (implemented from scratch)
- **Save & Load** — Persist text to files and reload with error handling

## Project Structure

```
Notepad/
├── main.cpp            — CLI menu loop and input helpers
├── TextEditor.h/cpp    — Text buffer management (write, display, insert, delete)
├── KMP.h/cpp           — KMP string-matching algorithm with LPS array
├── FileManager.h/cpp   — File save/load operations
└── README.md
```

## How to Compile & Run

### Prerequisites

- A C++17 compatible compiler (g++, clang++, or MSVC)

### Build

```bash
g++ -std=c++17 -Wall -Wextra -o editor.exe main.cpp TextEditor.cpp KMP.cpp FileManager.cpp
```

### Run

```bash
./editor.exe
```

## Usage

The editor presents a menu-driven interface:

```
===== Mini Text Editor =====
1. Write / Replace Text
2. Display Text
3. Insert Text
4. Delete Text
5. Search Text (KMP)
6. Save to File
7. Load from File
8. Exit
Choose an option:
```

### Writing Text

Select option **1** and type your text. Supports multiple lines. Type `END` on a new line to finish:

```
Enter text (type END on a new line to finish):
Hello World
This is line two
END
Text has been set. (28 characters)
```

### Inserting Text

Select option **3**, enter the index (0-based) and the text to insert:

```
Enter index to insert at: 5
Enter text to insert:  KMP
Inserted " KMP" at index 5.
```

### Deleting Text

Select option **4**, enter the starting index and number of characters:

```
Enter starting index: 0
Enter number of characters to delete: 6
Deleted 6 character(s): "Hello "
```

### Searching with KMP

Select option **5** and enter a pattern. The editor finds all occurrences, including overlapping matches:

```
Enter pattern to search for: ABAB
Pattern "ABAB" found 3 time(s) at index(es): 0, 2, 4
```

### Saving and Loading

- **Save** (option 6): Enter a filename to save the current text
- **Load** (option 7): Enter a filename to load text from a file

## OOP Design

| Class | Responsibility |
|---|---|
| `TextEditor` | Owns the text buffer (`std::string`). Provides insert, delete, display with input validation. |
| `KMP` | Static utility. Implements LPS array construction and KMP pattern search from scratch. |
| `FileManager` | Static utility. Handles file read/write operations with error handling. |

**Design principles:**
- **Encapsulation** — `TextEditor` keeps its data private; access only through validated methods
- **Single Responsibility** — Each class has one clear job
- **Separation of Concerns** — `main.cpp` coordinates between classes; no class depends on another

## KMP Algorithm

The Knuth–Morris–Pratt algorithm searches for a pattern in text in **O(n + m)** time, compared to **O(n × m)** for naive search.

**Key idea:** When a mismatch occurs, the LPS (Longest Proper Prefix which is also a Suffix) array tells us how far back to reset in the pattern — so the text pointer never goes backward.

| | Naive Search | KMP |
|---|---|---|
| Time Complexity | O(n × m) | O(n + m) |
| Space Complexity | O(1) | O(m) |

## Error Handling

- Invalid menu input → re-prompts without crashing
- Out-of-range indices → clear error messages
- Delete count exceeding available characters → clamped with a note
- Empty pattern for search → rejected
- File not found → error message, text buffer unchanged
- EOF on stdin → graceful exit

## Built With

- C++17
- Standard Library only (`<string>`, `<vector>`, `<fstream>`, `<sstream>`, `<iostream>`)
- No external dependencies

