#ifndef STACK_H
#define STACK_H

#include <stack> // use a partial full path so we don't recursively include this file

namespace std {
template <class T, class Container = deque<T>>
class ourStack : public stack<T, Container> {
public:
  static size_t _ctor_count;

  // these are pretty much copied from libc++'s stack header file
  ourStack() : stack<T, Container>() { _ctor_count++; };
  ourStack(const ourStack &q) : stack<T, Container>(q) { _ctor_count++; };
  ourStack(ourStack &&q) : stack<T, Container>(q) { _ctor_count++; };

  explicit ourStack(const Container &c) : stack<T, Container>(c) {
    _ctor_count++;
  };
  explicit ourStack(Container &&c) : stack<T, Container>(c) { _ctor_count++; };

  template <class Alloc>
  explicit ourStack(const Alloc &a) : stack<T, Container>(a) {
    _ctor_count++;
  };
  template <class Alloc>
  ourStack(const Container &c, const Alloc &a) : stack<T, Container>(c, a) {
    _ctor_count++;
  };
  template <class Alloc>
  ourStack(Container &&c, const Alloc &a) : stack<T, Container>(c, a) {
    _ctor_count++;
  };
  template <class Alloc>
  ourStack(const ourStack &c, const Alloc &a) : stack<T, Container>(c, a) {
    _ctor_count++;
  };
  template <class Alloc>
  ourStack(ourStack &&c, const Alloc &a) : stack<T, Container>(c, a) {
    _ctor_count++;
  };

  ourStack &operator=(const ourStack &other) = default;
};

template <class T, class Container>
size_t ourStack<T, Container>::_ctor_count = 0;
} // namespace std

#endif
