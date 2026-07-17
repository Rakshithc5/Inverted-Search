#include "main.h"

/*------------------------------------------------------------*/
/* Function : search_database                                 */
/* Description : Search a word in the database                */
/*------------------------------------------------------------*/

Status search_database(hash_t *hash, char *word)
{
    // Flag to check whether database is empty
    int flag = 0;

    // Check if any hash table index contains data
    for (int i = 0; i < 27; i++)
    {
        if (hash[i].main_link != NULL)
        {
            flag = 1;
            break;
        }
    }

    // Return if database is empty
    if (flag == 0)
    {
        printf("INFO : Database is empty. Please create or update the database first.\n");
        return FAILURE;
    }

    // Hash index
    int index;

    // Main node pointer
    main_node *mtemp;

    // Sub node pointer
    sub_node *stemp;

    /* Calculate hash index */

    // Calculate index based on first character
    if (isalpha(word[0]))
        index = tolower(word[0]) - 'a';
    else
        index = 26;

    /* Check hash table empty */

    // Check whether the calculated index is empty
    if (hash[index].main_link == NULL)
    {
        printf("\nWord \"%s\" not found\n", word);
        return FAILURE;
    }

    // Point to the first main node
    mtemp = hash[index].main_link;

    /* Search main node */

    // Traverse main node list
    while (mtemp != NULL)
    {
        // Compare the word
        if (strcmp(mtemp->word, word) == 0)
        {
            printf("\n--------------------------------------------\n");
            printf("Word Found\n");
            printf("--------------------------------------------\n");

            // Display word
            printf("Word       : %s\n", mtemp->word);

            // Display number of files
            printf("File Count : %d\n\n", mtemp->file_count);

            // Point to first sub node
            stemp = mtemp->sub_link;

            printf("File Name\tWord Count\n");
            printf("--------------------------------------------\n");

            // Traverse sub node list
            while (stemp != NULL)
            {
                // Display file name and word count
                printf("%-15s %d\n",
                       stemp->file_name,
                       stemp->word_count);

                // Move to next sub node
                stemp = stemp->sub_link;
            }

            printf("--------------------------------------------\n");

            return SUCCESS;
        }

        // Move to next main node
        mtemp = mtemp->main_link;
    }

    // Word not found
    printf("\nWord \"%s\" not found\n", word);

    return FAILURE;
}