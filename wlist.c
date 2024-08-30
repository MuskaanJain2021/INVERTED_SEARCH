#include "inverted_search.h"


Wlist* create_wlist(void) {
    Wlist *new_node = (Wlist*)malloc(sizeof(Wlist));
    if (new_node == NULL) {
        perror("Failed to allocate memory for Wlist");
        exit(EXIT_FAILURE);
    }
    // Initialize members of Wlist
    new_node->file_count = 0;
    new_node->Tlink = NULL;
    new_node->link = NULL;
    return new_node;
}