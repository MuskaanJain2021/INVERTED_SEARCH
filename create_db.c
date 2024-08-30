#include "inverted_search.h"

// Function to create a database by reading all files in the file list
void create_database(Flist *f_head, Wlist *head[])
{
    // Traverse through the file linked list
    while (f_head)
    {
        read_datafile(f_head, head, f_head->file_name);
        f_head = f_head->link;
    }
}

// Function to read a file and update the word database
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{
    // Open the file in read mode
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    char word[WORD_SIZE];

    // Read each word from the file
    while (fscanf(fptr, "%s", word) != EOF)
    {
        // Calculate the index based on the first character of the word
        int index = tolower(word[0]) - 'a';
        
        // Handle non-alphabetic characters
        if (index < 0 || index > 25)
            index = 26; // Use index 26 for non-alphabetic characters

        int flag = 1;  // Reset flag for each word

        // Check if the word is already in the list
        if (head[index] != NULL)
        {
            Wlist *temp = head[index];
            while (temp)
            {
                if (strcmp(temp->word, word) == 0)
                {
                    update_word_count(&temp, filename);
                    flag = 0;
                    break;
                }
                temp = temp->link;
            }
        }

        // If the word is not found, insert it at the end
        if (flag == 1)
        {
            insert_at_last(&head[index], word);
            // After insertion, the new word is the first node, so update its word count
            Wlist *new_word = head[index];
            update_word_count(&new_word, filename);
        }
    }

    // Close the file after processing
    fclose(fptr);

    return NULL;
}

// Function to write a word entry to the database file
void write_databasefile(Wlist *head, FILE *databasefile)
{
    if (head == NULL || databasefile == NULL)
        return;

    // Write the word and the number of files it appears in
    fprintf(databasefile, "%s %d", head->word, head->file_count);

    // Traverse the linked table for the current word and write each file info
    Ltable *link = head->Tlink;
    while (link)
    {
        fprintf(databasefile, " %s %d", link->file_name, link->word_count);
        link = link->table_link;
    }

    // Add a new line for the next word
    fprintf(databasefile, "\n");
}

// Function to update the word count for a given file
int update_word_count(Wlist **head, char *file_name)
{
    Ltable *temp = (*head)->Tlink;

    // Traverse the link table to check if the file already exists
    while (temp)
    {
        if (strcmp(temp->file_name, file_name) == 0)
        {
            // If file already exists, update the word count
            temp->word_count++;
            return SUCCESS;
        }
        temp = temp->table_link;
    }

    // If the file does not exist in the link table, create a new entry
    Ltable *new_entry = malloc(sizeof(Ltable));
    if (new_entry == NULL)
    {
        perror("Failed to allocate memory for new Ltable entry");
        return FAILURE;
    }

    new_entry->word_count = 1;
    strcpy(new_entry->file_name, file_name);
    new_entry->table_link = (*head)->Tlink; // Insert at the beginning
    (*head)->Tlink = new_entry;

    // Update file count
    (*head)->file_count++;

    return SUCCESS;
}

// Function to update the database and write it to a file
void update_database(Wlist *head[], Flist **f_head)
{
    // First, update the in-memory database by reading files
    create_database(*f_head, head);

    // Open the database file to write the updated data
    FILE *db_file = fopen("database.txt", "w");
    if (db_file == NULL)
    {
        perror("Failed to open database file for writing");
        return;
    }

    // Write the updated database to the file
    for (int i = 0; i < 27; i++)
    {
        Wlist *temp = head[i];
        while (temp)
        {
            write_databasefile(temp, db_file);
            temp = temp->link;
        }
    }

    fclose(db_file);
}

// Function to save the database with verbose output
void save_database(Wlist *head[])
{
    printf("Saving database...\n");
    FILE *db_file = fopen("database.txt", "w");
    if (db_file == NULL)
    {
        perror("Failed to open database file");
        return;
    }

    for (int i = 0; i < 27; i++)
    {
        Wlist *temp = head[i];
        while (temp)
        {
            if (temp->word != NULL)  // Ensure word is not NULL
            {
                printf("Writing word: %s with file count: %d\n", temp->word, temp->file_count);
                fprintf(db_file, "%s %d", temp->word, temp->file_count);
            }
            else
            {
                printf("Warning: Encountered NULL word in list at index %d\n", i);
            }

            Ltable *link = temp->Tlink;
            while (link)
            {
                if (link->file_name != NULL)  // Ensure file_name is not NULL
                {
                    printf("Writing file: %s with word count: %d\n", link->file_name, link->word_count);
                    fprintf(db_file, " %s %d", link->file_name, link->word_count);
                }
                else
                {
                    printf("Warning: Encountered NULL file_name in list at index %d\n", i);
                }
                link = link->table_link;
            }
            fprintf(db_file, "\n");
            temp = temp->link;
        }
    }

    fclose(db_file);
    printf("Database saved successfully.\n");
}
