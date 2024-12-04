#include <iostream>
using std::cout, std::endl, std::cerr;

#include <fstream>
using std::ifstream;

#include <map>
using std::map;

#include <string>
using std::string;

#include <filesystem>
namespace fs = std::filesystem;
// For std::filesystem::is_directory

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "USAGE: " << argv[0] << " path/to/input" << endl;
        return 1;
    }

    const fs::path path_to_file = fs::path(argv[1]);
    if (fs::is_directory(path_to_file)) {
        cerr << "ERROR: Input file is a directory" << endl;
        return 2;
    }

    ifstream input(argv[1]);

    if (!input.is_open()) {
        cerr << "ERROR: Failed to open " << argv[1] << endl;
        return 3;
    }

    map<string, int> table;
    string line;
    string key;
    while (std::getline(input, line)) {
        if (!input) {
            if (input.eof()) {
                break;
            }
            cerr << "ERROR: Failed to read from file" << endl;
            return 4;
        }
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
