trietraverse:test5.o trie.o heap.o myfile.o 
	gcc test5.o trie.o myfile.o heap.o -o trietraverse -lm

test5.o:test5.c trie.h gttypes.h heap.h
	gcc -c test5.c -o test5.o

trie.o:trie.c trie.h gttypes.h myfile.h heap.h
	gcc -c trie.c -o trie.o -lm

heap.o:heap.c heap.h gttypes.h
	gcc -c heap.c -o heap.o

myfile.o:myfile.c myfile.h gttypes.h
	gcc -c myfile.c -o myfile.o

clean:
	rm -rf *.o trietraverse *result*
