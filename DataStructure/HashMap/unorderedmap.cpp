// Below are the stubs for SOME methods
// Make sure all methods in unorderedmap.h are implemented

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::UnorderedMap(){
	// entrysize is 0
	entrysize = 0;
	// create a empty table
	array = new Entry *[entrysize];

	// set default tablesize is 101
	tablesize = 101;
	for(int i = 0; i<tablesize; i++){
		array[i] = nullptr;
	}
	
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::~UnorderedMap(){
	for( int i = 0; i < tablesize; i++){
		Entry* e = array[i];
		while(e){
			Entry * tem = e;
			delete tem;
			tem = NULL;
			e = e->next;
		}
	}
	delete array;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::insert(const KEY & newkey, const T & data){
	// get index
	H index = hash(newkey);
	// the key-value elem
	Entry *e = new Entry(newkey, data);
	e->next = array[index];
	array[index] = e;
	
	return true;
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::erase (const KEY& newkey){
	H index = hash(newkey);
	Entry *e = array[index];
	if( e == NULL)
		return false;
	
	Entry *cur = e;
	//find list
	while(cur){
		if( cur->key == newkey){
			cur->next = cur->next->next;
			delete cur;
			cur = NULL;
			return true;
		}
		else{ // iter the list
			cur = cur ->list
		}
	}
	return false;
}

template <typename KEY, typename T, typename H>
void UnorderedMap<KEY, T, H>::rehash( ){
	double load_factor = entrysize/tablesize;
	if(load_factor == 2){
		tablesize = tablesize * 2;
	}

}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::find( const KEY & newkey ) const{
	H index = hash(newkey);
	Entry *e;
	for(int i = 0; i < tablesize; i++){
		if( array[i]->key == index)
			e = array[i]->data;
		else
			return this->end()
	}
	return Iterator(e);

}


template<typename KEY, typename T, typename H>
T& UnorderedMap<KEY, T, H>::operator[](const KEY & key){
	H index = hash(key);
	Entry *e = array[index];
	if(e != NULL)
		return e->data;
	else:
		return NULL;
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::Iterator::operator++(int){
	
	return Iterator(NULL);
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::begin() const{
	Entry * cur;
	for(int i = 0; i < tablesize; i++){
		if(array[i] != NULL)
			cur = array[i]->data;
	}
	return Iterator(cur);
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::Iterator UnorderedMap<KEY, T, H>::end() const{
	Entry * cur;
	for(int i = tablesize; i > 0; i--){
		if(array[i] != NULL)
			cur = array[i]->data;
	}
	
	Entry *l = cur;
	while(l){
		l = l -> next;
	}
	return Iterator(l);
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::Entry* UnorderedMap<KEY, T, H>::Iterator::operator->(){
	
}

template <typename KEY, typename T, typename H>
UnorderedMap<KEY, T, H>::Entry& UnorderedMap<KEY, T, H>::Iterator::operator*(){
	
}


template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator!=(Iterator it){
	
}

template <typename KEY, typename T, typename H>
bool UnorderedMap<KEY, T, H>::Iterator::operator==(Iterator it){
	
}

// Internal method to test if a positive number is prime (not efficient)
bool isPrime( int n ){
	if( n == 2 || n == 3 )
		return true;
	if( n == 1 || n % 2 == 0 )
		return false;
	for( int i = 3; i * i <= n; i += 2 )
		if( n % i == 0 )
			return false;
	return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int nextPrime( int n ){
	if( n % 2 == 0 )
		n++;
	for( ; !isPrime( n ); n += 2 )
		;
	return n;
}

