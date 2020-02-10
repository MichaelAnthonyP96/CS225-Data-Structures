/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string &infile) : filename(infile) {
  /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const {
  TextFile infile(filename);
  vector<pair<string, int>> ret;
  Dict<string, int> hashTable(256);
  while (infile.good()) {
    string word = infile.getNextWord();

    hashTable[word]++;
  }
  // we iterate over the hash tables using iterators: it->first will give
  // us the key, it->second will give us the value. it++ moves to the
  // next (key, value) pair in the HashTable.
  typename Dict<string, int>::iterator it;
  for (it = hashTable.begin(); it != hashTable.end(); it++) {
    if (it->second >= threshold)
      ret.push_back(*it);
  }

  return ret;
}
