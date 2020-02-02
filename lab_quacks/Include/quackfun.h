/**
 * @file quackfun.h
 * Contains the QuackFun namespace definition.
 */

#ifndef STACKFUN_H
#define STACKFUN_H

#include "queue.cpp"
#include "stack.cpp"

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace QuackFun {
using std::ourQueue;
using std::ourStack;

template <typename T> T sum(ourStack<T> &s);

bool isBalanced(ourQueue<char> input);

template <typename T> void scramble(ourQueue<T> &q);

template <typename T> bool verifySame(ourStack<T> &s, ourQueue<T> &q);
}; // namespace QuackFun

#include "quackfun.cpp"
#endif
