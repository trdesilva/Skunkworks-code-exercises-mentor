all: player trie handler main
player: GhostPlayer.h HumanGhostPlayer.h HumanGhostPlayer.cpp
	g++ -c GhostPlayer.h HumanGhostPlayer.h HumanGhostPlayer.cpp
trie: MyTrie.h MyTrie.cpp
	g++ -c MyTrie.h MyTrie.cpp
handler: player trie GhostGameHandler.h GhostGameHandler.cpp
	g++ -c HumanGhostPlayer.o MyTrie.o GhostGameHandler.h GhostGameHandler.cpp
main: player trie handler main.cpp
	g++ HumanGhostPlayer.o MyTrie.o GhostGameHandler.o main.cpp -o GhostGame
clean:
	rm *.h.gch
	rm *.o
	rm GhostGame
