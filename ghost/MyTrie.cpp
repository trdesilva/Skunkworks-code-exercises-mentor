#include "MyTrie.h"
#include <map>
#include <stdlib.h>
#include <string>

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
