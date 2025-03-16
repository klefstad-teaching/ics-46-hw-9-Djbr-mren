#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    cout << "Loaded " << word_list.size() << " words from dictionary." << endl;
    
    char run_tests;
    cout << "Run verification tests? (y/n): ";
    cin >> run_tests;
    
    if (run_tests == 'y' || run_tests == 'Y') {
        verify_word_ladder();
        cout << endl;
    }
    
    string start_word, end_word;
    char continue_flag = 'y';
    
    while (continue_flag == 'y' || continue_flag == 'Y') {
        cout << "Enter start word: ";
        cin >> start_word;
        
        cout << "Enter end word: ";
        cin >> end_word;
        
        if (start_word == end_word) {
            error(start_word, end_word, "Start and end words cannot be the same");
            continue;
        }
        
        vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
        
        print_word_ladder(ladder);
        
        cout << "\nFind another word ladder? (y/n): ";
        cin >> continue_flag;
    }
    
    cout << "Goodbye!" << endl;
    return 0;
}