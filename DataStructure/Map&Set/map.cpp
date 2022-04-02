// A generic Map implemented with right-threaded BST
// BST is not balanced

#include <map> // helper container for thread copying

template <typename KEY, typename T>
Map<KEY, T>::Map(){
	// create a dummy root node
	_root = new Elem;
	_root->left = _root;  // empty tree
	_root->right = 0;
	_root->rightThread = false;
	_size = 0;

}

template <typename KEY, typename T>
void Map<KEY, T>::destructCode(Elem *& p){
	if( p == nullptr )
		return;
	else{
		if( p->left != nullptr )
			destructCode( p->left );
	  if( !p->rightThread )
	  	destructCide( p->right );
	  }
	  delete p;
	}


// copy constructor 
template <typename KEY, typename T>
Map<KEY, T>::Map(const Map<KEY,T> &v){
	// if empty tree
	if (v._root == v._root->left){
		_root = new Elem;
		_root->left = _root;  // empty tree
		_root->right = 0;
		_size = 0;
	} else {
		_root = new Elem;
		_root->left = _root;
		_root->right = 0;
		copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes
		copyThread(_root, v._root); // to copy the threading; must pass dummy nodes to complete the threads
		_size = v._size;
	}
} 

// construct a key-element map to rethread the new tree
// the map contains all nodes key values and their corresonding elem node address 
// for furture lookup in setting up threads
template <typename KEY, typename T>
void Map<KEY, T>::addToMap(Elem* root, map<KEY, Elem*> &keyElemMap){
	if (root) {
		keyElemMap[root->key] = root; 
		addToMap(root->left, keyElemMap);
		if (!root->rightThread)
			addToMap(root->right, keyElemMap);
	}
}

// common copy code for thread copying
template <typename KEY, typename T>
void Map<KEY, T>::copyThread(Elem* &newRoot, Elem* origRoot){
	// construct the key-element map for new and orig tree
	map<KEY, Elem*> newKeyElemMap; 
	map<KEY, Elem*> origKeyElemMap;
	addToMap(newRoot->left, newKeyElemMap);
	addToMap(origRoot->left, origKeyElemMap);

	// start at the last element in the tree, which threads to root
	typename std::map<KEY, Elem*>::reverse_iterator it = origKeyElemMap.rbegin();
	newKeyElemMap[it->first] -> rightThread = true;
	newKeyElemMap[it->first] -> right = newRoot;
	
	// then thread the rest of the tree backwardly 
	it++;
	while(it != origKeyElemMap.rend()){
		if (it->second->rightThread){
			newKeyElemMap[it->first] -> rightThread = true;
			newKeyElemMap[it->first] -> right = newKeyElemMap[ origKeyElemMap[it->first]->right->key ];
		}
		it++;
	} 
}

// common copy code for deep copy a tree without copying threads
template <typename KEY, typename T>
void  Map<KEY,T>::copyCode(Elem* &newRoot, Elem* origRoot){
	if (origRoot == 0)
		newRoot = 0;
	else{
		newRoot = new Elem;
		newRoot->key = origRoot->key;
		newRoot->data = origRoot->data;
		newRoot->rightThread = origRoot->rightThread; 
		copyCode(newRoot->left, origRoot->left);
		if (!origRoot->rightThread) 
			copyCode(newRoot->right, origRoot->right);
	}
} 


// helper method for inserting record into tree.
template <typename KEY, typename T>
bool Map<KEY,T>::insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft){
	Elem* cur;
	//if( cur == _root || cur == 0 )
}


// insert an element into the Map; return true if successful
template <typename KEY, typename T>
	bool Map<KEY,T>::insert(KEY key, T data){
		if(insert(_root->left,key,data,_root) ){
			_size++;
			return true;
		}
		return false;
	}

	// remove an element from the Map; return true if successful
template <typename KEY, typename T>
	bool Map<KEY,T>::erase(KEY key){
		if(erase(key)){
			_size--;
			return true;
		}
		return true;
			
	}



template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::find(KEY key) const{
	Elem* cur = _root->left;
	while( cur != _root&& cur != nullptr ){
	if( cur->key == key )
		return Iterator(cur);
	if( key < cur->key )
		cur = cur->left;
	else{
		if( cur->rightThread)
			return end();
		cur = cur->right;
		}
	}
	return end();
}

template <typename KEY, typename T>
T& Map<KEY, T>::operator[](KEY key){
	if( find(key) == end())
		insert(key, find(key)->data);
	return find(key)->data;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() const {  // return the left most (smallest) tree node
	// fill in here
	Elem* leftmost = _root->left;
	while( leftmost->left && leftmost != _root )
	     leftmost = leftmost->left;
	return Iterator(leftmost);
	
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const {  // return the dummy root node
	// fill in here
	Elem* rightmost = _root->right;
	while( rightmost->right && rightmost != _root )
	     rightmost = rightmost->right;
	return Iterator(rightmost);
} 


template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int){
	// fill in here
	Iterator it = *this;
	++(*this);
  return it;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem& Map<KEY, T>::Iterator::operator*(){ 
	// fill in here
	Iterator it = *this;
  return it;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::Iterator::operator->(){ 
	// fill in here
	Iterator it = *this; 
	(*this).first;
  return it;
}

template <typename KEY, typename T>
bool Map<KEY,T>::Iterator::operator==(Iterator it)
    {
    	Iterator itr;
        return  itr==it.itr;
    }

template <typename KEY, typename T>
bool Map<KEY,T>::Iterator::operator!=(Iterator it)
    {
    	Iterator itr;
        return  itr!=it.itr;
    }

template <typename KEY, typename T>
int Map<KEY, T>::size() const{
	return _size;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		if (p->right && !p->rightThread)
			printTree(out, level+1,p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << '\n';
		printTree(out, level+1,p->left);
	}
}

// outputs information in tree in inorder traversal order
template <typename KEY, typename T>
ostream& Map<KEY, T>::dump(ostream& out) const{
	if ( _root == _root->left) {// tree empty
		return out;
	}
	printTree(out, 0, _root->left);   // print tree structure
	return out;
}


// outputs using overloaded << operator
template<typename KEY, typename T>
ostream& operator<< (ostream& out, const Map<KEY, T>& v){
	v.dump(out);
	return out;
}
