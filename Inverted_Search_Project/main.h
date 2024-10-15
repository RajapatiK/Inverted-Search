#ifndef MAIN_H
#define MAIN_H

#include<stdio.h> // Standard I/O functions

typedef enum
{
    FAILURE, // Enumeration for failure status
    SUCCESS // Enumeration for success status
}Status;

//structure to store the file node 
typedef struct file_node
{
    char data[20]; 
    struct file_node *link; 
}list;

//strcuture to store the subnode
typedef struct sub_node
{
    char f_name[20]; 
    int w_count; 
    struct sub_node *link; 
}sub_node_t;

//structure to store the main node
typedef struct node
{
    char word[20]; 
    struct node *link;
    sub_node_t *sub_link;
    int f_count; 
}main_node_t;

//structure to store the hash table
typedef struct hash_node
{
    int index; 
    main_node_t *link; 
}hash_t;

Status read_and_validate(list **head, char *argv); // Function to read and validate input
Status create_list(list **head, char *data); // Function to create a linked list
Status create_DB(hash_t *arr); // Function to create a database
Status read_datafile(list *head, hash_t *arr); // Function to read data from a file
Status display_DB(hash_t *arr); // Function to display the database
Status save_DB(hash_t *arr); // Function to save the database
Status search_DB(hash_t *arr); // Function to search in the database
Status update_DB(hash_t *arr, list **head); // Function to update the database

#endif // MAIN_H

