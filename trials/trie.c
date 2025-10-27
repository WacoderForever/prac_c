#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

struct trie_node{
    struct trie_node *children[ALPHABET_SIZE];
    bool is_end_of_word;
};

typedef struct trie_node trie_node_t;

trie_node_t *trie_create_node(void){
    trie_node_t *node = (trie_node_t*) malloc(sizeof(trie_node_t));
    if(node != NULL){
        node->is_end_of_word = false;
        for(int i=0;i<ALPHABET_SIZE;i++) node->children[i]=NULL;
    }
    return node;
}

void trie_insert(trie_node_t *root,const char *word){
    trie_node_t *crawler = root;
    for(int level=0;word[level] != '\0';level++){
        int index = word[level]-'a';
        if(crawler->children[index] == NULL){
            crawler->children[index] = trie_create_node();
        } 
        crawler = crawler->children[index];
    } 
    crawler->is_end_of_word=true;  
}

bool trie_search(trie_node_t *root,const char *word){
    trie_node_t *crawler = root;
    for(int level=0;word[level] != '\0';level++){
        int index = word[level]-'a';
        if(crawler->children[index] == NULL) return false;
        crawler = crawler->children[index];
    }
    return ((crawler != NULL) && (crawler->is_end_of_word));
}

bool trie_is_empty(trie_node_t *root){
    for(int i=0;i<ALPHABET_SIZE;i++){
        if(root->children[i] != NULL) return false;
    }
    return true;
}

trie_node_t *trie_delete(trie_node_t *node,const char *word,int depth){
    if(node == NULL) return NULL;
    if(word[depth] != '\0'){
        int index = word[depth] - 'a';
        node->children[index] = trie_delete(node->children[index],word,depth+1);
        if((trie_is_empty(node)) && (!node->is_end_of_word)){
            free(node);
            node = NULL;
        }
        return node;
    }
    else{
        if(node->is_end_of_word) node->is_end_of_word = false;
        if(trie_is_empty(node)){
            free(node);
            node = NULL;
        }
        return node;
    }

}

int main (void){
  char *words[] = {"hello", "world", "trie", "algorithm", "data", "structure"};
  int n = sizeof (words) / sizeof (words[0]);

  trie_node_t *root = trie_create_node ();

  for (int i = 0; i < n; i++)
    trie_insert (root, words[i]);

  printf ("Searching for words:\n");
  printf ("hello: %s\n", trie_search (root, "hello") ? "Found" : "Not Found");
  printf ("world: %s\n", trie_search (root, "world") ? "Found" : "Not Found");
  printf ("trie: %s\n", trie_search (root, "trie") ? "Found" : "Not Found");
  printf ("unknown: %s\n",trie_search (root, "unknown") ? "Found" : "Not Found");

  trie_delete (root, "world", 0);
  printf ("\nAfter deleting 'world':\n");
  printf ("world: %s\n", trie_search (root, "world") ? "Found" : "Not Found");

  // Cleanup: Implement a function to free all allocated memory

  return 0;
}