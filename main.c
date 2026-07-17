/*====================================================================

                    INVERTED SEARCH

======================================================================

Name        : Rakshith C
Batch No    : 26001B
Date        : 12/07/2026

## Description :

The Inverted Search project is implemented using a Hash Table,
Main Nodes, and Sub Nodes to efficiently store and search words
across multiple text files. Each unique word is stored in the
hash table along with the list of files in which it appears and
its occurrence count.

## Features :

1. Create an inverted index from multiple text files
2. Display the complete database
3. Search for a word efficiently
4. Save the database into a backup file
5. Update the database from a backup file
6. Hash table implementation for fast searching
7. Dynamic memory allocation
8. Input validation and error handling

## Supported Operations :

1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Update Database

## Example Execution :

./a.out f1.txt f2.txt f3.txt f6.txt

## Data Structures Used :

1. Hash Table
2. Singly Linked List (File List)
3. Main Node Linked List
4. Sub Node Linked List

====================================================================*/

#include "main.h"

int main(int argc, char *argv[])
{
    // Head pointer for file linked list
    file_node *head = NULL;

    // Hash table
    hash_t hash[27];

    // Flag to avoid creating database multiple times
    int create_flag = 0;

    // Store user's menu choice
    int choice;

    // Store word to search
    char word[SIZE];

    // Store save/update file name
    char save_file[SIZE];

    /* Initialize Hash Table */

    // Initialize all hash table indices
    for (int i = 0; i < 27; i++)
    {
        hash[i].index = i;
        hash[i].main_link = NULL;
    }

    /* Check command line arguments */

    // Check whether file names are provided
    if (argc < 2)
    {
        printf("ERROR : Pass the file names\n");
        printf("Usage : ./a.out file1.txt file2.txt ...\n");
        return FAILURE;
    }

    /* Validate all files */

    // Validate every command-line file
    for (int i = 1; i < argc; i++)
    {
        // Skip invalid files
        if (validate_file(argv[i]) == FAILURE)
            continue;

        // Check duplicate file
        if (check_duplicate(head, argv[i]) == SUCCESS)
        {
            printf("INFO : %s is duplicate\n", argv[i]);
            continue;
        }

        // Insert valid file into linked list
        if (insert_file(&head, argv[i]) == FAILURE)
        {
            printf("ERROR : Unable to insert %s\n", argv[i]);
            continue;
        }

        printf("INFO : %s added successfully\n", argv[i]);
    }

    // Check whether any valid file exists
    if (head == NULL)
    {
        printf("ERROR : No valid files found\n");
        return FAILURE;
    }

    // Display menu continuously
    while (1)
    {
        printf("\n=====================================\n");
        printf("      INVERTED SEARCH DATABASE\n");
        printf("=====================================\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Word\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice : ");

        // Read user choice
        scanf("%d", &choice);

        // Perform selected operation
        switch (choice)
        {
            case 1:
            {
                // Check whether database is already created
                if (create_flag)
                {
                    printf("INFO : Database already created\n");
                    break;
                }

                // Create the database
                if (create_database(head, hash) == SUCCESS)
                {
                    printf("INFO : Database created successfully\n");
                    create_flag = 1;
                }
                else
                {
                    printf("ERROR : Failed to create database\n");
                }

                break;
            }

            case 2:
            {
                // Display the database
                if (display_database(hash) == FAILURE)
                    printf("ERROR : Database is empty\n");

                break;
            }

            case 3:
            {
                // Read word to search
                printf("Enter the word to search : ");
                scanf("%49s", word);

                // Search the word
                if (search_database(hash, word) == FAILURE)
                    printf("INFO : Word not found\n");

                break;
            }

            case 4:
            {
                // Read save file name
                printf("Enter save file name : ");
                scanf("%49s", save_file);

                // Save database
                if (save_database(hash, save_file) == SUCCESS)
                    printf("INFO : Database saved successfully\n");
                else
                    printf("ERROR : Failed to save database\n");

                break;
            }

            case 5:
            {
                // Read backup file name
                printf("Enter backup file name : ");
                scanf("%49s", save_file);

                // Update database from backup
                if (update_database(hash, save_file) == SUCCESS)
                {
                    printf("INFO : Database updated successfully\n");
                    create_flag = 1;
                }
                else
                {
                    printf("ERROR : Failed to update database\n");
                }

                break;
            }

            case 6:
            {
                // Exit the program
                printf("Exiting...\n");
                return SUCCESS;
            }

            default:
            {
                // Invalid menu option
                printf("ERROR : Invalid Choice\n");
            }
        }
    }

    return SUCCESS;
}