#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * preprocessor_total_file;
char preprocessor_buffer[255];
char * preprocessor_temp_filename;

int slength(char * s )
{
   int i;

   i=0;
   while(s[i]!='\0')
   {
		i++;
   }
   i++;
   return i;
}

int preprocessor_appendage(char * filename, int length)
{
	int preprocessor_lineno;
	char * preprocessor_file;
	char preprocessor_filebuffer[255];
	char c;
	char * temp_file;
	int i;
	int j;
	int k;
	int size;
	FILE * test;
	if(test = fopen(filename,"r"))
	{
	}
	else
	{
		printf("The file %s did not open!\n", filename);
		exit(0);
	}
	
	preprocessor_lineno=0;
	i=length;
	c = getc(test);
	while(c!=-1 && c!='\0')
	{
		if(c=='/')
		{
			c = getc(test);
			if(c=='*')
			{
				c = getc(test);
				while(c!=-1 && c!='\0')
				{
					while(c!='*')
					{
						c = getc(test);
					}
					c = getc(test);
					if(c=='/')
					{
						c = getc(test);
						break;
					}
				}
			}
			else
			{
				if(i<254)
				{
					preprocessor_buffer[i]='/';
					i++;
					preprocessor_buffer[i]=c;
					i++;
				}
				else
				{
					preprocessor_buffer[i]='/';
					i++;
					if(preprocessor_total_file)
					{
						size = slength(preprocessor_total_file);
						temp_file = calloc(size+256, sizeof(char));
						strcpy(temp_file, preprocessor_total_file);
						strcat(temp_file, preprocessor_buffer);
						for(j=0; j<255; j++)
						{
							preprocessor_buffer[j]='\0';
						}
						preprocessor_total_file = temp_file;
						i=0;
						preprocessor_buffer[i]=c;
						i++;
					}
					else
					{
						preprocessor_total_file = calloc(256, sizeof(char));
						strcpy(preprocessor_total_file, preprocessor_buffer);
						for(j=0; j<255; j++)
						{
							preprocessor_buffer[j]='\0';
						}
						i=0;
						preprocessor_buffer[i]=c;
						i++;
					}
					
				}
				c = getc(test);
			}
		}
		else if(c=='#')
		{
			c = getc(test);
			if(c=='i')
			{
				c = getc(test);
				if(c=='n')
				{
					c = getc(test);
					if(c=='c')
					{
						c = getc(test);
						if(c=='l')
						{
							c = getc(test);
							if(c=='u')
							{
								c = getc(test);
								if(c=='d')
								{
									c = getc(test);
									if(c=='e')
									{
										c = getc(test);
										if(c==' ')
										{
											c = getc(test);
											if(c=='"')
											{
												c = getc(test);
											}
											else
											{
												printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
												exit(0);
											}
										}
										else
										{
											printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
											exit(0);
										}
									}
									else
									{
										printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
										exit(0);
									}
								}
								else
								{
									printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
									exit(0);
								}
							}
							else
							{
								printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
								exit(0);
							}
						}
						else
						{
							printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
							exit(0);
						}
					}
					else
					{
						printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
						exit(0);
					}
				}
				else
				{
					printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
					exit(0);
				}
			}
			else
			{
				printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
				exit(0);
			}
			k=0;
			for(j=0; j<255; j++)
			{
				preprocessor_filebuffer[j]='\0';
			}
			while(c!='"')
			{
				if(c==-1 && c=='\0' && c=='\n')
				{
					printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
					exit(0);
				}
				if(i<255)
				{
					preprocessor_filebuffer[k]=c;
					k++;
				}
				else
				{
					if(preprocessor_file)
					{
						size = slength(preprocessor_file);
						temp_file = calloc(size+256, sizeof(char));
						strcpy(temp_file, preprocessor_file);
						strcat(temp_file, preprocessor_filebuffer);
						for(j=0; j<255; j++)
						{
							preprocessor_filebuffer[j]='\0';
						}
						preprocessor_file = temp_file; 
						k=0;
						preprocessor_filebuffer[k]=c;
						k++;
					}
					else
					{
						preprocessor_file = calloc(256, sizeof(char));
						strcpy(preprocessor_file, preprocessor_filebuffer);
						for(j=0; j<255; j++)
						{
							preprocessor_filebuffer[j]='\0';
						}
						k=0;
						preprocessor_filebuffer[k]=c;
						k++;
					}
					
				}
				c = getc(test);
			}
			if(preprocessor_file)
			{
				size = slength(preprocessor_file);
				temp_file = calloc(size+256, sizeof(char));
				strcpy(temp_file, preprocessor_file);
				strcat(temp_file, preprocessor_filebuffer);
				for(j=0; j<255; j++)
				{
					preprocessor_filebuffer[j]='\0';
				}
				preprocessor_file = temp_file;
			}
			else
			{
				preprocessor_file = calloc(256, sizeof(char));
				strcpy(preprocessor_file, preprocessor_filebuffer);
				for(j=0; j<255; j++)
				{
					preprocessor_filebuffer[j]='\0';
				}
			}
			if(c=='"')
			{
				c = getc(test);
			}
			else
			{
				printf("This is an unrecognized preprocessor command at line number %d in %s!\n", preprocessor_lineno, filename);
				exit(0);
			}

			i = preprocessor_appendage(preprocessor_file,i);

			if(c=='\n')
			{
				preprocessor_lineno++;
				if(i<254)
				{
					preprocessor_buffer[i]=c;
					i++;
				}
				else
				{
					if(preprocessor_total_file)
					{
						size = slength(preprocessor_total_file);
						temp_file = calloc(size+256, sizeof(char));
						strcpy(temp_file, preprocessor_total_file);
						strcat(temp_file, preprocessor_buffer);
						for(j=0; j<255; j++)
						{
							preprocessor_buffer[j]='\0';
						}
						preprocessor_total_file = temp_file;
						i=0;
						preprocessor_buffer[i]=c;
						i++;
					}
					else
					{
						preprocessor_total_file = calloc(256, sizeof(char));
						strcpy(preprocessor_total_file, preprocessor_buffer);
						for(j=0; j<255; j++)
						{
							preprocessor_buffer[j]='\0';
						}
						i=0;
						preprocessor_buffer[i]=c;
						i++;
					}
					
				}
				c = getc(test);
			}
			for(j=0;j<255; j++)
			{
				preprocessor_filebuffer[j]='\0';
			}
			preprocessor_file=0;
		}
		else
		{
			if(c=='\n')
			{
				preprocessor_lineno++;
			}
			if(i<254)
			{
				preprocessor_buffer[i]=c;
				i++;
			}
			else
			{
				if(preprocessor_total_file)
				{
					size = slength(preprocessor_total_file);
					temp_file = calloc(size+256, sizeof(char));
					strcpy(temp_file, preprocessor_total_file);
					strcat(temp_file, preprocessor_buffer);
					for(j=0; j<255; j++)
					{
						preprocessor_buffer[j]='\0';
					}
					preprocessor_total_file = temp_file;
					i=0;
					preprocessor_buffer[i]=c;
					i++;
				}
				else
				{
					preprocessor_total_file = calloc(256, sizeof(char));
					strcpy(preprocessor_total_file, preprocessor_buffer);
					for(j=0; j<255; j++)
					{
						preprocessor_buffer[j]='\0';
					}
					i=0;
					preprocessor_buffer[i]=c;
					i++;
				}
				
			}
			c = getc(test);
		}
	}
	if(preprocessor_total_file)
	{
		size = slength(preprocessor_total_file);
		temp_file = calloc(size+256, sizeof(char));
		strcpy(temp_file, preprocessor_total_file);
		strcat(temp_file, preprocessor_buffer);
		for(j=0; j<255; j++)
		{
			preprocessor_buffer[j]='\0';
		}
		preprocessor_total_file = temp_file;
		i=0;
	}
	else
	{
		preprocessor_total_file = calloc(i+1, sizeof(char));
		strcpy(preprocessor_total_file, preprocessor_buffer);
		for(j=0; j<255; j++)
		{
			preprocessor_buffer[j]='\0';
		}
		i=0;
	}
	fclose(test);
	return i;
}
int preprocessor_body(char * filename)
{
	char c;
	char * temp_number;
	FILE * temp_output;
	
	preprocessor_temp_filename = calloc(25, sizeof(char));
	strcpy(preprocessor_temp_filename, "temp_");
	temp_number = calloc(20, sizeof(char));
	sprintf(temp_number, "%d", 2000000000*(1.0/rand()));
	strcat(preprocessor_temp_filename, temp_number);

	preprocessor_appendage(filename,0);
	
	temp_output = fopen(preprocessor_temp_filename, "w");
	fprintf(temp_output, "%s", preprocessor_total_file);
	fclose(temp_output);

	
	return 0;
}
int main()
{
	char * filename;
	FILE * temp_input;

	filename = calloc(16, sizeof(char));
	strcpy(filename, "include_list.c");
	preprocessor_body(filename);
	
	temp_input = fopen(preprocessor_temp_filename, "r");
	stdin = temp_input;
	fclose(temp_input);

	remove(preprocessor_temp_filename);
	return 0;
}
