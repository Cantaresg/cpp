#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <string>
#include <sstream>

void display(const std::map<int, std::string> &text) {
    for(auto item:text) {
        std::cout << std::setw(4) <<std::left << item.first << item.second << std::endl;
    }
}  

void display(const std::map<std::string, std::set<int>> &text) {
    for(auto item:text) {
        std::cout << std::setw(10) <<std::left << item.first <<"\t" << "[";
        for (int i: item.second) {
            std::cout << i << " ";
        }
        std::cout << "]" << std::endl;
    }
} 

void display(const std::map<std::string, int> &text) {
    for(auto item:text) {
        std::cout << std::setw(10) <<std::left << item.first << item.second << std::endl;
    }
}  
bool read_file(std::map<int, std::string> &text, std::string filename) {
    
    std::ifstream in_file(filename);
    std::string line;
    size_t i{1};

     if(!in_file) {
        std::cerr << "Error opening file!" <<std::endl;
        return 1;
    }

    else {
        while (!in_file.eof()) {
            std::getline(in_file, line);
            text.insert((std::pair<int,std::string>(i, line)));
            i++;
        }
    }

    in_file.close();
    return 0;
}

std::string convert_word(std::string word) {
    std::string copy{""};
            std::for_each(word.begin(), word.end(),[&copy](char x)mutable{
                if (std::isalpha(x)) {
                    copy+= x;
                }
            });
            std::transform(copy.begin(), copy.end(), copy.begin(), [](char c) {
                return std::tolower(c);
                });
                return copy;
}

void text_to_word(const std::map<int,std::string> &text, std::set<std::string> &word_list) {
        for (auto it{text.begin()}; it != text.end(); it++ ) {
        std::stringstream s((*it).second);
           std::string word;
    
        while (s>>word) {
            std::string copy(convert_word(word));
            word_list.insert(copy);
        }
    }
}



int main() {
    std::string filename {"words.txt"};
    std::map<int, std::string> text;
    std::set<std::string> word_list;
    std::map<std::string, int> wordcount;
    std::map<std::string, std::set<int>> word_loc;

    read_file(text, filename);

    text_to_word(text, word_list);
 

    for(std::string word: word_list) {

        std::for_each(text.begin(), text.end(), [&wordcount, &word_loc,word](std::pair<int, std::string> line)mutable{
            std::stringstream ss(line.second);
            std::string elem;
            
            
            while (ss >> elem) {
                if (word == convert_word(elem)) {
                    wordcount[word]++;
                    word_loc[word].insert(line.first);
                }
            }
        } );

    }
    display(wordcount);
    display(word_loc);
    return 0;
}