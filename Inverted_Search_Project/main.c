#include "main.h" 
#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[])
{
    if (argv[1] == NULL) // Check if a file name is passed as argument
    {
	printf("Please pass file name\n");
	return FAILURE; // Return failure if no file name is passed
    }
    else
    {
	list *head=NULL; // Initialize head of the linked list to NULL
	for (int i=1;i<argc;i++)
	    read_and_validate(&head,argv[i]); // Read and validate each file passed as argument
	hash_t arr[28]; // Declare an array of hash_t
	create_DB(arr); // Initialize the database
	int n; // Variable to store user choice
	do
	{
	    printf("\n1.Create database\n2.Display database\n3.Search database\n4.Save database\n5.Update database\n6.Exit\nEnter your choice: ");
	    scanf("%d", &n); // Read user choice
	    switch (n)
	    {
		case 1: if ((read_datafile(head, arr)) == SUCCESS) // Case to create database
			    printf("\nList created Successfully\n");
			else
			    printf("\nError in creating list\n");
			break;
		case 2: if((display_DB(arr)==SUCCESS)) // Case to display database
			    printf("\n Displaying data  Successful\n");
			else
			    printf("\n Displaying data base failed\n");
			break;
		case 3: if((search_DB(arr)==SUCCESS)) // Case to search in the database
			    printf("\nSearching data successful\n");
			else
			    printf("\nSearching data failed\n");
			break;
		case 4: if ((save_DB(arr)) == SUCCESS) // Case to save database
			    printf("\nHash saved Successfully\n");
			else
			    printf("\nHash saving failed\n");
			break;
		case 5: if ((update_DB(arr,&head)) == SUCCESS) // Case to update database
			    printf("\nHash updated Successfully\n");
			else
			    printf("\nHash update failed\n");
			break;
		case 6: printf("Exit\n"); // Case to exit the program
			break;
		default: printf("Invalid Option\n"); // Handle invalid option
	    }
	} while(n!=6); // Continue until user chooses to exit
    }
}


