#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "queue.cpp"
#include "stack.cpp"
#include <sstream>
#include <string>

#include "exercises.h"
#include "quackfun.h"

using namespace std;
using namespace RecursionExercises;
using namespace QuackFun;

ourQueue<char> stringToQueue(std::string s) {
  ourQueue<char> q;

  for (char c : s)
    q.push(c);

  return q;
}

TEST_CASE("sumDigits") {
  SECTION("Base cases work") {
    REQUIRE(sumDigits(1) == 1);
    REQUIRE(sumDigits(0) == 0);
  }
  SECTION("Multiple digits sum correctly") {
    REQUIRE(sumDigits(243) == 9);
    REQUIRE(sumDigits(49) == 13);
  }
}

TEST_CASE("triangle") {
  SECTION("Base cases work") { REQUIRE(triangle(0) == 0); }
  SECTION("Recursive cases work") {
    REQUIRE(triangle(3) == 6);
    REQUIRE(triangle(6) == 21);
    REQUIRE(triangle(8) == 36);
  }
}

TEST_CASE("sum") {
  ourStack<int> s;
  for (int i = 0; i <= 16; i++)
    s.push(i);
  ourStack<int> s2 = s;
  SECTION("Sum is correct") { REQUIRE(QuackFun::sum(s) == 136); }
  SECTION("Stack is unchanged") { REQUIRE(s == s2); }

  ourStack<double> s3;
  for (int i = 0; i <= 10; i++)
    s3.push(2.1 + 4.5 * i);
  ourStack<double> s4 = s3;

  ourStack<double>::_ctor_count = 0;
  double sumFloat = QuackFun::sum<double>(s3);

  SECTION("Float sum is correct") {
    if (sumFloat > 270.61 || sumFloat < 270.59)
      FAIL("Expected sum = 270.6; Actual = " + to_string(sumFloat));
  }
  SECTION("Stack is unchanged") { REQUIRE(s3 == s4); }
  SECTION("Did not make any additional stack objects") {
    REQUIRE(ourStack<double>::_ctor_count == 0);
  }
}

TEST_CASE("isBalanced") {

  SECTION("balanced") {
    std::vector<std::string> strings = {"",        "[]",        "cs225[]522sc",
                                        "[cs225]", ")[[[][]]]", "[)[([ )][]]]"};

    for (std::string &s : strings) {
      INFO(s)
      REQUIRE(QuackFun::isBalanced(stringToQueue(s)));
    }
  }

  SECTION("unbalanced") {

    std::vector<std::string> strings = {
        "[", "[[]", "][][]", "[[()][][", "[]][[]", "[[[[[]]c]s]2]2]5"};

    for (std::string &s : strings) {
      INFO(s)
      REQUIRE(!QuackFun::isBalanced(stringToQueue(s)));
    }
  }

  SECTION("Only used 1 stack") {
    ourQueue<char> q = stringToQueue("notempty");

    ourStack<char>::_ctor_count = 0;
    ourQueue<char>::_ctor_count = 0;

    isBalanced(q);

    REQUIRE(ourStack<char>::_ctor_count == 1);
    REQUIRE(ourQueue<char>::_ctor_count == 1);
  }
}

TEST_CASE("scramble 17") {
  ourQueue<int> q;
  for (int i = 1; i <= 17; i++)
    q.push(i);

  QuackFun::scramble<int>(q);

  stringstream scrambled_output;
  while (!q.empty()) {
    scrambled_output << q.front() << ' ';
    q.pop();
  }
  string scrambled = scrambled_output.str();
  string expected = "1 3 2 4 5 6 10 9 8 7 11 12 13 14 15 17 16 ";

  stringstream str;

  str << "Scrambled queue: " << scrambled << endl;
  str << "Expected:        " << expected << endl;

  INFO(str.str())

  if (scrambled != expected)
    FAIL("See output above");
}

