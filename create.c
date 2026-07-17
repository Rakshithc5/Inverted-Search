#include "main.h"

/* Function Prototypes */
int get_index(char *word);
main_node *create_main_node(char *word, char *filename);
sub_node *create_sub_node(char *filename);

/*----------------------------------------------------------------*/
/* Get Hash Index */
/*----------------------------------------------------------------*/

int get_index(char *word)
{
    // Convert first character to lowercase
    char ch = tolower(word[0]);

    // Return index for alphabetic characters
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a';

    // Return 26 for non-alphabetic characters
    return 26;
}

/*----------------------------------------------------------------*/
/* Create Main Node */
/*----------------------------------------------------------------*/

main_node *create_main_node(char *word, char *filename)
{
    // Allocate memory for main node
    main_node *mnew = malloc(sizeof(main_node));

    // Check memory allocation
    if (mnew == NULL)
        return NULL;

    // Copy the word into the main node
    strcpy(mnew->word, word);

    // Initialize file count
    mnew->file_count = 1;

    // Initialize main link
    mnew->main_link = NULL;

    // Create first sub node
    mnew->sub_link = create_sub_node(filename);

    // Check sub node creation
    if (mnew->sub_link == NULL)
    {
        free(mnew);
        return NULL;
    }

    return mnew;
}

/*----------------------------------------------------------------*/
/* Create Sub Node */
/*----------------------------------------------------------------*/

sub_node *create_sub_node(char *filename)
{
    // Allocate memory for sub node
    sub_node *snew = malloc(sizeof(sub_node));

    // Check memory allocation
    if (snew == NULL)
        return NULL;

    // Copy file name
    strcpy(snew->file_name, filename);

    // Initialize word count
    snew->word_count = 1;

    // Initialize sub link
    snew->sub_link = NULL;

    return snew;
}

/*----------------------------------------------------------------*/
/* Create Database */
/*----------------------------------------------------------------*/

Status create_database(file_node *head, hash_t *hash)
{
    FILE *fp;

    // Store each word from the file
    char word[SIZE];

    // Traverse all input files
    while (head != NULL)
    {
        // Open the current file
        fp = fopen(head->file_name, "r");

        // Skip if file cannot be opened
        if (fp == NULL)
        {
            head = head->link;
            continue;
        }

        // Read words one by one
        while (fscanf(fp, "%49s", word) == 1)
        {
            // Calculate hash index
            int index = get_index(word);
            /* Hash table empty */

        if (hash[index].main_link == NULL)
{
    main_node *mnew = create_main_node(word, head->file_name);

    if (mnew == NULL)
    {
        fclose(fp);
        return FAILURE;
    }

    hash[index].main_link = mnew;

    continue;
}
            /* Continue in Part-2 */
            main_node *mtemp = hash[index].main_link;
            main_node *prev = NULL;

            /* Search for the word in main node list */
            while (mtemp != NULL)
            {
                /* Word found */
                if (strcmp(mtemp->word, word) == 0)
                {
                    sub_node *stemp = mtemp->sub_link;
                    sub_node *sprev = NULL;

                    /* Search file in sub node list */
                    while (stemp != NULL)
                    {
                        if (strcmp(stemp->file_name, head->file_name) == 0)
                        {
                            /* Same file, increment word count */
                            stemp->word_count++;
                            break;
                        }

                        sprev = stemp;
                        stemp = stemp->sub_link;
                    }

                    /* File not present, create new sub node */
                    if (stemp == NULL)
                    {
                        sub_node *snew = create_sub_node(head->file_name);

                        if (snew == NULL)
                        {
                            fclose(fp);
                            return FAILURE;
                        }

                        sprev->sub_link = snew;
                        mtemp->file_count++;
                    }

                    break;
                }

                prev = mtemp;
                mtemp = mtemp->main_link;
            }

            /* Word not found, create new main node */
            if (mtemp == NULL)
            {
                main_node *mnew =
                    create_main_node(word, head->file_name);

                if (mnew == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                if (prev == NULL)
{
    hash[index].main_link = mnew;
}
else
{
    prev->main_link = mnew;
}
            }
        }

        fclose(fp);

        head = head->link;
    }

    return SUCCESS;
}