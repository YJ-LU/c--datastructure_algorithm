// A non-generic Map ADT implemented with a BST data structure
// The BST is not-balanced and non-threaded
#include "map.h"

Map::Map(){
	// create a dummy root node and set up an empty tree
	_root = new Elem;
	_root->left = _root;  
	_root->right = 0;
	_size = 0;

}

// copy constructor
Map::Map(const Map &v){
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
		copyCode(_root->left, v._root->left);
		_size = v._size;
	}
} 

// common copy code for deep copy a tree
void  Map::copyCode(Elem* &newRoot, Elem* origRoot){
	if (origRoot == 0)
		newRoot = 0;
	else{
		newRoot = new Elem;
		newRoot->key = origRoot->key;
		newRoot->data = origRoot->data;
		copyCode(newRoot->left, origRoot->left);
		copyCode(newRoot->right, origRoot->right);
	}
}

//assignment operator
    Map& Map::operator=(const Map &rhs)
    {
      if( this == &rhs )
      	return *this;
      _size = rhs._size;
    }
    
// insert an element; return true if successful
    bool Map::insert(KEY_TYPE s1, VALUE_TYPE s2)
    {
       if(insert(_root,s1,s2))
       	{
       		_size++;
       		return true;
       	}
       	return false;
    }
    
// helper method for inserting record into tree.
    bool Map::insert(Elem *& root, const KEY_TYPE& s1, const VALUE_TYPE& s2)
    {
		Elem *e;
		e->data = s2;
		e->key = s1;

		//insert root
		if(s1 == root->key || !root){
			root = e;
			return true;
		}

		//insert left most
		if( !root->left){
			e = root->left;
			return true;
		}

		//insert left
		if( s1 < root->key){
			if(s1 < root->key && root->left->key < s1){
				root->left = e;
				e->left = root->left->left;
				return true;
			}
			else
				return insert(root->left, s1, s2);
		}
		
		// insert right most
		if( !root->right){
			e = root->right;
			return true;
		}

        // insert right
		if(root->key < s1){
			if(root->key < s1 && s1 < root->right->key ){
				root->right = e;
				e->right = root->right->right;
				return true;
			}
			else
				return insert(root->right, s1, s2);
		}
    }
    
// remove an element; return true if successful
    bool Map::erase(KEY_TYPE s1)
    {
    	if( erase(s1) )
    	{
    		_size--;
    		return true;
    	}
    	return false;
    }
// return size of the Map
    int Map::size() const
    {
    	return _size;
    }
    		
	Map::Iterator Map::find(KEY_TYPE s) const
	{  
		Elem *cur = _root;
		while(cur){
			if(s == cur->key)
				return Iterator(cur);
			if(s < cur->key)
				cur = cur->left;
			else if( cur->key < s)
				cur = cur->right;
		}
		return this->end();
	}
	
	Map::Iterator Map::begin() const
	{
		Elem *cur = _root;
		return Iterator(cur);
		
	}
	
	Map::Iterator Map::end() const
	{
		Elem *cur = _root;
		while(cur->right){
			cur = cur->right;
		}
		return Iterator(cur);
	}
	
// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Map::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		printTree(out, level+1, p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << '\n';
		printTree(out, level+1, p->left);
	}
}

// outputs information in tree
ostream& Map::dump(ostream& out) const{
	if ( _root == _root->left) { // tree empty
		return out;
	}
	printTree(out, 0, _root->left);   // print tree structure
	return out;
}

// outputs using overloaded << operator
ostream& operator<< (ostream& out, const Map& v){
	v.dump(out);
	return out;
}
