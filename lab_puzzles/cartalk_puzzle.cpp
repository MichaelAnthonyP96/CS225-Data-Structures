/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    /* Your code goes here! */
    //"opens" the file
    ifstream words(word_list_fname);
    string word;
    vector<string> eligibleWords;
    if(words.is_open()){
    	//reads a WORD from words to word as shown in the documentation
    	while(getline(words,word)){
    		//we are only concerned with the words of length 5
    		if(word.length() == 5){
    			//pushes the 5 lettered word into eligibleWords vector
    			eligibleWords.push_back(word);
    		}
    	}
    }
    //now that we have the eligible 5 letter words, must see if removing the first
    //letter AND removing the second letter produce the correct homophones
    for(auto & eligibleWord : eligibleWords){
    	//removes the first letter of the eligible word using substring starting at
    	//the second letter until the length of the word minus 1
    	string removeFirstLetter = eligibleWord.substr(1,eligibleWord.length()-1);
    	string removeSecondLetter = "";
    	//Using substring to extract only the first character
    	removeSecondLetter = eligibleWord.substr(0,1);
    	//appends the rest of the eligible word
    	removeSecondLetter.append(eligibleWord.begin()+2, eligibleWord.end());
    	//if all three are homophones, then construct and tuple of those three words
    	if(d.homophones(eligibleWord,removeFirstLetter) && d.homophones(eligibleWord,removeSecondLetter) 
    		&& d.homophones(removeSecondLetter,removeFirstLetter)){
    		std::tuple<string, string, string> carTalk(eligibleWord,removeFirstLetter,removeSecondLetter);
    		//add the tuple of the homophones to the returned vector of tuples
    		ret.push_back(carTalk);
    	}
    }
    return ret;
}
