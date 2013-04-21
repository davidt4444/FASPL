/*
David Thigpen
*/

#include "header.h"

void scopeError()
{ 
	printf("\n>>> ");
	printf("Scope error: You aren't popping all of the variables at higher scopes\n");
	Error = TRUE;
	exit(0);
}

void voidMainError()
{ 
	printf("\n>>> ");
	printf("Main error: You shouldn't have a main with data type void\n");
	Error = TRUE;
	exit(0);
}

void doubleMainError()
{ 
	printf("\n>>> ");
	printf("Main error: You shouldn't have a main with data type double\n");
	Error = TRUE;
	exit(0);
}

void intMainError()
{ 
	printf("\n>>> ");
	printf("Main error: You shouldn't have a main with data type int\n");
	Error = TRUE;
	exit(0);
}

void stringMainError()
{ 
	printf("\n>>> ");
	printf("Main error: You shouldn't have a main with data type string\n");
	Error = TRUE;
	exit(0);
}

void mainNotFoundError()
{ 
	printf("\n>>> ");
	printf("Main error: You need to have a main function of type dataset at the end of your program\n");
	Error = TRUE;
	exit(0);
}

void mainParamNotVoid()
{ 
	printf("\n>>> ");
	printf("Main error: Your main function does not have a void parameter list\n");
	Error = TRUE;
	exit(0);
}

void mainNotLastError()
{ 
	printf("\n>>> ");
	printf("Main error: Main should be the last declaration in a program\n");
	Error = TRUE;
	exit(0);
}

void mainDeclaredMultipleTimes()
{ 
	printf("\n>>> ");
	printf("Main error: Main is being declared multiple times in the program\n");
	Error = TRUE;
	exit(0);
}

void semanticIntError(char * message)
{ 
	printf("\n>>> ");
	printf("Semantic error at line %d: %s\n", currentLine, message);
	Error = TRUE;
	exit(0);
}
void semanticSymbolError(char * message)
{ 
	printf("\n>>> ");
	printf("Semantic error variable %s at line %d: %s\n",currentIdentifier, currentLine, message);
	Error = TRUE;
	exit(0);
}
void returnTypeMismatchError(int errorLineNumber)
{ 
	printf("\n>>> ");
	printf("Semantic error at line %d: The returned value does not match the type that is required by the function.\n", errorLineNumber);
	Error = TRUE;
	exit(0);
}
void returnMissingError(char * message)
{ 
	printf("\n>>> ");
	printf("Semantic error function %s is missing a return value.\n", message);
	Error = TRUE;
	exit(0);
}

Symbol * newSymbol(char * name, int scope, Type symbolType, int function, int lineno)
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
	s->offset=0;
	s->num=0;
	s->float_num=0;
	s->value=0;
	s->is_double=0;
	s->is_file=0;
	s->is_input=0;
	s->stream=0;
	return s;
}

Symbol * lookup(Symbol * s)
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

void insertSymbol(Symbol * s)
{
	Symbol * s1;

	if(!symbolTable[s->name[0]%26])
	{
		symbolTable[s->name[0]%26] = s;	
	}
	else if(lookup(s) && !strcmp(symbolTable[s->name[0]%26]->name, s->name) && (symbolTable[s->name[0]%26]->scope == s->scope))
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

void popSymbolsByScope(int scope)
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
			else
			{
				/* You shouldn't be here */
				scopeError();				
			}
		}
	}
}

