#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;

    int i = 0, j = 0, edits = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++edits > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return edits + abs(len1 - i) + abs(len2 - j) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    string start = begin_word;
    string end = end_word;
    
    if (start == end) {
        return {start};
    }
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({start});
    set<string> visited;
    visited.insert(start);
    
    if (word_list.find(end) == word_list.end() && end != start) {
        return {};
    }
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end) {
                    return new_ladder;
                }
                
                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open dictionary file: " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found:";
    for (const string& word : ladder) {
        cout << " " << word;
    }
    cout << " " << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    cout << "Test 1: " << (generate_word_ladder("cat", "dog", word_list).size() == 4 ? "Passed" : "Failed") << endl;
    cout << "Test 2: " << (generate_word_ladder("marty", "curls", word_list).size() == 6 ? "Passed" : "Failed") << endl;
    cout << "Test 3: " << (generate_word_ladder("code", "data", word_list).size() == 6 ? "Passed" : "Failed") << endl;
    cout << "Test 4: " << (generate_word_ladder("work", "play", word_list).size() == 6 ? "Passed" : "Failed") << endl;
    cout << "Test 5: " << (generate_word_ladder("sleep", "awake", word_list).size() == 8 ? "Passed" : "Failed") << endl;
    cout << "Test 6: " << (generate_word_ladder("car", "cheat", word_list).size() == 4 ? "Passed" : "Failed") << endl;
}
