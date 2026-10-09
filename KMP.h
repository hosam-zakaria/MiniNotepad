#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

class KMP {
public:
    // Build the LPS (Longest Proper Prefix which is also Suffix) array.
    // LPS[i] = length of the longest proper prefix of pattern[0..i]
    //          that is also a suffix of pattern[0..i].
    // Time: O(m)   Space: O(m)   where m = pattern.length()
    static std::vector<int> buildLPS(const std::string& pattern);

    // Search for all occurrences of 'pattern' in 'text' using KMP.
    // Returns a vector of starting indices (0-based) where the pattern
    // occurs, including overlapping matches.
    // Time: O(n + m)   Space: O(m)   where n = text.length()
    static std::vector<int> search(const std::string& text,
                                   const std::string& pattern);
};

#endif

