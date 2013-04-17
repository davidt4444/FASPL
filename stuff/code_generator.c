/*
David Thigpen
*/

#include "header.h"

ComponentList * gen_XFDLComponentList(char * file_path, int tab, FILE * shortcut)
{
	if(verbose1){puts("Entering gen_XFDLComponentList\n");}
	int i;
	int j;

	int length;
	int maps_length;
	int bounds_length;
	char buffer[275];
	char * maps_count;
	char * maps_holder;
	char * bounds_holder;
	char * filename;
	char current_character;
	ComponentList * list;
	ComponentList * list1;
	ComponentList * list2;
	ComponentList * list_left;
	ComponentList * list_right;

	FILE * XFDL_file;
	
	list = (ComponentList *) calloc(1, sizeof(ComponentList));
	list->maps_count = 0;
	list->bounds_count = 0;
	list->maps = 0;
	list->bounds = 0;
	maps_length = 0;
	bounds_length = 0;
	maps_holder = 0;
	bounds_holder = 0;
	
	
	filename = (char *) calloc(slength(file_path)+12, sizeof(char));
	filename[0]='.';
	filename[1]='/';
	filename[2]='t';
	filename[3]='e';
	filename[4]='s';
	filename[5]='t';
	filename[6]='d';
	filename[7]='a';
	filename[8]='t';
	filename[9]='a';
	filename[10]='/';
	filename[11]='\0';
	strcat(filename, file_path);
	
	if(XFDL_file = fopen(filename, "r"))
	{
		current_character = (char) getc(XFDL_file);
		i=0;
		while(current_character != -1)
		{
			if(current_character == '<')
			{
				while(current_character != ' ' && current_character != -1)
				{
					buffer[i]=current_character;
					i++;
					current_character = (char) getc(XFDL_file);
				}
				buffer[i]='\0';
				
				if(!strcmp(buffer, "<Bounds"))
				{
					while(current_character != '>' && current_character != -1)
					{
						buffer[i]=current_character;
						i++;
						current_character = (char) getc(XFDL_file);
					}
					buffer[i]='>';
					i++;
					buffer[i]='\n';
					i++;
					buffer[i]='\0';
					i++;

					bounds_length = bounds_length + i +tab+3;
					list->bounds = (char *) calloc(bounds_length, sizeof(char));
					list->bounds_count++;
					list->bounds[0]='\0';
					if(bounds_holder)
					{
						strcat(list->bounds, bounds_holder);
					}
					for(i=0; i<tab+3; i++)
					{
						strcat(list->bounds, "\t");
					}
					strcat(list->bounds, buffer);
					bounds_holder = list->bounds;


				}
				else if(!strcmp(buffer, "<Field"))
				{
					i=0;
					buffer[i]='<';
					i++;
					buffer[i]='M';
					i++;
					buffer[i]='a';
					i++;
					buffer[i]='p';
					i++;
					buffer[i]=' ';
					i++;
					buffer[i]='p';
					i++;
					buffer[i]='o';
					i++;
					buffer[i]='s';
					i++;
					buffer[i]='i';
					i++;
					buffer[i]='t';
					i++;
					buffer[i]='i';
					i++;
					buffer[i]='o';
					i++;
					buffer[i]='n';
					i++;
					buffer[i]='=';
					i++;
					buffer[i]='"';
					i++;

					maps_count = (char *) calloc(20, sizeof(char));
					sprintf(maps_count, "%d", list->maps_count);
					for(j=0; j<20; j++)
					{
						if(maps_count[j] == '\0')
						{
							break;
						}
					}
					sprintf(&buffer[i], "%s", maps_count);
					i=i+j;
					
					buffer[i]='"';
					i++;
					buffer[i]=current_character;
					i++;
					current_character = (char) getc(XFDL_file);
					while(current_character != ' ' && current_character != -1)
					{
						buffer[i]=current_character;
						i++;
						current_character = (char) getc(XFDL_file);
					}
					buffer[i]='/';
					i++;
					buffer[i]='>';
					i++;
					buffer[i]='\n';
					i++;
					buffer[i]='\0';
					i++;

					maps_length = maps_length + i+tab+3;
					list->maps = (char *) calloc(maps_length, sizeof(char));
					list->maps_count++;
					list->maps[0]='\0';
					if(maps_holder)
					{
						strcat(list->maps, maps_holder);
					}
					for(i=0; i<tab+3; i++)
					{
						strcat(list->maps, "\t");
					}
					strcat(list->maps, buffer);
					maps_holder = list->maps;


				}
				else
				{
					while(current_character != '>' && current_character != -1)
					{
						buffer[i]=current_character;
						i++;
						current_character = (char) getc(XFDL_file);
					}
					buffer[i]='>';
					buffer[i+1]='\0';
				}
					
			}
			i=0;
			current_character = (char) getc(XFDL_file);
		}
		close(XFDL_file);
		return list;
	}
	else
	{
		return 0;
	}
	return 0;
}




