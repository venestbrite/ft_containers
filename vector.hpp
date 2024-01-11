#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include "ft_pair.hpp"
#include "iterator.hpp"

namespace ft
{
	template<class InputIterator>
	int	distance(InputIterator first, InputIterator last)
	{
		int count = 0;
		while (first != last)
		{
			count++;
			first++;
		}
		return (count);
	};

	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
	{
	while (first1!=last1)
	{
		if (first2==last2 || *first2<*first1) return false;
		else if (*first1<*first2) return true;
		++first1; ++first2;
	}
	return (first2!=last2);
	}
}

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef T*													pointer_type;
			typedef T&													reference_type;
			typedef typename allocator_type::reference       			reference;
			typedef typename allocator_type::const_reference 			const_reference;
			typedef typename allocator_type::size_type					size_type;
			typedef typename allocator_type::difference_type			difference_type;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::move_iterator<pointer>							iterator;
			typedef ft::move_iterator<const_pointer >					const_iterator;
			typedef ft::reverse_iterator<iterator >						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator >				const_reverse_iterator;
		private:
			bool			_is_initialized;
			size_type		_vector_size;
			size_type		_vector_capacity;
			allocator_type	_allocator;
		public:
			T*				_values;
			vector()
			{ 
				this->_values = nullptr;
				this->_vector_size = 0;
				this->_vector_capacity = 0;
				this->_is_initialized = false; 
			};

			~vector()
			{
				this->_allocator.deallocate(this->_values, this->_vector_capacity);
			}

			vector(size_type n)
			{
				this->_is_initialized = true;
				this->_vector_size = n;
				this->_vector_capacity = n;
				this->_values = this->_allocator.allocate(this->_vector_capacity);
			};

			vector(size_type n, const value_type& value, const allocator_type& = allocator_type())
			{
				this->_is_initialized = true;
				this->_vector_size = n;
				this->_vector_capacity = n;
				this->_values = this->_allocator.allocate(this->_vector_capacity);
				size_type i = 0;
				while(i < n)
				{
					this->_allocator.construct(this->_values + i, value);
					i++;
				}
			};

			template <class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type(), 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				this->_vector_size = 0;
				this->_vector_capacity = 0;
				this->_values = nullptr;
				while (first != last)
				{
					this->push_back(*first);
					first++;
				}
			};

			vector(const vector& x)
			{
				this->_values = this->_allocator.allocate(x.capacity());
				this->_vector_size = x.size();
				this->_vector_capacity = x.capacity();
				size_t i = 0;
				while (i < x.size())
				{
					this->_allocator.construct(this->_values + i, x._values[i]);
					i++;
				}
			};

			vector& operator=(const vector& x)
			{
				this->_values = x._values;
				this->_vector_size = x.size();
				this->_vector_capacity = x.capacity();
				this->_values = this->_allocator.allocate(x.capacity());
				this->assign(x.begin(), x.end());
				return (*this);		
			};

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				vector temp(first, last);
				this->swap(temp);
			};

			void assign(size_type n, const value_type& u)
			{
				if (this->_vector_capacity < n)
				{
					vector temp(n, u);
					this->swap(temp);
				}
				else
				{
					this->erase();
					for (size_type i = 0; i < u; i++)
					{
						this->push_back(u);
					}
				}
			};

			allocator_type			get_allocator() const { return this->_allocator;};
			size_type				max_size() const { return allocator_type().max_size(); }
			iterator				begin() { return iterator(this->_values);};
			const_iterator			begin()   const { return const_iterator(this->_values);};
			iterator				end() { return iterator(this->_values + this->_vector_size);};
			const_iterator			end()     const { return const_iterator(this->_values + this->_vector_size);};
			reverse_iterator		rbegin() { return reverse_iterator(end());};
			const_reverse_iterator	rbegin()  const { return const_reverse_iterator(end());};
			reverse_iterator		rend() { return reverse_iterator(begin());};
			const_reverse_iterator	rend()    const { return const_reverse_iterator(begin());};
			size_type				size() const { return static_cast<size_type> (this->_vector_size); };
			size_type				capacity() const { return static_cast<size_type> (this->_vector_capacity); };
			bool					empty() const { return begin() == end(); };

			void reserve(size_type n)
			{
				if (n > this->_vector_capacity)
				{
					T* temp = this->_allocator.allocate(n);
					size_type i = 0;
					while(i < this->_vector_size)
					{
						this->_allocator.construct(temp + i, this->_values[i]);
						i++;
					}
					this->_allocator.deallocate(this->_values, this->_vector_capacity);
					this->_vector_capacity = n;
					this->_values = temp;
				}
			};

			reference       operator[](size_type n)
			{
				if (n > this->_vector_size)
					throw std::out_of_range("vector");
				return this->_values[n];
			};

			const_reference operator[](size_type n) const
			{
				if (n > this->_vector_size)
					throw std::out_of_range("vector");
				return this->_values[n];
			};

			reference       at(size_type n)
			{ 
				if (n > this->_vector_size)
					throw std::out_of_range("vector");
				return this->_values[n];
			};
			
			const_reference at(size_type n) const
			{
				if (n > this->_vector_size)
					throw std::out_of_range("vector");
				return this->_values[n];
			};

			reference       front()
			{
				if (this->_vector_size == 0)
					throw std::out_of_range("vector");
				return this->_values[0];
			};

			const_reference front() const
			{
				if (this->_vector_size == 0)
					throw std::out_of_range("vector");
				return this->_values[0];
			};

			reference       back()
			{
				if (this->_vector_size == 0)
					throw std::out_of_range("vector");
				return this->_values[this->_vector_size - 1];	
			};

			const_reference back() const
			{
				if (this->_vector_size == 0)
					throw std::out_of_range("vector");
				return this->_values[this->_vector_size - 1];	
			};

			void push_back(const value_type& x)
			{
				size_type i = 0;
				if (this->_vector_capacity == 0)
				{
					this->reserve(1);
					this->_vector_size++;
					this->_allocator.construct(this->_values, x);
					return ;
				}

				if (this->_vector_size == this->_vector_capacity)
				{
					if (this->_vector_capacity == 0)
						this->_vector_capacity = 1;
					T* temp = this->_allocator.allocate(2 * this->_vector_capacity);
					this->_vector_capacity *= 2;
					while(i < this->_vector_size)
					{
						this->_allocator.construct(temp + i, this->_values[i]);
						i++;
					}
					this->_allocator.deallocate(this->_values, this->_vector_size);
					this->_values = temp;
				}
				this->_allocator.construct(this->_values + this->_vector_size, x);
				this->_vector_size++;
			};

			void pop_back() { this->_vector_size -= 1; };

			iterator insert (iterator position, const value_type& val)
			{
				size_type pos = 0;
				for (iterator it = begin(); it != position; ++it)
					pos++;
				if (this->_vector_size + 1 > this->_vector_capacity)
					reserve((this->_vector_size  + 1)*2);
				this->_vector_size ++;
				size_t iter = this->_vector_size ;
				while (iter != pos && (iter - 1) != pos)
				{
					this->_values[iter - 1] = this->_values[iter - 2];
					iter--;
				}
				this->_values[pos] = val;
				return (position);
			}
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type pos = 0;
				for (iterator it = begin(); it != position; ++it)
					pos++;
				if (this->_vector_size + n > this->_vector_capacity)
					reserve((this->_vector_size + n) *2);
				this->_vector_size += n;
				size_type index = this->_vector_size;
				while (index > pos && (index - n) > pos)
				{
					this->_values[index - 1] = this->_values[index - n - 1];
					index--;
				}
				size_type j = 0;
				while (j < n)
				{
					this->_values[pos] = val;
					pos++;
					j++;
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				size_type distance = 0;
				for (InputIterator i = first; i != last; ++i)
					distance++;
				size_type pos = 0;
				for (iterator it = begin(); it != position; ++it)
					pos++;
				if (this->_vector_size + distance > this->_vector_capacity)
					reserve((this->_vector_size + distance)*2);
				this->_vector_size += distance;
				size_type index = this->_vector_size;
				while (index > pos && (index - distance) > pos)
				{
					this->_values[index - 1] = this->_values[index - distance - 1];
					index--;
				}
				for(; first != last; first++, pos++)
					this->_values[pos] = *first;
			}

			iterator erase(iterator position)
			{
				iterator start = this->begin();
				iterator end = this->end();
				size_type pos = 0;
				
				while (start != position)
				{
					start++;
					pos++;
				}
				iterator to_ret = start++;
				while (position != end)
				{
					this->_values[pos] = this->_values[pos + 1];
					position++;
					pos++;
				}
				this->pop_back();
				return (to_ret);
			};

			iterator erase(iterator first, iterator last)
			{
				size_type pos = first - begin();
				size_type n = last - first;
				_vector_size -= n;
				for (size_type i = pos; i < _vector_size; i++)
					_allocator.construct(&_values[i], _values[i + n]);
				return iterator(begin() + pos);
			};

			void clear() { this->_vector_size = 0; };

			void resize(size_type sz)
			{
				if (sz > this->_vector_capacity)
				{
					this->_is_initialized = true;
					
					T* temp = this->_allocator.allocate(sz);
					size_type i = 0;
					while(i < this->_vector_size)
					{
						this->_allocator.construct(temp + i, this->_values[i]);
						i++;
					}
					while (i < sz)
					{
						temp[i] = T();
						i++;
					}
					this->_allocator.deallocate(this->_values, this->_vector_capacity);
					this->_vector_size = sz;
					this->_vector_capacity = sz;
					this->_values = temp;
				}
				else if (sz < this->_vector_capacity)
				{
					T* temp = this->_allocator.allocate(sz);
					size_type i = 0;
					while(i < sz)
					{
						this->_allocator.construct(temp + i, this->_values[i]);
						i++;
					}
					this->_allocator.deallocate(this->_values, this->_vector_capacity);
					this->_vector_capacity = sz;
					this->_values = temp;
					this->_vector_size = sz;
				}
			};

			void resize(size_type n, const value_type& c)
			{
				if (n > this->_vector_capacity)
				{
					this->_is_initialized = true;
					
					T* temp = this->_allocator.allocate(n);
					size_t i = 0;
					while(i < this->_vector_size)
					{
						this->_allocator.construct(temp + i, this->_values[i]);
						i++;
					}
					this->_allocator.deallocate(this->_values, this->_vector_capacity);
					this->_vector_capacity = n;
					this->_values = temp;
				}
				else if (n < this->_vector_capacity)
				{
					T* temp = this->_allocator.allocate(n);
					size_t i = 0;
					while(i < n)
					{
						this->_allocator.construct(temp + i, this->_values[i]);
						i++;
					}
					this->_allocator.deallocate(this->_values, this->_vector_capacity);
					this->_vector_capacity = n;
					this->_values = temp;
				}
				if(n > this->_vector_size)
				{
					size_t i = this->_vector_size;
					while (i < n)
					{
						this->_allocator.construct(this->_values + i, c);
						i++;
					}
				}
				this->_vector_size = n;
			};

			void swap (vector& x)
			{
				std::swap(this->_values, x._values);
				std::swap(this->_vector_size, x._vector_size);
				std::swap(this->_vector_capacity, x._vector_capacity);
			}
	};

	template<class T>
	bool operator== (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	};

	template<typename T>
	bool operator!= (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return true;
		}
		return false;
	};

	template<typename T>
	bool operator< (const vector<T>& lhs, const vector<T>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template<typename T>
	bool operator> (const vector<T>& lhs, const vector<T>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	};

	template<typename T>
	bool operator<= (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (lhs < rhs)
			return true;
		if (lhs == rhs)
			return true;
		return false;
	};

	template<typename T>
	bool operator>= (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (lhs > rhs)
			return true;
		if (lhs == rhs)
			return true;
		return false;
	};
}




#endif