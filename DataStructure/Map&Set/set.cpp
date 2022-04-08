/*
      File: set.cpp
      Name: Yongjin Lu
      Date: 2019/3/21
*/
 #include "set.h"
// set implemented with doubly and head sentinal linked list

// constructs empty set
Set::Set(){
	_head = new Elem;
	_tail = new Elem;
	_head->prev = nullptr;
	_head->next = _tail;
	_tail->next = nullptr;
	_tail->prev = _head;
  	_size = 0;
}
  
// copy constructor (you can call copyCode method)
Set::Set(const Set &rhs){
	copyCode(rhs);
}
   
// destructor (you can call destructCode method)
Set::~Set(){
	destructCode();
}


// Constructs a container with as many elements as the range [first,last), 
// with each element constructed from its corresponding element in that range.
Set::Set(ELEMENT_TYPE* first, ELEMENT_TYPE* last){
	_head = new Elem;
	_tail = new Elem;
	_head->prev = nullptr;
	_head->next = _tail;
	_tail->next = nullptr;
	_tail->prev = _head;
  _size = 0;
	while( first != last ){
		insert(*first);
		++first;
	}
	
	
}
   
// assignment operator (you can call destructCode and copyCode methods)
Set& Set::operator=(const Set &rhs){
	if(*this == rhs)
		return *this;
	destructCode();
	copyCode(rhs);
	return *this;
}
   
// insert an int into the set;
void Set::insert(ELEMENT_TYPE s){
	if(_head->next == _tail){
		Elem *e = new Elem;
		e->info = s;
		_head->next = e;
		_tail->prev = e;
		e->next = _tail;
		e->prev = _head;
		_size++;
	}
	else{
		Elem *cur = _head->next;
		while(cur != _tail){
			if(s.size() < (cur->info).size()){
				Elem *e = new Elem;
				e->info = s;
				e->prev = cur->prev;
				cur->prev->next = e;
				cur->prev = e;
				e->next = cur;
				_size++;
				break;
			}
			else if(cur->next == _tail && (cur->info).size() < s.size()){
				Elem *e = new Elem;
				e->info = s;
				e->prev = _tail->prev;
				_tail->prev->next = e;
				_tail->prev = e;
				e->next = _tail;
				_size++;
				break;
			}
			else
				cur = cur->next;
		}
	}
}
    
// remove an int from the set; 
void Set::erase(ELEMENT_TYPE s){
    Elem *cur = _head->next;
    while(cur != _tail && cur->info!=s)
        cur = cur->next;
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    _size--;
    delete cur;
}
    
// remove all elements from set
void Set::clear(){
	Elem *cur  = _head->next;
	while(cur != _tail){
		Elem *e = cur->next;
		delete cur;
		cur = e;
	}
	_head->next = _tail;
	_tail->prev = _head;
	_size = 0;
}


// return size of the set
int Set::size() const{
	return _size;
}

// return an iterator to the element if val is found, or set::end() otherwise
Set::Iterator Set::find(ELEMENT_TYPE s) const{
	Set::Iterator it;
	Set se;
	for( it = se.begin(); it!=se.end(); it++)
	{
		if( *it == s )
			return it;
		else
			return se.end();
		}	
	}
// return an iterator pointing at the begining of the list
Set::Iterator Set::begin() const{
	Elem *cur = _head->next;	
	return Iterator(cur);
	}
	
	
// return an iterator pointing at one element beyond the end of list
    Set::Iterator Set::end() const{
    	Elem *cur = _tail->prev;	
	return Iterator(cur);
	  }
    	
// return an reverse iterator pointing at the reverse beginning of the list
    Set::Reverse_Iterator Set::rbegin() const{
    	Elem *cur = _tail->prev;	
	return Iterator(cur);
	  }
    
 // return an reverse iterator pointing at one element beyond the beginning of list
    Set::Reverse_Iterator Set::rbegin() const{
    	Elem *cur = _head->next;	
	return Iterator(cur);
	  }
	



// common code for copy constructor and assignment operator
void Set::copyCode(const Set & rhs){
	_head = new Elem;
	_tail = new Elem;
	_head->prev = nullptr;
	_head->next = _tail;
	_tail->next = nullptr;
	_tail->prev = _head;
	_size = rhs._size;
	if(rhs._head == nullptr)
		_head = _tail = nullptr;
	else{
		Elem *e = rhs._head->next;
		Elem *newHead = _head;
		while(e != rhs._tail){
			newHead->next = new Elem;
			newHead->next->prev = newHead;
			newHead = newHead->next;
			newHead->info = e->info;
			e = e->next;
		}
		_tail->prev = newHead;
		newHead->next = _tail;
	}
}
    
// common code for deallocation (destructor and assignment operator)
void Set::destructCode(){
	clear();
	delete _head;
	delete _tail;
	_size = 0;
}