TEST_CASE("scramble 9") {
  ourQueue<int> q;
  for (int i = 4; i <= 12; i++)
    q.push(i);

  QuackFun::scramble<int>(q);

  stringstream scrambled_output;
  while (!q.empty()) {
    scrambled_output << q.front() << ' ';
    q.pop();
  }
  string scrambled = scrambled_output.str();
  string expected = "4 6 5 7 8 9 12 11 10 ";

  stringstream str;

  str << "Scrambled queue: " << scrambled << endl;
  str << "Expected:        " << expected << endl;

  INFO(str.str())

  if (scrambled != expected)
    FAIL("See output above");
}

TEST_CASE("verifySame results") {
  // Test different
  {
    ourStack<int> s;
    ourQueue<int> q;
    for (int i = 2; i < 7; i++) {
      s.push(i);
      q.push(i);
    }
    s.push(4);
    q.push(6);
    for (int i = 7; i < 10; i++) {
      s.push(i);
      q.push(i);
    }
    ourStack<int> sb = s;
    ourQueue<int> qb = q;

    SECTION("Result for different stack and queue is false") {
      bool result = verifySame(s, q);
      REQUIRE(!result);
    }
    SECTION("Data structures are unmodified") {
      if (s != sb)
        FAIL("Stack was modified");
      else if (q != qb)
        FAIL("Queue was modified");
    }
  }

  // Test the same
  {
    ourStack<int> s;
    ourQueue<int> q;
    for (int i = 2; i < 7; i++) {
      s.push(i);
      q.push(i);
    }
    ourStack<int> sb = s;
    ourQueue<int> qb = q;

    SECTION("Result for same stack and queue is true") {
      bool result = verifySame(s, q);
      REQUIRE(result);
    }
    SECTION("Data structures are unmodified") {
      if (s != sb)
        FAIL("Stack was modified");
      else if (q != qb)
        FAIL("Queue was modified");
    }
  }
}

TEST_CASE("verifySame structures unmodified (EXTRA CREDIT)") {
  // Test different
  {
    ourStack<int> s;
    ourQueue<int> q;
    for (int i = 2; i < 7; i++) {
      s.push(i);
      q.push(i);
    }
    s.push(4);
    q.push(6);
    for (int i = 7; i < 10; i++) {
      s.push(i);
      q.push(i);
    }
    ourStack<int> sb = s;
    ourQueue<int> qb = q;

    ourStack<int>::_ctor_count = 0;
    ourQueue<int>::_ctor_count = 0;
    SECTION("Result for different stack and queue is different") {
      bool result = verifySame(s, q);
      REQUIRE(!result);
    }
    SECTION("Data structures are unmodified") {
      if (s != sb)
        FAIL("Stack was modified");
      else if (q != qb)
        FAIL("Queue was modified");
    }
    SECTION("No new stacks or queues are made") {
      if (ourStack<int>::_ctor_count != 0)
        FAIL("You may not make a second stack object");
      if (ourQueue<int>::_ctor_count != 0)
        FAIL("You may not make a second queue object");
    }
  }

  // Test the same
  {
    ourStack<int> s;
    ourQueue<int> q;
    for (int i = 2; i < 7; i++) {
      s.push(i);
      q.push(i);
    }
    ourStack<int> sb = s;
    ourQueue<int> qb = q;

    ourStack<int>::_ctor_count = 0;
    ourQueue<int>::_ctor_count = 0;
    SECTION("Result for same stack and queue is the same") {
      bool result = verifySame(s, q);
      REQUIRE(result);
    }
    SECTION("Data structures are unmodified") {
      if (s != sb)
        FAIL("Stack was modified");
      else if (q != qb)
        FAIL("Queue was modified");
    }
    SECTION("No new stacks or queues are made") {
      if (ourStack<int>::_ctor_count != 0)
        FAIL("You may not make a second stack object");
      if (ourQueue<int>::_ctor_count != 0)
        FAIL("You may not make a second queue object");
    }
  }
}
