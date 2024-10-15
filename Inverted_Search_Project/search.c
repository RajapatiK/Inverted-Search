#include "main.h"
#include <string.h>
#include <stdio.h>

Status search_DB(hash_t *arr)
{
    int sum=0,arr1[28]={0};// Initialize sum and array to track empty indices
    for (int i=0;i<28;i++) //Loop through the hash table
    {
	if (arr[i].link == NULL) 
	{
	    arr1[i] = 1;
	    sum+=arr1[i];
	}
    }
    if (sum==28) // Check if all entries are empty
    {
	printf("List empty\n");
	return FAILURE;
    }
    char data[30]; // Buffer to store the word to be searched
    printf("Enter the word: \n");
    scanf(" %s", data);
    int flag=0;// Flag to indicate if the word is found
    for (int i=0;i<28;i++)// Loop through the hash table again
    {
	if(arr[i].link!=NULL)// Loop through the hash table agai
	{
	    main_node_t *temp_main=arr[i].link;
	    while(temp_main!=NULL)
	    {
		if(strcmp(temp_main->word,data)==0)// Check if the word matches
		{
		    flag=1;// Set the flag to indicate the word is found
		    printf("\nIndex          word        Filecount    Filename        Wordcount\n");
		    printf("[%d] ->         %-12s %-12d",arr[i].index,temp_main->word,temp_main->f_count);
		    sub_node_t *temp_sub=temp_main->sub_link;
		    while(temp_sub!=NULL)
		    {
			printf("%-18s %d\n",temp_sub->f_name,temp_sub->w_count);
			if(temp_sub->link!=NULL)
			    printf("%-40s", "");
			temp_sub=temp_sub->link;// Move to the next sub node
		    }
		}
		temp_main=temp_main->link;// Move to the next main node
	    }
	}
    }
    if(flag==0)// If the word is not found
    {
	printf("Word not found\n");
	return FAILURE;
    }
    return SUCCESS;
}
