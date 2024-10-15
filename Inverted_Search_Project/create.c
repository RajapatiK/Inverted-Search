#include "main.h" 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

Status create_DB(hash_t *HT)
{
    for(int i=0;i<28;i++) // Initialize hash table entries
    {
	HT[i].index=i; // Set the index of each hash table entry
	HT[i].link=NULL; // Initialize the link to NULL
    }
    return SUCCESS; 
}

Status read_datafile(list *head, hash_t *arr)
{
    list *temp=head;
    while(temp!=NULL) 
    {
	FILE *fptr=fopen(temp->data,"r"); // Open the file in read mode
	if (fptr == NULL) // Check if the file opened successfully
	{
	    printf("Unable to open the file\n");
	    return FAILURE; 
	}
	char buffer[30]; 
	int i=0; 
	while((fscanf(fptr," %s",buffer))!=EOF)// Read words from the file until EOF
	{
	    if(buffer[0]>='a'&&buffer[0]<='z')i=buffer[0]-'a'; // Calculate index for lowercase letters
	    else if(buffer[0]>='A'&&buffer[0]<='Z') i=buffer[0]-'A'; // Calculate index for uppercase letters
	    else if(buffer[0]>='0'&&buffer[0]<='9')i=26; // Set index for digits
	    else i=27; // Set index for other characters

	    if(arr[i].link==NULL) 
	    {
		main_node_t *newm=malloc(sizeof(main_node_t));
		if(newm==NULL) return FAILURE; 
		sub_node_t *news=malloc(sizeof(sub_node_t)); 
		if(news==NULL) return FAILURE; 
		newm->f_count=1; // Initialize file count
		strcpy(newm->word,buffer); // Copy the word to the new main node
		news->w_count=1; // Initialize word count
		strcpy(news->f_name,temp->data); // Copy the file name to the new sub node
		news->link=NULL; // Initialize the link of the new sub node to NULL
		newm->sub_link=news; // Link the sub node to the main node
		newm->link=NULL; // Initialize the link of the main node to NULL
		arr[i].link=newm; // Link the main node to the hash table entry
	    }
	    else 
	    {
		int flag=0,flag1=0; 
		main_node_t *temp1=arr[i].link; 
		main_node_t *prevm=NULL; 
		while(temp1!=NULL) // Traverse main nodes
		{
		    if(strcmp(temp1->word,buffer)==0) // Check if the word matches
		    {
			sub_node_t *sub_temp = temp1->sub_link; 
			sub_node_t *prevs = NULL; 
			while (sub_temp != NULL) 
			{
			    if (strcmp(sub_temp->f_name,temp->data)==0) // Check if the file name matches
			    {
				sub_temp->w_count++; // Increment the word count
				flag = 1; 
				flag1 = 1; 
				break; 
			    }
			    prevs=sub_temp; // Update the previous sub node pointer
			    sub_temp=sub_temp->link; // Move to the next sub node
			}
			if (flag1 == 0) 
			{
			    sub_node_t *new_sub=malloc(sizeof(sub_node_t));
			    if (new_sub == NULL) return FAILURE; 
			    new_sub->w_count = 1; // Initialize word count
			    strcpy(new_sub->f_name,temp->data); // Copy the file name to the new sub node
			    temp1->f_count++; // Increment the file count
			    new_sub->link = NULL; 
			    if (prevs == NULL) // If there is no previous sub node
				temp1->sub_link = new_sub; // Link the new sub node to the main node
			    else
				prevs->link = new_sub; // Link the new sub node to the previous sub node
			    flag = 1; 
			}
		    }
		    prevm = temp1; // Update the previous main node pointer
		    temp1 = temp1->link; // Move to the next main node
		}
		if(flag==0) 
		{
		    main_node_t *newm=malloc(sizeof(main_node_t)); 
		    if (newm == NULL) return FAILURE; 
		    sub_node_t *news = malloc(sizeof(sub_node_t)); 
		    if (news == NULL) return FAILURE; 
		    newm->f_count = 1; // Initialize file count
		    strcpy(newm->word, buffer); // Copy the word to the new main node
		    news->w_count = 1; // Initialize word count
		    strcpy(news->f_name,temp->data); // Copy the file name to the new sub node
		    news->link = NULL; 
		    newm->sub_link = news; // Link the sub node to the main node
		    newm->link = NULL; // Initialize the link of the main node to NULL
		    prevm->link = newm; // Link the new main node to the previous main node
		}
	    }
	}
	temp = temp->link; // Move to the next file in the list
    }
    return SUCCESS; 
}

