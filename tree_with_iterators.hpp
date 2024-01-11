#ifndef TREE_ITERATORS_HPP
#define TREE_ITERATORS_HPP

#include <iostream>

#include "vector.hpp"

#include "ft_pair.hpp"

namespace ft
{
	template <class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 __x, T2 __y) { return (ft::pair<T1, T2>(__x, __y)); }

}

template <class T, class Node, class Compare>
class BinaryTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
	public:
		typedef Node* 					node_ptr;
		typedef std::allocator<Node>	node_allocator;
		node_allocator					__allocator;

		BinaryTreeIterator()
		{
			this->__current_ptr = nullptr;
			this->__root_ptr = nullptr;
			this->__is_last = false;
			this->__last_ptr = nullptr;
		}

		BinaryTreeIterator(node_ptr root, bool is_last)
		{
			this->__root_ptr = root;
			this->__last_ptr = nullptr;
			this->__is_last = is_last;
			if (!root)
			{
				this->__current_ptr = nullptr;
				return ;
			}
			if (!is_last)
			{
				this->__current_ptr = find_leftest_node(root);
			}
			else
			{
				if (find_rightest_node(root))
					this->__current_ptr = find_rightest_node(root);
				else
					this->__current_ptr = root;
				this->__current_ptr = nullptr;
			}
		}

		BinaryTreeIterator(const BinaryTreeIterator& other)
		{
			this->__root_ptr = other.__root_ptr;
			this->__current_ptr = other.__current_ptr;
			this->__last_ptr = other.__last_ptr;
		}

		~BinaryTreeIterator(){}

		typedef T    value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;

		T*	operator->() const { return &(__current_ptr->value); }
		reference	operator*() const { return (__current_ptr->value);}
		bool	operator!=(const BinaryTreeIterator& other) { return (this->__current_ptr != other.__current_ptr);}
		bool	operator<(const BinaryTreeIterator& other) { return (!__compare_func(this->__current_ptr->value.first, other.__current_ptr->value.first)); }
		bool	operator==(const BinaryTreeIterator& other){ return (this->__current_ptr == other.__current_ptr); }

		BinaryTreeIterator& operator=(const BinaryTreeIterator & other)
		{
			this->__root_ptr = other.__root_ptr;
			this->__current_ptr = other.__current_ptr;
			this->__last_ptr = other.__last_ptr;
			this->__is_last = other.__is_last;
			return (*this);
		}

		BinaryTreeIterator& operator++()
		{
			__current_ptr = find_next(this->__current_ptr);
			return (*this);	
		}

		BinaryTreeIterator operator++(int) { BinaryTreeIterator __tmp(*this); operator++(); return __tmp; };

		BinaryTreeIterator& operator--()
		{
			__current_ptr = find_previous(this->__current_ptr);
			return (*this);
		}

		BinaryTreeIterator operator--(int){ BinaryTreeIterator __tmp(*this); operator--(); return __tmp; };

		node_ptr find_leftest_node(node_ptr head)
		{
			while (head->left)
				head = head->left;
			return head;
		}

		node_ptr find_next(node_ptr head)
		{
			if (!head)
				return __last_ptr;
			if (head->right)
				return (find_leftest_node(head->right));
			while (head->parent != NULL && head == head->parent->right)
				head = head->parent;
			return (head->parent);	
		}

		node_ptr find_rightest_node(node_ptr head)
		{
			while (head->right)
				head = head->right;
			return head;
		}

		node_ptr find_previous(node_ptr head)
		{
			if (!head)
				return find_rightest_node(__root_ptr);
			if (head->left)
				return (find_rightest_node(head->left));
			while (head->parent != NULL && head == head->parent->left)
				head = head->parent;
			if (head->parent == NULL)
				return (head);	
			else
				return (head->parent);
		}

	public:
		node_ptr		__root_ptr;
		node_ptr		__current_ptr;
		node_ptr		__last_ptr;
		Compare			__compare_func;
		bool 			__is_last;
};

