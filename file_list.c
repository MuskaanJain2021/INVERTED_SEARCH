#include "inverted_search.h"

void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    int i = 1;
    int empty;

    while (argv[i] != NULL)
    {
        empty = isFileEmpty(argv[i]);
        switch (empty) {
            case FILE_NOTAVAILABLE:
                printf("File: %s is not available\n", argv[i]);
                printf("Hence, we are not adding that file\n");
                break;

            case FILE_EMPTY:
                printf("File: %s is empty\n", argv[i]);
                printf("Hence, we are not adding that file\n");
                break;

            default:
            {
                int ret_val = to_create_list_of_files(f_head, argv[i]);

                if (ret_val == SUCCESS)
                {
                    printf("Successfully inserted the file: %s into file linked list\n", argv[i]);
                }
                else if (ret_val == REPEATATION)
                {
                    printf("File: %s is repeated, hence not added to the file linked list\n", argv[i]);
                }
                else
                {
                    printf("Failed to add the file: %s\n", argv[i]);
                }
                break;
            }
        }
        i++;
    }
}
int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        if (errno == ENOENT)
            return FILE_NOTAVAILABLE;
        perror("Error opening file"); // Provide more detail on the error
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);
    int result = (ftell(fptr) == 0) ? FILE_EMPTY : SUCCESS;
    fclose(fptr);

    return result;
}

int to_create_list_of_files(Flist **f_head, char *name)
{
    Flist *temp = *f_head;

    // Check for duplicate file names
    while (temp)
    {
        if (strcmp(temp->file_name, name) == 0)
        {
            return REPEATATION; // File already in the list
        }
        temp = temp->link;
    }

    // Create a new node
    Flist *new_node = malloc(sizeof(Flist));
    if (new_node == NULL)
    {
        perror("Memory allocation failed"); // Provide more detail on allocation failure
        return FAILURE;
    }

    strncpy(new_node->file_name, name, FNAME_SIZE - 1);
    new_node->file_name[FNAME_SIZE - 1] = '\0'; // Ensure null termination
    new_node->link = *f_head;
    *f_head = new_node;

    return SUCCESS;
}
