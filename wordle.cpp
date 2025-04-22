#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::string floating, const std::set<std::string>& dict, 
    std::set<std::string>& results, std::string current, unsigned int idx);
    
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    string current = in;
    wordleHelper(floating, dict, results, current, 0);  
    return results;
}

// Define any helper functions here
void wordleHelper(
    std::string floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& results,
    std::string current,
    unsigned int idx)
{
    int slotsLeft = current.length() - idx;
    if ((int)floating.length() > slotsLeft) return;


    if (idx == current.length()){
        if (dict.count(current) > 0 && floating.empty()){
            results.insert(current);
        }
        return;
    }

    if (current[idx] != '-'){
        wordleHelper(floating, dict, results, current, idx + 1);
        return;
    } else {
        for (unsigned int i = 0; i < floating.length(); ++i){
            char c = floating[i];
            current[idx] = c;
            string newFloating = floating;
            newFloating.erase(i, 1);
            wordleHelper(newFloating, dict, results, current, idx + 1);
            current[idx] = '-';
        }

        for (char c = 'a'; c <= 'z'; ++c){
            if (floating.find(c) == string::npos){
                current[idx] = c;
                wordleHelper(floating, dict, results, current, idx + 1);
                current[idx] = '-';
            }
        }
    }
}

