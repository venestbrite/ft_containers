#ifndef ITERATOR_NEW_HPP
#define ITERATOR_NEW_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    struct input_iterator_tag  {};
    struct output_iterator_tag {};
    struct forward_iterator_tag       : public input_iterator_tag         {};
    struct bidirectional_iterator_tag : public forward_iterator_tag       {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n);

    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
        distance(InputIterator first, InputIterator last);

    template <class InputIterator>
    InputIterator next(InputIterator x,
    typename iterator_traits<InputIterator>::difference_type n = 1);

    template <class BidirectionalIterator>
    BidirectionalIterator prev(BidirectionalIterator x,
        typename iterator_traits<BidirectionalIterator>::difference_type n = 1);

    template <class Iterator>
    class reverse_iterator
        : public iterator<typename iterator_traits<Iterator>::iterator_category, typename iterator_traits<Iterator>::value_type,
            typename iterator_traits<Iterator>::difference_type, typename iterator_traits<Iterator>::pointer, typename iterator_traits<Iterator>::reference>
    {
        protected:
            Iterator current;
        public:
            typedef Iterator                                            iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::reference       reference;
            typedef typename iterator_traits<Iterator>::pointer         pointer;

            reverse_iterator() : current() {};
            explicit reverse_iterator(Iterator x) : current(x) { };
            template <class U>  reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) {};
            template <class U>  reverse_iterator& operator=(const reverse_iterator<U>& u) { current = u.base(); return *this; };
            Iterator base() const { return current; };
            reference operator*() const {Iterator __tmp = current; return *--__tmp;};
            pointer   operator->() const { return &(operator*()); };
            reverse_iterator& operator++() {--current; return *this; };
            reverse_iterator  operator++(int) { reverse_iterator __tmp(*this); --current; return __tmp; };
            reverse_iterator& operator--() {++current; return *this;};
            reverse_iterator  operator--(int) {reverse_iterator __tmp(*this); ++current; return __tmp;};
            reverse_iterator  operator+ (difference_type __n) const {return reverse_iterator(current - __n);};
            reverse_iterator& operator+=(difference_type __n) { current -= __n; return *this; };
            reverse_iterator  operator- (difference_type __n) const { return reverse_iterator(current + __n); };
            reverse_iterator& operator-=(difference_type __n) {current += __n; return *this; };
            reference         operator[](difference_type __n) const {return *(*this + __n); };
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1>& __x, const reverse_iterator<Iterator2>& __y)
    {
        return __x.base() == __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator<(const reverse_iterator<Iterator1>& __x, const reverse_iterator<Iterator2>& __y)
    {
        return __x.base() > __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1>& __x, const reverse_iterator<Iterator2>& __y)
    {
        return __x.base() != __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator>(const reverse_iterator<Iterator1>& __x, const reverse_iterator<Iterator2>& __y)
    {
        return __x.base() < __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator1>& __x, const reverse_iterator<Iterator2>& __y)
    {
        return __x.base() <= __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator1>& __x, const reverse_iterator<Iterator2>& __y)
    {
        return __x.base() >= __y.base();
    };


    template <class _Iter1, class _Iter2>
    typename reverse_iterator<_Iter1>::difference_type
    operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __y.base() - __x.base();
    };

    template <class _Iter>
    reverse_iterator<_Iter>
    operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)
    {
        return reverse_iterator<_Iter>(__x.base() - __n);
    };

    template <class Iterator>
    class move_iterator
    {
        public:
            typedef Iterator                                              iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type   difference_type;
            typedef Iterator                                              pointer;
            typedef typename iterator_traits<Iterator>::value_type        value_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::reference			reference;

            move_iterator() : current() {};
            explicit move_iterator(Iterator i) : current(i) {};
            template <class U>
            move_iterator(const move_iterator<U>& u) : current(u.base()) {};
            template <class U>
            move_iterator& operator=(const move_iterator<U>& u) { current = u.base(); return *this;};
            iterator_type base() const { return current; };
            reference operator*() const { return static_cast<reference>(*current); };
            pointer operator->() const {return current; };
            move_iterator& operator++() { ++current; return *this; };
            move_iterator operator++(int) { move_iterator __tmp(*this); ++current; return __tmp; };
            move_iterator& operator--() { --current; return *this; };
            move_iterator operator--(int) {move_iterator __tmp(*this); --current; return __tmp;};
            move_iterator operator+(difference_type __n) const { return move_iterator(current + __n); };
            move_iterator& operator+=(difference_type __n) { current += __n; return *this; };
            move_iterator operator-(difference_type __n) const { return move_iterator(current - __n); };
            move_iterator& operator-=(difference_type __n) { current -= __n; return *this; };
            reference operator[](difference_type __n) const { return static_cast<reference>(current[__n]); };
        private:
            Iterator current;
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const move_iterator<Iterator1>& __x, const move_iterator<Iterator2>& __y)
    {
        return __x.base() == __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator!=(const move_iterator<Iterator1>& __x, const move_iterator<Iterator2>& __y)
    {
            return __x.base() != __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator<(const move_iterator<Iterator1>& __x, const move_iterator<Iterator2>& __y)
    {
            return __x.base() < __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator<=(const move_iterator<Iterator1>& __x, const move_iterator<Iterator2>& __y)
    {
        return __x.base() <= __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator>(const move_iterator<Iterator1>& __x, const move_iterator<Iterator2>& __y)
    {
        return __x.base() > __y.base();
    };

    template <class Iterator1, class Iterator2>
    bool operator>=(const move_iterator<Iterator1>& __x, const move_iterator<Iterator2>& __y)
    {
            return __x.base() >= __y.base();
    };

    template <class _Iter1, class _Iter2>
    typename move_iterator<_Iter1>::difference_type
    operator-(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
    {
        return __x.base() - __y.base();
    }

    template <class _Iter>
    move_iterator<_Iter>
    operator+(typename move_iterator<_Iter>::difference_type __n, const move_iterator<_Iter>& __x)
    {
        return move_iterator<_Iter>(__x.base() + __n);
    }
}

#endif