template <class T, class Node, class Compare>
class ConstBinaryTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
	public:
		typedef Node*					node_ptr;
		typedef std::allocator<Node>	node_allocator;
		node_allocator					__allocator;

		ConstBinaryTreeIterator()
		{
			this->__current_ptr = nullptr;
			this->__root_ptr = nullptr;
			this->__is_last = false;
			this->__last_ptr = nullptr;
		}

		ConstBinaryTreeIterator(node_ptr root, bool is_last)
		{
			this->__root_ptr = root;
			this->__last_ptr = nullptr;
			if (!root)
			{
				this->__current_ptr = nullptr;
				return ;
			}
			if (!is_last)
				this->__current_ptr = find_leftest_node(root);
			else
				this->__current_ptr = nullptr;
		}

		ConstBinaryTreeIterator(const ConstBinaryTreeIterator& other)
		{
			this->__root_ptr = other.__root_ptr;
			this->__current_ptr = other.__current_ptr;
			this->__last_ptr = other.__last_ptr;
		}

		ConstBinaryTreeIterator(const BinaryTreeIterator<T, Node, Compare>& other)
		{
			this->__root_ptr = other.__root_ptr;
			this->__current_ptr = other.__current_ptr;
			this->__last_ptr = other.__last_ptr;
		}

		typedef const T    value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;

		pointer		operator->() const { return &(__current_ptr->value); }
		reference	operator*() const { return (__current_ptr->value);}
		bool		operator!=(const ConstBinaryTreeIterator& other){ return (this->__current_ptr != other.__current_ptr); }
		bool		operator!=(const BinaryTreeIterator<T, Node, Compare>& other) { return (this->__current_ptr != other.__current_ptr); }
		bool		operator<(const ConstBinaryTreeIterator& other) { return (!__compare_func(this->__current_ptr->value.first, other.__current_ptr->value.first));}
		bool		operator==(const ConstBinaryTreeIterator& other) { return (this->__current_ptr == other.__current_ptr); }

		ConstBinaryTreeIterator& operator=(const ConstBinaryTreeIterator & other)
		{
			this->__root_ptr = other.__root_ptr;
			this->__current_ptr = other.__current_ptr;
			this->__last_ptr = other.__last_ptr;
			this->__is_last = other.__is_last;
			return (*this);
		}

		ConstBinaryTreeIterator& operator=(const BinaryTreeIterator<T, Node, Compare> & other)
		{
			this->__root_ptr = other.__root_ptr;
			this->__current_ptr = other.__current_ptr;
			this->__last_ptr = other.__last_ptr;
			this->__is_last = other.__is_last;
			return (*this);
		}

		ConstBinaryTreeIterator& operator++()
		{
			__current_ptr = find_next(this->__current_ptr);
			return (*this);	
		}

		ConstBinaryTreeIterator operator++(int) { ConstBinaryTreeIterator __tmp(*this); operator++(); return __tmp; };

		ConstBinaryTreeIterator& operator--()
		{
			__current_ptr = find_previous(this->__current_ptr);
			return (*this);
		}

		ConstBinaryTreeIterator operator--(int) { ConstBinaryTreeIterator __tmp(*this); operator--(); return __tmp; };

		node_ptr find_leftest_node(node_ptr head)
		{
			while (head->left)
				head = head->left;
			return head;
		}

		node_ptr find_next(node_ptr head)
		{
			if (!head)
			{
				return __last_ptr;
			}
			if (head->right)
				return (find_leftest_node(head->right));
			while (head->parent != NULL && head == head->parent->right)
				head = head->parent;
			return (head->parent);	
		}

		node_ptr find_rightest_node(node_ptr head)
		{
			while (head->right)
				head = head->right;
			return head;
		}

		node_ptr find_previous(node_ptr head)
		{
			if (!head)
				return find_rightest_node(__root_ptr);
			if (head->left)
				return (find_rightest_node(head->left));
			while (head->parent != NULL && head == head->parent->left)
				head = head->parent;
			if (head->parent == NULL)
				return (head);	
			else
				return (head->parent);
		}

	private:
		node_ptr		__root_ptr;
		node_ptr		__current_ptr;
		node_ptr		__last_ptr;
		Compare			__compare_func;
		bool 			__is_last;
};

