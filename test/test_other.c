#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * get_novel_input(char * total_item, int total_item_length)
{
	char current_item; 
	char line_item[255]; 
	char * temp_item; 
	int i; 

	for(i=0; i<255; i++)
	{
		line_item[i]='\0';
	}

	total_item=0;
	i=current_item=0;
	current_item = getchar();
	if(current_item==-1) 
	{
		total_item=(char *) calloc(3, sizeof(char));
		strcpy(total_item, "-1");
		return total_item;
	}
	while(current_item!='\n' && current_item!='\r' && current_item!=-1) 
	{
		if(i<254)
		{
			line_item[i]=current_item;
			i++;
		}
		else
		{
			total_item_length = total_item_length + i; 
			temp_item=(char *) calloc(total_item_length, sizeof(char));
			if(total_item)
			{
				strcpy(temp_item, total_item);
				strcat(temp_item, line_item);
			}
			else
			{
				strcpy(temp_item, line_item);
			}
			total_item = temp_item;	
			for(i=0; i<255; i++)
			{
				line_item[i]='\0';
			}
			i=0;
		}
		current_item = getchar();
	}
	total_item_length = total_item_length + i; 
	temp_item=(char *) calloc(total_item_length, sizeof(char));
	if(total_item)
	{
		strcpy(temp_item, total_item);
		strcat(temp_item, line_item);
	}
	else
	{
		strcpy(temp_item, line_item);
	}
	total_item = temp_item;	
	for(i=0; i<255; i++)
	{
		line_item[i]='\0';
	}
	i=0;
	return total_item;
}
int main()
{
	char * c;
	c = get_novel_input(0, 1);
	while(strcmp(c,"-1"))
	{
		printf("\n%s\n", c);
		c = get_novel_input(0, 1);
	}
	printf("\n%s\n", c);
}