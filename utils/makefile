help:
	@echo "Targets available for utils are: test"

CC=gcc

test: ../dataStructures/hashTable/dependencies/murmur3.c ../dataStructures/hashTable/hashTable.c ../dataStructures/linkedList/linkedList.c ../dataStructures/triePatricia/triePatricia.c parseCSV.c
	$(CC) -o CSVTest ../dataStructures/hashTable/dependencies/murmur3.c ../dataStructures/hashTable/hashTable.c ../dataStructures/linkedList/linkedList.c ../dataStructures/triePatricia/triePatricia.c parseCSV.c