char * gen_datasetList_label(TreeNode * root, int tab, FILE * shortcut)
{
	TreeNode * holderNode;	
	TreeNode * holderNode2;	
	TreeNode * holderNode3;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	int j;
	int length;
	char * map_list;
	char * temp_list1;
	char * temp_list2;

	map_list = 0;
	temp_list1 = 0;
	temp_list2 = 0;
	length = 0;

	currentNode = root;
	if(currentNode->type == VOID)
	{
	}
	else
	{
		length = (tab+1)*2+34+20+slength(currentNode->tokenString)+4;
		map_list = (char *) calloc(length, sizeof(char));
		for(j=0; j<tab+1; j++)
		{
			strcat(map_list, "\t");
		}
		sprintf(&map_list[j], "<Map position='%d' fieldName='%s' />\n", position_counter, currentNode->tokenString);
	}
	position_counter++;
	if(currentNode->sibling)
	{
		temp_list1 = gen_datasetList_label(currentNode->sibling, tab, shortcut);
		if(temp_list1)
		{
			length = length + slength(temp_list1);
			temp_list2 = (char *) calloc(length, sizeof(char));
			if(map_list)
			{
				strcat(temp_list2,map_list);
			}
			strcat(temp_list2,temp_list1);
			map_list = temp_list2;	
		}
	}
	return map_list;
}
char * gen_datasetList_coordinate(TreeNode * root, int tab, FILE * shortcut)
{
	TreeNode * holderNode;	
	TreeNode * holderNode2;	
	TreeNode * holderNode3;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	int j;
	int length;
	char * map_list;
	char * temp_list1;
	char * temp_list2;

	map_list = 0;
	temp_list1 = 0;
	temp_list2 = 0;
	length = 0;

	currentNode = root;

	length = (tab+1)*2+34+20+slength(currentNode->tokenString)+4;
	map_list = (char *) calloc(length, sizeof(char));
	for(j=0; j<tab+1; j++)
	{
		strcat(map_list, "\t");
	}

	sprintf(&map_list[j], "<Bounds lower='%d' upper='%d' />\n", currentNode->left->number, currentNode->right->number);

	position_counter++;
	if(currentNode->sibling)
	{
		temp_list1 = gen_datasetList_coordinate(currentNode->sibling, tab, shortcut);
		if(temp_list1)
		{
			length = length + slength(temp_list1);
			temp_list2 = (char *) calloc(length, sizeof(char));
			if(map_list)
			{
				strcat(temp_list2,map_list);
			}
			strcat(temp_list2,temp_list1);
			map_list = temp_list2;	
		}
	}
	return map_list;
}
ComponentList * gen_subDataset(TreeNode * root, int tab, FILE * shortcut)
{
	if(verbose1){puts("Entering gen_subDataset\n");}
	int i;
	int paramnum;
	TreeNode * t1;	
	TreeNode * t2;	
	TreeNode * t3;	

	int j;
	int passmode;
	int begin;
	int quote;
	int left;
	int right;
	int here;
	int length;
	char * filename;
	ComponentList * list;
	ComponentList * list1;
	ComponentList * list2;
	ComponentList * list_left;
	ComponentList * list_right;

	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	

	
	list = 0;
	length =0;
	list_left = 0;
	list_right = 0;
	list1 = 0;
	list2 = 0;
	currentNode = root;

	list = (ComponentList *) calloc(1, sizeof(ComponentList));
	list->bounds = 0;
	list->maps = 0;

	if(currentNode->type == ATTRIBUTE_JOIN
		|| currentNode->type == BLOCK_JOIN
		|| currentNode->type == STRING_LITERAL
		|| currentNode->type == COMPOUND_DATASET)
	{
		if(currentNode->type == ATTRIBUTE_JOIN)
		{

			here=opcounter;
			opcounter++;
			left=opcounter;
			if(currentNode->left)
			{
				list_left = gen_subDataset(currentNode->left, tab, shortcut);
			}
			else
			{
				list_left = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_left->bounds = 0;
				list_left->maps = 0;
				opcounter++;
			}
			right=opcounter;
			if(currentNode->right)
			{
				list_right = gen_subDataset(currentNode->right, tab, shortcut);
			}
			else
			{
				list_right = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_right->bounds = 0;
				list_right->maps = 0;
				opcounter++;
			}
			if(!list_left)
			{
				list_left = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_left->maps = 0;
				list_left->bounds = 0;
			}
			if(!list_right)
			{
				list_right = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_right->maps = 0;
				list_right->bounds = 0;
			}


			if(currentNode->left && currentNode->left->type == COMPOUND_DATASET)
			{
				if(currentNode->left->right->left)
				{
					position_counter=0;
					list_left->maps = gen_datasetList_label(currentNode->left->right->left, tab+2, shortcut);
					list_left->maps_count = position_counter; 
				}
				if(currentNode->left->right->right)
				{
					position_counter=0;
					list_left->bounds = gen_datasetList_coordinate(currentNode->left->right->right, tab+2, shortcut);
					list_left->bounds_count = position_counter; 
				}
				
			}

			if(currentNode->right && currentNode->right->type == COMPOUND_DATASET)
			{
				if(currentNode->right->right->left)
				{
					position_counter=0;
					list_right->maps = gen_datasetList_label(currentNode->right->right->left, tab+2, shortcut);
					list_right->maps_count = position_counter; 
				}
				if(currentNode->right->right->right)
				{
					position_counter=0;
					list_right->bounds = gen_datasetList_coordinate(currentNode->right->right->right, tab+2, shortcut);
					list_right->bounds_count = position_counter; 
				}

			}
			for(j=0; j<tab+1; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "<DataSource dsName='op%d' type='joined'>\n", here);
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "<Component dsName='op%d'>\n", left);
			if(list_left)
			{
				if(list_left->maps)
				{
					fprintf(shortcut, "%s", list_left->maps);
				}
				
				if(list_left->bounds)
				{
					fprintf(shortcut, "%s", list_left->bounds);
				}
				else if(list_right)
				{
					if(list_right->bounds)
					{
						fprintf(shortcut, "%s", list_right->bounds);
					}
				}
			}
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "</Component>\n", left);
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "<Component dsName='op%d' >\n", right);
			if(list_right)
			{
				if(list_right->maps)
				{
					fprintf(shortcut, "%s", list_right->maps);
				}
				if(list_right->bounds)
				{
					fprintf(shortcut, "%s", list_right->bounds);
				}
				else if(list_left)
				{
					if(list_left->bounds)
					{
						fprintf(shortcut, "%s", list_left->bounds);
					}
				}
			}
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "</Component>\n", left);
			for(j=0; j<tab+1; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "</DataSource>\n");


			length = 0;
			if(list_left)
			{
				if(list_left->maps)
				{
					length+=slength(list_left->maps);
				}
			}
			if(list_right)
			{
				if(list_right->maps)
				{
					length+=slength(list_right->maps);
				}
			}
			list->maps = (char *) calloc(length, sizeof(char));
			if(list_left)
			{
				if(list_left->maps)
				{
					strcat(list->maps, list_left->maps);
				}
				if(list_left->bounds)
				{
					list->bounds = list_left->bounds;
				}
			}
			if(list_right)
			{
				if(list_right->maps)
				{
					strcat(list->maps, list_right->maps);
				}
				if(list_right->bounds)
				{
					list->bounds = list_right->bounds;
				}
			}
			return list;
		}
		else if(currentNode->type == BLOCK_JOIN)
		{

			here=opcounter;
			opcounter++;
			left=opcounter;
			if(currentNode->left)
			{
				list_left = gen_subDataset(currentNode->left, tab, shortcut);
			}
			else
			{
				list_left = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_left->bounds = 0;
				list_left->maps = 0;
				opcounter++;
			}
			right=opcounter;
			if(currentNode->right)
			{
				list_right = gen_subDataset(currentNode->right, tab, shortcut);
			}
			else
			{
				list_right = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_right->bounds = 0;
				list_right->maps = 0;
				opcounter++;
			}
			if(!list_left)
			{
				list_left = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_left->maps = 0;
				list_left->bounds = 0;
			}
			if(!list_right)
			{
				list_right = (ComponentList *) calloc(1, sizeof(ComponentList));
				list_right->maps = 0;
				list_right->bounds = 0;
			}


			if(currentNode->left && currentNode->left->type == COMPOUND_DATASET)
			{
				if(currentNode->left->right->left)
				{
					position_counter=0;
					list_left->maps = gen_datasetList_label(currentNode->left->right->left, tab+2, shortcut);
					list_left->maps_count = position_counter; 
				}
				if(currentNode->left->right->right)
				{
					position_counter=0;
					list_left->bounds = gen_datasetList_coordinate(currentNode->left->right->right, tab+2, shortcut);
					list_left->bounds_count = position_counter; 
				}
				
			}

			if(currentNode->right && currentNode->right->type == COMPOUND_DATASET)
			{
				if(currentNode->right->right->left)
				{
					position_counter=0;
					list_right->maps = gen_datasetList_label(currentNode->right->right->left, tab+2, shortcut);
					list_right->maps_count = position_counter; 
				}
				if(currentNode->right->right->right)
				{
					position_counter=0;
					list_right->bounds = gen_datasetList_coordinate(currentNode->right->right->right, tab+2, shortcut);
					list_right->bounds_count = position_counter; 
				}

			}
			for(j=0; j<tab+1; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "<DataSource dsName='op%d' type='blocked'>\n", here);
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "<Component dsName='op%d'>\n", left);
			if(list_left)
			{
				if(list_left->maps)
				{
					fprintf(shortcut, "%s", list_left->maps);
				}
				
				if(list_left->bounds)
				{
					fprintf(shortcut, "%s", list_left->bounds);
				}
				else if(list_right)
				{
					if(list_right->bounds)
					{
						fprintf(shortcut, "%s", list_right->bounds);
					}
				}
			}
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "</Component>\n", left);
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "<Component dsName='op%d' >\n", right);
			if(list_right)
			{
				if(list_right->maps)
				{
					fprintf(shortcut, "%s", list_right->maps);
				}
				if(list_right->bounds)
				{
					fprintf(shortcut, "%s", list_right->bounds);
				}
				else if(list_left)
				{
					if(list_left->bounds)
					{
						fprintf(shortcut, "%s", list_left->bounds);
					}
				}
			}
			for(j=0; j<tab+2; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "</Component>\n", left);
			for(j=0; j<tab+1; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "</DataSource>\n");




			length = 0;
			if(list_left)
			{
				if(list_left->maps)
				{
					length+=slength(list_left->maps);
				}
			}
			if(list_right)
			{
				if(list_right->maps)
				{
					length+=slength(list_right->maps);
				}
			}
			list->maps = (char *) calloc(length, sizeof(char));
			if(list_left)
			{
				if(list_left->maps)
				{
					strcat(list->maps, list_left->maps);
				}
				if(list_left->bounds)
				{
					list->bounds = list_left->bounds;
				}
			}
			if(list_right)
			{
				if(list_right->maps)
				{
					strcat(list->maps, list_right->maps);
				}
				if(list_right->bounds)
				{
					list->bounds = list_right->bounds;
				}
			}
			return list;
		}
		else if(currentNode->type == STRING_LITERAL)
		{
			here=opcounter;
			opcounter++;

			for(j=0; j<tab+1; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "<DataSource dsName='op%d' type='physical' fileName='%s'>\n", here, currentNode->tokenString);
			
			list = gen_XFDLComponentList(currentNode->tokenString, tab, shortcut);

			if(list)
			{
				for(j=0; j<tab+2; j++)
				{
					fprintf(shortcut, "\t");
				}
				fprintf(shortcut, "<Component dsName='op%d'>\n", here);
			
				if(list->maps)
				{
					fprintf(shortcut, "%s", list->maps);
				}
				if(list->bounds)
				{
					fprintf(shortcut, "%s", list->bounds);
				}
				for(j=0; j<tab+2; j++)
				{
					fprintf(shortcut, "\t");
				}
				fprintf(shortcut, "</Component>\n");
			}
			for(j=0; j<tab+1; j++)
			{
				fprintf(shortcut, "\t");
			}
			fprintf(shortcut, "</DataSource>\n");
			
			if(list)
			{
				return list;
			}
		}
		else if(currentNode->type == COMPOUND_DATASET)
		{
			if(currentNode->left->type == STRING_LITERAL)
			{
				here=opcounter;
				opcounter++;
				for(j=0; j<tab+1; j++)
				{
					fprintf(shortcut, "\t");
				}
				fprintf(shortcut, "<DataSource dsName='op%d' type='physical' fileName='%s'>\n", here, currentNode->left->tokenString);
				
				list = gen_XFDLComponentList(currentNode->left->tokenString, tab, shortcut);
				if(list)
				{
					for(j=0; j<tab+2; j++)
					{
						fprintf(shortcut, "\t");
					}
					fprintf(shortcut, "<Component dsName='op%d'>\n", here);
				
					if(list->maps)
					{
						fprintf(shortcut, "%s", list->maps);
					}
					if(list->bounds)
					{
						fprintf(shortcut, "%s", list->bounds);
					}
					for(j=0; j<tab+2; j++)
					{
						fprintf(shortcut, "\t");
					}
					fprintf(shortcut, "</Component>\n");
				}
				for(j=0; j<tab+1; j++)
				{
					fprintf(shortcut, "\t");
				}
				fprintf(shortcut, "</DataSource>\n");
				
				if(list)
				{
					return list;
				}

			}
			else
			{
				return gen_subDataset(currentNode->left, tab, shortcut);
			}
		}

	}
	if(verbose1){puts("Leaving gen_subDataset\n");}

	return 0;
}


