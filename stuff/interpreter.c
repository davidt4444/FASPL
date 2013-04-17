/*
David Thigpen
*/

#include "header.h"

void runtimeError(char * message)
{ 
	printf("\n>>> ");
	printf("Runtime error at line %d: %s\n", currentLine, message);
	Error = TRUE;
	exit(0);
}
char * write_novel_input(char * total_item, char *line_item)
{
	char current_item; 
	char * temp_item; 
	int total_item_length; 

	if(total_item && line_item)
	{
		total_item_length = slength(total_item) + slength(line_item); 
		temp_item=(char *) calloc(total_item_length, sizeof(char));
		strcpy(temp_item, total_item);
		strcat(temp_item, "\n");
		strcat(temp_item, line_item);
		return temp_item;
	}
	else if(total_item)
	{
		total_item_length = slength(total_item); 
		temp_item=(char *) calloc(total_item_length, sizeof(char));
		strcpy(temp_item, total_item);
		return temp_item;
	}
	else if(line_item)
	{
		total_item_length = slength(line_item); 
		temp_item=(char *) calloc(total_item_length, sizeof(char));
		strcpy(temp_item, line_item);
		return temp_item;
	}
	else
	{
		return 0;
	}
	return 0;

}

char * get_novel_input(FILE * stream_location, char * total_item, int total_item_length)
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
	current_item = getc(stream_location);
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
		current_item = getc(stream_location);
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

Symbol * interpreter_newSymbol(char * name, int scope, Type symbolType, int function, int lineno)
{
	Symbol * s = (Symbol *) calloc(1, sizeof(Symbol));
	s->next = 0;
	s->name = (char *) calloc(slength(name), sizeof(char));
	strcpy(s->name, name);
	s->scope = scope;
	s->symbolType = symbolType;
	s->function = function;
	s->lineno = lineno;
	s->param_list = 0;
	s->instructions = 0;
	s->num = 0;
	s->float_num = 0;
	s->value = 0;
	s->offset=0;
	s->is_double=0;
	s->is_file=0;
	s->is_input=0;
	s->stream=0;
	
	return s;
}

Symbol * interpreter_lookup(Symbol * s)
{
	Symbol * current;
	Symbol * s1;
	Symbol * s2;
	
	current = 0;
	s1 = symbolTable[s->name[0]%26];
	while(s1)
	{
		if(!strcmp(s1->name, s->name) && (s1->function == s->function) && (s1->symbolType == s->symbolType))
		{
			current = s1;
			return current;
		}
		s2 = s1->next;
		s1=s2;		
	}
	return current;
}

void interpreter_insertSymbol(Symbol * s)
{
	Symbol * s1;

	if(!symbolTable[s->name[0]%26])
	{
		symbolTable[s->name[0]%26] = s;	
	}
	else if(interpreter_lookup(s) && !strcmp(symbolTable[s->name[0]%26]->name, s->name) && (symbolTable[s->name[0]%26]->scope == s->scope))
	{
		currentIdentifier = s->name;
		currentLine = s->lineno;
		semanticSymbolError("This symbol is already defined at this scope.");
	}
	else
	{
		s1 = symbolTable[s->name[0]%26];
		s->next = s1;
		symbolTable[s->name[0]%26] = s;	
	}
/*
printf("%d: %s\n", s->scope, s->name);
*/
}

void interpreter_popSymbolsByScope(int scope)
{
	int i;
	Symbol * temp;
	Symbol * current;

	for(i=0; i<26; i++)
	{
		current = symbolTable[i];
		while(current)
		{
			if(current->scope<scope)
			{
				symbolTable[i] = current;
				current = 0;
			}
			else if(current->scope == scope)
			{
				if(current->next)
				{
					symbolTable[i] = current->next;
					current = symbolTable[i];
				}
				else
				{
					symbolTable[i] = 0;
					current = 0;
				}
			}
		}
	}
}

TreeNode * interpreter_variables(TreeNode * root, int tab)
{
	int i;
	TreeNode * currentNode;	
	TreeNode * paramNode;	
	TreeNode * tempNode;	
	Symbol * param_list;	
	Symbol * temp_list;	 
	Symbol * current_list;	
	Symbol * currentSymbol;	

	currentNode = root;
	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable"))
		{

			paramNode = currentNode;
			if(paramNode->type == INT)
			{
				currentSymbol = interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_INT, 0, paramNode->left->lineno);
				interpreter_insertSymbol(currentSymbol);
				return interpreter_variables(root->sibling, tab);
			}
			else if(paramNode->type == DOUBLE)
			{
				currentSymbol = interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_DOUBLE, 0, paramNode->left->lineno);
				interpreter_insertSymbol(currentSymbol);
				return interpreter_variables(root->sibling, tab);
			}
			else if(paramNode->type == DATASET)
			{
				currentSymbol = interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_DATASET, 0, paramNode->left->lineno);
				interpreter_insertSymbol(currentSymbol);
				return interpreter_variables(root->sibling, tab);
			}
			else if(paramNode->type == STRING)
			{
				currentSymbol = interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_STRING, 0, paramNode->left->lineno);
				currentSymbol->is_file = paramNode->is_file;
				currentSymbol->is_input = paramNode->is_input;
				interpreter_insertSymbol(currentSymbol);
				return interpreter_variables(root->sibling, tab);
			}
		}
		else
		{
			return currentNode;
		}
	}
	else
	{
		return currentNode;
	}
}


TreeNode * interpreter_datasetList_label(TreeNode * root, int tab)
{
	TreeNode * holderNode;	
	TreeNode * holderNode2;	
	TreeNode * holderNode3;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	int i;


	currentNode = root;
	if(currentNode->type == VOID)
	{
		holderNode = newNode();
		holderNode->type = VOID;
		holderNode->tokenString = (char *) calloc(slength(currentNode->tokenString), sizeof(char));
		strcpy(holderNode->tokenString, currentNode->tokenString);
		if(currentNode->sibling)
		{
			holderNode->sibling = interpreter_datasetList_label(currentNode->sibling, tab);
		}
		else
		{
			holderNode->sibling = 0;
		}
		return holderNode;
	}
	else
	{
		holderNode = interpreter_subInt(currentNode, tab);
		if(currentNode->sibling)
		{
			holderNode->sibling = interpreter_datasetList_label(currentNode->sibling, tab);
		}
		else
		{
			holderNode->sibling = 0;
		}
		return holderNode;
	}
}

