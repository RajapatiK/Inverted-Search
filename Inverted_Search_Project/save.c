#include <stdio.h>
#include <string.h>
#include "main.h"
#include <stdlib.h>


Status save_DB(hash_t *arr)
{
    int sum=0,arr1[28]={0};// Initialize sum and array to track empty indices
    for(int i=0;i<28;i++)// Loop through the hash table
    {
	if(arr[i].link==NULL)
	{
	    arr1[i]=1;// Loop through the hash table
	    sum=sum+arr1[i];
	}
    }
    if(sum==28)// Check if all entries are empty
    {
	printf("List empty\n");
	return FAILURE;
    }
    FILE *fptr;// File pointer to write the database
    printf("Enter the file name: \n");
    char data[50];
    scanf(" %s",data);// Read the file name input
    if(strstr(data,".txt"))// Check if the file has a .txt extension
    {
	fptr=fopen(data,"w");// Open the file in write mode
	if(fptr==NULL)
	{
	    printf("Error in opening the file\n");
	    return FAILURE;
	}
	else 
	{
	    fseek(fptr, 0, SEEK_END);// Move the file pointer to the end
	    if(ftell(fptr)==0)// Check if the file is empty
	    {
		printf("File opened successfully\n");
		fseek(fptr, 0, SEEK_SET);
	    }
	}
    }
    else// File does not have a .txt extension
    {
	printf("The file must have a .txt extension\n");
	return FAILURE;
    }
    for (int i=0;i<28;i++)// Loop through the hash table again
    {
	if (arr[i].link!=NULL)// Check if the hash table entry is not empty
	{
	    main_node_t *temp_main=arr[i].link;
	    while(temp_main!=NULL)
	    {
		fprintf(fptr,"#%d;#%s;#%d;",arr[i].index,temp_main->word,temp_main->f_count);
		sub_node_t *temp_sub=temp_main->sub_link;
		while(temp_sub!=NULL)
		{
		    fprintf(fptr,"#%s;#%d;",temp_sub->f_name,temp_sub->w_count);
		    temp_sub=temp_sub->link;// Move to the next sub node
		}
		fprintf(fptr,"\n");
		temp_main=temp_main->link;// Move to the next main node
	    }
	}
    }
    return SUCCESS;
}