void variables(TreeNode * root, int tab)
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
			if(main_found && tab==0)
			{
				if(currentNode->left && !strcmp(currentNode->left->tokenString, "main"))
				{
					mainDeclaredMultipleTimes();
				}
				else
				{
					mainNotLastError();					
				}
			}

			paramNode = currentNode;
			if(paramNode->type == INT)
			{
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_INT, 0, paramNode->left->lineno);
				insertSymbol(currentSymbol);
				variables(root->sibling, tab);
			}
			else if(paramNode->type == DOUBLE)
			{
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_DOUBLE, 0, paramNode->left->lineno);
				insertSymbol(currentSymbol);
				variables(root->sibling, tab);
			}
			else if(paramNode->type == STRING)
			{
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_STRING, 0, paramNode->left->lineno);
				currentSymbol->is_file = paramNode->is_file;
				currentSymbol->is_input = paramNode->is_input;
				insertSymbol(currentSymbol);
				variables(root->sibling, tab);
			}
			else if(paramNode->type == DATASET)
			{
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_DATASET, 0, paramNode->left->lineno);
				insertSymbol(currentSymbol);
				variables(root->sibling, tab);
			}
		}
		else if(!strcmp(currentNode->tokenString, "function"))
		{
			if(main_found && tab==0)
			{
				if(currentNode->left && !strcmp(currentNode->left->left->tokenString, "main"))
				{
					mainDeclaredMultipleTimes();
				}
				else
				{
					mainNotLastError();					
				}
			}
			if(tab!=0)
			{
				currentIdentifier = currentNode->left->left->tokenString;
				currentLine = currentNode->left->left->lineno;
				semanticSymbolError("Cannot declare a function inside another function.");
			}
			else
			{
				popSymbolsByScope(tab+1);
			}
			paramNode = currentNode->left;
			if(paramNode->type == DATASET)
			{
				return_dataset = 1;
				return_int = 0;
				return_double = 0;
				return_string = 0;

				if(!strcmp(paramNode->left->tokenString, "main"))
				{
					main_found = 1;					
					if(paramNode->right)
					{
						mainParamNotVoid();
					}
				}
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_DATASET, 1, paramNode->left->lineno);
				if(paramNode->right)
				{
					tempNode = paramNode->right;
					paramNode = tempNode;

					if(!strcmp(paramNode->tokenString, "variable"))
					{
						if(paramNode->type == INT)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == STRING)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
							current_list->is_file = paramNode->is_file;
							current_list->is_input = paramNode->is_input;
							insertSymbol(current_list);
						}
						else if(paramNode->type == DOUBLE)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == DATASET)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						param_list = current_list;
						i=0;
					}
					tempNode = paramNode->sibling;
					paramNode = tempNode;

					while(paramNode)
					{
						if(!strcmp(paramNode->tokenString, "variable"))
						{
							if(paramNode->type == INT)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DOUBLE)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == STRING)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
								current_list->next->is_file = paramNode->is_file;
								current_list->next->is_input = paramNode->is_input;
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DATASET)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
						}
						tempNode = paramNode->sibling;
						paramNode = tempNode;

						temp_list = current_list->next;
						current_list = temp_list;
					}
					currentSymbol->param_list = param_list;
				}
				currentSymbol->instructions = currentNode->right;
				insertSymbol(currentSymbol);

				return_flag=0;
				block(currentNode->right, tab+1);
				if(!return_flag)
				{
					returnMissingError(currentNode->left->left->tokenString);
				}
				variables(root->sibling, tab);
			}
			else if(paramNode->type == INT)
			{
				return_int = 1;
				return_double = 0;
				return_dataset = 0;
				return_string = 0;

				if(!strcmp(paramNode->left->tokenString, "main"))
				{
					intMainError();					
				}
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_INT, 1, paramNode->left->lineno);
				if(paramNode->right)
				{
					tempNode = paramNode->right;
					paramNode = tempNode;

					if(!strcmp(paramNode->tokenString, "variable"))
					{
						if(paramNode->type == INT)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == DOUBLE)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == DATASET)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == STRING)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
							current_list->is_file = paramNode->is_file;
							current_list->is_input = paramNode->is_input;
							insertSymbol(current_list);
						}
						param_list = current_list;
						i=0;
					}
					tempNode = paramNode->sibling;
					paramNode = tempNode;

					while(paramNode)
					{
						if(!strcmp(paramNode->tokenString, "variable"))
						{
							if(paramNode->type == INT)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DOUBLE)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DATASET)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == STRING)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
								current_list->next->is_file = paramNode->is_file;
								current_list->next->is_input = paramNode->is_input;
								insertSymbol(current_list->next);
							}
						}
						tempNode = paramNode->sibling;
						paramNode = tempNode;

						temp_list = current_list->next;
						current_list = temp_list;
					}
					currentSymbol->param_list = param_list;
				}
				currentSymbol->instructions = currentNode->right;
				insertSymbol(currentSymbol);

				return_flag=0;
				block(currentNode->right, tab+1);
				if(!return_flag)
				{
					returnMissingError(currentNode->left->left->tokenString);
				}
				variables(root->sibling, tab);
			}
			else if(paramNode->type == DOUBLE)
			{
				return_int = 0;
				return_double = 1;
				return_dataset = 0;
				return_string = 0;

				if(!strcmp(paramNode->left->tokenString, "main"))
				{
					doubleMainError();					
				}
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_DOUBLE, 1, paramNode->left->lineno);
				if(paramNode->right)
				{
					tempNode = paramNode->right;
					paramNode = tempNode;

					if(!strcmp(paramNode->tokenString, "variable"))
					{
						if(paramNode->type == INT)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == DOUBLE)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == DATASET)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == STRING)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
							current_list->is_file = paramNode->is_file;
							current_list->is_input = paramNode->is_input;
							insertSymbol(current_list);
						}
						param_list = current_list;
						i=0;
					}
					tempNode = paramNode->sibling;
					paramNode = tempNode;

					while(paramNode)
					{
						if(!strcmp(paramNode->tokenString, "variable"))
						{
							if(paramNode->type == INT)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DOUBLE)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DATASET)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == STRING)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
								current_list->next->is_file = paramNode->is_file;
								current_list->next->is_input = paramNode->is_input;
								insertSymbol(current_list->next);
							}
						}
						tempNode = paramNode->sibling;
						paramNode = tempNode;

						temp_list = current_list->next;
						current_list = temp_list;
					}
					currentSymbol->param_list = param_list;
				}
				currentSymbol->instructions = currentNode->right;
				insertSymbol(currentSymbol);

				return_flag=0;
				block(currentNode->right, tab+1);
				if(!return_flag)
				{
					returnMissingError(currentNode->left->left->tokenString);
				}
				variables(root->sibling, tab);
			}
			else if(paramNode->type == STRING)
			{
				return_int = 0;
				return_double = 0;
				return_string = 1;
				return_dataset = 0;

				if(!strcmp(paramNode->left->tokenString, "main"))
				{
					stringMainError();					
				}
				currentSymbol = newSymbol(paramNode->left->tokenString, tab, TYPE_STRING, 1, paramNode->left->lineno);
				if(paramNode->right)
				{
					tempNode = paramNode->right;
					paramNode = tempNode;

					if(!strcmp(paramNode->tokenString, "variable"))
					{
						if(paramNode->type == INT)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == DOUBLE)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						else if(paramNode->type == STRING)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
							current_list->is_file = paramNode->is_file;
							current_list->is_input = paramNode->is_input;
							insertSymbol(current_list);
						}
						else if(paramNode->type == DATASET)
						{
							current_list = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
							insertSymbol(current_list);
						}
						param_list = current_list;
						i=0;
					}
					tempNode = paramNode->sibling;
					paramNode = tempNode;

					while(paramNode)
					{
						if(!strcmp(paramNode->tokenString, "variable"))
						{
							if(paramNode->type == INT)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_INT, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DOUBLE)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DOUBLE, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == STRING)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_STRING, 0, paramNode->left->lineno);
								current_list->next->is_file = paramNode->is_file;
								current_list->next->is_input = paramNode->is_input;
								insertSymbol(current_list->next);
							}
							else if(paramNode->type == DATASET)
							{
								current_list->next = newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno);
								insertSymbol(current_list->next);
							}
						}
						tempNode = paramNode->sibling;
						paramNode = tempNode;

						temp_list = current_list->next;
						current_list = temp_list;
					}
					currentSymbol->param_list = param_list;
				}
				currentSymbol->instructions = currentNode->right;
				insertSymbol(currentSymbol);

				return_flag=0;
				block(currentNode->right, tab+1);
				if(!return_flag)
				{
					returnMissingError(currentNode->left->left->tokenString);
				}
				variables(root->sibling, tab);
			}
		}
	}
}

