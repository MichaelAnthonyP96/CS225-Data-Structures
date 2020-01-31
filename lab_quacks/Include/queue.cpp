#ifndef QUEUE_H
#define QUEUE_H

// #define queue libcpp_queue
#include <queue> // use a partial full path so we don't recursively include this file

// #undef queue
namespace std {
    template <class T, class Container = deque<T> >
    class ourQueue : public queue<T, Container> {
        public:
            static size_t _ctor_count;

            // these are pretty much copied from libc++'s stack header file
            ourQueue() : queue<T, Container>() { _ctor_count ++; };
            ourQueue(const ourQueue& q) : queue<T, Container>(q) { _ctor_count ++; };
            ourQueue(ourQueue&& q) : queue<T, Container>(q) { _ctor_count ++; };

            explicit ourQueue(const Container& c) : queue<T, Container>(c) { _ctor_count ++; };
            explicit ourQueue(Container&& c) : queue<T, Container>(c) { _ctor_count ++; };

            template <class Alloc> explicit ourQueue(const Alloc& a) : queue<T, Container>(a) { _ctor_count ++; };
            template <class Alloc> ourQueue(const Container& c, const Alloc& a) : queue<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> ourQueue(Container&& c, const Alloc& a) : queue<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> ourQueue(const ourQueue& c, const Alloc& a) : queue<T, Container>(c, a) { _ctor_count ++; };
            template <class Alloc> ourQueue(ourQueue&& c, const Alloc& a) : queue<T, Container>(c, a) { _ctor_count ++; };

            ourQueue& operator=(const ourQueue& other) = default;
    };

    template <class T, class Container>
    size_t ourQueue<T, Container>::_ctor_count = 0;
}

#endif

/* vim: set ft=cpp: */
