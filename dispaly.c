#include "main.h"

/*------------------------------------------------------------*/
/* Function : display_database                                */
/* Description : Display complete database                    */
/*------------------------------------------------------------*/

Status display_database(hash_t *hash)
{
    // Loop variable
    int i;

    // Flag to check whether database is empty
    int flag = 0;

    // Main node pointer
    main_node *mtemp;

    // Sub node pointer
    sub_node *stemp;

    printf("\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Index\tWord\t\tFile Count\tFile Name\t\tWord Count\n");
    printf("--------------------------------------------------------------------------------------------\n");

    // Traverse all hash table indices
    for (i = 0; i < 27; i++)
    {
        // Skip empty index
        if (hash[i].main_link == NULL)
            continue;

        // Database is not empty
        flag = 1;

        // Point to first main node
        mtemp = hash[i].main_link;

        // Traverse main node list
        while (mtemp != NULL)
        {
            // Point to first sub node
            stemp = mtemp->sub_link;

            // Print main node details
            printf("[%2d]\t%-15s %-15d",
                   i,
                   mtemp->word,
                   mtemp->file_count);

            // Print first sub node
            if (stemp != NULL)
            {
                printf("%-30s %d\n",
                       stemp->file_name,
                       stemp->word_count);

                // Move to next sub node
                stemp = stemp->sub_link;
            }

            // Print remaining sub nodes
            while (stemp != NULL)
            {
                printf("\t\t\t\t\t%-29s %d\n",
                       stemp->file_name,
                       stemp->word_count);

                // Move to next sub node
                stemp = stemp->sub_link;
            }

            // Move to next main node
            mtemp = mtemp->main_link;
        }
    }

    // Check whether database is empty
    if (flag == 0)
    {
        return FAILURE;
    }

    printf("--------------------------------------------------------------------------------------------\n");

    // Display completed successfully
    return SUCCESS;
}