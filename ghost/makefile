all: player trie handler main
player: GhostPlayer.h
	g++ GhostPlayer.h
trie: MyTrie.h MyTrie.cpp
	g++ -c MyTrie.h MyTrie.cpp
handler: player trie GhostGameHandler.h GhostGameHandler.cpp
	g++ -c GhostPlayer.h MyTrie.o GhostGameHandler.h GhostGameHandler.cpp
main: player trie handler main.cpp
	g++ GhostPlayer.h MyTrie.o GhostGameHandler.o main.cpp -o GhostGame
clean:
	rm *.h.gch
	rm *.o
	rm GhostGame