TreeNode * interpreter_datasetList_coordinate(TreeNode * root, int tab)
{
	TreeNode * holderNode;	
	TreeNode * holderNode2;	
	TreeNode * holderNode3;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	int i;


	currentNode = root;
	
	holderNode = newNode();
	holderNode->type = COORDINATE;
	holderNode->tokenString = (char *) calloc(9, sizeof(char));
	strcpy(holderNode->tokenString, "variable");

	holderNode->left = interpreter_subInt(currentNode->left, tab);
	holderNode->right = interpreter_subInt(currentNode->right, tab);
	if(currentNode->sibling)
	{
		holderNode->sibling = interpreter_datasetList_coordinate(currentNode->sibling, tab);
	}
	else
	{
		holderNode->sibling = 0;
	}
	return holderNode;
}

TreeNode * interpreter_subDataset(TreeNode * root, int tab)
{
	TreeNode * holderNode;	
	TreeNode * holderNode2;	
	TreeNode * holderNode3;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * holder_list;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	int i;


	currentNode = root;
	if(currentNode->type == ATTRIBUTE_JOIN)
	{
		holderNode = newNode();
		holderNode->type = ATTRIBUTE_JOIN;
		holderNode->tokenString = (char *) calloc(4, sizeof(char));
		strcpy(holderNode->tokenString, "[+]");
		holderNode->left = interpreter_subDataset(currentNode->left, tab);
		holderNode->right = interpreter_subDataset(currentNode->right, tab);
		return holderNode;
	}
	else if(currentNode->type == BLOCK_JOIN)
	{
		holderNode = newNode();
		holderNode->type = BLOCK_JOIN;
		holderNode->tokenString = (char *) calloc(4, sizeof(char));
		strcpy(holderNode->tokenString, "{+}");
		holderNode->left = interpreter_subDataset(currentNode->left, tab);
		holderNode->right = interpreter_subDataset(currentNode->right, tab);
		return holderNode;
	}
	else if(currentNode->type == '=')
	{
		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno)))
		{
			currentSymbol->value=interpreter_subDataset(currentNode->right, tab);
			return currentSymbol->value;
		}
	}
	else if(currentNode->type == READ
	|| currentNode->type == WRITE
	)
	{
			return interpreter_subInt(interpreter_subInt(currentNode, tab), tab);
	}
	else if(currentNode->type == STRING_LITERAL)
	{
		holderNode = newNode();
		holderNode->type = STRING_LITERAL;
		holderNode->tokenString = (char *) calloc(slength(currentNode->tokenString), sizeof(char));
		strcpy(holderNode->tokenString, currentNode->tokenString);
		return holderNode;
	}
	else if(currentNode->type==COMPOUND_DATASET)
	{
		holderNode = newNode();
		holderNode->type = COMPOUND_DATASET;
		holderNode->tokenString = (char *) calloc(13, sizeof(char));
		strcpy(holderNode->tokenString, "dataset []{}");
		holderNode->left = interpreter_subDataset(currentNode->left, tab);
		holderNode->right = newNode();
		holderNode->right->type = DATASET_INFO;
		holderNode->right->tokenString = (char *) calloc(5, sizeof(char));
		strcpy(holderNode->right->tokenString, "[]{}");

		if(currentNode->right->left)
		{
			holderNode->right->left = interpreter_datasetList_label(currentNode->right->left, tab);
		}
		if(currentNode->right->right)
		{
			holderNode->right->right = interpreter_datasetList_coordinate(currentNode->right->right, tab);
		}
		return holderNode;
	}
	else if(currentNode->type==IDENTIFIER)
	{
		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno)))
		{
			return currentSymbol->value;
		}
		else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
			holderNode = newNode();
			holderNode->type = STRING_LITERAL;
	
			holderNode->number = 0;
			holderNode->float_number = 0;
			holderNode->tokenString = (char *) calloc(slength(currentSymbol->value->tokenString), sizeof(char));
			strcpy(holderNode->tokenString, currentSymbol->value->tokenString);
	
			return holderNode;
		}
	}
	else if(currentNode->type==PAR)
	{
		return interpreter_function_call(currentNode, tab);
	}
}

