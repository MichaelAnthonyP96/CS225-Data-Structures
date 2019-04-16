#include "list.h"
#include <iostream>
using namespace std;

int main() {

  List<int> hedge;
  hedge.insertFront(1);
  hedge.insertFront(2);
  hedge.insertFront(3);
  hedge.insertFront(4);
  hedge.insertBack(5);

  //testing that my overloaded operators work
  //List<int>::RevIterator h = hedge.rbegin();
  //List<int>::iterator g = hedge.begin();

  // cout << *(++g) <<endl;
  // g--;
  // cout << *g << endl;
  // cout << hedge <<endl;
  // cout << *h << endl;
  // h++;
  // cout << *h << endl;

  cout << hedge << endl;
  hedge.reverseNth(2);
  cout << hedge << endl;

  return 0;
}
