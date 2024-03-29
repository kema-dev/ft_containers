#ifndef MAP_HPP
#define MAP_HPP
#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "../Iterators/Iterator.hpp"
#include "../Tools/Exceptions.hpp"
#include "../Tools/Node.hpp"

namespace ft {

// SECTION map
template <class K, class V, class Compare = ft::less<K>, class Allocator = std::allocator<ft::pair<const K, V> > >
class map {
   public:
	typedef K key_type;
	typedef V mapped_type;

	typedef ft::node<K, V>* nodePtr;
	typedef ft::node<K, V>& nodeRef;
	typedef ft::node<K, V> nodeType;
	typedef ft::pair<const key_type, mapped_type> value_type;
	typedef ft::pair<const key_type, mapped_type>& pairRef;
	typedef ft::pair<const key_type, mapped_type>* pairPtr;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef mapped_type* mapped_type_pointer;
	typedef mapped_type& mapped_type_reference;
	typedef const mapped_type* const_mapped_type_pointer;
	typedef const mapped_type& const_mapped_type_reference;
	typedef Allocator allocator_type;
	typedef Compare key_compare;

	class MapIterator : public ft::iterator<std::bidirectional_iterator_tag, value_type> {
	   public:
		typedef typename ft::iterator_traits<ft::map<K, V, Compare, Allocator> >::difference_type difference_type;
		typedef typename ft::iterator_traits<ft::map<K, V, Compare, Allocator> >::value_type value_type;
		typedef typename ft::iterator_traits<ft::map<K, V, Compare, Allocator> >::pointer pointer;
		typedef typename ft::iterator_traits<ft::map<K, V, Compare, Allocator> >::reference reference;
		typedef typename ft::iterator_traits<ft::map<K, V, Compare, Allocator> >::iterator_category iterator_category;

	   public:
		MapIterator(void) : ptr(NULL) {}
		MapIterator(nodePtr ptr) : ptr(ptr) {}
		MapIterator(const MapIterator& other) : ptr(other.ptr) {}
		MapIterator& operator=(const MapIterator& other) {
			ptr = other.ptr;
			return *this;
		}
		MapIterator& operator++() {
			ptr = ptr->getSuccessor();
			return *this;
		}
		MapIterator operator++(int) {
			MapIterator tmp(*this);
			ptr = ptr->getSuccessor();
			return tmp;
		}
		MapIterator& operator--() {
			ptr = ptr->getPredecessor();
			return *this;
		}
		MapIterator operator--(int) {
			MapIterator tmp(*this);
			ptr = ptr->getPredecessor();
			return tmp;
		}
		bool operator==(const MapIterator& other) const {
			return ptr == other.ptr;
		}
		bool operator!=(const MapIterator& other) const {
			return ptr != other.ptr;
		}
		value_type& operator*() {
			return ptr->pair;
		}
		value_type* operator->() const {
			return &(ptr->pair);
		}
		bool operator<(const MapIterator& other) const {
			return ptr < other.ptr;
		}
		bool operator>(const MapIterator& other) const {
			return ptr > other.ptr;
		}
		bool operator<=(const MapIterator& other) const {
			return ptr <= other.ptr;
		}
		bool operator>=(const MapIterator& other) const {
			return ptr >= other.ptr;
		}
		bool operator==(const MapIterator& other) {
			return ptr == other.ptr;
		}
		bool operator!=(const MapIterator& other) {
			return ptr != other.ptr;
		}
		bool operator!() {
			return ptr == NULL;
		}
		const K& first() {
			return ptr->pair.first();
		}
		const V& second() {
			return ptr->pair.second();
		}
		MapIterator operator+(int n) {
			return ptr + n;
		}
		MapIterator operator-(int n) {
			return ptr - n;
		}
		nodePtr ptr;
	};