int datasetList_label(TreeNode * root, int tab)
{
	if(root->type==VOID){}
	else
	{
		subString(root, tab);
	}
	if(root->sibling)
	{
		datasetList_label(root->sibling, tab);
	}
	return 1;
}

int datasetList_coordinate(TreeNode * root, int tab)
{
	if(root->type==COORDINATE)
	{
		subInt(root->left, tab);
		subInt(root->right, tab);
	}
	if(root->sibling)
	{
		datasetList_coordinate(root->sibling, tab);
	}
	return 1;
}

int subDataset(TreeNode * root, int tab)
{
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	int i;


	currentNode = root;
	if(currentNode->type == ATTRIBUTE_JOIN
		|| currentNode->type == BLOCK_JOIN
		|| currentNode->type == '='
		)
	{
		subDataset(currentNode->left, tab);
		subDataset(currentNode->right, tab);
	}
	else if(currentNode->type == READ
		|| currentNode->type == WRITE
		)
	{
		subString(currentNode->left, tab);
		subString(currentNode->right, tab);
	}
	else if(currentNode->type == STRING || currentNode->type == STRING_LITERAL)
	{
	}
	else if(currentNode->type==COMPOUND_DATASET)
	{
		subDataset(currentNode->left, tab);
		if(currentNode->right->right)
		{
			datasetList_coordinate(currentNode->right->right, tab);
		}
		if(currentNode->right->left)
		{
			datasetList_label(currentNode->right->left, tab);
		}
	}
	else if(currentNode->type==IDENTIFIER)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno)))
		{
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
		}
		else
		{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
		}
	}
	else if(currentNode->type==PAR)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else
		{
			currentIdentifier = currentNode->left->tokenString;
			currentLine = currentNode->left->lineno;
			semanticSymbolError("This is an undefined function. ");
		}
	}
	else
	{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticIntError("This expression is not the required type of dataset.");
	}
	return 1;
}

