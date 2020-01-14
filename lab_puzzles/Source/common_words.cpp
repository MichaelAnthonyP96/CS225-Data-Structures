/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for(size_t j = 0; j < words.size(); ++j){
            //find how many times the word appears in the file
            file_word_maps[i][words[j]]++;
        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    //iterates over all the file word maps
    for(auto & fileWordMap : file_word_maps){
        //iterates over all maps in the file
        for(auto & map : fileWordMap){
            //updates the count of the word occurence
            common[map.first]++;
        }
    }

}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    //iterate over the list of potential common words
    for(auto & commonWord : common){
        //if the number of files it occurs in is equal to the total number 
        //of files, the word is in all files 
        if(commonWord.second == file_word_maps.size()){
            //file counter for the current commonWord
            size_t numFiles = 0;
            //iterate over the list of file word maps
            for(auto & fileWordMap : file_word_maps){
                //search for the current commonWord
                auto map = fileWordMap.find(commonWord.first);
                //extract the number of times found
                size_t numTimesFound = map->second;
                //if it exceeds n, then we count this file and move on
                if(numTimesFound >= n){
                    numFiles++;
                }
            }
            //if the current word meets the minimum number of files, 
            //then place it in the return vector
            if(numFiles == file_word_maps.size()){
                out.push_back(commonWord.first);
            }
        }
    }
    //return the vector of commonWords that exceed n in the files
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
