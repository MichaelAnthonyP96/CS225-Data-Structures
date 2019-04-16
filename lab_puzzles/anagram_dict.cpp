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
	ifstream File(filename);
	string word;
	vector<string> words;
	//reads all the words from the file into the words vector
	if(File.is_open()){
		while(getline(File,word)){
			//push the word to the words vector
			words.push_back(word);
		}
	}
	//iterate over all the words in the words vector
	for(auto & currWord : words){
		//find the place in the dictionary of the current word
		auto value = dict.find(currWord);
		//means that the word was not found already in the dictionary,
		//so we must add it in
		if(value == dict.end()){
			vector<char> charVector;
			//converts the std::string in a vector of char's
			for(size_t i = 0; i < currWord.length(); ++i){
				charVector.push_back(currWord.at(i));
			}
			//sort the charVector for anagram purposes
			std::sort(charVector.begin(), charVector.end());
			//insert the word and its sorted vector of characters into the dictionary
			dict.insert (std::pair<std::string, std::vector<char>> (currWord,charVector));
		}
		//if key == dict.end() then the word is already in the dictionary :
		//do nothing in that case
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    //iterate over all the words in the words vector
    for(auto & currWord : words){
		//find the place in the dictionary of the current word
		auto value = dict.find(currWord);
		//means that the word was not found already in the dictionary,
		//so we must add it in
		if(value == dict.end()){
			vector<char> charVector;
			//converts the std::string in a vector of char's
			for(size_t i = 0; i < currWord.length(); ++i){
				charVector.push_back(currWord.at(i));
			}
			//sort the charVector for anagram purposes
			std::sort(charVector.begin(), charVector.end());
			//insert the word and its sorted vector of characters into the dictionary
			dict.insert (std::pair<std::string, std::vector<char>> (currWord,charVector));
		}
		//if key == dict.end() then the word is already in the dictionary :
		//do nothing in that case
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
    //uses the anagram helper function to build a vector of anagram words
    vector<string> ret;
    ret = getAnagrams(word);
    //if the anagram vector is of size one, then we return empty vector
    //size one corresponds to just the original word
    if(ret.size() == 1) return vector<string>();
    else return ret; 
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
	vector<vector<string>> ret;
	//iterate over all words in the dictionary
	for(auto & entry : dict){
		//get the anagrams for the current word
		vector<string> anagrams = getAnagrams(entry.first);
		//if the vector contains other words other than itself, 
		//add that vector of anagrams to the ret
		if(anagrams.size() > 1) ret.push_back(anagrams);
	}
    return ret;
}

//anagram helper
vector< string > AnagramDict::getAnagrams(const string& word) const
{
	vector<string> ret;
	auto value = dict.find(word);
	//if the word is in the dictionary
	if(value != dict.end()){
		//iterate over all the entries in the dictionary
		for(auto & entry : dict){
			//if the ordered vector of chars matches the ordered vector
			//of chars for the word we are concerned with, push the word
			//into the return vector
			if(entry.second == value->second) ret.push_back(entry.first);
		}
	}
	return ret;
}