	class MapReverseIterator : public ft::iterator<std::bidirectional_iterator_tag, value_type> {
	   public:
		typedef typename MapIterator::difference_type difference_type;
		typedef typename MapIterator::value_type value_type;
		typedef typename MapIterator::pointer pointer;
		typedef typename MapIterator::reference reference;
		typedef typename MapIterator::iterator_category iterator_category;

	   public:
		MapReverseIterator(void) : ptr(NULL) {}
		MapReverseIterator(nodePtr ptr) : ptr(ptr) {}
		MapReverseIterator(const MapReverseIterator& other) : ptr(other.ptr) {}
		MapReverseIterator& operator=(const MapReverseIterator& other) {
			ptr = other.ptr;
			return *this;
		}
		MapReverseIterator& operator++() {
			ptr = ptr->getPredecessor();
			return *this;
		}
		MapReverseIterator operator++(int) {
			MapReverseIterator tmp(*this);
			ptr = ptr->getPredecessor();
			return tmp;
		}
		MapReverseIterator& operator--() {
			ptr = ptr->getSuccessor();
			return *this;
		}
		MapReverseIterator operator--(int) {
			MapReverseIterator tmp(*this);
			ptr = ptr->getSuccessor();
			return tmp;
		}
		bool operator==(const MapReverseIterator& other) const {
			return ptr == other.ptr;
		}
		bool operator!=(const MapReverseIterator& other) const {
			return ptr != other.ptr;
		}
		value_type& operator*() {
			return ptr->pair;
		}
		value_type* operator->() {
			return &(ptr->pair);
		}
		bool operator<(const MapReverseIterator& other) const {
			return ptr < other.ptr;
		}
		bool operator>(const MapReverseIterator& other) const {
			return ptr > other.ptr;
		}
		bool operator<=(const MapReverseIterator& other) const {
			return ptr <= other.ptr;
		}
		bool operator>=(const MapReverseIterator& other) const {
			return ptr >= other.ptr;
		}
		bool operator==(const MapReverseIterator& other) {
			return ptr == other.ptr;
		}
		bool operator!=(const MapReverseIterator& other) {
			return ptr != other.ptr;
		}
		bool operator!() {
			return ptr == NULL;
		}
		const K& first() {
			return ptr->pair.first();
		}
		const V& second() {
			return ptr->pair.second();
		}
		MapReverseIterator operator+(int n) {
			return ptr + n;
		}
		MapReverseIterator operator-(int n) {
			return ptr - n;
		}
		nodePtr ptr;
	};

	typedef MapIterator iterator;
	typedef MapIterator const_iterator;
	typedef MapReverseIterator reverse_iterator;
	typedef MapReverseIterator const_reverse_iterator;

	class value_compare {
	   public:
		bool operator()(const value_type& lhs, const value_type& rhs) const {
			return comp(lhs.first, rhs.first);
		}
		value_compare(Compare comp) : comp(comp) {}

	   private:
		Compare comp;
	};

   private:
	nodePtr _root;
	size_type _size;
	allocator_type _alloc;
	Compare _comp;