template <class T, class Compare, class Allocator = std::allocator<T> >
class BinaryTree
{
	struct node
	{
		T				value;
		struct node*	right;
		struct node*	left;
		struct node*	parent;
		bool			pippo;
		node(T val, struct node* _right, struct node* _left, struct node* _parent)
		{
			this->value = val;
			this->right = _right;
			this->left = _left;
			this->parent = _parent;
		}
	};

	public:
		typedef Compare								compare_function;
		typedef Allocator							allocator_type;
		typedef typename allocator_type::size_type	size_type;


		BinaryTree()
		{
			this->root = NULL;
			this->treeSize = 0;
		};
		
		~BinaryTree() { this->free_tree(this->root); };
		void add(T val) { add(&(this->root), val); };
		void reorder_tree() { reorder_tree(this->root); };
		size_type size() const { return treeSize; };
		bool lookup(T val);
		
		typedef typename ft::vector<T>::iterator					vector_iterator;
		typedef typename std::allocator<node>						node_allocator;
		typedef typename Allocator::template rebind<node>::other	node_max_size_allocator;
		typedef BinaryTreeIterator<T, node, Compare>				iterator;
		typedef ConstBinaryTreeIterator<T, node, Compare>			const_iterator;
		typedef ft::reverse_iterator<iterator >						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator >				const_reverse_iterator;
		node_max_size_allocator										__max_size_allocator;

		iterator begin() { return iterator(this->root, false); }

		size_type max_size() const
		{
			return __max_size_allocator.max_size();
			return __node_allocator.max_size();
		}

		const_iterator begin()  const { return const_iterator(this->root, false); };

		node_allocator __node_allocator;
		
