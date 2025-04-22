#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void wordleHelper(
    vector<int>& freq,
    int floatsLeft,
    const unordered_set<string>& dictSet,
    set<string>& results,
    string& current,
    unsigned idx);

// Definition of primary wordle function
set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> results;
    string current = in;
    unordered_set<string> dictSet(dict.begin(), dict.end());
    vector<int> freq(26, 0);
    for (char c : floating)
        freq[c - 'a']++;
    wordleHelper(freq, floating.size(), dictSet, results, current, 0);
    return results;
}

// Define any helper functions here
void wordleHelper(
    vector<int>& freq,
    int floatsLeft,
    const unordered_set<string>& dictSet,
    set<string>& results,
    string& current,
    unsigned idx)
{
    unsigned n = current.size();
    int slotsLeft = n - idx;
    if (floatsLeft > slotsLeft)
        return;

    if (idx == n) {
        if (floatsLeft == 0 && dictSet.count(current))
            results.insert(current);
        return;
    }

    if (current[idx] != '-') {
        wordleHelper(freq, floatsLeft, dictSet, results, current, idx + 1);
        return;
    } else {
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == 0) continue;
            char c = 'a' + i;
            current[idx] = c;
            freq[i]--;
            wordleHelper(freq, floatsLeft - 1, dictSet, results, current, idx + 1);
            freq[i]++;
            current[idx] = '-';
        }
        for (int i = 0; i < 26; ++i) {
            if (freq[i] != 0) continue;
            char c = 'a' + i;
            current[idx] = c;
            wordleHelper(freq, floatsLeft, dictSet, results, current, idx + 1);
            current[idx] = '-';
        }
    }
}