   public:
	// SECTION Constructors / Destructors
	// INFO Create an map tree with a custom allocator and comparator
	explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = Allocator())
		: _root(NULL), _size(0), _alloc(alloc), _comp(comp){};
	// INFO Create a map filled with a range of elements
	template <class InputIterator>
	map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
		: _root(NULL), _size(0), _alloc(alloc), _comp(comp) {
		insert(first, last);
	}
	// INFO Copy <other>
	map(const map& other)
		: _root(NULL), _size(0), _alloc(other._alloc), _comp(other._comp) {
		insert(other.begin(), other.end());
		_root->color = black;
	}
	/*
	INFO Create a tree with root node containing pair <dpair>
	INFO Can throw exception (self: allocFail)
	*/
	map(value_type dpair) {
		_root = standaloneNode(dpair);
		_root->color = black;
		_size = 1;
	};
	/*
	INFO Clear the tree from nodePtr <node>
	INFO No exception
	*/
	 private:
	void clear(nodePtr node) {
		if (!node)
			return;
		clear(node->left);
		clear(node->right);
		std::allocator<nodeType>().deallocate(node, 1);
		_size--;
	};
	 public:
	// INFO Clear the tree (fully)
	void clear(void) {
		clear(_root);
		_root = NULL;
		_size = 0;
	};
	/*
	INFO Clear the entire tree
	INFO No exception
	*/
	~map(void) {
		clear(_root);
	};
	/*
	INFO Make map <this> become a copy of map <rhs>
	INFO Can throw exception (calls)
	*/
	map& operator=(map const& rhs) {
		if (this != &rhs) {
			clear();
			if (rhs.size() > 0) {
				insert(rhs.begin(), rhs.end());
				_root->color = black;
			}
		}
		return *this;
	};
	// INFO Get the allocator
	allocator_type get_allocator(void) const {
		return _alloc;
	};
	/*
	INFO Create a map with map <src> as "root"
	INFO Can throw exception (calls)
	*/
	// !SECTION Constructors / Destructors
	// SECTION Operators and basic functions
	 private:
	// INFO Get the root node
	nodePtr getRoot(void) const {
		return _root;
	};
	 public:
	// INFO access specified element with bounds checking
	const_mapped_type_reference at(const key_type& key) {
		iterator node = find(key);
		if (!node)
			throw std::out_of_range("map::at: key not found");
		return node->pair.second;
	};
	// INFO access or insert specified element
	mapped_type_reference operator[](const key_type& key) {
		iterator node = find(key);
		if (!node) {
			return insert_old_kv(key, V())->pair.second;
		}
		return node.ptr->pair.second;
	};
	// INFO Get the first element as an iterator
	iterator begin(void) {
		return iterator(this->getMin());
	};
	// INFO Get the first element as a const_iterator
	const_iterator begin(void) const {
		return const_iterator(this->getMin());
	};
	// INFO Get the last element as an iterator
	iterator end(void) {
		return NULL;
	};
	// INFO Get the last element as a const_iterator
	const_iterator end(void) const {
		return NULL;
	};
	// INFO Get the first element as a reverse_iterator
	reverse_iterator rbegin(void) {
		return reverse_iterator(this->getMax());
	};
	// INFO Get the first element as a const_reverse_iterator
	const_reverse_iterator rbegin(void) const {
		return const_reverse_iterator(this->getMax());
	};
	// INFO Get the last element as a reverse_iterator
	reverse_iterator rend(void) {
		return NULL;
	};
	// INFO Get the last element as a const_reverse_iterator
	const_reverse_iterator rend(void) const {
		return NULL;
	};
	// INFO Check if the map is empty
	bool empty(void) const {
		return _size == 0;
	};
	// INFO Get the size of the map
	size_type size(void) const {
		return _size;
	};
	// INFO Get the maximum size of the map
	size_type max_size(void) const {
		return std::numeric_limits<difference_type>::max();
	};
	// INFO erase the element at position <pos>
	void erase(iterator pos) {
		remove(pos.ptr);
	};
	// INFO erase the elements in the range [<first>, <last>)
	void erase(iterator first, iterator last) {
		// if (first > this->getMax() || last < this->getMin())
		// 	return;
		while (first != last)
			erase(first++);
	};
	// INFO erase the element with key <key>
	size_type erase(const key_type& key) {
		iterator node = find(key);
		if (!node)
			return 0;
		erase(node);
		return 1;
	};
	// INFO swap the contents of <this> and <other>
	void swap(map& other) {
		std::swap(_root, other._root);
		std::swap(_size, other._size);
		std::swap(_alloc, other._alloc);
		std::swap(_comp, other._comp);
	};
	// SECTION Searching
	 private:
	/*
	INFO Search for a node by <key>, from <this>'s root
	INFO No exception
	*/
	nodePtr searchKey(key_type key) const {
		return (searchKey(_root, key));
	};
	/*
	INFO Search for a node by <key>, from specified nodePtr <start>
	INFO No exception
	*/
	nodePtr searchKey(nodePtr start, key_type key) const {
		if (!start || !key) {
			return NULL;
		} else {
			if (key == start->pair.first) {
				return start;
			} else if (_comp(key, start->pair.first)) {
				return searchKey(start->left, key);
			} else {
				return searchKey(start->right, key);
			}
		}
	};
	// !SECTION Searching
	 public:
	// INFO Find the first element with key <key>
	iterator find(const key_type& key) const {
		return iterator(searchKey(key));
	};
	// // INFO Find the first element with key <key>
	// const_iterator find(const key_type& key) const{
	// 	return const_iterator(searchKey(key));
	// };
	// INFO Count the number of elements with key <key>
	size_type count(const key_type& key) const {
		if (!find(key))
			return 0;
		else
			return 1;
	};
	// INFO Get the range of elements with key <key>
	ft::pair<iterator, iterator> equal_range(const key_type& key) {
		return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
	};
	// INFO Get the range of elements with key <key>
	pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
		return ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
	};
	// INFO Get the lower bound of the elements with key <key> (the first element with key >= <key>)
	iterator lower_bound(const key_type& key) {
		iterator it = begin();
		while (it != end() && _comp(it->first, key))
			it++;
		return (it);
	};
	// INFO Get the lower bound of the elements with key <key> (the first element with key >= <key>)
	const_iterator lower_bound(const key_type& key) const {
		const_iterator it = begin();
		while (it != end() && _comp(it->first, key))
			it++;
		return (it);
	};
	// INFO Get the upper bound of the elements with key <key> (the first element with key < <key>)
	iterator upper_bound(const key_type& key) {
		iterator it = begin();
		while (it != end() && (_comp(it->first, key) || it->first == key))
			it++;
		return (it);
	};
	// INFO Get the upper bound of the elements with key <key> (the first element with key < <key>)
	const_iterator upper_bound(const key_type& key) const {
		const_iterator it = begin();
		while (it != end() && (_comp(it->first, key) || it->first == key))
			it++;
		return (it);
	};
	// INFO Get the comparison object
	key_compare key_comp(void) const {
		return key_compare(_comp);
	};
	// INFO Get the value comparison object
	value_compare value_comp(void) const {
		return _comp;
	};
	 private:
	/*
	INFO Get a mint new node with pair <dpair>
	INFO Can throw exception (self: allocFail)
	*/
	nodePtr standaloneNode(value_type dpair) const {
		nodePtr buf = std::allocator<nodeType>().allocate(1);
		std::allocator<nodeType>().construct(buf, dpair);
		return buf;
	};
	/*
	INFO Get a copy of nodePtr <node>
	INFO Can throw exception (calls)
	*/
	nodePtr copy(nodePtr node) {
		if (!node)
			return NULL;
		nodePtr newNode;
		newNode = standaloneNode(node->pair);
		newNode->color = node->color;
		newNode->parent = NULL;
		_size++;
		newNode->left = copy(node->left);
		newNode->right = copy(node->right);
		if (newNode->left)
			newNode->left->parent = newNode;
		if (newNode->right)
			newNode->right->parent = newNode;
		return newNode;
	};
	// !SECTION Operators and basic functions
	// SECTION Insertion
	/*
	INFO /!\ DO NOT USE /!\ (Use "add" instead)
	INFO Can throw exception (calls)
	*/
	nodePtr add(value_type dpair) {
		nodePtr newNode = standaloneNode(dpair);
		nodePtr curNode = _root;
		nodePtr parent = NULL;
		while (curNode) {
			parent = curNode;
			if (newNode->pair.first == curNode->pair.first) {
				std::allocator<nodeType>().destroy(newNode);
				std::allocator<nodeType>().deallocate(newNode, 1);
				throw duplicateKey();
			} else if (_comp(newNode->pair.first, curNode->pair.first)) {
				curNode = curNode->left;
			} else {
				curNode = curNode->right;
			}
		}
		newNode->parent = parent;
		if (!parent) {
			_root = newNode;
			_root->color = black;
			_size++;
			return newNode;
		} else {
			if (_comp(newNode->pair.first, parent->pair.first))
				parent->left = newNode;
			else if (!_comp(newNode->pair.first, parent->pair.first) && (newNode->pair.first != parent->pair.first))
				parent->right = newNode;
			else {
				std::allocator<nodeType>().deallocate(newNode, 1);
				throw duplicateKey();
			}
		}
		newNode->color = red;
		_size++;
		return newNode;
	};
	 public:
	/*
	INFO Add pair <dpair> to the tree
	INFO Can throw exception (calls)
	*/
	ft::pair<iterator, bool> insert(const value_type& dpair) {
		nodePtr newNode;

		try {
			newNode = add(dpair);
		} catch (duplicateKey const&) {
			return ft::pair<iterator, bool>(find(dpair.first), false);
		}
		fixInsert(newNode);
		return ft::pair<iterator, bool>(iterator(newNode), true);
	};
	/*
	INFO Add pair <dpair> to the tree
	INFO Can throw exception (calls)
	*/
	iterator insert(iterator pos, const value_type& dpair) {
		static_cast<void>(pos);
		nodePtr newNode;
		try {
			newNode = add(dpair);
		} catch (duplicateKey const&) {
			return find(dpair.first);
		}
		return iterator(newNode);
	};

	void insert(key_type key) {
		insert(value_type(key, mapped_type()));
	};

	/*
	INFO Add pair <first> to <last> to the tree
	INFO Can throw exception (calls)
	*/
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last) {
		while (first != last) {
			insert(*first);
			++first;
		}
	};
	/*
	INFO Add pair (non const) <dpair> to the tree
	INFO Can throw exception (calls)
	*/
	ft::pair<iterator, bool> insert(iterator pos, const ft::pair<K, V>& dpair) {
		static_cast<void>(pos);
		nodePtr newNode;
		value_type dpair2(dpair.first, dpair.second);
		try {
			newNode = add(dpair2);
		} catch (duplicateKey const&) {
			return ft::pair<iterator, bool>(find(dpair2.first), false);
		}
		fixInsert(newNode);
		return ft::pair<iterator, bool>(iterator(newNode), true);
	};
	ft::pair<iterator, bool> insert(const ft::pair<K, V>& dpair) {
		nodePtr newNode;
		value_type dpair2(dpair.first, dpair.second);
		try {
			newNode = add(dpair2);
		} catch (duplicateKey const&) {
			return ft::pair<iterator, bool>(find(dpair2.first), false);
		}
		fixInsert(newNode);
		return ft::pair<iterator, bool>(iterator(newNode), true);
	};
	 private:
	/*
	INFO Add a new node with pair <dpair> to the tree
	INFO Can throw exception (calls)
	*/
	nodePtr insert_old_kv(const K& key, const V& value) {
		value_type dpair = ft::make_pair<const K, V>(key, value);
		nodePtr newNode;
		try {
			newNode = add(dpair);
		} catch (duplicateKey const&) {
			return find(key).ptr;
		}
		fixInsert(newNode);
		return newNode;
	};
	/*
	INFO Fix the map after insertion of nodePtr <node>
	INFO Can throw exception (calls)
	*/
	void fixInsert(nodePtr node) {
		while (node->parent && node->parent->color == red) {
			if (node->parent == node->parent->parent->left) {
				nodePtr uncle = node->parent->parent->right;
				if (uncle && uncle->color == red) {
					node->parent->color = black;
					uncle->color = black;
					node->parent->parent->color = red;
					node = node->parent->parent;
				} else {
					if (node == node->parent->right) {
						node = node->parent;
						leftRotate(node);
					}
					node->parent->color = black;
					node->parent->parent->color = red;
					rightRotate(node->parent->parent);
				}
			} else {
				nodePtr uncle = node->parent->parent->left;
				if (uncle && uncle->color == red) {
					node->parent->color = black;
					uncle->color = black;
					node->parent->parent->color = red;
					node = node->parent->parent;
				} else {
					if (node == node->parent->left) {
						node = node->parent;
						rightRotate(node);
					}
					node->parent->color = black;
					node->parent->parent->color = red;
					leftRotate(node->parent->parent);
				}
			}
		}
		_root->color = black;
	};
	/*
	INFO Rotate nodePtr <node> to the left
	INFO Can throw exception (calls)
	*/
	void leftRotate(nodePtr node) {
		nodePtr right = node->right;
		node->right = right->left;
		if (right->left)
			right->left->parent = node;
		right->parent = node->parent;
		if (!node->parent)
			_root = right;
		else if (node == node->parent->left)
			node->parent->left = right;
		else
			node->parent->right = right;
		right->left = node;
		node->parent = right;
	};
	/*
	INFO Rotate nodePtr <node> to the right
	INFO Can throw exception (calls)
	*/
	void rightRotate(nodePtr node) {
		nodePtr left = node->left;
		node->left = left->right;
		if (left->right)
			left->right->parent = node;
		left->parent = node->parent;
		if (!node->parent)
			_root = left;
		else if (node == node->parent->right)
			node->parent->right = left;
		else
			node->parent->left = left;
		left->right = node;
		node->parent = left;
	};
	// !SECTION Insertion
	// SECTION Deletion
	/*
	INFO Remove nodePtr <node> from the tree
	INFO Can throw exception (calls)
	*/
	void remove(nodePtr node) {
		if (!node)
			return;
		if (node == _root) {
			nodePtr l = _root->left;
			nodePtr r = _root->right;
			std::allocator<nodeType>().deallocate(_root, 1);
			nodePtr curNode = r;
			if (!curNode) {
				_root = l;
				if (_root)
					_root->parent = NULL;
				_size--;
				return;
			}
			if (!curNode->left) {
				_root = curNode;
				if (_root)
					_root->parent = NULL;
				_root->left = l;
				if (l)
					_root->left->parent = curNode;
				_size--;
				return;
			}
			while (curNode->left)
				curNode = curNode->left;
			curNode->parent->left = curNode->right;
			if (curNode->right)
				curNode->right->parent = curNode->parent;
			_root = curNode;
			_root->parent = NULL;
			_root->left = l;
			_root->right = r;
			if (_root->left)
				_root->left->parent = _root;
			if (_root->right)
				_root->right->parent = _root;
			_size--;
			if (_root)
				_root->parent = NULL;
			return;
		}
		nodePtr save = node;
		nodePtr curNode = node;
		nodePtr parent = node->parent;
		nodePtr child = NULL;
		nodePtr sibling = NULL;
		bool isLeft = false;
		if (node->left && node->right) {
			bool isLeft = (node == node->parent->left);
			curNode = node->left;
			while (curNode->right)
				curNode = curNode->right;
			if (parent) {
				if (isLeft)
					parent->left = curNode;
				else
					parent->right = curNode;
			} else {
				// TODO verify this
				_root = curNode;
				curNode->right = save->right;
				if (curNode->right)
					curNode->right->parent = curNode;
				curNode->color = save->color;
				return;
			}
			if (curNode->parent->right == curNode) {
				curNode->parent->right = NULL;
			} else {
				curNode->parent->left = NULL;
			}
			curNode->parent = parent;
			curNode->right = save->right;
			if (curNode->right)
				curNode->right->parent = curNode;
			curNode->left = save->left;
			if (curNode->left)
				curNode->left->parent = curNode;
			curNode->color = save->color;
			std::allocator<nodeType>().deallocate(save, 1);
			_size--;
			return;
		} else if (node->left) {
			child = node->left;
		} else
			child = node->right;
		if (!parent) {
			_root = child;
		} else if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
		if (child)
			child->parent = parent;
		if (node->color == black)
			fixRemove(child, sibling, isLeft);
		std::allocator<nodeType>().deallocate(node, 1);
		_size--;
	};
	/*
	INFO Fix the map after deletion of nodePtr <node>
	INFO Can throw exception (calls)
	*/
	void fixRemove(nodePtr node, nodePtr sibling, bool isLeft) {
		if (!node)
			return;
		if (node->color == red) {
			node->color = black;
			return;
		}
		if (sibling) {
			if (sibling->color == red) {
				sibling->color = black;
				if (isLeft) {
					node->parent->color = red;
					rightRotate(node->parent);
				} else {
					node->parent->color = red;
					leftRotate(node->parent);
				}
				sibling = node->parent->left;
			}
			if (sibling->left->color == black && sibling->right->color == black) {
				sibling->color = red;
				node = node->parent;
			} else {
				if (sibling->left->color == black) {
					sibling->right->color = black;
					sibling->color = red;
					leftRotate(sibling);
					sibling = node->parent->left;
				}
				sibling->color = node->parent->color;
				node->parent->color = black;
				sibling->left->color = black;
				rightRotate(node->parent);
				node = _root;
			}
		} else {
			node->color = black;
			node = node->parent;
		}
		fixRemove(node, node->left, true);
		fixRemove(node, node->right, false);
	};
	// !SECTION Deletion
	// SECTION Printing
	/*
	INFO Set the terminal color according to node color
	INFO No exception
	*/
	void setColor(nodePtr node) {
		if (node->color == red)
			cout << RED;
		else if (node->color == black)
			cout << BLACK;
	};
	/*
	INFO Set the terminal color to default (white)
	INFO No exception
	*/
	void unsetColor(void) {
		cout << DEFAULT;
	};
	// INFO /!\ DO NOT USE /!\ (Use function "print" instead)
	void recursivePrint(const string& prefix, const nodePtr node, bool isLeft) {
		if (node != NULL) {
			cout << prefix;
			cout << (isLeft ? "├──" : "└──");
			setColor(node);
			cout << node->pair.first << ":" << node->pair.second << endl;
			unsetColor();
			recursivePrint(prefix + (isLeft ? "│   " : "    "), node->left, true);
			recursivePrint(prefix + (isLeft ? "│   " : "    "), node->right, false);
		}
	}
	/*
	INFO Prints the tree from specified nodePtr <node>
	INFO No exception
	*/
	void print(const nodePtr node) {
		recursivePrint("", node, false);
	};
	/*
	INFO Prints <this> tree from root
	INFO No exception
	*/
	void print(void) {
		recursivePrint("", _root, false);
	};
	// !SECTION Printing
	/*
	INFO Return the root nodePtr
	INFO No exception
	*/
	nodePtr getRoot(void) {
		return _root;
	};
	/*
	INFO Return the size of <this> tree
	INFO No exception
	*/
	size_t getSize(void) {
		return _size;
	};
	/*
	INFO Get the nodePtr of the minimum value
	INFO No exception
	*/
	nodePtr getMin(void) const {
		nodePtr curNode = _root;
		while (curNode && curNode->left)
			curNode = curNode->left;
		return curNode;
	};
	/*
	INFO Get the nodePtr of the maximum value
	INFO No exception
	*/
	nodePtr getMax(void) const {
		nodePtr curNode = _root;
		while (curNode && curNode->right)
			curNode = curNode->right;
		return curNode;
	};
	/*
	INFO Get the range of pairs with keys equal to <key>
	INFO No exception
	*/
	ft::pair<nodePtr, nodePtr> getRange(K key) {
		nodePtr start = searchKey(_root, key);
		if (start) {
			nodePtr end = getSuccessor(start);
			return (make_pair(start, end));
		} else {
			return (make_pair(NULL, NULL));
		}
	};
	 public:
};
// !SECTION map
}  // namespace ft
// !SECTION namespace ft
#endif