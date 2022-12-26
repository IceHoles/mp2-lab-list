#pragma once
#include <initializer_list>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>

template <typename T> 
struct Node {
		T elem; 
		Node<T>* next;
		Node() {
			next = nullptr;
		}
		Node(T value) {
			elem = value;	 
			next = nullptr;
		}				    
	};

template <typename T>
class List {
	Node<T>* first = nullptr;	  
public:
	template <typename T>
	class iterator {

		Node<T>* ptr;

	public:

		iterator() {};

		iterator(Node<T>* data) {
			ptr = data;
		};

		iterator& operator++() {
			ptr = ptr->next;
			return *this;
		};

		iterator operator++(int) {
			iterator copy(this->ptr);
			ptr = ptr->next;
			return copy;
		};

		friend bool operator!=(const iterator& it1, const iterator& it2) {
			if (it1.ptr != it2.ptr)
				return true;
			else
				return false;
		};

		friend bool operator==(const iterator& it1, const iterator& it2) {
			return !(it1 != it2);
		};

		T& operator*() {
			return ptr->elem;
		};

		Node<T>* get_node() {
			return this->ptr;
		};
	};

	explicit List(size_t count) {
		first = new Node<T>();
		auto it = first;
		for (int i = 1; i < count; i++) {
			it->next = new Node<T>();
			it = it->next;
		}
	};

	List() :first(nullptr) {}

	List(const List& list) {
		Node<T>* lptr = list.first;							 
		if (!list.first)
			return;
		first = new Node<T>(lptr->elem);
		lptr = lptr->next;
		Node<T>* tmp = first;
		while (lptr) {
			tmp->next = new Node<T>(lptr->elem);
			lptr = lptr->next;
			tmp = tmp->next;
		}
	};

	List(List&& list) {
		this->first = list.first;
		list.first = nullptr;
	};

	List(Node<T>* list) {
		first = list;
	}

	List(const std::initializer_list<T>& list) {
		for (auto it = list.begin(); it != list.end(); ++it) {
			push_front(*it);
		}					
		this->reverse();
	};

