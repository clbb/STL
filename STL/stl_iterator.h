#pragma once
#include<iostream>
#include<assert.h>
using namespace std;


template <class T>
struct ListNode
{
	T _data;
	ListNode<T>* _prev;
	ListNode<T>* _next; 
	ListNode(const T& data)
		:_data(data)
		,_prev(NULL)
		,_next(NULL)
	{}
};
template <class T,class Ref,class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T,T&,T*> Iterator;
	typedef ListIterator<T,const T&,const T*> ConstIterator;
	typedef ListIterator<T,Ref,Ptr> Self;
	
	ListIterator()
	{}
	ListIterator(Node* node)
		:_ptr(node)
	{}
	ListIterator(const Iterator& x)
		:_ptr(x._ptr)
	{}
	
	Self& operator++()
	{
		_ptr = (*_ptr)._next;
		return(*this);
	}
	Self operator++(int)
	{
		Self tmp = *this;
		++(*this);
		return tmp;
	}
	Self& operator--()
	{
		_ptr = (*_ptr)._prev;
		return(*this);
	}
	Self operator--(int)
	{
		Self tmp = (*this);
		--(*this);
		return tmp;
	}

	Ref operator*()
	{
		return _ptr->_data;
	}
	Ptr operator->()
	{
		return &(_ptr->_data);
	}
	
	bool operator==(const Self& it)
	{
		return _ptr == it._ptr;
	}
	bool operator!=(const Self& it)
	{
		return _ptr != it._ptr;
	}
	Node* _ptr;
}; 
//有头节点 便于管理
//DCList
template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef ListIterator<T,T&,T*> Iterator;
	typedef ListIterator<T,const T&,const T*> ConstIterator;
public:
	List()
		:_head(new Node(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	Iterator Begin() const
	{
		return _head->_next;
	}
	Iterator End() const
	{
		return _head;
	}
	Iterator Begin()
	{
		return _head->_next;
	}
	Iterator End()
	{
		return _head;
	}
	Iterator Insert(Iterator pos,const T& x)//pos之前
	{
		Node* tmp = new Node(x);
		Node* cur = pos._ptr;
		Node* prev = cur->_prev;

		tmp->_next = cur;
		tmp->_prev = prev;
		prev->_next = tmp;
		cur->_prev = tmp;
		return tmp;
	}
	void Push_Back(const T& x)
	{
		Insert(End(),x);
	}
	void Push_Front(const T& x)
	{
		Insert(Begin(),x);
	}
	Iterator Earse(Iterator pos)
	{
		assert(pos._ptr && pos._ptr != _head);

		Node* cur = pos._ptr->_next;
		Node* prev = pos._ptr->_prev;

		Node* del = pos._ptr;
		prev->_next = cur;
		cur->_prev = prev;
		delete del;
		del = NULL;
		return Iterator(cur);
	}
	void Pop_Back()
	{
		Iterator tmp = End();
		Earse(--tmp);
	}	
	void Pop_Front()
	{
		Earse(Begin());
	}
protected:
	Node* _head;
};

void Testiterator()
{
	List<int> l;
	l.Push_Back(1);
	l.Push_Back(2);
	l.Push_Back(3);
	l.Push_Back(4);

	l.Push_Front(10);
	l.Push_Front(20);
	l.Push_Front(30);

	l.Pop_Back();
	l.Pop_Front();
	List<int>::ConstIterator it = l.Begin();
	while(it != l.End())
	{
		//it->_ptr->_data = 100;
		cout<<*it<<" ";
		it++;
	}
	
	cout<<endl;
}