int generate()
{
	int j;

	TreeNode * root;
	TreeNode * super_root;
	Symbol * currentSymbol;
	char * name;
	Symbol * holderSymbol;
	char * name2;
	Symbol * holderSymbol2;

	set_main_found(0);
	root = parse();

/*
printTree(root,0);
*/
	stdin = actual_out;
	
	super_root = interpreter_analyze(root);
	for(j=0;j<26;j++)
	{
		if(symbolTable[j])
		{
			symbolTable[j]=get_symbolTable(j);
		}
	}

	name = (char *) calloc(7, sizeof(char));
	name[0]='x';
	name[1]='m';
	name[2]='l';
	name[3]='o';
	name[4]='u';
	name[5]='t';
	name[6]='\0';
	holderSymbol = interpreter_lookup(interpreter_newSymbol(name, 0, TYPE_STRING, 0, 0));

	fprintf(holderSymbol->stream, "<?xml version='1.0' encoding='UTF-8'?>\n");
	fprintf(holderSymbol->stream, "<!DOCTYPE DataSourceList PUBLIC '-//SDB//DTD//EN' 'ddl.dtd'>\n");
	fprintf(holderSymbol->stream, "<DataSourceList>\n");
	if(super_root)
	{
		gen_subDataset(super_root, 0, holderSymbol->stream);
	}
	fprintf(holderSymbol->stream, "\t<PublicDS dsName='op0' />\n");
	fprintf(holderSymbol->stream, "</DataSourceList>\n");

	for(j=0;j<26;j++)
	{
		if(symbolTable[j])
		{
			deleteTableRow(symbolTable[j]);
			symbolTable[j]=0;
		}
	}
	return 1;
}

