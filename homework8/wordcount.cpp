#include <iostream>
using std::cout, std::endl, std::cerr;

#include <fstream>
using std::ifstream;

#include <map>
using std::map;

#include <string>
using std::string;

// To-Do: A line that does not have a line ending does not work


int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "USAGE: " << argv[0] << " path/to/input" << endl;
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open()) {
        cerr << "ERROR: Failed to open " << argv[1] << endl;
        return 2;
    }

    map<string, int> table;
    string line;
    string key;
    while (std::getline(input, line)) {
        for (auto let : line) {
            if (let != ' ') {
                key += let;
            }
            else {
                table[key] += 1;
                key = "";
            }
        }
        
        // Get line delimits at new lines so when we reach the end of 
        //   the loop we still have one leftover word
        if (key != "") {
            table[key] += 1;
            key = "";
        }
    }

    int word_sum = 0;
    for (const auto pair : table) {
        word_sum += 1;
    }

    cout << "Number of distinct words: " << word_sum << endl << endl;

    for (auto key : table) {
        cout << key.first << ": " << key.second << endl;
    }

    return 0;
}
