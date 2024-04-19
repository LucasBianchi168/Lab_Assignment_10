/*
COP 3502C, Spring 2024, Session 0003, Lab 0024
Lucas Bianchi, Lab Assignment 10
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie* children[26]; // 26 pointers to other trie nodes, each node representing the letters A - Z (lowercase only)
    int count; // number of times a word has appeared in the trie
};

struct Trie *createTrie(); // added function header to make the insert function more efficient

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int length = strlen(word); // get the length of the word
    struct Trie* temp = pTrie; // a temporary trie pointer to scroll through the trie
    int trieIndex; // the index of the children list
    for (int i = 0; i < length; i++) {
        trieIndex = word[i] - 'a';
        if (temp->children[trieIndex] == NULL) {
            temp->children[trieIndex] = createTrie(); // create a new trie node when necessary
        }
        temp = temp->children[trieIndex]; // scroll through the trie
    }
    temp->count += 1; // increase the number of times a word has appeared
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int length = strlen(word); // get the length of the word
    struct Trie* temp = pTrie; // a temporary trie pointer to scroll through the trie
    int trieIndex; // the index of the children list
    for (int i = 0; i < length; ++i) {
        trieIndex = word[i] - 'a';
        temp = temp->children[trieIndex];
        if (temp == NULL) {
            return 0; // if you run out of trie nodes to scroll through
        }
    }
    return temp->count; // return the number of times the word appears
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie != NULL) {
        for (int i = 0; i < 26; ++i) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]); // deallocate the children first
        }
        free(pTrie); // deallocate the current trie node
    }
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* newTrie = (struct Trie*)malloc(sizeof(struct Trie)); // allocate memory for the trie
    for (int i = 0; i < 26; ++i) {
        newTrie->children[i] = NULL; // for each child pointer, set them to NULL
    }
    newTrie->count = 0;
    return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* ifp = fopen(filename, "r");
    int wordCount;
    fscanf(ifp, "%d", &wordCount); // get the maximum amount of words to scan
    for (int i = 0; i < wordCount; i++) {
        pInWords[i] = (char*)malloc(31 * sizeof(char)); // allocate memory for each word
        fscanf(ifp, "%s", pInWords[i]); // store the word in pInWords[i]
    }
    return wordCount;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
