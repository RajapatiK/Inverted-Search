#include <string.h>
#include "main.h"
#include <stdlib.h>
#include<stdio.h>

// Function to delete a node from the linked list
void delete_node(list **head, char *data);
Status update_DB(hash_t *arr,list **head)
{
    for(int i=0;i<28;i++)// Check if the hash table is full
    {
	if(arr[i].link!=NULL)
	{
	    printf("List is Full\n");// Print message if the list is full
	    return FAILURE;
	}	    
    }
    FILE *fptr;// File pointer to open and read the file
    char data[30];// Buffer to store the file name
    printf("Enter the text file: \n");
    scanf(" %s",data);// Read the file name
    if(strstr(data,".txt"))
    {
	fptr=fopen(data,"r");// Open the file in read mode
	if(fptr!=NULL)
	{
	    fseek(fptr, 0, SEEK_END);// Move to the end of the file
	    if(ftell(fptr)!=0)// Check if the file is not empty
		fseek(fptr, 0, SEEK_SET);// Move the file pointer to the beginning		
	    else
		printf("The file is empty.\n");
	}
	else
	    printf("Error opening the file.\n");
    }
    else
	printf("The file must have a .txt extension.\n");
    char str[100];
    while(fscanf(fptr," %[^\n]",str)!=EOF) // Read each line from the file
    {
	char *token=strtok(str,"#;");// Tokenize the line using # and ; as delimiters
	int i=atoi(token);// Get the index from the token
	token=strtok(NULL,"#;");
	main_node_t *newm=malloc(sizeof(main_node_t));
	if(newm==NULL) return FAILURE;
	strcpy(newm->word,token);// Copy the word into the main node
	token=strtok(NULL,"#;");
	newm->f_count=atoi(token);// Set the file count in the main node
	newm->sub_link=NULL;
	newm->link=NULL;
	// Insert the new main node into the hash table
	if(arr[i].link==NULL)
	    arr[i].link=newm;
	else
	{
	    main_node_t *current=arr[i].link;
	    while(current->link!=NULL)
		current=current->link;// Move to the end of the list
	    current->link=newm;// Insert the new node at the end of the list
	}
	int j=0;
	sub_node_t *prevs=NULL;// Previous sub-node pointer
	while(j<newm->f_count)
	{
	    sub_node_t *news=malloc(sizeof(main_node_t));
	    if(news==NULL) return FAILURE;
	    token=strtok(NULL,"#;");// Get the file name from the token
	    delete_node(head,token);	// Delete the file name from the list    
	    strcpy(news->f_name,token);
	    token=strtok(NULL,"#;");// Get the word count from the token
	    news->w_count=atoi(token);
	    news->link=NULL;// Initialize the link to NULL
	    if(prevs==NULL)
		newm->sub_link=news;
	    else
		prevs->link=news;// Update the previous sub-node pointer
	    prevs=news;
	    j++;
	}
    }
    return SUCCESS;
}
void delete_node(list **head, char *data)
{
    if(*head==NULL)// Check if the list is empty
    {
	return;// Nothing to delete
    }
    list *temp = *head;// Temporary pointer to traverse the list
    if(strcmp(temp->data,data)==0)
    {
	list *temp = *head;// Update head to the next node
	*head = temp->link;
	free(temp);
	return;
    }
    else
    {
	list *prev = NULL;// Previous node pointer
	while(temp!=NULL)
	{
	    if(strcmp(temp->data,data)!=0)// If current node is not the one to delete
	    {
		prev=temp;
		temp=temp->link;
	    }
	    else
	    {
		prev->link= temp->link;// Skip the node to delete
		free(temp);// Free the memory of the node
		return;
	    }

	}
    }
}


