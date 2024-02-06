/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    string word, temp;
    ifstream wordsFile(filename);
    if(wordsFile.is_open()){
        while(getline(wordsFile, word)){
            temp = word;
            std::sort(temp.begin(), temp.end());
            dict[temp].push_back(word);
        }
    }
    wordsFile.close();
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    string temp;
    for(string word : words){
        temp = word;
        std::sort(temp.begin(), temp.end());
        dict[temp].push_back(word);
    }
}



/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string temp = word;
    std::sort(temp.begin(), temp.end());
    if(dict.find(temp) != dict.end()){
        return dict.at(temp);
    }
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all_anagrams;
    std::map<string, vector<string>>::const_iterator it = dict.begin();
    while(it != dict.end()){
        if(it->second.size() > 1){
            all_anagrams.push_back(it->second);
        }
        it++;
    }
    return all_anagrams;

}