int subInt(TreeNode * root, int tab)
{
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	currentNode = root;
	if(currentNode->type == '='
	|| currentNode->type == '+'
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
		if(currentNode->left)
		{
			subInt(currentNode->left, tab);
		}
		subInt(currentNode->right, tab);
	}
	else if(currentNode->type == NOT)
	{
		subInt(currentNode->right, tab);
	}
	else if(currentNode->type==IDENTIFIER)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
		{
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
		{
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
		}
		else
		{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
		}
	}
	else if(currentNode->type==NUMBER)
	{
	}
	else if(currentNode->type==STRING)
	{
	}
	else if(currentNode->type==STRING_LITERAL)
	{
	}
	else if(currentNode->type==COMPOUND_DATASET)
	{
		subString(currentNode->left, tab);
		datasetList_coordinate(currentNode->right->left, tab);
		if(currentNode->right->right)
		{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticSymbolError("You cannot use {} with strings.");
		}
	}
	else if(currentNode->type==PAR)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else
		{
			currentIdentifier = currentNode->left->tokenString;
			currentLine = currentNode->left->lineno;
			semanticSymbolError("This is an undefined function. ");
		}
	}
	else
	{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticIntError("This expression is not the required type of int.");
	}
	return 1;
}

int subDouble(TreeNode * root, int tab)
{
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	currentNode = root;
	if(currentNode->type == '='
	|| currentNode->type == '+'
	|| currentNode->type == '-'
	|| currentNode->type == '/'
	|| currentNode->type == '*'
	|| currentNode->type == IE
	|| currentNode->type == NE
	|| currentNode->type == LT
	|| currentNode->type == LTE
	|| currentNode->type == GT
	|| currentNode->type == GTE
	)
	{
		if(currentNode->left)
		{
			subDouble(currentNode->left, tab);
		}
		subDouble(currentNode->right, tab);
	}
	else if(currentNode->type == '%')
	{
		subInt(currentNode->left, tab);
		subInt(currentNode->right, tab);
	}
	else if(currentNode->type == NOT)
	{
		subDouble(currentNode->right, tab);
	}
	else if(currentNode->type==IDENTIFIER)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
		{
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
		{
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
		}
		else
		{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
		}
	}
	else if(currentNode->type==NUMBER)
	{
	}
	else if(currentNode->type==STRING)
	{
	}
	else if(currentNode->type==STRING_LITERAL)
	{
	}
	else if(currentNode->type==COMPOUND_DATASET)
	{
		subString(currentNode->left, tab);
		datasetList_coordinate(currentNode->right->left, tab);
		if(currentNode->right->right)
		{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticSymbolError("You cannot use {} with strings.");
		}
	}
	else if(currentNode->type==PAR)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else
		{
			currentIdentifier = currentNode->left->tokenString;
			currentLine = currentNode->left->lineno;
			semanticSymbolError("This is an undefined function. ");
		}
	}
	else
	{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticIntError("This expression is not the required type of double.");
	}
	return 1;
}