	~List() {
		Node<T>* tmp = first;
		while (tmp) {
			Node<T>* tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
	};

	List& operator=(const List& list) {
		if (this == &list) return *this;
		List copy(list);
		this->clear();
		this->first = copy.first;
		return *this;
	};

	List& operator=(List&& list) {
		Node<T>* tmp = list.first;
		list.first = this->first;
		this->first = tmp;
		return *this;
	};

	T& operator[](size_t n) { 
		Node<T>* it = first;
		for (int i = 0; i < n; i++) {
			it = it->next;
		}
		return it->elem;
	}

	bool empty() const {
		if (!first)
			return false;
		return true;
	};

	size_t size() {
		Node<T>* tmp = first;
		size_t count = 0;
		while (tmp) {
			Node<T>* tmp2 = tmp->next;
			count++;
			tmp = tmp2;
		}
		return count;
	};

	Node<T>* get_first() { return this->first; }

	Node<T>* get_node(size_t pos) {
		Node<T>* tmp = first;
		for (int i = 1; i < pos; i++) tmp = tmp->next;
		return tmp;
	}

	void clear() {
		Node<T>* tmp = this->first;
		while (tmp) {
			Node<T>* tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
		first = nullptr;
	};

	void erase_after(Node<T>* prev) {
		Node<T>* tmp = prev->next;
		prev->next = prev->next->next;
		delete tmp;
	};

	void merge(List& list) {
		Node<T>* tmp = this->first;
		Node<T>* tmp2;
		while (tmp)	{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		tmp2->next = list.first;
	};

	void merge(List&& list) {
		Node<T>* tmp = this->first;
		Node<T>* tmp2;
		while (tmp) {
			tmp2 = tmp;
			tmp = tmp->next;
		}
		tmp2->next = list.first;
	};

	void sort();		// O(n log n)

	void insert_after(Node<T>* prev, T value) {
		Node<T>* tmp = prev->next;
		prev->next = new Node();
		prev->next->elem = value;
		prev->next->next = tmp;
	};

	void push_front(T value) {
		Node<T>* tmp = new Node<T>(value);
		tmp->next = first;
		first = tmp;
	}

	void reverse() {
		Node<T>* tmp = first;
		Node<T>* it = first;
		Node<T>* tmp1 = nullptr;
		while (it) {
			tmp = it->next;
			it->next = tmp1;
			tmp1 = it;
			it = tmp;
		}
		first = tmp1;
	};

	void reverse_print() {
		this->reverse();
		for (auto it = first; it != it.end(); ++it) {
			std::cout << it->elem << ' ';
		}
		std::cout << std::endl;
		this->reverse;
	};

	 std::vector<T> middle() {
		Node<T>* tmp1 = first;
		Node<T>* tmp2 = first;
		Node<T>* prev = first;
		std::vector<T> res;
		bool odd = 0;
		while (tmp2) {
			if (tmp2->next)
				tmp2 = tmp2->next->next;
			else { 
				odd = 1;
				break;
			}
			prev = tmp1;
			tmp1 = tmp1->next;
		}
		if (odd) {
			res.push_back(tmp1->elem);
		}
		else {
			res.push_back(prev->elem);
			res.push_back(tmp1->elem);
		}
		return res;
	}

	void erase_middle() {
		Node<T>* tmp1 = first;
		Node<T>* tmp2 = first;
		Node<T>* prev = first;
		bool odd = 0;
		while (tmp2) {
			if (tmp2->next)
				tmp2 = tmp2->next->next;
			else {
				odd = 1;
				break;
			}
			prev = tmp1;
			tmp1 = tmp1->next;
		}
		if (odd) {
			erase_after(tmp1);
		}
		else {
			erase_after(tmp1);
			erase_after(prev);
		}
	}

	void merge_sorted_lists(List& list) {
		Node<T>* ptr1 = first;
		Node<T>* ptr2 = list.first;
		Node<T>* tmp = new Node<T>();
		Node<T>* ptr3 = tmp;
		while (ptr1 && ptr2) {
			if (ptr1->elem <= ptr2->elem) {
				ptr3->next = ptr1;
				ptr3 = ptr1;
				ptr1 = ptr1->next;
			}
			else {
				ptr3->next = ptr2;
				ptr3 = ptr2;
				ptr2 = ptr2->next;
			}
		}
		while (ptr2) {
			ptr3->next = ptr2;
			ptr3 = ptr2;
			ptr2 = ptr2->next;
		}
		while(ptr1) {
			ptr3->next = ptr1;
			ptr3 = ptr1;
			ptr1 = ptr1->next;
		}
		first = tmp->next;
		delete tmp;
		list.first = nullptr;
	};

	void sorted_insert(T value) {
		if (first != nullptr) {
			Node<T>* tmp = first;
			auto tmp2 = tmp;
			while (tmp->elem < value) {
				tmp2 = tmp;
				tmp = tmp->next;
			}
			tmp2->next = new Node<T>(value);
			tmp2->next->next = tmp;
		}
		else push_front(value);
	}

	void erase_last_duplicate(T value) {
		if (first != nullptr) {
			Node<T>* tmp = first;
			auto prev = tmp;
			while(tmp->next) {
				if (tmp->next->elem == value) {
					prev = tmp;
				}
				tmp = tmp->next;
			}
			prev->next = prev->next->next;
		}
	}

	T& at_end(size_t n) {
		Node<T>* it = first;
		Node<T>* fast = first;
		size_t i = 1;
		while (fast) {
			if (i > n) {
				it = it->next;
			}
			fast = fast->next;
			i++;
		}
		return it->elem;
	}

	void cyclic_shift(size_t n) {
		if (first != nullptr) {
			Node<T>* it = first;
			Node<T>* fast = first;
			Node<T>* prev = first; 
			Node<T>* itprev = first;
			size_t i = 1;
			while (fast) {
				if (i > n) {
					itprev = it;
					it = it->next;
				}
				prev = fast;
				fast = fast->next;
				i++;
			}
			prev->next = first;
			first = it;
			itprev->next = nullptr;
		}
	}

	void reverse_nodes(size_t sz, size_t pos) {
		Node<T>* tmp = first;
		Node<T>* it = first;
		Node<T>* prev = nullptr;
		Node<T>* tmp1 = nullptr;
		Node<T>* tmp2 = nullptr;
		for (int i = 1; i < pos; i++) {
			prev = tmp;
			tmp = tmp->next;
		}
		it = tmp;
		tmp2 = tmp;	   // 10  -> 15
		for (int i = 0; i < sz; i++) {
			tmp = it->next;
			it->next = tmp1;
			tmp1 = it;
			it = tmp;
		}
		prev->next = tmp1;
		tmp2->next = tmp;
	}

	void erase_duplicates() {
		if (first == nullptr) return;
		Node<T>* tmp = first;
		Node<T>* tmp1;
		Node<T>* prev;
		while (tmp) {
			tmp1 = tmp;
			while (tmp1->next){
				prev = tmp1;
				tmp1 = tmp1->next;
				if (tmp1->elem == tmp->elem) {
					tmp1 = prev;
					erase_after(prev);
				}
			}
			tmp = tmp->next;
		}
	}

	void add_integer(int number) {
		this->reverse(); 
		Node<T>* tmp = first;
		int overflow = 0;
		while (tmp) {
			tmp->elem += (number % 10) + overflow;
			overflow = 0;
			number /= 10;
			if (tmp->elem > 9) { 
				tmp->elem %= 10;
				overflow++;
			}
			tmp = tmp->next;
		}
		this->reverse();
		if (overflow > 0) push_front(1);
	}

	List<int> multiply_integer(int number) { 
		List<int> result;
		Node<T>* tmp = first;
		int listnumber = 0;
		while (tmp) {
			listnumber *= 10;
			listnumber += tmp->elem;
			tmp = tmp->next;
		}
		listnumber *= number;
		while (listnumber > 0) {
			result.push_front(listnumber % 10);
			listnumber /= 10;
		}
		return result;
	}

	void print() {
		auto tmp = first;
		while (tmp) {
			std::cout << tmp->elem << ' ';
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}	

	void merge_sort() {
		if (!first->next) {
			Node<T>* center = first;
			Node<T>* tmp = first;
			Node<T>* prev = center;
			while (tmp) {
				if (tmp->next)
					tmp = tmp->next->next;
				else break;
				prev = center;
				center = center->next;
			}
			if (prev == first->next) return;
			List rightList(prev->next);
			prev->next = nullptr;
			merge_sort();	
			rightList.merge_sort();
			this->merge_sorted_lists(rightList);
			//std::cout << "leftList  ";
			//node_print(leftList);
			//std::cout << "rightList  ";
			//node_print(rightList);
		}
	};

	Node<T>* merge_sorted_nodes(Node<T>* ptr1, Node<T>* ptr2) {
		Node<T>* list1 = ptr1;
		Node<T>* list2 = ptr2;
		Node<T>* res = new Node<T>();
		Node<T>* tmp = res;
		while (list1 && list2) {
			if (list1->elem < list2->elem) {
				tmp->next = list1;
				tmp = list1;
				list1 = list1->next;
			}							  
			else {
				tmp->next = list2;
				tmp = list2;
				list2 = list2->next;
			}
		}
		while (list2) {
			tmp->next = list2;
			tmp = list2;
			list2 = list2->next;
		}
		while (list1) {
			tmp->next = list1;
			tmp = list1;
			list1 = list1->next;
		}
		Node<T>* tmp1 = res->next;
		Node<T>* tmp2 = res->next;
		delete res;
		while (tmp2) {
			std::cout << tmp2->elem << ' ';
			tmp2 = tmp2->next;
		}
		std::cout << std::endl;
		return tmp1;
	};

	Node<T>* slice_list(Node<T>* prev) {
		Node<T>* fast = prev;
		Node<T>* slow = prev;
		if (!prev->next)
			return prev;
		if (!prev->next->next) {
			fast = prev->next;
			prev->next = nullptr;
			return fast;
		}
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		Node<T>* slice = slow->next;
		slow->next = nullptr;
		return slice;
	}

	Node<T>* find_loop_start(){
		Node<T>* slow = first;
		Node<T>* fast = first;
		while (fast && fast->next){
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) break;
		}
		if (fast || slow) throw std::invalid_argument("This list has no loop");
		slow = first;
		while (slow != fast) {
			slow = slow->next;
			fast = fast->next;
		}
		return slow;
	}

	void node_print(Node<T>* nod) {
		Node<T>* tmp = nod;
		while (tmp) {
			std::cout << tmp->elem << ' ';
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}
};




class ListList {
public:
	struct NNode {
		NNode* data;
		NNode* next;
		int num;
		NNode() {
			next = nullptr;
			data = nullptr;
			num = 0;
		}
	};	   
	NNode* first = nullptr;
	ListList() {};
	ListList(size_t n) {
		first = new NNode();
		NNode* tmp = first;
		for (int i = 1; i < n; i++) {
			tmp->num = i;
			tmp->next = new NNode();
			tmp = tmp->next;
		}
	}
	~ListList() {
		NNode* tmp = first;
		auto tmp2 = tmp;
		while(tmp) {
			tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
	}
	NNode* get_node(size_t pos) {
		NNode* tmp = first;
		for (int i = 0; i < pos; i++) {
			tmp = tmp->next;
		}
		return tmp;
	}
	ListList(ListList& list) {
		if (list.first == nullptr) throw std::invalid_argument("List is empty");
		if (list.first->next == nullptr) { 
			first = new NNode();
			if (list.first->data)first->data = first;		
		} // list is 1 in length, no need to copy anything except first element and data pointer
		else {
			NNode* tmp = list.first;
			while (tmp != nullptr) {
				NNode* tmp3 = tmp->next;
				tmp->next = new NNode();  		 // creating new nodes to copy original list
				tmp->next->num = tmp->num;		 // copying all elements (essentially making list 0123->00112233)
				tmp->next->next = tmp3;
				tmp = tmp3;
			}

			tmp = list.first;
			while (tmp) {
				tmp->next->data = tmp->data->next;
				tmp = tmp->next->next;				// copying data pointer of the original list to the data pointer of copied list shifted 1 to right, where all newly created nodes are
			}

			tmp = list.first;
			first = tmp->next;
			NNode* tmp1 = first;
			while (tmp->next->next) {
				tmp->next = tmp1->next;			//dividing list in two - original stays untouched and copy retains the structure of original
				tmp = tmp->next;
				tmp1->next = tmp->next;
				tmp1 = tmp1->next;
			}
			tmp->next = tmp1->next;			//dividing list in two - original stays untouched and copy retains the structure of original
			tmp1->next = nullptr;
		}
	}

	void print() {
		NNode* tmp = first;
		while (tmp) {
			std::cout << tmp->num << ' ';
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}

	void print_data() {
		NNode* tmp = first;
		while(tmp) {
			std::cout << tmp->data->num << ' ';
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}
};