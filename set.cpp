#include "set.h"

// constructs empty set
Set::Set(){
    _root = new TrieNode;
    _size = 0;
}

bool Set::insert( string s){
    if( find(s)){
        return false;
    }
    else{
        int len = s.size();
        Set::TrieNode *parent = _root;
        for(int i = 0; i < len; i++){
            int n = s[i]-'a';
            if(parent->child[n] == nullptr)
                parent->child[n] = new TrieNode;
            parent = parent->child[n];
        }
        parent->isWord = true;
        _size++;
        return true;

    }

}

bool Set::erase( string s ){
    if( find(s)){
        int len = s.size();
        Set::TrieNode *parent = _root;
        for(int i = 0; i < len; i++){
            int n = s[i]-'a';
            parent = parent->child[n];
        }
        parent->isWord = false;
        _size--;
        return true;
        }
        else{
            return false;
        }

}


bool Set::find( string s ){
    int len = s.size();
	if(len == 0)
		return false;
	Set::TrieNode *parent = _root;
	for(int i = 0; i < len; i++){
		int n = s[i]-'a';
		if(parent->child[n] == nullptr)
			return false;
		else
			parent = parent->child[n];
	}
	if(!parent->isWord)
		return false;
	return true;

}

int Set::size(){
    return _size;
}