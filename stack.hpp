#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"


namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
	public:
			typedef Container                                container_type;
			typedef typename container_type::value_type      value_type;
			typedef typename container_type::reference       reference;
			typedef typename container_type::const_reference const_reference;
			typedef typename container_type::size_type       size_type;

	protected:
			container_type c;

	public:
		stack() : c() {}
		explicit stack(const container_type& __c) : c(__c) {};
		~stack() {}; 
		stack(const stack& __q) : c(__q.c) {}
		stack& operator=(const stack& __q) { c = __q.c; return *this; };
		bool empty() const { return c.empty(); };
		size_type size() const { return c.size(); };
		reference top() { return c.back(); };
		const_reference top() const { return c.back(); };
		void push(const value_type& x) { c.push_back(x); };
		void pop() { c.pop_back(); };

		template <class T1, class _C1>
		friend bool operator==(const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);

		template <class T1, class _C1>
		friend bool operator< (const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
};

template <class T, class Container>
bool operator==(const stack<T, Container>& __x, const stack<T, Container>& __y)
{
	return __x.c == __y.c;
};

template <class T, class Container>
bool operator< (const stack<T, Container>& __x, const stack<T, Container>& __y)
{
return __x.c < __y.c; 
};

template <class T, class Container>
bool operator!=(const stack<T, Container>& __x, const stack<T, Container>& __y)
{
	return !(__x == __y);
};

template <class T, class Container>
bool operator> (const stack<T, Container>& __x, const stack<T, Container>& __y)
{
	return __y < __x;
};

template <class T, class Container>
bool operator>=(const stack<T, Container>& __x, const stack<T, Container>& __y)
{
	return !(__x < __y);
};

template <class T, class Container>
bool operator<=(const stack<T, Container>& __x, const stack<T, Container>& __y)
{
	return !(__y < __x);
};
}

#endif