TreeNode * interpreter_subInt(TreeNode * root, int tab)
{
	TreeNode * holderNode;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	TreeNode * leftNode;	
	TreeNode * rightNode;	
	Symbol * holder_list;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	Symbol * holderSymbol1;	
	Symbol * holderSymbol2;	
	Symbol * tempSymbol;	
	char * name;	
	currentNode = root;

	int length;
	int upper;
	int lower;
	int temp;
	int i;

	if(currentNode->type == '=')
	{
		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
		{
			currentSymbol->value=interpreter_subInt(currentNode->right, tab);
			currentSymbol->num=(int)currentSymbol->value->float_number;
			currentSymbol->value->number=(int)currentSymbol->value->float_number;
			currentSymbol->value->tokenString = (char *) calloc(20, sizeof(char));
			sprintf(currentSymbol->value->tokenString, "%d", currentSymbol->value->number);
			currentSymbol->value->is_double=0;
			currentSymbol->float_num=currentSymbol->value->float_number;
			return currentSymbol->value;
		}
		else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
		{
			currentSymbol->value=interpreter_subInt(currentNode->right, tab);
			currentSymbol->num=(int)currentSymbol->value->float_number;
			currentSymbol->float_num=currentSymbol->value->float_number;
			return currentSymbol->value;
		}
		else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{

			if(currentSymbol->is_file)
			{
				if(currentSymbol->is_input)
				{
					if(currentNode->right->type == IDENTIFIER)
					{
						currentSymbol->value=currentNode->right;
					}
					else
					{
						currentSymbol->value=interpreter_subInt(currentNode->right, tab);
					}
					if(currentSymbol->value->type == IDENTIFIER)
					{
						if(tempSymbol = interpreter_lookup(interpreter_newSymbol(currentSymbol->value->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
						{
							if(tempSymbol->is_file && tempSymbol->is_input)
							{
								currentSymbol->stream=tempSymbol->stream;
							}
							else
							{
								currentSymbol->stream=fopen(tempSymbol->value->tokenString, "r");
							}
						}
						
					}
					else
					{
						currentSymbol->stream=fopen(currentSymbol->value->tokenString, "r");
						currentSymbol->num=0;
						currentSymbol->float_num=0;

						currentSymbol->value = newNode();
						currentSymbol->value->type = IDENTIFIER;
						currentSymbol->value->tokenString = (char *) calloc(slength(currentSymbol->name), sizeof(char));
						strcpy(currentSymbol->value->tokenString, currentSymbol->name);
					}
					return currentSymbol->value;
				}
				else
				{
					if(currentNode->right->type == IDENTIFIER)
					{
						currentSymbol->value=currentNode->right;
					}
					else
					{
						currentSymbol->value=interpreter_subInt(currentNode->right, tab);
					}
					if(currentSymbol->value->type == IDENTIFIER)
					{
						if(tempSymbol = interpreter_lookup(interpreter_newSymbol(currentSymbol->value->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
						{
							if(tempSymbol->is_file && !tempSymbol->is_input)
							{
								currentSymbol->stream=tempSymbol->stream;
							}
							else
							{
								currentSymbol->stream=fopen(tempSymbol->value->tokenString, "w");
							}
						}
						
					}
					else
					{
						currentSymbol->stream=fopen(currentSymbol->value->tokenString, "w");
						currentSymbol->num=0;
						currentSymbol->float_num=0;

						currentSymbol->value = newNode();
						currentSymbol->value->type = IDENTIFIER;
						currentSymbol->value->tokenString = (char *) calloc(slength(currentSymbol->name), sizeof(char));
						strcpy(currentSymbol->value->tokenString, currentSymbol->name);
					}
					return currentSymbol->value;
				}
			}
			else
			{


				currentSymbol->value=interpreter_subInt(currentNode->right, tab);
				currentSymbol->num=0;
				currentSymbol->float_num=0;
				return currentSymbol->value;
			}
		}
	}
	else if(currentNode->type == READ)
	{
		leftNode= currentNode->left;
		if(currentNode->right->type==READ)
		{
			rightNode= interpreter_subInt(currentNode->right, tab);
		}
		else
		{
			rightNode= currentNode->right;
		}
		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(leftNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
			if(tempSymbol = interpreter_lookup(interpreter_newSymbol(rightNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				if(tempSymbol->is_file && tempSymbol->is_input)
				{
					currentSymbol->value = newNode();
					currentSymbol->value->type = STRING_LITERAL;
					currentSymbol->value->tokenString = get_novel_input(tempSymbol->stream, 0, 1);
					return rightNode;
				}
			}
		}
	}
	else if(currentNode->type == WRITE)
	{
		rightNode= interpreter_subInt(currentNode->right, tab);
		if(currentNode->left->type==WRITE)
		{
			leftNode= interpreter_subInt(currentNode->left, tab);
		}
		else
		{
			leftNode= currentNode->left;
		}
		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(leftNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
			if(currentSymbol->is_file && !currentSymbol->is_input)
			{
				fprintf(currentSymbol->stream, "%s", rightNode->tokenString);
				return leftNode;
			}
		}
	}
	else if(currentNode->type == '+')
	{
		holderNode = newNode();
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		if(leftNode->type==STRING_LITERAL || rightNode->type==STRING_LITERAL)
		{
			holderNode->type = STRING_LITERAL;

			holderNode->tokenString = (char *) calloc(slength(leftNode->tokenString)+slength(leftNode->tokenString), sizeof(char));
			strcpy(holderNode->tokenString, leftNode->tokenString);
			strcat(holderNode->tokenString, rightNode->tokenString);
		}
		else
		{
			holderNode->type = NUMBER;
			holderNode->is_double = leftNode->is_double+rightNode->is_double; 
			holderNode->number = leftNode->number + rightNode->number;
			holderNode->float_number = leftNode->float_number + rightNode->float_number;
			if(holderNode->is_double)
			{
				holderNode->tokenString = (char *) calloc(320, sizeof(char));
				sprintf(holderNode->tokenString, "%f", holderNode->float_number);
			}
			else
			{
				holderNode->tokenString = (char *) calloc(20, sizeof(char));
				sprintf(holderNode->tokenString, "%d", holderNode->number);
			}
		}
		return holderNode;
	}
	else if(currentNode->type == '-')
	{
		holderNode = newNode();
		holderNode->type = NUMBER;
		if(currentNode->left)
		{
			leftNode = interpreter_subInt(currentNode->left, tab);
			rightNode = interpreter_subInt(currentNode->right, tab);
			holderNode->is_double = leftNode->is_double+rightNode->is_double; 
			holderNode->number = leftNode->number - rightNode->number;
			holderNode->float_number = leftNode->float_number - rightNode->float_number;
		}
		else
		{
			rightNode = interpreter_subInt(currentNode->right, tab);
			holderNode->is_double = rightNode->is_double; 
			holderNode->number = - rightNode->number;
			holderNode->float_number = - rightNode->float_number;
		}
		if(holderNode->is_double)
		{
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%f", holderNode->float_number);
		}
		else
		{
			holderNode->tokenString = (char *) calloc(20, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		return holderNode;
	}
	else if(currentNode->type == '/')
	{
		holderNode = newNode();
		holderNode->type = NUMBER;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->is_double = leftNode->is_double+rightNode->is_double; 
		holderNode->number = leftNode->number / rightNode->number;
		holderNode->float_number = leftNode->float_number / rightNode->float_number;
		if(holderNode->is_double)
		{
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%f", holderNode->float_number);
		}
		else
		{
			holderNode->tokenString = (char *) calloc(20, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		return holderNode;
	}
	else if(currentNode->type == '*')
	{
		holderNode = newNode();
		holderNode->type = NUMBER;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->is_double = leftNode->is_double+rightNode->is_double; 
		holderNode->number = leftNode->number * rightNode->number;
		holderNode->float_number = leftNode->float_number * rightNode->float_number;
		if(holderNode->is_double)
		{
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%f", holderNode->float_number);
		}
		else
		{
			holderNode->tokenString = (char *) calloc(20, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		return holderNode;
	}
	else if(currentNode->type == '%')
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		holderNode->type = NUMBER;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->is_double = leftNode->is_double+rightNode->is_double; 
		holderNode->number = leftNode->number % rightNode->number;
		if(holderNode->is_double)
		{
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%f", holderNode->float_number);
		}
		else
		{
			holderNode->tokenString = (char *) calloc(20, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		return holderNode;
	}
	else if(currentNode->type == IE)
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);

		holderNode->type = NUMBER;
		if(!strcmp(leftNode->tokenString, rightNode->tokenString))
		{
			holderNode->number = 1;
			holderNode->float_number = 1;
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		else
		{
			holderNode->number = 0;
			holderNode->float_number = 0;
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		return holderNode;
	}
	else if(currentNode->type == NE)
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);

		holderNode->type = NUMBER;
		if(strcmp(leftNode->tokenString, rightNode->tokenString))
		{
			holderNode->number = 1;
			holderNode->float_number = 1;
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		else
		{
			holderNode->number = 0;
			holderNode->float_number = 0;
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		return holderNode;
	}
	else if(currentNode->type == LT)
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->type = NUMBER;

		holderNode->tokenString = (char *) calloc(2, sizeof(char));


		if(leftNode->type==STRING_LITERAL || rightNode->type==STRING_LITERAL)
		{
			if(strcmp(leftNode->tokenString,rightNode->tokenString)<0)
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}	
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}
		else
		{
			if((!leftNode->is_double && !rightNode->is_double) && (leftNode->number<rightNode->number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else if((leftNode->is_double || rightNode->is_double) && (leftNode->float_number<rightNode->float_number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}
		return holderNode;
	}
	else if(currentNode->type == LTE)
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->type = NUMBER;

		holderNode->tokenString = (char *) calloc(2, sizeof(char));

		if(leftNode->type==STRING_LITERAL || rightNode->type==STRING_LITERAL)
		{
			if(strcmp(leftNode->tokenString,rightNode->tokenString)<=0)
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}	
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}
		else
		{
			if((!leftNode->is_double && !rightNode->is_double) && (leftNode->number<=rightNode->number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else if((leftNode->is_double || rightNode->is_double) && (leftNode->float_number<=rightNode->float_number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}

		return holderNode;
	}
	else if(currentNode->type == GT)
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->type = NUMBER;

		holderNode->tokenString = (char *) calloc(2, sizeof(char));

		if(leftNode->type==STRING_LITERAL || rightNode->type==STRING_LITERAL)
		{
			if(strcmp(leftNode->tokenString,rightNode->tokenString)>0)
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}	
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}
		else
		{
			if((!leftNode->is_double && !rightNode->is_double) && (leftNode->number>rightNode->number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else if((leftNode->is_double || rightNode->is_double) && (leftNode->float_number>rightNode->float_number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}
		
		return holderNode;
	}
	else if(currentNode->type == GTE)
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		leftNode = interpreter_subInt(currentNode->left, tab);
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->type = NUMBER;

		holderNode->tokenString = (char *) calloc(2, sizeof(char));

		if(leftNode->type==STRING_LITERAL || rightNode->type==STRING_LITERAL)
		{
			if(strcmp(leftNode->tokenString,rightNode->tokenString)>=0)
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}	
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}
		else
		{
			if((!leftNode->is_double && !rightNode->is_double) && (leftNode->number>=rightNode->number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else if((leftNode->is_double || rightNode->is_double) && (leftNode->float_number>=rightNode->float_number))
			{
				strcpy(holderNode->tokenString, "1");
				holderNode->float_number =holderNode->number = 1;
			}
			else
			{
				strcpy(holderNode->tokenString, "0");
				holderNode->float_number =holderNode->number = 0;
			}
		}

		return holderNode;
	}
	else if(currentNode->type == NOT)
	{
		holderNode = newNode();
		holderNode->is_double = 0;
		rightNode = interpreter_subInt(currentNode->right, tab);
		holderNode->type = NUMBER;

		holderNode->number = !rightNode->number;
		holderNode->float_number = !rightNode->float_number;
		holderNode->tokenString = (char *) calloc(2, sizeof(char));
		if(!rightNode->is_double && holderNode->number)
		{
			strcpy(holderNode->tokenString, "1");
			holderNode->float_number =holderNode->number = 1;
		}
		else if(rightNode->is_double && holderNode->float_number)
		{
			strcpy(holderNode->tokenString, "1");
			holderNode->float_number =holderNode->number = 1;
		}
		else
		{
			strcpy(holderNode->tokenString, "0");
			holderNode->float_number =holderNode->number = 0;
		}
		
		return holderNode;
	}
	else if(currentNode->type==COMPOUND_DATASET)
	{
		leftNode = interpreter_datasetList_label(currentNode->right->left, tab);

		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
			length = slength(currentSymbol->value->tokenString);
			lower = leftNode->number;
			if(leftNode->sibling)
			{
				upper = leftNode->sibling->number;
			}
			else
			{
				upper = leftNode->number;
			}

			if(upper<0)
			{
				upper=0;
			}
			if(lower<0)
			{
				lower=0;
			}
			if(upper<lower)
			{
				temp=lower;
				lower=upper;
				upper=temp;
			}
			holderNode = newNode();
			holderNode->type = STRING_LITERAL;
	
			holderNode->number = 0;
			holderNode->float_number = 0;
			holderNode->tokenString = (char *) calloc(length, sizeof(char));
			if(lower>(length-1))
			{
				holderNode->tokenString[0]='\0';
			}
			else
			{
				for(i=0;(i<=(upper-lower))&&((i+lower)<(length-1)); i++)
				{
					holderNode->tokenString[i]=currentSymbol->value->tokenString[i+lower];
				}
				holderNode->tokenString[i]='\0';
				
			}
			return holderNode;
		}
		else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
		{
			length = slength(currentSymbol->value->tokenString);
			lower = leftNode->number;
			if(leftNode->sibling)
			{
				upper = leftNode->sibling->number;
			}
			else
			{
				upper = leftNode->number;
			}

			if(upper<0)
			{
				upper=0;
			}
			if(lower<0)
			{
				lower=0;
			}
			if(upper<lower)
			{
				temp=lower;
				lower=upper;
				upper=temp;
			}
			holderNode = newNode();
			holderNode->type = STRING_LITERAL;
	
			holderNode->number = 0;
			holderNode->float_number = 0;
			holderNode->tokenString = (char *) calloc(length, sizeof(char));
			if(lower>(length-1))
			{
				holderNode->tokenString[0]='\0';
			}
			else
			{
				for(i=0;(i<=(upper-lower))&&((i+lower)<(length-1)); i++)
				{
					holderNode->tokenString[i]=currentSymbol->value->tokenString[i+lower];
				}
				holderNode->tokenString[i]='\0';
				
			}
			return holderNode;
		}
		else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
		{
			length = slength(currentSymbol->value->tokenString);
			lower = leftNode->number;
			if(leftNode->sibling)
			{
				upper = leftNode->sibling->number;
			}
			else
			{
				upper = leftNode->number;
			}

			if(upper<0)
			{
				upper=0;
			}
			if(lower<0)
			{
				lower=0;
			}
			if(upper<lower)
			{
				temp=lower;
				lower=upper;
				upper=temp;
			}
			holderNode = newNode();
			holderNode->type = STRING_LITERAL;
	
			holderNode->number = 0;
			holderNode->float_number = 0;
			holderNode->tokenString = (char *) calloc(length, sizeof(char));
			if(lower>(length-1))
			{
				holderNode->tokenString[0]='\0';
			}
			else
			{
				for(i=0;(i<=(upper-lower))&&((i+lower)<(length-1)); i++)
				{
					holderNode->tokenString[i]=currentSymbol->value->tokenString[i+lower];
				}
				holderNode->tokenString[i]='\0';
				
			}
			return holderNode;
		}
	}
	else if(currentNode->type==IDENTIFIER)
	{
		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
		{
			holderNode = newNode();
			holderNode->type = NUMBER;
			holderNode->is_double = 0;
	
			holderNode->number = currentSymbol->num;
			holderNode->float_number = currentSymbol->float_num;
			holderNode->tokenString = (char *) calloc(20, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
	
			return holderNode;
		}
		else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
		{
			holderNode = newNode();
			holderNode->type = NUMBER;
			holderNode->is_double = 1;
	
			holderNode->number = currentSymbol->num;
			holderNode->float_number = currentSymbol->float_num;
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%f", holderNode->float_number);
	
			return holderNode;
		}
		else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{

			holderNode = newNode();
			holderNode->type = STRING_LITERAL;
	
			holderNode->number = 0;
			holderNode->float_number = 0;
			holderNode->tokenString = (char *) calloc(slength(currentSymbol->value->tokenString), sizeof(char));
			strcpy(holderNode->tokenString, currentSymbol->value->tokenString);
	
			return holderNode;
		}
	}
	else if(currentNode->type==NUMBER)
	{
		holderNode = newNode();
		holderNode->type = NUMBER;
		holderNode->number = currentNode->number;
		holderNode->is_double = currentNode->is_double;
		holderNode->float_number = currentNode->float_number;
		if(holderNode->is_double)
		{
			holderNode->tokenString = (char *) calloc(320, sizeof(char));
			sprintf(holderNode->tokenString, "%f", holderNode->float_number);
		}
		else
		{
			holderNode->tokenString = (char *) calloc(20, sizeof(char));
			sprintf(holderNode->tokenString, "%d", holderNode->number);
		}
		return holderNode;
	}
	else if(currentNode->type==STRING_LITERAL)
	{
		holderNode = newNode();
		holderNode->type = STRING_LITERAL;
		holderNode->number = 0;
		holderNode->float_number = 0;
		holderNode->tokenString = (char *) calloc(slength(currentNode->tokenString), sizeof(char));
		strcpy(holderNode->tokenString, currentNode->tokenString);
		return holderNode;
	}
	else if(currentNode->type==PAR)
	{
		return interpreter_function_call(currentNode, tab);
	}
}

TreeNode * interpreter_blockDataset(TreeNode * root, int tab)
{
	TreeNode * holderNode;	
	TreeNode * currentNode;	
	Symbol * holder_list;
	currentNode = root;


	holder_list = interpreter_newSymbol("return", tab, TYPE_DATASET, 0, tab);
	holder_list->num=0;
	holder_list->float_num=0;
	interpreter_insertSymbol(holder_list);

	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable")
		|| !strcmp(currentNode->tokenString, "function"))
		{
			root = interpreter_variables(root, tab);
		}
		holderNode = interpreter_traverse(root, tab);
		interpreter_popSymbolsByScope(tab);		
	}
	return holderNode;
}
TreeNode * interpreter_blockInt(TreeNode * root, int tab)
{
	TreeNode * result;	
	TreeNode * currentNode;	
	Symbol * holder_list;
	currentNode = root;

	holder_list = interpreter_newSymbol("return", tab, TYPE_INT, 0, tab);
	holder_list->num=0;
	holder_list->float_num=0;
	interpreter_insertSymbol(holder_list);

	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable")
		|| !strcmp(currentNode->tokenString, "function"))
		{
			root = interpreter_variables(root, tab);
		}
		result = interpreter_traverse(root, tab);
		interpreter_popSymbolsByScope(tab);
		return_flag = 0;
	}
	return result;
}
TreeNode * interpreter_blockDouble(TreeNode * root, int tab)
{
	TreeNode * result;	
	TreeNode * currentNode;	
	Symbol * holder_list;
	currentNode = root;

	holder_list = interpreter_newSymbol("return", tab, TYPE_DOUBLE, 0, tab);
	holder_list->num=0;
	holder_list->float_num=0;
	interpreter_insertSymbol(holder_list);

	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable")
		|| !strcmp(currentNode->tokenString, "function"))
		{
			root = interpreter_variables(root, tab);
		}
		result = interpreter_traverse(root, tab);
		interpreter_popSymbolsByScope(tab);
		return_flag = 0;
	}
	return result;
}
TreeNode * interpreter_blockString(TreeNode * root, int tab)
{
	TreeNode * result;	
	TreeNode * currentNode;	
	Symbol * holder_list;
	currentNode = root;

	holder_list = interpreter_newSymbol("return", tab, TYPE_STRING, 0, tab);
	holder_list->num=0;
	holder_list->float_num=0;
	interpreter_insertSymbol(holder_list);

	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable")
		|| !strcmp(currentNode->tokenString, "function"))
		{
			root = interpreter_variables(root, tab);
		}
		result = interpreter_traverse(root, tab);
		interpreter_popSymbolsByScope(tab);
		return_flag = 0;
	}
	return result;
}

TreeNode * interpreter_function_call(TreeNode * root, int tab)
{
	TreeNode * holderNode;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	TreeNode * leftNode;	
	TreeNode * rightNode;	
	TreeNode * tempNode2;	
	Symbol * holder_list;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * temp_list2;	
	Symbol * currentSymbol;	
	currentNode = root;

	if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 1, currentNode->left->lineno)))
	{
	}
	else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 1, currentNode->left->lineno)))
	{
	}
	else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 1, currentNode->left->lineno)))
	{
	}
	else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 1, currentNode->left->lineno)))
	{
	}

	if(currentSymbol->param_list)
	{
		if(currentNode->right)
		{
			paramNode = currentNode->right;
			current_list = currentSymbol->param_list;
			while(current_list)
			{
				if(paramNode)
				{
					if(paramNode->type == IDENTIFIER)
					{
						if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_DATASET && current_list->symbolType == TYPE_DATASET))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
						}
						else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->tokenString, tab, TYPE_INT, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_INT && current_list->symbolType == TYPE_INT))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
								holder_list->is_double=0;
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
							else if((currentSymbol->symbolType == TYPE_INT && current_list->symbolType == TYPE_DOUBLE))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DOUBLE, 0, paramNode->lineno);
								holder_list->is_double=1;
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
							else if((currentSymbol->symbolType == TYPE_INT && current_list->symbolType == TYPE_STRING))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
						}
						else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->tokenString, tab, TYPE_DOUBLE, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_DOUBLE && current_list->symbolType == TYPE_INT))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
							if((currentSymbol->symbolType == TYPE_DOUBLE && current_list->symbolType == TYPE_DOUBLE))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DOUBLE, 0, paramNode->lineno);
								holder_list->is_double=1;
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
							else if((currentSymbol->symbolType == TYPE_DOUBLE && current_list->symbolType == TYPE_STRING))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
						}
						else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->tokenString, tab, TYPE_STRING, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_STRING && current_list->symbolType == TYPE_STRING))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
							else if((currentSymbol->symbolType == TYPE_STRING && current_list->symbolType == TYPE_DATASET))
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
								holder_list->num=currentSymbol->num;
								holder_list->float_num=currentSymbol->float_num;
								holder_list->value=currentSymbol->value;
								interpreter_insertSymbol(holder_list);
							}
						}
					}
					else
					{
						if(current_list->symbolType == TYPE_DATASET)
						{
							if(paramNode->type == STRING_LITERAL)
							{
								holderNode = newNode();
								holderNode->type = STRING_LITERAL;
								holderNode->tokenString = (char *) calloc(slength(paramNode->tokenString), sizeof(char));
								strcpy(holderNode->tokenString, paramNode->tokenString);
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
								holder_list->value=holderNode;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == '=')
							{
								if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
									holder_list->value=interpreter_subDataset(paramNode, tab);
									interpreter_insertSymbol(holder_list);
									currentSymbol->value=holder_list->value;
								}
							}
							else if(paramNode->type == READ
							|| paramNode->type == WRITE
							)
							{
								if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_STRING, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
									holder_list->value=interpreter_subDataset(paramNode, tab);
									interpreter_insertSymbol(holder_list);
									currentSymbol->value=holder_list->value;
								}
							}
							else
							if(paramNode->type == ATTRIBUTE_JOIN)
							{
								holderNode = newNode();
								holderNode->type = ATTRIBUTE_JOIN;
								holderNode->tokenString = (char *) calloc(4, sizeof(char));
								strcpy(holderNode->tokenString, "[+]");
								holderNode->left = interpreter_subDataset(paramNode->left, tab);
								holderNode->right = interpreter_subDataset(paramNode->right, tab);
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
								holder_list->value=holderNode;
								interpreter_insertSymbol(holder_list);
							}
							else
							if(paramNode->type == BLOCK_JOIN)
							{
								holderNode = newNode();
								holderNode->type = BLOCK_JOIN;
								holderNode->tokenString = (char *) calloc(4, sizeof(char));
								strcpy(holderNode->tokenString, "{+}");
								holderNode->left = interpreter_subDataset(paramNode->left, tab);
								holderNode->right = interpreter_subDataset(paramNode->right, tab);
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
								holder_list->value=holderNode;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type==COMPOUND_DATASET)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
								holder_list->value=interpreter_subDataset(paramNode, tab);
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type==PAR)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DATASET, 0, paramNode->lineno);
								holder_list->value=interpreter_subDataset(paramNode, tab);
								interpreter_insertSymbol(holder_list);
							}
						}
						else if( current_list->symbolType == TYPE_INT)
						{
							if(paramNode->type == NUMBER)
							{
								holderNode = newNode();
								holderNode->type = NUMBER;
								holderNode->tokenString = (char *) calloc(slength(paramNode->tokenString), sizeof(char));
								strcpy(holderNode->tokenString, paramNode->tokenString);
								holderNode->number=paramNode->number;
								holderNode->float_number=paramNode->float_number;
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
								holder_list->value=holderNode;
								holder_list->num=paramNode->number;
								holder_list->float_num=paramNode->float_number;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == '=')
							{
								if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_INT, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									holder_list->num=holder_list->value->number;
									holder_list->float_num=holder_list->value->float_number;
									interpreter_insertSymbol(holder_list);
								}
								else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_DOUBLE, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									holder_list->num=holder_list->value->number;
									holder_list->float_num=holder_list->value->float_number;
									interpreter_insertSymbol(holder_list);
								}
							}
							else 
							if(paramNode->type == '+'
							|| paramNode->type == '-'
							|| paramNode->type == '/'
							|| paramNode->type == '*'
							|| paramNode->type == '%'
							|| paramNode->type == IE
							|| paramNode->type == NE
							|| paramNode->type == LT
							|| paramNode->type == LTE
							|| paramNode->type == GT
							|| paramNode->type == GTE
							|| paramNode->type == NOT
							)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
								holder_list->value=interpreter_subInt(paramNode, tab);
								holder_list->num=holder_list->value->number;
								holder_list->float_num=holder_list->value->float_number;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == PAR)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
								holder_list->value=interpreter_subInt(paramNode, tab);
								holder_list->num=holder_list->value->number;
								holder_list->float_num=holder_list->value->float_number;
								interpreter_insertSymbol(holder_list);
							}
						}
						else if( current_list->symbolType == TYPE_DOUBLE)
						{
							if(paramNode->type == NUMBER)
							{
								holderNode = newNode();
								holderNode->type = NUMBER;
								holderNode->tokenString = (char *) calloc(slength(paramNode->tokenString), sizeof(char));
								strcpy(holderNode->tokenString, paramNode->tokenString);
								holderNode->is_double=1;
								holderNode->number=paramNode->number;
								holderNode->float_number=paramNode->float_number;
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DOUBLE, 0, paramNode->lineno);
								holder_list->value=holderNode;
								holder_list->num=paramNode->number;
								holder_list->float_num=paramNode->float_number;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == '=')
							{
								if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_INT, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DOUBLE, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									holder_list->value->is_double=1;
									holder_list->num=holder_list->value->number;
									holder_list->float_num=holder_list->value->float_number;
									interpreter_insertSymbol(holder_list);
								}
								else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_DOUBLE, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DOUBLE, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									holder_list->value->is_double=1;
									holder_list->num=holder_list->value->number;
									holder_list->float_num=holder_list->value->float_number;
									interpreter_insertSymbol(holder_list);
								}
							}
							else 
							if(paramNode->type == '+'
							|| paramNode->type == '-'
							|| paramNode->type == '/'
							|| paramNode->type == '*'
							|| paramNode->type == IE
							|| paramNode->type == NE
							|| paramNode->type == LT
							|| paramNode->type == LTE
							|| paramNode->type == GT
							|| paramNode->type == GTE
							|| paramNode->type == NOT
							)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DOUBLE, 0, paramNode->lineno);
								holder_list->value=interpreter_subInt(paramNode, tab);
								holder_list->value->is_double=1;
								holder_list->num=holder_list->value->number;
								holder_list->float_num=holder_list->value->float_number;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == PAR)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_DOUBLE, 0, paramNode->lineno);
								holder_list->value=interpreter_subInt(paramNode, tab);
								holder_list->value->is_double=1;
								holder_list->num=holder_list->value->number;
								holder_list->float_num=holder_list->value->float_number;
								interpreter_insertSymbol(holder_list);
							}
						}
						else if( current_list->symbolType == TYPE_STRING)
						{
							if(paramNode->type == STRING_LITERAL)
							{
								holderNode = newNode();
								holderNode->type = STRING_LITERAL;
								holderNode->tokenString = (char *) calloc(slength(paramNode->tokenString), sizeof(char));
								strcpy(holderNode->tokenString, paramNode->tokenString);
								holderNode->number=0;
								holderNode->float_number=0;
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_INT, 0, paramNode->lineno);
								holder_list->value=holderNode;
								holder_list->num=0;
								holder_list->float_num=0;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == '=')
							{
								if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_STRING, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									holder_list->num=0;
									holder_list->float_num=0;
									interpreter_insertSymbol(holder_list);
								}
								else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_INT, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									holder_list->num=0;
									holder_list->float_num=0;
									interpreter_insertSymbol(holder_list);
								}
								else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_DOUBLE, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									holder_list->num=0;
									holder_list->float_num=0;
									interpreter_insertSymbol(holder_list);
								}
							}
							else if(paramNode->type == READ
							|| paramNode->type == WRITE
							)
							{
								if(currentSymbol = interpreter_lookup(interpreter_newSymbol(paramNode->left->tokenString, tab, TYPE_STRING, 0, paramNode->lineno)))
								{
									holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
									holder_list->value=interpreter_subInt(paramNode, tab);
									interpreter_insertSymbol(holder_list);
									currentSymbol->value=holder_list->value;
								}
							}
							else 
							if(paramNode->type == '+'
							)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
								holder_list->value=interpreter_subInt(paramNode, tab);
								holder_list->num=0;
								holder_list->float_num=0;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == PAR)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
								holder_list->value=interpreter_subInt(paramNode, tab);
								holder_list->num=0;
								holder_list->float_num=0;
								interpreter_insertSymbol(holder_list);
							}
							else if(paramNode->type == COMPOUND_DATASET)
							{
								holder_list = interpreter_newSymbol(current_list->name, tab+1, TYPE_STRING, 0, paramNode->lineno);
								holder_list->value=interpreter_subInt(paramNode, tab);
								holder_list->num=0;
								holder_list->float_num=0;
								interpreter_insertSymbol(holder_list);
							}
						}
					}
					temp_list=current_list->next;
					current_list = temp_list;
					tempNode = paramNode->sibling;
					paramNode = tempNode;
				}
			}
		}
	}
	if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 1, currentNode->left->lineno)))
	{
		return interpreter_blockInt(currentSymbol->instructions, tab+1);
	}
	else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 1, currentNode->left->lineno)))
	{
		return interpreter_blockDouble(currentSymbol->instructions, tab+1);
	}
	else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 1, currentNode->left->lineno)))
	{
		return interpreter_blockInt(currentSymbol->instructions, tab+1);
	}
	else if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 1, currentNode->left->lineno)))
	{
		return interpreter_blockDataset(currentSymbol->instructions, tab+1);
	}

}

