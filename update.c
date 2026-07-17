#include "main.h"

// Free all nodes in the database
void clear_database(hash_t *hash)
{
    // Traverse all hash table indices
    for (int i = 0; i < 27; i++)
    {
        // Point to first main node
        main_node *mtemp = hash[i].main_link;

        // Delete all main nodes
        while (mtemp != NULL)
        {
            // Point to first sub node
            sub_node *stemp = mtemp->sub_link;

            // Delete all sub nodes
            while (stemp != NULL)
            {
                // Store current sub node
                sub_node *sdel = stemp;

                // Move to next sub node
                stemp = stemp->sub_link;

                // Free current sub node
                free(sdel);
            }

            // Store current main node
            main_node *mdel = mtemp;

            // Move to next main node
            mtemp = mtemp->main_link;

            // Free current main node
            free(mdel);
        }

        // Reset hash table entry
        hash[i].main_link = NULL;
    }
}

/*------------------------------------------------------------*/
/* Function : update_database                                 */
/* Description : Update database from backup file             */
/*------------------------------------------------------------*/

Status update_database(hash_t *hash, char *filename)
{
    // File pointer
    FILE *fp;

    // Store current character
    char ch;

    // Hash index
    int index;

    // Number of files
    int file_count;

    // Word count
    int word_count;

    // Store word
    char word[SIZE];

    // Store file name
    char file_name[SIZE];

    // Main node pointers
    main_node *mtemp;
    main_node *mprev;
    main_node *mnew;

    // Sub node pointers
    sub_node *stemp;
    sub_node *sprev;
    sub_node *snew;

    // Get file extension
    char *ext = strrchr(filename, '.');

    // Validate file extension
    if (ext == NULL || strcmp(ext, ".txt") != 0)
    {
        printf("ERROR : File should have .txt extension\n");
        return FAILURE;
    }

    // Open backup file
    fp = fopen(filename, "r");

    // Check whether file opened successfully
    if (fp == NULL)
    {
        printf("ERROR : Unable to open %s\n", filename);
        return FAILURE;
    }

    // Read first character
    ch = fgetc(fp);

    // Move file pointer to beginning
    rewind(fp);

    // Check backup file format
    if (ch != '#')
    {
        printf("ERROR : Invalid backup file\n");
        fclose(fp);
        return FAILURE;
    }

    // Clear existing database
    //clear_database(hash);

    // Read each backup record
    while ((ch = fgetc(fp)) == '#')
    {
        // Read hash index
        fscanf(fp, "%d;", &index);

        // Read word
        fscanf(fp, "%[^;];", word);

        // Read file count
        fscanf(fp, "%d;", &file_count);

        // Point to first main node
        mtemp = hash[index].main_link;

        // Previous main node
        mprev = NULL;

        // Search for the word
        while (mtemp != NULL)
        {
            if (strcmp(mtemp->word, word) == 0)
                break;

            // Move to next main node
            mprev = mtemp;
            mtemp = mtemp->main_link;
        }

        // If word not found
        if (mtemp == NULL)
        {
            // Allocate memory for main node
            mnew = (main_node *)malloc(sizeof(main_node));

            // Check memory allocation
            if (mnew == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            // Copy word
            strcpy(mnew->word, word);

            // Initialize members
            mnew->file_count = 0;
            mnew->main_link = NULL;
            mnew->sub_link = NULL;

            // Read all sub nodes
            for (int i = 0; i < file_count; i++)
            {
                // Read file name
                fscanf(fp, "%[^;];", file_name);

                // Read word count
                fscanf(fp, "%d;", &word_count);

                // Allocate memory for sub node
                snew = (sub_node *)malloc(sizeof(sub_node));

                // Check memory allocation
                if (snew == NULL)
                {
                    free(mnew);
                    fclose(fp);
                    return FAILURE;
                }

                // Copy file name
                strcpy(snew->file_name, file_name);

                // Store word count
                snew->word_count = word_count;

                // Initialize link
                snew->sub_link = NULL;

                // Insert first sub node
                if (mnew->sub_link == NULL)
                {
                    mnew->sub_link = snew;
                }
                else
                {
                    // Traverse sub node list
                    stemp = mnew->sub_link;

                    while (stemp->sub_link != NULL)
                        stemp = stemp->sub_link;

                    // Link new sub node
                    stemp->sub_link = snew;
                }

                // Increment file count
                mnew->file_count++;
            }

            // Insert main node into hash table
            if (hash[index].main_link == NULL)
                hash[index].main_link = mnew;
            else
                mprev->main_link = mnew;
        }
        else
        {
            // Read all sub nodes
            for (int i = 0; i < file_count; i++)
            {
                // Read file name
                fscanf(fp, "%[^;];", file_name);

                // Read word count
                fscanf(fp, "%d;", &word_count);

                // Point to first sub node
                stemp = mtemp->sub_link;
                sprev = NULL;

                // Search for file
                while (stemp != NULL)
                {
                    if (strcmp(stemp->file_name, file_name) == 0)
                        break;

                    // Move to next sub node
                    sprev = stemp;
                    stemp = stemp->sub_link;
                }

                // If file not found
                if (stemp == NULL)
                {
                    // Allocate memory for sub node
                    snew = (sub_node *)malloc(sizeof(sub_node));

                    // Check memory allocation
                    if (snew == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }

                    // Copy file name
                    strcpy(snew->file_name, file_name);

                    // Store word count
                    snew->word_count = word_count;

                    // Initialize link
                    snew->sub_link = NULL;

                    // Insert sub node
                    if (sprev == NULL)
                        mtemp->sub_link = snew;
                    else
                        sprev->sub_link = snew;

                    // Increment file count
                    mtemp->file_count++;
                }
                else
                {
                    // Update word count
                    stemp->word_count = word_count;
                }
            }
        }

        // Skip '#' and newline
        fgetc(fp);
        fgetc(fp);
    }

    // Close backup file
    fclose(fp);

    // Database updated successfully
    return SUCCESS;
}