#include "inverted_search.h"

// Definition of the global variable
char fname[FNAME_SIZE];

// Function to update the link table for a word
int update_link_table(Wlist **head)
{
    // Allocate memory for a new Ltable node
    Ltable *new_entry = malloc(sizeof(Ltable));

    // Check for memory allocation failure
    if (new_entry == NULL)
        return FAILURE;

    // Initialize the new Ltable node
    new_entry->word_count = 1;  // Initial word count
    strcpy(new_entry->file_name, fname);  // Copy the global filename
    new_entry->table_link = NULL;  // Initialize the link to the next node in the table as NULL

    // Check if this is the first entry in the link table
    if ((*head)->Tlink == NULL)
    {
        (*head)->Tlink = new_entry;  // Point the head's Tlink to the new Ltable node
    }
    else
    {
        // Otherwise, insert the new node at the beginning of the link table
        new_entry->table_link = (*head)->Tlink;
        (*head)->Tlink = new_entry;
    }

    return SUCCESS;
}

// Function to insert a word at the end of the Wlist
int insert_at_last(Wlist **head, data_t *data)
{
    // Create a new node
    Wlist *new_node = malloc(sizeof(Wlist));

    // Check for memory allocation failure
    if (new_node == NULL)
        return FAILURE;

    // Initialize the new node
    new_node->file_count = 1;
    strcpy(new_node->word, data);
    new_node->Tlink = NULL;
    new_node->link = NULL;

    // Call update_link_table to update the link table for this word
    update_link_table(&new_node); // No need to pass fname again, it's a global variable

    // If the word list is empty, insert the first node
    if (*head == NULL)
    {
        *head = new_node;
        return SUCCESS;
    }

    // Otherwise, traverse to the end of the list and insert the node
    Wlist *temp = *head;
    while (temp->link)
    {
        temp = temp->link;
    }
    temp->link = new_node;
    
    return SUCCESS;
}
