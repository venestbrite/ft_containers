#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>


#include "tree_with_iterators.hpp"

namespace ft
{

	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef BinaryTree<ft::pair<key_type, mapped_type >, Compare >	tree_type;
			typedef typename allocator_type::reference       				reference;
			typedef typename allocator_type::const_reference 				const_reference;
			typedef typename allocator_type::pointer         				pointer;
			typedef typename allocator_type::const_pointer   				const_pointer;
			typedef typename allocator_type::size_type       				size_type;
			typedef typename allocator_type::difference_type 				difference_type;
			typedef typename tree_type::iterator							iterator;
			typedef typename tree_type::const_iterator						const_iterator;
			typedef ft::reverse_iterator<iterator >							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator >					const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, allocator_type>;
			protected:
				key_compare comp;
				value_compare(key_compare c) : comp(c) {};
			public:
				bool operator() (const value_type& x, const value_type& y) const
				{ return (comp(x.first, y.first)); };
		};

		private:
			BinaryTree<ft::pair<Key, T>, Compare >	__tree_;
			Compare							__comp_function;
			allocator_type					__map_allocator;

		public:
			map() : __tree_() {};
			explicit map(const key_compare& comp) : __tree_(value_compare(comp)) {};

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare()) : __comp_function(comp)
			{
				this->insert(first, last);
			};

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp, const allocator_type& a) : __map_allocator(a), __comp_function(comp)
			{
				while (first != last)
				{
					this->__tree_.insert_from_root(*first);
					first++;
				}
			};

			map(const map& m)
			{
				if (&m == this)
					return ;
				clear();
				insert(m.begin(), m.end());
			};

			explicit map(const allocator_type& a);
			map(const map& m, const allocator_type& a) : __map_allocator(a)
			{
				insert(m.begin(), m.end());
			};

			~map() {};

			map& operator=(const map& m)
			{
				if (&m == this)
					return (*this);
				clear();
				insert(m.begin(), m.end());
				return (*this);
			};

			iterator begin() { return iterator (__tree_.begin());};
			const_iterator begin() const { return const_iterator(__tree_.begin()); };
			iterator end() {return iterator (__tree_.end());};
			const_iterator end()   const { return const_iterator(__tree_.end()); };
			reverse_iterator rbegin() { return reverse_iterator (this->end()); }
			const_reverse_iterator rbegin() const { return reverse_iterator (this->end());};
			reverse_iterator rend() {return reverse_iterator (this->begin()); };
			const_reverse_iterator rend()   const {return reverse_iterator (this->begin());};

			bool empty() const
			{
				if (__tree_.size()) 
					return false;
				return true;
			};

			size_type size()     const { return this->__tree_.size(); };
			size_type max_size() const { return __tree_.max_size(); };

			mapped_type& operator[](const key_type& k)
			{
				if (find(k) != end())
				{
					return (find(k)->second);
				}
				insert(ft::make_pair(k, mapped_type()));
				return find(k)->second;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last,
			typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				while (first != last)
				{
					this->insert(*first);
					first++;
				}
			};

			ft::pair<iterator,bool> insert(const value_type& other)
			{
				if (find(other.first) != end())
				{
					return (ft::make_pair(iterator(find(other.first)), false));
				}

				this->__tree_.insert_from_root(other);
				return (ft::make_pair(find(other.first), true));
			};

			void print_inorder() { this->__tree_.print_inorder(); }

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				if (find(val.first) != end())
					return (find(val.first));
				__tree_.insert_from_root(val);
				return(find(val.first)); 
			}

			void  erase(iterator position) { __tree_.erase_from_tree(*position); };
			size_type erase(const key_type& k) { return (__tree_.erase_from_tree(ft::make_pair(k, mapped_type()))); };

			void  erase(iterator first, iterator last)
			{
				if (first == begin() && last == end())
					return this->clear();
				bool is_last = false;
				if (last == end())
				{
					is_last = true;
					last--;
				}
				while (first != last)
				{
					this->erase(first);
					first++;
				}
				if (is_last)
					this->erase(--end());
			};
			
			void clear()
			{
				tree_type new_tree;
				this->__tree_.swap(new_tree);
			};

			allocator_type get_allocator() const { return __map_allocator; };
			key_compare    key_comp()      const { return (key_compare()); };
			value_compare  value_comp()    const { return (value_compare(key_compare())); };

			iterator find(const key_type& k)
			{
				iterator it = this->begin();
				while (it != this->end())
				{
					if (it->first == k)
						break ;
					it++;
				}
				return (it);
			}

			const_iterator find(const key_type& k) const
			{
				const_iterator it = this->begin();
				while (it != this->end())
				{
					if (it->first == k)
						break ;
					it++;
				}
				return (it);
			}

			size_type      count(const key_type& k) const
			{
				return (__tree_.count_unique(ft::make_pair(k, T())));
			}

			iterator lower_bound(const key_type& k)
			{
				for (iterator i = begin(); i != end(); i++)
				{
					if (!__comp_function(i->first, k))
						return (i);
				}
				return (end());
			};
			
			const_iterator lower_bound(const key_type& k) const
			{	
				for (const_iterator i = begin(); i != end(); i++)
				{
					if (!__comp_function(i->first, k))
						return (i);
				}
				return (end());
			};

			iterator upper_bound(const key_type& k)
			{
				for (iterator i = begin(); i != end(); i++)
				{
					if (__comp_function(k, i->first))
						return (i);
				}
				return (end());
			};

			const_iterator upper_bound(const key_type& k) const
			{
				for (const_iterator i = begin(); i != end(); i++)
				{
					if (__comp_function(k, i->first))
						return (i);
				}
				return (end());
			};

			ft::pair<iterator,iterator>             equal_range(const key_type& k)
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); };

			ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); };

			void 	swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y);
			void	swap(map &other) { __tree_.swap(other.__tree_);}
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return x.size() == y.size();
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return !(x == y);
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)		   
	{
		return y < x;
	};

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return !(y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	void
	swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
	{
		((x.swap(y)));
	};
}


#endif