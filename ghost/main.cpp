#include "MyTrie.h"
#include <iostream>

int main(int argc, char** argv)
{
	MyTrie* trie = new MyTrie();
	trie->addChild('a', false);
	trie->getChild('a')->addChild('b', false);
	trie->getDeepChild("ab")->addChild('c', true);
	
	MyTrie* word = trie->getDeepChild("abc");
	if(word->isTerminal())
		std::cout << "true";
	return 0;
}
