#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

#include <iostream>

namespace ft
{
	template <class _Tp> struct remove_const            { typedef _Tp type; };
	template <class _Tp> struct remove_const<const _Tp> { typedef _Tp type; };
	template <class _Tp> struct remove_volatile               { typedef _Tp type; };
	template <class _Tp> struct remove_volatile<volatile _Tp> { typedef _Tp type; };
	template <class _Tp> struct remove_cv { typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type; };

	template <class _Tp, _Tp __v>
	struct integral_constant
	{
		static const _Tp      value = __v;
		typedef _Tp               value_type;
		typedef integral_constant type;
		 operator value_type() const {return value;}
	};

	#define _LIBCPP_BOOL_CONSTANT(__b) integral_constant<bool,(__b)>
	typedef _LIBCPP_BOOL_CONSTANT(true)  true_type;
	typedef _LIBCPP_BOOL_CONSTANT(false) false_type;

	template <bool, class _Tp = void> struct enable_if {};
	template <class _Tp> struct enable_if<true, _Tp> { typedef _Tp type; };
	template <class _Tp> struct __libcpp_is_integral                     : public false_type {};
	template <>          struct __libcpp_is_integral<bool>               : public true_type {};
	template <>          struct __libcpp_is_integral<char>               : public true_type {};
	template <>          struct __libcpp_is_integral<signed char>        : public true_type {};
	template <>          struct __libcpp_is_integral<unsigned char>      : public true_type {};
	template <>          struct __libcpp_is_integral<wchar_t>            : public true_type {};
	template <>          struct __libcpp_is_integral<short>              : public true_type {};
	template <>          struct __libcpp_is_integral<unsigned short>     : public true_type {};
	template <>          struct __libcpp_is_integral<int>                : public true_type {};
	template <>          struct __libcpp_is_integral<unsigned int>       : public true_type {};
	template <>          struct __libcpp_is_integral<long>               : public true_type {};
	template <>          struct __libcpp_is_integral<unsigned long>      : public true_type {};
	template <>          struct __libcpp_is_integral<long long>          : public true_type {};
	template <>          struct __libcpp_is_integral<unsigned long long> : public true_type {};
	template <class _Tp> struct is_integral : public __libcpp_is_integral<typename remove_cv<_Tp>::type> {};

	template <class T1, class T2>
	struct pair
	{
		public :
			typedef T1 first_type;
			typedef T2 second_type;
			first_type first;
			second_type second;
			pair() : first(), second() {}
			template<class U, class V>
				pair (const pair<U, V>& pr) : first(pr.first), second(pr.second) {}
			pair (const first_type& a, const second_type& b) : first(a), second(b) {}
			pair& operator= (const pair& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}
	};
	
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs < rhs); }
}

#endif