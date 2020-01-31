/**
 * @file quackfun.h
 * Contains the QuackFun namespace definition.
 */

#ifndef STACKFUN_H
#define STACKFUN_H

#include "stack.cpp"
#include "queue.cpp"

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace QuackFun
{
    using std::ourStack;
    using std::ourQueue;

    template <typename T>
    T sum(ourStack<T>& s);

    bool isBalanced(ourQueue<char> input);

    template <typename T>
    void scramble(ourQueue<T>& q);

    template <typename T>
    bool verifySame(ourStack<T>& s, ourQueue<T>& q);
};

#include "quackfun.cpp"
#endif