TreeNode * interpreter_traverse(TreeNode * root, int tab)
{
	TreeNode * decision;
	TreeNode * return_value;
	int i;
	TreeNode * for_current;	
	TreeNode * for_temp;	
	TreeNode * for_last;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	Symbol * returnSymbol;	

	currentNode = root;
	if(currentNode)
	{
		if(currentNode->type == '='
		)
		{
			if(interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				return_value = interpreter_subInt(currentNode, tab);
			}
			else if(interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				return_value = interpreter_subInt(currentNode, tab);
			}
			else if(interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno)))
			{
				return_value = interpreter_subDataset(currentNode, tab);
			}
			else if(interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				return_value = interpreter_subInt(currentNode, tab);
			}
		}
		else if(currentNode->type == READ
		|| currentNode->type == WRITE
		)
		{
			return_value = interpreter_subInt(currentNode, tab);
		}
		else
		if(currentNode->type == ATTRIBUTE_JOIN
		|| currentNode->type == BLOCK_JOIN
		)
		{
			interpreter_subDataset(currentNode, tab);
		}
		else 
		if(currentNode->type == '+'
		|| currentNode->type == '-'
		|| currentNode->type == '/'
		|| currentNode->type == '*'
		|| currentNode->type == '%'
		|| currentNode->type == IE
		|| currentNode->type == NE
		|| currentNode->type == LT
		|| currentNode->type == LTE
		|| currentNode->type == GT
		|| currentNode->type == GTE
		)
		{
			interpreter_subInt(currentNode, tab);
		}
		else if(currentNode->type == NOT)
		{
			interpreter_subInt(currentNode, tab);
		}
		else if(currentNode->type == '-')
		{
			interpreter_subInt(currentNode, tab);
		}
		else if(currentNode->type==COMPOUND_DATASET)
		{
			interpreter_subDataset(currentNode, tab);
		}
		else if(currentNode->type==IDENTIFIER)
		{
			if(interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				interpreter_subInt(currentNode, tab);
			}
			else if(interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				interpreter_subInt(currentNode, tab);
			}
			else if(interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno)))
			{
				interpreter_subDataset(currentNode, tab);
			}
			else if(interpreter_lookup(interpreter_newSymbol(currentNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				interpreter_subInt(currentNode, tab);
			}
		}
		else if(currentNode->type==RETURN)
		{
			if(currentNode->left)
			{
				if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_INT, 0, tab)))
				{
					returnSymbol->num = 1;
					returnSymbol->float_num = 1;
					return_value = interpreter_subInt(currentNode->left, tab);
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DOUBLE, 0, tab)))
				{
					returnSymbol->num = 1;
					returnSymbol->float_num = 1;
					return_value = interpreter_subInt(currentNode->left, tab);
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_STRING, 0, tab)))
				{
					returnSymbol->num = 1;
					returnSymbol->float_num = 1;
					return_value = interpreter_subInt(currentNode->left, tab);
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DATASET, 0, tab)))
				{
					returnSymbol->num = 1;
					returnSymbol->float_num = 1;
					return_value = interpreter_subDataset(currentNode->left, tab);
				}
			}
		}
		else 
		if(currentNode->type==FOR)
		{
			for_current = currentNode->left;
			for_temp = for_current->sibling;
			for_last = for_temp->sibling;
			interpreter_subInt(for_current, tab);
			decision = interpreter_subInt(for_temp, tab);
			while(decision->number)
			{
				if(currentNode->right)
				{
					return_value = interpreter_traverse(currentNode->right, tab);
				}
				if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_INT, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DOUBLE, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_STRING, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DATASET, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				interpreter_subInt(for_last, tab);
				decision = interpreter_subInt(for_temp, tab);
			}
		}
		else 
		if(currentNode->type==DO)
		{
			for_current = currentNode->left;
			do
			{
				if(currentNode->right)
				{
					return_value = interpreter_traverse(currentNode->right, tab);
				}
				if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_INT, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DOUBLE, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_STRING, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DATASET, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				decision = interpreter_subInt(for_current, tab);
			}while(decision->number);
		}
		else 
		if(currentNode->type==WHILE)
		{
			for_current = currentNode->left;
			decision = interpreter_subInt(for_current, tab);
			while(decision->number)
			{
				if(currentNode->right)
				{
					return_value = interpreter_traverse(currentNode->right, tab);
				}
				if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_INT, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DOUBLE, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_STRING, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DATASET, 0, tab)))
				{
					if(returnSymbol->num)
					{
						break;
					}
				}
				decision = interpreter_subInt(for_current, tab);
			}
		}
		else 
		if(currentNode->type==IF)
		{
			for_current = currentNode->left;
			decision = interpreter_subInt(for_current, tab);
			if(decision->number)
			{
				return_value = interpreter_traverse(currentNode->right, tab);
			}
			else if(currentNode->otherChild)
			{
				return_value = interpreter_traverse(currentNode->otherChild, tab);
			}
		}
		else if(currentNode->type==PAR)
		{
			interpreter_function_call(currentNode, tab);
		}

		if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_INT, 0, tab)))
		{
			if(returnSymbol->num)
			{
				return return_value;
			}
		}
		else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DOUBLE, 0, tab)))
		{
			if(returnSymbol->num)
			{
				return return_value;
			}
		}
		else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_STRING, 0, tab)))
		{
			if(returnSymbol->num)
			{
				return return_value;
			}
		}
		else if(returnSymbol = interpreter_lookup(interpreter_newSymbol("return", tab, TYPE_DATASET, 0, tab)))
		{
			if(returnSymbol->num)
			{
				return return_value;
			}
		}

		if(currentNode->sibling)
		{
			return interpreter_traverse((currentNode->sibling), tab);
		}	
	} 
	return 0;
	
}

