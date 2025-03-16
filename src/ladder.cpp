#include "ladder.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <cctype>
#include <cmath>
#include <cassert>
using namespace std;

void error(string word1, string word2, string msg) {
    cout << word1 << word2 << msg << endl;
}

void lowercase(string &word) {
    for (char& c: word) {
        c = tolower(c);
    }
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    vector<string> begin {begin_word};
    
    if (begin_word == end_word) { // check invalid input: beginning and end are the same!
        error(begin_word, end_word, " are invalid.");
        return begin;
    }

    queue<vector<string>> ladder_queue; // initialize ladder queue with initial stack
    ladder_queue.push(begin);

    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back(); // last element in the current ladder
        for (auto word: word_list) {

            if (is_adjacent(last_word, word)) {

                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                } 
            }
        }
    }
    vector<string> none;
    return none;
}

bool is_adjacent(const string& word1, const string& word2) {
    // two cases: one word is 1 char longer than the other or the words differ by one letter
    return edit_distance_within(word1, word2, 1);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // checking for adjacency
    int skipped = d;
    int i = 0, j = 0;
    int len1 = str1.size(), len2 = str2.size();

    if (abs(len1 - len2) > d) return false;

    while (i < len1 && j < len2) {
        if (str1[i] == str2[j]) {
            i++;
            j++;
        } else {
            if (skipped == 0) return false;
            skipped--;
            if (len1 == len2) {
                i++;
                j++;
            } else if (len1 < len2) {
                j++;
            } else { 
                i++;
            }
        
        }
    }
    return true;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream infile(file_name);
    if (!infile) {
        cout << "Error: Cannot open file." << endl;
        return;
    }
    string word;
    while (infile >> word) {
        lowercase(word);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() == 0) {
            cout << "No word ladder found." << endl;
            return;
    }
    for (auto word: ladder) {
        cout << word <<  " ";
    }
}

void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "src/words.txt");
    assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    assert(generate_word_ladder("code", "data", word_list).size() == 6);
    assert(generate_word_ladder("work", "play", word_list).size() == 6);
    assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    assert(generate_word_ladder("car", "cheat", word_list).size() == 4);    
}