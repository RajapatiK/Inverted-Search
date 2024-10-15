#include <stdio.h> 
#include <string.h> 
#include "main.h" 
#include <stdlib.h> 

Status read_and_validate(list **head, char *argv)
{
    if (strstr(argv, ".txt")) // Check if the file has a .txt extension
    {
	FILE *fptr = fopen(argv, "r"); // Open the file in read mode
	if (fptr != NULL) // Check if the file opened successfully
	{
	    fseek(fptr, 0, SEEK_END); // Move the file pointer to the end
	    if (ftell(fptr) != 0) // Check if the file is not empty
	    {
		if (create_list(head, argv)) // Create a node for the file
		{
		    printf("%s created successfully\n", argv);
		    return SUCCESS; // Return success if the list is created
		}
	    }
	    else
		printf("%s is Empty file\n", argv); // Print if the file is empty
	}
    }
    else
	printf("%s file must have a .txt extension\n", argv); // Print if the file does not have a .txt extension
}

Status create_list(list **head, char *data)
{
    list *new=malloc(sizeof(list)); // Allocate memory for a new node
    if (new==NULL)
	return FAILURE; // Return failure if memory allocation failed
    strcpy(new->data,data); // Copy data to the new node
    new->link=NULL; // Set the link of the new node to NULL
    if(*head==NULL) // Check if the list is empty
    {
	*head=new; // Set the new node as the head of the list
	return SUCCESS; // Return success
    }
    else
    {
	list *temp=*head; 
	while(temp!=NULL) 
	{
	    if(strcmp(temp->data,data)==0) // Check for duplicate file
	    {
		printf("%s is Duplicate file\n", data); 
		return FAILURE; // Return failure if duplicate file is found
	    }
	    temp = temp->link; // Move to the next node
	}
	free(temp); // Free the temporary pointer
	temp=*head; 
	while(temp->link!=NULL) // Traverse to the end of the list
	    temp = temp->link; 
	temp->link=new; // Link the new node at the end of the list
    }
    return SUCCESS; 
}

