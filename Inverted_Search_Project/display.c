#include"main.h"
#include<string.h>
#include<stdio.h>

Status display_DB(hash_t *arr)
{
    int sum=0,arr1[28]={0};
    for(int i=0;i<28;i++)
    {
	if (arr[i].link==NULL) // Check if the hash table entry is empty
	{
	    arr1[i] = 1; // Mark the index as empty
	    sum = sum + arr1[i]; // Increment the sum of empty entries
	}
    }
    if (sum == 28) // Check if all entries are empty
    {
	printf("List empty\n"); // Print that the list is empty
	return FAILURE;
    }
    printf("\nIndex	        word        Filecount    Filename        Wordcount\n");
    for (int i=0;i<28;i++)// Loop through the hash table again
    {
	if(arr[i].link!=NULL)// Loop through the hash table again
	{
	    main_node_t *temp_main=arr[i].link;
	    while(temp_main!=NULL)
	    {
		printf("[%d] ->		%-12s %-12d",arr[i].index,temp_main->word,temp_main->f_count);
		sub_node_t *temp_sub=temp_main->sub_link;
		while(temp_sub!=NULL)
		{
		    printf("%-18s %d\n",temp_sub->f_name,temp_sub->w_count);
		    if(temp_sub->link!=NULL)
			printf("%-41s", "");
		    temp_sub=temp_sub->link;// Move to the next sub node
		}
		temp_main=temp_main->link;// Move to the next main node
	    }
	}
    }
    return SUCCESS;
}