		iterator end() { return iterator (this->root, true); }
		const_iterator end() const { return const_iterator(this->root, true);};
		reverse_iterator rbegin() { return reverse_iterator(end());};
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end());};
		reverse_iterator rend(){ return reverse_iterator(begin());};
		const_reverse_iterator rend() const { return const_reverse_iterator(begin());};
		
		void swap(BinaryTree &other)
		{
			std::swap(root, other.root);
			std::swap(treeSize, other.treeSize);
		}

		struct node* get_rightest_node() const
		{
			if (!this->root)
				return NULL;
			struct node *head = this->root;
			while(head->right)
				head = head->right;
			return (head);
		}

		struct node* get_root() const { return this->root; }

		struct node* search_all_by_key(T val) const { return (search_by_key(root, val)); }

		void	delete_by_key(T val)
		{
			if (!search_all_by_key(val))
				return ;
			ft::vector<T> temp;
			BinaryTree<T, Compare, Allocator> temp_tree;
			for (iterator i = begin(); i < end(); i++)
			{
				if (val.first != i->first)
					temp_tree.add(*i);
			}
			this->swap(temp_tree);
		}

		size_type count_unique(T val) const
		{
			for (const_iterator i = begin(); i != end(); i++)
			{
				if (val.first == i->first)
					return (1);
			}
			return (0);
		}

		iterator find(T val)
		{
			for (iterator i = begin(); i != end(); i++)
			{
				if (val.first == i->first)
					return (i);
			}
			return (end());
			
		}

		void delete_new_by_key(T value)
		{
			deleteNode(this->root, value);
			this->treeSize--;
		}

		int erase_from_tree(T value)
		{
			if (!this->root)
				return 0;
			size_type size = this->treeSize;
			this->deleteNode(this->root, value);
			if (this->treeSize == size)
				return 0;
			return (1);
		}

		struct node* find_leftest_node(struct node* temp)
		{
			while (temp->left)
				temp = temp->left;
			return (temp);
		}

		struct node* find_rightest_node(struct node* temp)
		{
			while (temp->right)
				temp = temp->right;
			return (temp);
		}

		void deleteNode(struct node* root, T key)
		{
			struct node* temp = root;

			if (temp == nullptr)
				return ;
			while (temp)
			{
				if (key.first > temp->value.first)
					temp = temp->right;
				else if (key.first < temp->value.first)
					temp = temp->left;
				else
					break ;
			}
			if (temp == nullptr)
				return ;
			if (!temp->left && !temp->right)
			{
				if (temp->parent)
				{
					if (temp->parent->left == temp) // left son
					{
						temp->parent->left = nullptr; 
						this->__node_allocator.deallocate(temp, 1);
					}
					else
					{
						temp->parent->right = nullptr;
						this->__node_allocator.deallocate(temp, 1);
					}
				}
				else
				{
					this->__node_allocator.deallocate(temp, 1);
					temp = nullptr;
				}
			}
			else if (!temp->left && temp->right)
			{
				if (temp->parent)
				{
					if (temp->parent->left == temp) // left son
					{
						temp->parent->left = temp->right;
						temp->right->parent = temp->parent;
						this->__node_allocator.deallocate(temp, 1);
					}
					else // right son
					{
						temp->parent->right = temp->right;
						temp->right->parent = temp->parent;
						this->__node_allocator.deallocate(temp, 1);
					}
				}
				else
				{
					temp = this->root->right;
					this->__node_allocator.deallocate(this->root, 1);
					this->root = temp;
					this->root->parent = nullptr;
				}
			}
			else if (!temp->right && temp->left)
			{
				if (temp->parent)
				{
					if (temp->parent->left == temp) // left son
					{
						temp->parent->left = temp->left;
						temp->left->parent = temp->parent;
					}
					else // right son
					{
						temp->parent->right = temp->left;
						temp->left->parent = temp->parent;
					}
				}
				else // trying to delete root
				{
					temp = this->root->left;
					this->__node_allocator.deallocate(this->root, 1);
					this->root = temp;
					this->root->parent = nullptr;
				}
			}
			else if (temp->left && temp->right)
			{
				struct node *max_value = find_rightest_node(temp->left);
				temp->value = max_value->value;
				deleteNode(temp->left, max_value->value);
				return ;
			}
			this->treeSize--;
			return ;
		}

	private:
		struct node* root;
		size_type treeSize;
		compare_function	__comparison_func;
		
		struct node* insert(struct node* node, T st)
		{
			if (node == nullptr) 
			{

				node = this->__node_allocator.allocate(1);
				node->value = st;
				node->left = nullptr;
				node->right = nullptr;
				node->parent = nullptr;

				this->treeSize++;
				return (node);
			}
			if (__comparison_func(st.first, node->value.first))
			{
				struct node *lchild = insert(node->left, st);
				node->left  = lchild;
				lchild->parent = node;
			}
			else if (!__comparison_func(st.first, node->value.first))
			{
				struct node *rchild = insert(node->right, st);
				node->right  = rchild;
				rchild->parent = node;
			}
			return node;
		}

	public:
		struct node* insert_from_root(T value)
		{
			struct node* temp = insert(this->root, value);
			if (!this->root)
				this->root = temp;
			return this->root;
		}

	private:
		struct node* search_by_pair(struct node* node, T val)
		{
			if(node == nullptr)
				return nullptr;
			else
			{
				if (val == node->value)
					return node;
				if (!(__comparison_func(val.first, node->value.first)))
					return search_by_pair(node->right, val);
				else
					return search_by_pair(node->left, val);
			}
		};

		struct node* search_by_key(struct node *temp, T val) const
		{
			if(temp == nullptr)
				return nullptr;
			else
			{
				if(val.first == temp->value.first)
					return temp;
				if (!__comparison_func(val.first, temp->value.first))
					return search_by_key(temp->right, val);
				else
					return search_by_key(temp->left, val);
			}
		};

		void free_tree(struct node *node)
		{
			if (node == nullptr)
				return ;
			free_tree(node->right);
			free_tree(node->left);
			this->__node_allocator.deallocate(node, 1);
		}
};

#endif