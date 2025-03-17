#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > 1) return false;

    int diff_count = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff_count > d) return false;
            if (len1 > len2) i++; 
            else if (len1 < len2) j++; 
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

vector<string> generate_word_ladder(string begin_word, string end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        if (last_word == end_word) {
            return ladder;
        }

        for (const string& word : word_list) {
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}


void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i];
            if (i != ladder.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    print_word_ladder(generate_word_ladder("cat", "dog", word_list));
    print_word_ladder(generate_word_ladder("marty", "curls", word_list));
    print_word_ladder(generate_word_ladder("code", "data", word_list));
    print_word_ladder(generate_word_ladder("work", "play", word_list));
    print_word_ladder(generate_word_ladder("sleep", "awake", word_list));
    print_word_ladder(generate_word_ladder("car", "cheat", word_list));
}
