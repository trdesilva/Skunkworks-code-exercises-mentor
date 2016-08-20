#ifndef MYTRIE_H
#define MYTRIE_H

#include <map>
#include <string>

// Trie class for holding a list of words.
class MyTrie
{
private:
	MyTrie* parent;
	bool terminal; // whether this node's ancestry forms a full word; NOT whether this node is a leaf
	
	std::map<char, MyTrie*> children;
	
protected:
	MyTrie(MyTrie* parent, bool terminal);
	
public:
	MyTrie();
	
	MyTrie* getParent();
	MyTrie* getChild(char letter);
	bool isTerminal();
	
	void addChild(char letter, bool terminal);
	
	MyTrie* getDeepChild(std::string path);
	void addDeepChild(std::string path);
	bool hasChildren();
};
#endif