int main(int argc, char *argv[], char *envp[])
{
	char * filename;
	FILE * temp_input;

	int i;
	char * p;
	FILE * input;

	verbose1=0;

	if(argc>=2)
	{
		i=slength(argv[1]) - 7;
		
		if(strcmp(&argv[1][i], ".faspl"))
		{
			printf("\n>>> ");
			printf("File error: You need to use a file name that ends in .faspl\n");
			Error = TRUE;
			exit(0);
		}
	}
	if(argc==3)
	{
		printf("%s:%s\n", argv[1], argv[2]);

		if(input = fopen(argv[1], "r"))
		{
		}
		else
		{
			printf("\n>>> ");
			printf("File error: There is no file pointed to at the location specified or an incorrect command is being used.\n");
			printf("Check the file and make sure to use the format [compiler file name] [input file] [output file]\n");
			printf("\t\t\t\t\t    or [compiler file name] [input file]\n");
			Error = TRUE;
			exit(0);
		}
		
		fclose(input);

		filename = calloc(slength(argv[1]), sizeof(char));
		strcpy(filename, argv[1]);
		preprocessor_body(filename);
		input = fopen(preprocessor_temp_filename, "r");

		output = fopen(argv[2], "w");
	}
	else if(argc==2)
	{
		printf("%s:a.xddl\n", argv[1]);
		if(input = fopen(argv[1], "r"))
		{
		}
		else
		{
			printf("\n>>> ");
			printf("File error: There is no file pointed to at the location specified or an incorrect command is being used.\n");
			printf("Check the file and make sure to use the format [compiler file name] [input file] [output file]\n");
			printf("\t\t\t\t\t    or [compiler file name] [input file]\n");
			Error = TRUE;
			exit(0);
		}
		fclose(input);

		filename = calloc(slength(argv[1]), sizeof(char));
		strcpy(filename, argv[1]);
		preprocessor_body(filename);
		input = fopen(preprocessor_temp_filename, "r");

		output = fopen("a.xddl", "w");
	}
	else
	{
		printf("\n>>> ");
		printf("File error: You need to use the format [compiler file name] [input file] [output file]\n");
		printf("\t\t\t\t\tor [compiler file name] [input file]\n");
		Error = TRUE;
		exit(0);
	}
	actual_out = stdin;
	stdin = input;

	generate();

	fclose(input);
	fclose(output);

	remove(preprocessor_temp_filename);

	return 0;
}