void interpreter_printTableRow(Symbol * s1)
{
	if(s1->next)
	{
		printTableRow(s1->next);
	}
	printf("name:%s function:%d\n"/*instructions:%d*/, s1->name, s1->function, s1->instructions);
}

void interpreter_deleteTableRow(Symbol * s1)
{
	if(s1->next)
	{
		interpreter_deleteTableRow(s1->next);
	}
	free(s1);
}

TreeNode * interpreter_analyze(TreeNode * root)
{
	Symbol * s1;
	Symbol * s2;
	Symbol * s3;
	Symbol * s4;
	Symbol * currentSymbol;
	Symbol * current_list;
	int i;
	int j;
	char name[255];
/*
	for(i=0; i<26; i++)
	{
		symbolTable[i] = 0;
	}
*/

	analyze(root, 0);

	for(j=0;j<26;j++)
	{
		if(symbolTable[j])
		{
			symbolTable[j]=get_symbolTable(j);
		}
	}
	for(j=0;j<255;j++)
	{
		name[j]='\0';
	}
	name[0]='m';
	name[1]='a';
	name[2]='i';
	name[3]='n';
	if(currentSymbol = interpreter_lookup(interpreter_newSymbol(name, 0, TYPE_DATASET, 1, 0)))
	{
		return_flag = 0;
		root = interpreter_blockDataset(currentSymbol->instructions, 1);
	}
	
/*
		printTree(root, 0);
*/	
/*
	for(j=0;j<26;j++)
	{
		if(symbolTable[j])
		{
			interpreter_deleteTableRow(symbolTable[j]);
			symbolTable[j]=0;
		}
	}
*/
	return root;
}

void interpreter_set_main_found(int val)
{
	main_found=0;
}
int interpreter_get_main_found()
{
	return main_found;
}
/*
int main(int argc, char *argv[], char *envp[])
{
	int holder;
	int i;
	FILE * input;
	TreeNode *root;
	
	for(i=1;i<argc;i++)
	{
		printf("%s:\n", argv[i]);
		input = fopen(argv[i], "r");
		stdin = input;
		setLine();
		main_found=0;

		root = interpreter_analyze();

		printTree(root, 0);

		fclose(input);
	}
	return 0;
}
*/