int subString(TreeNode * root, int tab)
{
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	Symbol * tempSymbol;	
	currentNode = root;

	if(currentNode->type == '=')
	{
/*
		if(currentSymbol = interpreter_lookup(interpreter_newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{

			if(currentSymbol->is_file)
			{
				if(currentSymbol->is_input)
				{
					if(currentNode->right->type == IDENTIFIER)
					{
						currentSymbol->value=currentNode->right;
						if(tempSymbol = interpreter_lookup(interpreter_newSymbol(currentSymbol->value->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
						{
							if(tempSymbol->is_file && tempSymbol->is_input)
							{
							}
							else if(tempSymbol->is_file)
							{
								currentIdentifier = currentSymbol->value->tokenString;
								currentLine = currentSymbol->value->lineno;
								semanticSymbolError("This variable is not of the type input. You must declare it at the top of a block.");
							}
							else
							{
								subString(currentNode->right, tab);
							}
						}
						
					}
					else
					{
						subString(currentNode->right, tab);
					}
				}
				else
				{
					if(currentNode->right->type == IDENTIFIER)
					{
						currentSymbol->value=currentNode->right;
						if(tempSymbol = interpreter_lookup(interpreter_newSymbol(currentSymbol->value->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
						{
							if(tempSymbol->is_file && !tempSymbol->is_input)
							{
							}
							else if(tempSymbol->is_file)
							{
								currentIdentifier = currentSymbol->value->tokenString;
								currentLine = currentSymbol->value->lineno;
								semanticSymbolError("This variable is not of the type output. You must declare it at the top of a block.");
							}
							else
							{
								subString(currentNode->right, tab);
							}
						}
					}
					else
					{
						subString(currentNode->right, tab);
					}
				}
			}
			else
			{
				subString(currentNode->right, tab);
			}
		}
		else
		{
			subString(currentNode->left, tab);
			subString(currentNode->right, tab);
		}
*/
		subString(currentNode->left, tab);
		subString(currentNode->right, tab);
	}
	else if(currentNode->type == '+')
	{
		subString(currentNode->left, tab);
		subString(currentNode->right, tab);
	}
	else if(currentNode->type == READ)
	{
		subString(currentNode->left, tab);
		if(currentNode->right->type==READ)
		{
			subString(currentNode->right, tab);
		}
		else
		{
			if(tempSymbol = lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				if(tempSymbol->is_file && tempSymbol->is_input)
				{
				}
				else
				{
					currentIdentifier = currentNode->right->tokenString;
					currentLine = currentNode->lineno;
					semanticSymbolError("This variable is not of the type input. You must declare it at the top of a block.");
				}
			}
			else
			{
				currentIdentifier = currentNode->right->tokenString;
				currentLine = currentNode->lineno;
				semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
			}
		}
	}
	else if(currentNode->type == WRITE)
	{
		subString(currentNode->right, tab);
		if(currentNode->left->type==WRITE)
		{
			subString(currentNode->left, tab);
		}
		else
		{
			if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				if(currentSymbol->is_file && !currentSymbol->is_input)
				{
				}
				else
				{
					currentIdentifier = currentNode->right->tokenString;
					currentLine = currentNode->lineno;
					semanticSymbolError("This variable is not of the type output. You must declare it at the top of a block.");
				}
			}
			else
			{
				currentIdentifier = currentNode->right->tokenString;
				currentLine = currentNode->lineno;
				semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
			}
		}
	}
	else if(currentNode->type == '-'
	|| currentNode->type == '*'
	|| currentNode->type == '/'
	)
	{
		if(currentNode->left)
		{
			subDouble(currentNode->left, tab);
		}
		subDouble(currentNode->right, tab);
	}
	else if(currentNode->type == '%')
	{
		subInt(currentNode->left, tab);
		subInt(currentNode->right, tab);
	}
	else if(currentNode->type==IDENTIFIER)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
		{
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
		{
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
		{
		}
		else
		{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
		}
	}
	else if(currentNode->type==COMPOUND_DATASET)
	{
		subString(currentNode->left, tab);
		datasetList_coordinate(currentNode->right->left, tab);
		if(currentNode->right->right)
		{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticSymbolError("You cannot use {} with strings.");
		}
	}
	else if(currentNode->type==STRING || currentNode->type == STRING_LITERAL)
	{
	}
	else if(currentNode->type==NUMBER)
	{
	}
	else if(currentNode->type==PAR)
	{
		if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 1, currentNode->left->lineno)))
		{
			function_call(currentNode, tab);
		}
		else
		{
			currentIdentifier = currentNode->left->tokenString;
			currentLine = currentNode->left->lineno;
			semanticSymbolError("This is an undefined function. ");
		}
	}
	else
	{
			currentIdentifier = currentNode->tokenString;
			currentLine = currentNode->lineno;
			semanticIntError("This expression is not the required type of string.");
	}
	return 1;
}

void block(TreeNode * root, int tab)
{
	TreeNode * currentNode;	
	currentNode = root;
	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable")
		|| !strcmp(currentNode->tokenString, "function"))
		{
			variables(root, tab);
		}
		traverse(root, tab);
		popSymbolsByScope(tab);
	}
}

