#include "MyTrie.h"
#include <map>
#include <stdlib.h>
#include <string>
#include <stdexcept>
#include <ctype.h>

MyTrie::MyTrie(MyTrie* parent, bool terminal)
{
	this->parent = parent;
	this->terminal = terminal;
	this->children = std::map<char, MyTrie*>();
}

MyTrie::MyTrie()
{
	this->parent = NULL;
	this->terminal = false;
	this->children = std::map<char, MyTrie*>();
}

MyTrie* MyTrie::getParent() 
{
	return parent;
}

MyTrie* MyTrie::getChild(char letter) 
{
	if(children.count(letter) > 0)
	{
		return children.at(letter);
	}
	else
	{
		return NULL;
	}
}

bool MyTrie::isTerminal() 
{
	return terminal;
}

void MyTrie::addChild(char letter, bool terminal)
{
	MyTrie* child = new MyTrie(this, terminal);
	letter = tolower(letter);
	if(letter < 'a' || 'z' < letter) throw std::invalid_argument("letter");
	children[letter] = child;
}

MyTrie* MyTrie::getDeepChild(std::string path) 
{
	if(path.length() == 0)
	{
		return this;
	}
	else
	{
		MyTrie* next = this->getChild(path[0]);
		if(next != NULL)
		{
			return next->getDeepChild(path.substr(1));
		}
		else
		{
			return NULL;
		}
	}
}

void MyTrie::addDeepChild(std::string path)
{
	if(path.size() == 0) return;
	
	char next = path[0];
	if(getChild(next) == NULL) addChild(next, path.size() == 1);
	getChild(next)->addDeepChild(path.substr(1));
}

bool MyTrie::hasChildren()
{
	return !children.empty();
}
