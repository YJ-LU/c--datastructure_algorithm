
// Minimal Priority Queue implemented with a binary heap
// Stores item of type T

// default constructor, construct an empty heap
template< class T, int MAX_SIZE >
PQueue<T,MAX_SIZE>::PQueue(){
	_size = 0;
	for(int i = 0; i < MAX_SIZE; i++)
		_array[i]=0; 
}

// construct a heap from an array of elements
template< class T, int MAX_SIZE >
PQueue<T,MAX_SIZE>::PQueue(T* items, int size){
	_size = size;
	for(int i = 0; i < size; i++)
		_array[i+1]=items[i];
	for(int i = _size/2; i > 0; i--)
		moveDown(i);
}

// insert an item; duplicates are allowed.
template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::insert(T data){
	if(isEmpty()){
		_array[1] = data;
		_size++;
	}
	else{
		_array[++_size] = data;
		moveUp();
	}
}

// return the smallest item from the queue
template< class T, int MAX_SIZE >
T PQueue<T,MAX_SIZE>::findMin(){
	if(isEmpty())
		return 0;
	else
		return _array[1];
}

// remove the smallest item from the queue
template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::deleteMin(){
	if(isEmpty())
		return;
	else{
		_array[1] = _array[_size];
		_size--;
		moveDown(1);
	}
}

// test if the priority queue is logically empty
template< class T, int MAX_SIZE >
bool PQueue<T,MAX_SIZE>::isEmpty(){
	return (size() == 0) ? true : false;
}

// return queue size
template< class T, int MAX_SIZE >
int PQueue<T,MAX_SIZE>::size(){
	return _size;
}

// linear heap construction
template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::buildHeap(){
	for(int i = _size/2; i > 0; i--)
		moveDown(i);
}

// move down element at given index
template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::moveDown(int index){
	int tmpData = _array[index];
	int childIndex;
	while(index <= size()/2){
		childIndex = 2*index;
		if(childIndex != _size && _array[childIndex+1] < _array[childIndex])
			childIndex++;
		if(tmpData <= _array[childIndex])
			break;
		else
			_array[index] = _array[childIndex];
		index = childIndex;
	}
	_array[index] = tmpData;
}

// move up the last element in the heap array
template< class T, int MAX_SIZE >
void PQueue<T,MAX_SIZE>::moveUp(){
	if(isEmpty())
		return;
	int lastElem = _size;
	while(lastElem > 1){
		int parent = lastElem/2;
		if(_array[lastElem] < _array[parent]){
			int tmpData = _array[lastElem];
			_array[lastElem] = _array[parent];
			_array[parent] = tmpData;
			lastElem /= 2;
		}
		else
			break;	
	}
}