void function_call(TreeNode * root, int tab)
{
	int i;
	int last;
	TreeNode * for_current;	
	TreeNode * for_temp;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	

	currentNode = root;
	last = currentNode->lineno;
	if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 1, currentNode->left->lineno)))
	{
	}
	else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 1, currentNode->left->lineno)))
	{
	}
	else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 1, currentNode->left->lineno)))
	{
	}
	else if(currentSymbol = lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 1, currentNode->left->lineno)))
	{
	}
	else
	{
		currentIdentifier = currentNode->left->tokenString;
		currentLine = currentNode->left->lineno;
		semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
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
						if(currentSymbol = lookup(newSymbol(paramNode->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_DATASET && current_list->symbolType == TYPE_DATASET))
							{
							}
							else
							{
								currentIdentifier = currentNode->left->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else if(currentSymbol = lookup(newSymbol(paramNode->tokenString, tab, TYPE_INT, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_INT && current_list->symbolType == TYPE_INT))
							{
							}
							else if((currentSymbol->symbolType == TYPE_INT && current_list->symbolType == TYPE_DOUBLE))
							{
							}
							else if((currentSymbol->symbolType == TYPE_INT && current_list->symbolType == TYPE_STRING))
							{
							}
							else
							{
								currentIdentifier = currentNode->left->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else if(currentSymbol = lookup(newSymbol(paramNode->tokenString, tab, TYPE_DOUBLE, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_DOUBLE && current_list->symbolType == TYPE_INT))
							{
							}
							else if((currentSymbol->symbolType == TYPE_DOUBLE && current_list->symbolType == TYPE_DOUBLE))
							{
							}
							else if((currentSymbol->symbolType == TYPE_DOUBLE && current_list->symbolType == TYPE_STRING))
							{
							}
							else
							{
								currentIdentifier = currentNode->left->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else if(currentSymbol = lookup(newSymbol(paramNode->tokenString, tab, TYPE_STRING, 0, paramNode->lineno)))
						{
							if((currentSymbol->symbolType == TYPE_STRING && current_list->symbolType == TYPE_STRING))
							{
							}
							else if((currentSymbol->symbolType == TYPE_STRING && current_list->symbolType == TYPE_DATASET))
							{
							}
							else
							{
								currentIdentifier = currentNode->left->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else
						{
							currentIdentifier = paramNode->tokenString;
							currentLine = paramNode->lineno;
							semanticSymbolError("This is an undefined variable. You must declare it at the top of a block.");
						}
					}
					else
					{
						if(current_list->symbolType == TYPE_DATASET)
						{
							if(paramNode->type == DATASET 
							|| paramNode->type == STRING
							|| paramNode->type == STRING_LITERAL
							)
							{
							}
							else if(paramNode->type == '=')
							{
								subDataset(paramNode->left, tab);
								subDataset(paramNode->right, tab);
							}
							else if(currentNode->type == READ
							|| currentNode->type == WRITE
							)
							{
								subString(paramNode->left, tab);
								subString(paramNode->right, tab);
							}
							else
							if(paramNode->type == ATTRIBUTE_JOIN
							|| paramNode->type == BLOCK_JOIN
							)
							{
								subDataset(paramNode->left, tab);
								subDataset(paramNode->right, tab);
							}
							else if(paramNode->type == COMPOUND_DATASET)
							{
								if(lookup(newSymbol(paramNode->left->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno)))
								{
									subDataset(paramNode, tab);
								}
								else if(lookup(newSymbol(paramNode->left->tokenString, tab, TYPE_STRING, 0, paramNode->lineno)))
								{
									subString(paramNode, tab);
								}
								else
								{
									subDataset(paramNode, tab);
								}
							}
							else if(paramNode->type==PAR)
							{
								subDataset(paramNode, tab);
							}
							else
							{
								currentIdentifier = paramNode->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else if( current_list->symbolType == TYPE_INT)
						{
							if(paramNode->type == INT || paramNode->type == NUMBER)
							{
							}
							else if(paramNode->type == '=')
							{
								subInt(paramNode->left, tab);
								subInt(paramNode->right, tab);
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
							)
							{
								if(paramNode->left)
								{
									subInt(paramNode->left, tab);
								}
								subInt(paramNode->right, tab);
							}
							else if(paramNode->type == NOT)
							{
								subInt(paramNode->right, tab);
							}
							else if(paramNode->type == PAR)
							{
								subInt(paramNode, tab);
							}
							else
							{
								currentIdentifier = paramNode->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else if( current_list->symbolType == TYPE_DOUBLE)
						{
							if(paramNode->type == INT || paramNode->type == DOUBLE || paramNode->type == NUMBER)
							{
							}
							else if(paramNode->type == '=')
							{
								subDouble(paramNode->left, tab);
								subDouble(paramNode->right, tab);
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
							)
							{
								if(paramNode->left)
								{
									subDouble(paramNode->left, tab);
								}
								subDouble(paramNode->right, tab);
							}
							else if(paramNode->type == NOT)
							{
								subDouble(paramNode->right, tab);
							}
							else if(paramNode->type == PAR)
							{
								subDouble(paramNode, tab);
							}
							else
							{
								currentIdentifier = paramNode->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else if( current_list->symbolType == TYPE_STRING)
						{
							if(paramNode->type == STRING || paramNode->type == STRING_LITERAL)
							{
							}
							else if(paramNode->type == '=')
							{
								subString(paramNode->left, tab);
								subString(paramNode->right, tab);
							}
							else if(currentNode->type == READ
							|| currentNode->type == WRITE
							)
							{
								subString(paramNode->left, tab);
								subString(paramNode->right, tab);
							}
							else if(paramNode->type == '+')
							{
								subString(paramNode->left, tab);
								subString(paramNode->right, tab);
							}
							else 
							if(paramNode->type == PAR)
							{
								subString(paramNode, tab);
							}
							else if(paramNode->type==COMPOUND_DATASET)
							{
								subString(paramNode, tab);
							}
							else
							{
								currentIdentifier = paramNode->tokenString;
								currentLine = paramNode->lineno;
								semanticSymbolError("Parameter types for function don't match.");
							}
						}
						else
						{
							currentIdentifier = paramNode->tokenString;
							currentLine = paramNode->lineno;
							semanticSymbolError("Parameter types for function don't match.");
						}
					}
					temp_list=current_list->next;
					current_list = temp_list;
					tempNode = paramNode->sibling;
					paramNode = tempNode;
				}
				else
				{
					currentIdentifier = current_list->name;
					currentLine = last;
					semanticSymbolError("This function does not have all the required parameters.");
				}
			}
			if(paramNode)
			{
				currentIdentifier = paramNode->tokenString;
				currentLine = paramNode->lineno;
				semanticSymbolError("This function has more than the required parameters.");
			}
		}
		else
		{
			currentIdentifier = currentNode->left->tokenString;
			currentLine = currentNode->left->lineno;
			semanticSymbolError("This function does not have all the required parameters.");
		}				
	}
	else
	{
		if(currentNode->right)
		{
			currentIdentifier = currentNode->left->tokenString;
			currentLine = currentNode->left->lineno;
			semanticSymbolError("This function has more than the required parameters.");
		}				
	}
}

void traverse(TreeNode * root, int tab)
{
	int i;
	TreeNode * for_current;	
	TreeNode * for_temp;	
	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	

	currentNode = root;
	if(currentNode)
	{
		if(currentNode->type == '='
		)
		{
			if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno)))
			{
				subDataset(currentNode->left, tab);
				subDataset(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				subString(currentNode->left, tab);
				subString(currentNode->right, tab);
			}
			else
			{
				subString(currentNode->left, tab);
				subString(currentNode->right, tab);
			}
		}
		else if(currentNode->type == READ
		|| currentNode->type == WRITE
		)
		{
			subString(currentNode->left, tab);
			subString(currentNode->right, tab);
		}
		else
		if(currentNode->type == ATTRIBUTE_JOIN
		|| currentNode->type == BLOCK_JOIN
		)
		{
			subDataset(currentNode->left, tab);
			subDataset(currentNode->right, tab);
		}
		else 
		if(currentNode->type == '+'
		)
		{
			if(currentNode->left->type == STRING || currentNode->left->type == STRING_LITERAL)
			{
				subString(currentNode->left, tab);
				subString(currentNode->right, tab);
			}
			else if(currentNode->right->type == STRING || currentNode->right->type == STRING_LITERAL)
			{
				subString(currentNode->left, tab);
				subString(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				subString(currentNode->left, tab);
				subString(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				subString(currentNode->left, tab);
				subString(currentNode->right, tab);
			}
			else if(currentNode->left->type == NUMBER && currentNode->left->is_double)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->right->type == NUMBER && currentNode->right->is_double)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->left->type == DOUBLE)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->right->type == DOUBLE)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->left->type == NUMBER || currentNode->left->type == INT)
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(currentNode->right->type == NUMBER || currentNode->right->type == INT)
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
		}
		else 
		if(currentNode->type == '-'
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
			if(!currentNode->left && currentNode->right->is_double)
			{
				subDouble(currentNode->right, tab);
			}
			else if(!currentNode->left && !currentNode->right->is_double)
			{
				subInt(currentNode->right, tab);
			}
			else if(currentNode->left->type == NUMBER && currentNode->left->is_double)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->right->type == NUMBER && currentNode->right->is_double)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->left->type == DOUBLE)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->right->type == DOUBLE)
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->left->type == NUMBER || currentNode->left->type == INT)
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(currentNode->right->type == NUMBER || currentNode->right->type == INT)
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else
			{
				subDouble(currentNode->left, tab);
				subDouble(currentNode->right, tab);
			}
		}
		else 
		if(currentNode->type == '%')
		{
			if(currentNode->left->type == NUMBER || currentNode->left->type == INT)
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(currentNode->right->type == NUMBER || currentNode->right->type == INT)
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
			else
			{
				subInt(currentNode->left, tab);
				subInt(currentNode->right, tab);
			}
		}
		else if(currentNode->type == NOT)
		{
			if(currentNode->right->type == NUMBER && currentNode->right->is_double)
			{
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->right->type == DOUBLE)
			{
				subDouble(currentNode->right, tab);
			}
			else if(currentNode->right->type == NUMBER || currentNode->right->type == INT)
			{
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_INT, 0, currentNode->lineno)))
			{
				subInt(currentNode->right, tab);
			}
			else if(lookup(newSymbol(currentNode->right->tokenString, tab, TYPE_DOUBLE, 0, currentNode->lineno)))
			{
				subDouble(currentNode->right, tab);
			}
			else
			{
				subDouble(currentNode->right, tab);
			}
		}
		else if(currentNode->type==COMPOUND_DATASET)
		{
			if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno)))
			{
				subDataset(currentNode, tab);
			}
			else if(lookup(newSymbol(currentNode->left->tokenString, tab, TYPE_STRING, 0, currentNode->lineno)))
			{
				subString(currentNode, tab);
			}
			else
			{
				subDataset(currentNode, tab);
			}
		}
		else if(currentNode->type==RETURN)
		{
			return_flag=1;
			if(return_dataset)
			{
				if(currentNode->left)
				{
					subDataset(currentNode->left, tab);
				}
				else
				{
					returnTypeMismatchError(currentNode->lineno);
				}
			}
			else if(return_int)
			{
				if(currentNode->left)
				{
					subInt(currentNode->left, tab);
				}
				else
				{
					returnTypeMismatchError(currentNode->lineno);
				}
			}
			else if(return_double)
			{
				if(currentNode->left)
				{
					subDouble(currentNode->left, tab);
				}
				else
				{
					returnTypeMismatchError(currentNode->lineno);
				}
			}
			else if(return_string)
			{
				if(currentNode->left)
				{
					subString(currentNode->left, tab);
				}
				else
				{
					returnTypeMismatchError(currentNode->lineno);
				}
			}
			else
			{
				if(currentNode->left)
				{
					returnTypeMismatchError(currentNode->lineno);
				}
			}
		}
		else 
		if(currentNode->type==FOR
		|| currentNode->type==DO
		|| currentNode->type==WHILE
		|| currentNode->type==IF)
		{
			for_current = for_temp = currentNode->left;
			while(for_current)
			{
				subInt(for_current, tab);
				for_temp = for_current->sibling;
				for_current = for_temp;
			}
			traverse(currentNode->right, tab);
			if(currentNode->otherChild)
			{
				traverse(currentNode->otherChild, tab);
			}
		}
		else if(currentNode->type==PAR)
		{
			function_call(currentNode, tab);
		}

		if(currentNode->sibling)
		{
			traverse((currentNode->sibling), tab);
		}	
	} 
	
}

