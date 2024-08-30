/*Author Muskaan Jain
  Project Title: INVERTED SEARCH
  DESCRIPTION:
  
  */

#include "inverted_search.h"

// Function pointer typedefs
typedef void (*DatabaseOperationFunc)(Flist *f_head, Wlist *head[]);
typedef void (*DisplayOperationFunc)(Wlist *head[]);
typedef void (*ExitOperationFunc)();

// Initialize the linked list heads for each letter
void initialize_head(Wlist *head[]) {
    for (int i = 0; i < 27; i++) {
        head[i] = create_wlist(); // Ensure create_wlist() initializes Wlist* correctly
    }
}

// Menu option functions
void create_database_option(Flist *f_head, Wlist *head[]) {
    create_database(f_head, head);
}

void display_database_option(Wlist *head[]) {
    display_database(head);
}

void update_database_option(Flist *f_head, Wlist *head[]) {
    update_database(head, &f_head);
}

// Function to search for a word in the inverted index
void search(Wlist *head[], char *word) {
    int index = tolower(word[0]) - 'a';
    if (index < 0 || index > 25) {
        printf("Invalid word or word does not start with a letter.\n");
        return;
    }

    Wlist *temp = head[index];
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            printf("Word found: %s\n", word);
            printf("Number of files containing the word: %d\n", temp->file_count);

            Ltable *lt = temp->Tlink;
            while (lt != NULL) {
                printf("File: %s, Word Count: %d\n", lt->file_name, lt->word_count);
                lt = lt->table_link;
            }
            return;
        }
        temp = temp->link;
    }

    printf("Word '%s' not found in the database.\n", word);
}

void search_option(Wlist *head[]) {
    char search_word[WORD_SIZE];
    printf("Enter the word to search: ");
    if (scanf("%s", search_word) != 1) {
        printf("Error reading input.\n");
        // Clear input buffer to avoid infinite loop
        while (getchar() != '\n');
        return;
    }
    search(head, search_word);
}

void save_database_option(Wlist *head[]) {
    save_database(head);
}

void exit_option() {
    printf("Exiting...\n");
}

int main(int argc, char *argv[]) {
    system("clear");

    Wlist *head[27] = {NULL};  // Array of word list heads, one for each letter (a-z)
    Flist *f_head = NULL;
    initialize_head(head);    // Initialize the head array

    if (argc <= 1) {
        printf("No input files provided.\n");
        printf("Usage: ./Slist.exe f1.txt f2.txt...\n");
        return 0;
    }

    file_validation_n_file_list(&f_head, argv);

    if (f_head == NULL) {
        printf("No files are available in the file linked list\n");
        printf("Terminating process.\n");
        return 1;
    }

    DatabaseOperationFunc db_operations[] = {
        create_database_option,
        update_database_option
    };

    DisplayOperationFunc display_operations[] = {
        display_database_option,
        search_option,
        save_database_option
    };

    ExitOperationFunc exit_operation = exit_option;

    int choice;
    do {
        printf("\nSelect your choice among the following options:\n");
        printf("1. Create DATABASE\n");
        printf("2. Display Database\n");
        printf("3. Update DATABASE\n");
        printf("4. Search\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Error reading input.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                db_operations[0](f_head, head);
                break;
            case 2:
                display_operations[0](head);
                break;
            case 3:
                db_operations[1](f_head, head);
                break;
            case 4:
                display_operations[1](head);
                break;
            case 5:
                display_operations[2](head);
                break;
            case 6:
                exit_operation();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    // Free dynamically allocated memory here
    // free_memory(head, f_head);

    return 0;
}
