#include "main.h"

/*---------------------------------------------------------*/
/* Function : save_database                                */
/* Description : Save the database into a file             */
/*---------------------------------------------------------*/

Status save_database(hash_t *hash, char *filename)
{
    // File pointer
    FILE *fp;

    // Loop variable
    int i;

    // Main node pointer
    main_node *mtemp;

    // Sub node pointer
    sub_node *stemp;

    // Get file extension
    char *ext = strrchr(filename, '.');

    // Check whether the file has .txt extension
    if (ext == NULL || strcmp(ext, ".txt") != 0)
    {
        printf("ERROR : Save file should have .txt extension\n");
        return FAILURE;
    }

    // Open file in write mode
    fp = fopen(filename, "w");

    // Check if file opened successfully
    if (fp == NULL)
    {
        printf("ERROR : Unable to open %s\n", filename);
        return FAILURE;
    }

    /* Traverse Hash Table */

    // Traverse all hash table indices
    for (i = 0; i < 27; i++)
    {
        // Skip empty indices
        if (hash[i].main_link == NULL)
            continue;

        // Point to first main node
        mtemp = hash[i].main_link;

        // Traverse main node list
        while (mtemp != NULL)
        {
            // Write index, word and file count
            fprintf(fp, "#%d;%s;%d;",
                    i,
                    mtemp->word,
                    mtemp->file_count);

            // Point to first sub node
            stemp = mtemp->sub_link;

            // Write all sub nodes
            while (stemp != NULL)
            {
                // Write file name and word count
                fprintf(fp, "%s;%d;",
                        stemp->file_name,
                        stemp->word_count);

                // Move to next sub node
                stemp = stemp->sub_link;
            }

            // Mark end of one record
            fprintf(fp, "#\n");

            // Move to next main node
            mtemp = mtemp->main_link;
        }
    }

    // Close the file
    fclose(fp);

    // Database saved successfully
    return SUCCESS;
}