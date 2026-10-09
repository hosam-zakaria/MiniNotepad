#include "KMP.h"

std::vector<int> KMP::buildLPS(const std::string& pattern) {
    int m = static_cast<int>(pattern.length());
    std::vector<int> lps(m, 0);  // LPS[0] is always 0

    // 'len' tracks the length of the previous longest prefix-suffix.
    // We start comparing from index 1 (LPS[0] is always 0).
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            // Characters match — extend the current prefix-suffix
            len++;
            lps[i] = len;
            i++;
        } else {
            // Mismatch
            if (len != 0) {
                // Don't increment i. Fall back to the previous LPS value
                // to try a shorter prefix-suffix.
                len = lps[len - 1];
            } else {
                // No prefix-suffix exists for pattern[0..i]
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

std::vector<int> KMP::search(const std::string& text,
                              const std::string& pattern) {
    std::vector<int> result;

    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());

    // Edge case: empty pattern — nothing to search for
    if (m == 0) return result;

    // Edge case: pattern longer than text — no possible match
    if (m > n) return result;

    std::vector<int> lps = buildLPS(pattern);

    int i = 0;  // index into text
    int j = 0;  // index into pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            // Characters match — advance both pointers
            i++;
            j++;
        }

        if (j == m) {
            // Full pattern matched! Record the starting index.
            result.push_back(i - j);

            // Continue searching for overlapping matches.
            // Fall back using LPS to check for the next possible match
            // without re-examining characters we already know match.
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            // Mismatch after some matches
            if (j != 0) {
                // Fall back in the pattern using LPS
                j = lps[j - 1];
            } else {
                // No fallback possible — advance text pointer
                i++;
            }
        }
    }

    return result;
}

