#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie* children[26];
    int count;
};

struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int length = strlen(word);
    struct Trie* temp = pTrie;
    int trieIndex;
    for (int i = 0; i < length; i++) {
        trieIndex = word[i] - 'a';
        if (temp->children[trieIndex] == NULL) {
            temp->children[trieIndex] = createTrie();
        }
        temp = temp->children[trieIndex];
    }
    temp->count += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int length = strlen(word);
    struct Trie* temp = pTrie;
    int trieIndex;
    for (int i = 0; i < length; ++i) {
        trieIndex = word[i] - 'a';
        temp = temp->children[trieIndex];
        if (temp == NULL) {
            return 0;
        }
    }
    return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie != NULL) {
        for (int i = 0; i < 26; ++i) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
        free(pTrie);
    }
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* newTrie = (struct Trie*)malloc(sizeof(struct Trie));
    for (int i = 0; i < 26; ++i) {
        newTrie->children[i] = NULL;
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
    fscanf(ifp, "%d", &wordCount);
    for (int i = 0; i < wordCount; i++) {
        pInWords[i] = (char*)malloc(100 * sizeof(char));
        fscanf(ifp, "%s", pInWords[i]);
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