void printTableRow(Symbol * s1)
{
	if(s1->next)
	{
		printTableRow(s1->next);
	}
	printf("name:%s function:%d\n", s1->name, s1->function);
}

void deleteTableRow(Symbol * s1)
{
	if(s1->next)
	{
		deleteTableRow(s1->next);
	}
	free(s1);
}

TreeNode * analyze(TreeNode * root, int tab)
{
	Symbol * s1;
	Symbol * s2;
	Symbol * s3;
	Symbol * s4;
	Symbol * currentSymbol;
	Symbol * current_list;
	TreeNode * holderNode;
	Symbol * holderSymbol;
	Symbol * tempSymbol;

	char * name;
	int i;
	int j;

	for(i=0; i<26; i++)
	{
		symbolTable[i] = 0;
	}
/*
	root = parse();
*/
/*
		printTree(root, 0);
*/
	name = (char *) calloc(6, sizeof(char));
	name[0]='s';
	name[1]='t';
	name[2]='d';
	name[3]='i';
	name[4]='n';
	name[5]='\0';
	tempSymbol = newSymbol(name, 0, TYPE_STRING, 0, 0);
	tempSymbol->is_file = 1;
	tempSymbol->is_input = 1;
	tempSymbol->stream = stdin;
	insertSymbol(tempSymbol);

	name = (char *) calloc(7, sizeof(char));
	name[0]='s';
	name[1]='t';
	name[2]='d';
	name[3]='o';
	name[4]='u';
	name[5]='t';
	name[6]='\0';
	tempSymbol = newSymbol(name, 0, TYPE_STRING, 0, 0);
	tempSymbol->is_file = 1;
	tempSymbol->is_input = 0;
	tempSymbol->stream = stdout;
	insertSymbol(tempSymbol);

	name = (char *) calloc(7, sizeof(char));
	name[0]='x';
	name[1]='m';
	name[2]='l';
	name[3]='o';
	name[4]='u';
	name[5]='t';
	name[6]='\0';

	holderSymbol = newSymbol(name, 0, TYPE_STRING, 0, 0);
	holderSymbol->is_file = 1;
	holderSymbol->is_input = 0;
	holderSymbol->stream = output;
	insertSymbol(holderSymbol);

	variables(root, tab);

	if(!main_found)
	{
		mainNotFoundError();					
	}

/*
	for(j=0;j<26;j++)
	{
		if(symbolTable[j])
		{
			printTableRow(symbolTable[j]);
			symbolTable[j]=0;
		}
	}
*/

	return root;
}

Symbol * get_symbolTable(int val)
{
	return symbolTable[val];
}
void set_symbolTable(int val, Symbol * symbol_row)
{
	symbolTable[val]=symbol_row;
}

void set_main_found(int val)
{
	main_found=val;
}
int get_main_found()
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

		root = analyze();

		printTree(root, 0);

		fclose(input);
	}
	return 0;
}
*/
