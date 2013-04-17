/*
David Thigpen
*/

#include "header.h"
#define FP 5
#define SP 6
#define PC 7


int verbose1;
typedef struct scopeoffset
{ 
	struct scopeoffset * next;
	int scope;
	int positive_offset;
	int negative_offset;
} ScopeOffset;
;
typedef struct ilist
{ 
	struct ilist * next;
	char instruction[255];
} iList;
;
typedef struct ll
{ 
	struct ll * next;
	Symbol * current;
} LL;
;

Symbol * symbolTable[26];
char currentIdentifier[MAXTOKENLEN+1];
int currentLine;
int currentCodeLine;
int notFirst;
int main_found;
int return_int;
ScopeOffset global_offset;
ScopeOffset * current_offset;

char instruction[55];
iList * front_ilist;
iList * current_ilist;
int main_offset;

void gen_newIList(char a[]);
ScopeOffset * gen_newOffset(int scope);
void gen_setCurrentScope(int scope);
Symbol * gen_newSymbol(char * name, int scope, Type symbolType, int function, int lineno, int offset);
Symbol * gen_lookup(Symbol * s);
void gen_insertSymbol(Symbol * s);
void gen_popSymbolsByScope(int scope);
void gen_variables(TreeNode * root, int tab);
int gen_subDataset(TreeNode * root, int tab);
void gen_block(TreeNode * root, int tab);
void gen_traverse(TreeNode * root, int tab);

LL * gen_newLL(Symbol * s)
{
	LL * l = (LL *) malloc(sizeof(LL));
	l->next = 0;
	l->current = s;
	return l;
}

void gen_newIList(char a[])
{
	if(verbose1){puts("Entering gen_newIList");}

	iList * s;
	if(!notFirst)
	{
		if(verbose1){puts("First ELEMENT");}
		if( !(current_ilist = front_ilist = s = (iList *) malloc(sizeof(iList))) )
		{
			if(verbose1){puts("Not enough memory");}
		}
		if(verbose1){printf("memory_location:%d\n", s);}
		current_ilist->next = 0;
		notFirst = 1;
	}
	else
	{
		if(verbose1){puts("Additional ELEMENT");}
		if( !(s = (iList *) malloc(sizeof(iList))) )
		{
			if(verbose1){puts("Not enough memory");}
		}
		if(verbose1){printf("memory_location:%d\n", s);}
		if(verbose1){puts("Additional ELEMENT Malloc");}
		current_ilist->next = s;
		if(verbose1){puts("Additional ELEMENT Appended");}
		current_ilist = s;
	}
	if(verbose1){puts("ILIST ELEMENT CREATED");}
	s->next = 0;
	sprintf(s->instruction, "%s\n", a);
	
	if(main_found)
	{
		main_offset = currentCodeLine;
	}
	currentCodeLine++;
	if(verbose1){puts("Leaving gen_newIList");}
}

ScopeOffset * gen_newOffset(int scope)
{
	ScopeOffset * s = (ScopeOffset *) malloc(sizeof(ScopeOffset));
	s->next = 0;
	s->scope = scope;
	s->positive_offset = 2;
	s->negative_offset = -1;
	return s;
}

void gen_setCurrentScope(int scope)
{
	ScopeOffset * placeholder;
	current_offset = &global_offset;
	while(current_offset && current_offset->scope != scope)
	{
		placeholder = current_offset->next;
		current_offset = placeholder;
	}
}

Symbol * gen_newSymbol(char * name, int scope, Type symbolType, int function, int lineno, int offset)
{
	Symbol * s = (Symbol *) malloc(sizeof(Symbol));
	s->next = 0;
	strcpy(s->name, name);
	s->scope = scope;
	s->symbolType = symbolType;
	s->function = function;
	s->lineno = lineno;
	s->offset = offset;
	s->param_list = 0;

/*
printf("%d: %s\n", s->scope, s->name);
*/

	return s;
}

Symbol * gen_lookup(Symbol * s)
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

void gen_insertSymbol(Symbol * s)
{
	Symbol * s1;

	if(!symbolTable[s->name[0]%26])
	{
		symbolTable[s->name[0]%26] = s;	
	}
	else
	{
		s1 = symbolTable[s->name[0]%26];
		s->next = s1;
		symbolTable[s->name[0]%26] = s;	
	}
}

void gen_popSymbolsByScope(int scope)
{
	int i;
	Symbol * temp;
	Symbol * current;
/*
printf("scope:%d\n", scope);
*/
	gen_setCurrentScope(scope-1);
	if(current_offset)
	{
		current_offset->next = 0;
	}
	else
	{
		printf("Scope overrun");
	}

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

void gen_variables(TreeNode * root, int tab)
{
	if(verbose1){puts("Entering gen_variables\n");}

	int i;
	int paramnum;
	TreeNode * t1;	
	TreeNode * t2;	
	TreeNode * t3;	
	
	TreeNode * currentNode;	
	TreeNode * paramNode;	
	TreeNode * tempNode;	
	Symbol * param_list;	
	Symbol * temp_list;	
	Symbol * current_list;	
	Symbol * currentSymbol;	
	Symbol * symbol;	

	gen_setCurrentScope(tab);

	currentNode = root;
	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable"))
		{
			if(verbose1){puts("Variables\n");}
			paramNode = currentNode->left;
			currentSymbol = gen_newSymbol(paramNode->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno, current_offset->positive_offset);
			gen_insertSymbol(gen_newSymbol(paramNode->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno, current_offset->positive_offset));
			current_offset->positive_offset++;

			sprintf(instruction, "<DataSource dsName='%s' />", paramNode->tokenString);
			gen_newIList(instruction);

			gen_variables(root->sibling, tab);
		}
		else if(!strcmp(currentNode->tokenString, "function"))
		{
			if(verbose1){puts("function\n");}
			gen_popSymbolsByScope(tab+1);
			paramNode = currentNode->left;

			if(verbose1){puts("parameter0");}

			if(!strcmp(paramNode->left->tokenString, "main"))
			{
				main_found = 1;
			}
			if(paramNode->type == DATASET)
			{
				if(verbose1){puts("parameter1");}
				return_int = 1;

				paramnum=0;
				t1 = paramNode->right;
				while(t1)
				{
					paramnum++;
					t2=t1->sibling;
					t1=t2;
				}
				if(verbose1){puts("parameter2");}
				sprintf(instruction, "<DataSource dsName='%s' type='composite_function_dataset' params='%d'>", paramNode->left->tokenString, paramnum);
				gen_newIList(instruction);

				currentSymbol = gen_newSymbol(paramNode->left->tokenString, tab, TYPE_DATASET, 1, paramNode->left->lineno, currentCodeLine);
				if(paramNode->right)
				{
					tempNode = paramNode->right;
					paramNode = tempNode;

					if(!strcmp(paramNode->tokenString, "variable"))
					{
						current_list = gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno, current_offset->negative_offset);
						gen_insertSymbol(gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno, current_offset->negative_offset));
						current_offset->negative_offset--;
						param_list = current_list;
						i=0;

						sprintf(instruction, "<DataSource dsName='%s' />", paramNode->left->tokenString);
						gen_newIList(instruction);

					}
					tempNode = paramNode->sibling;
					paramNode = tempNode;

					while(paramNode)
					{
						if(!strcmp(paramNode->tokenString, "variable"))
						{
							current_list->next = gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno, current_offset->negative_offset);
							gen_insertSymbol(gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno, current_offset->negative_offset));
							current_offset->negative_offset--;

							sprintf(instruction, "<DataSource dsName='%s' />", paramNode->left->tokenString);
							gen_newIList(instruction);

						}
						tempNode = paramNode->sibling;
						paramNode = tempNode;

						temp_list = current_list->next;
						current_list = temp_list;
					}
					currentSymbol->param_list = param_list;
				}


				gen_insertSymbol(currentSymbol);
				gen_block(currentNode->right, tab+1);
	
				sprintf(instruction, "</DataSource>");
				gen_newIList(instruction);

				gen_variables(root->sibling, tab);
			}
			else if(paramNode->type == VOID)
			{
				if(verbose1){puts("parameter1_void");}
				return_int = 0;

				paramnum=0;
				t1 = paramNode->right;
				while(t1)
				{
					paramnum++;
					t2=t1->sibling;
					t1=t2;
				}
				if(verbose1){puts("parameter2_void");}
				sprintf(instruction, "<DataSource dsName='%s' type='composite_function_void' params='%d'>", paramNode->left->tokenString, paramnum);
				if(verbose1){puts("parameter2.001_void");}

				gen_newIList(instruction);
				if(verbose1){puts("parameter2.002_void");}

				currentSymbol = gen_newSymbol(paramNode->left->tokenString, tab, TYPE_VOID, 1, paramNode->lineno, currentCodeLine);
				if(verbose1){puts("parameter2.01_void");}
				if(paramNode->right)
				{
					if(verbose1){puts("parameter2.1_void");}
					tempNode = paramNode->right;
					paramNode = tempNode;

					if(!strcmp(paramNode->tokenString, "variable"))
					{
						current_list = gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->lineno, current_offset->negative_offset);
						gen_insertSymbol(gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->lineno, current_offset->negative_offset));
						current_offset->negative_offset--;
						param_list = current_list;
						i=0;

						sprintf(instruction, "<DataSource dsName='%s' />", paramNode->left->tokenString);
						gen_newIList(instruction);
					}
					tempNode = paramNode->sibling;
					paramNode = tempNode;

					while(paramNode)
					{
						if(!strcmp(paramNode->tokenString, "variable"))
						{
							current_list->next = gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno, current_offset->negative_offset);
							gen_insertSymbol(gen_newSymbol(paramNode->left->tokenString, tab+1, TYPE_DATASET, 0, paramNode->left->lineno, current_offset->negative_offset));
							current_offset->negative_offset--;

							sprintf(instruction, "<DataSource dsName='%s' />", paramNode->left->tokenString);
							gen_newIList(instruction);

						}
						tempNode = paramNode->sibling;
						paramNode = tempNode;

						temp_list = current_list->next;
						current_list = temp_list;
					}
					currentSymbol->param_list = param_list;
				}
				if(verbose1){puts("parameter3_void");}
				gen_insertSymbol(currentSymbol);
				gen_block(currentNode->right, tab+1);

				sprintf(instruction, "</DataSource>");
				gen_newIList(instruction);

				gen_variables(root->sibling, tab);
			}
		}
	}
	if(verbose1){puts("Leaving gen_variables\n");}
}

int gen_subDataset(TreeNode * root, int tab)
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
	char * filename;

	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	currentNode = root;
	if(currentNode->type == ATTRIBUTE_JOIN
		|| currentNode->type == BLOCK_JOIN
		|| currentNode->type == '='
		|| currentNode->type == STRING_LITERAL)
	{
		if(currentNode->type == ATTRIBUTE_JOIN)
		{
			sprintf(instruction, "<DataSource dsName='op%d' type='attribute_joined'>", opcounter);
			gen_newIList(instruction);
			opcounter++;
		}
		else if(currentNode->type == BLOCK_JOIN)
		{
			sprintf(instruction, "<DataSource dsName='op%d' type='block_joined'>", opcounter);
			gen_newIList(instruction);
			opcounter++;
		}
		else if(currentNode->type == '=')
		{
			if(currentNode->left->type==IDENTIFIER && currentNode->right->type==STRING_LITERAL)
			{
				begin=quote=passmode=0;
				for(j=0;j<MAXTOKENLEN+1; j++)
				{
					if(currentNode->right->tokenString[j]=='/')
					{
						if(passmode==0)
						{
							passmode++;
						}
						else if(passmode==1)
						{
							passmode++;
							begin=j+1;
						}
					}
					if(currentNode->right->tokenString[j]=='"')
					{
						quote=j;
					}
				}
				filename= calloc(sizeof(char), quote-begin+1);
				strncpy(filename, &currentNode->right->tokenString[begin], quote-begin);
				sprintf(instruction, "<DataSource dsName='%s' type='physical' fileName='%s'>", currentNode->left->tokenString, filename);
				gen_newIList(instruction);
				free(filename);
			}
			else if(currentNode->left->type==IDENTIFIER)
			{
				sprintf(instruction, "<DataSource dsName='%s' type='composite'>", currentNode->left->tokenString, SP);
				gen_newIList(instruction);
			}
		}
		else if(currentNode->type == STRING_LITERAL)
		{
		}

		if(currentNode->left && currentNode->type != '=')
			gen_subDataset(currentNode->left, tab);
		if(currentNode->right)
			gen_subDataset(currentNode->right, tab);

		if(currentNode->type == ATTRIBUTE_JOIN)
		{
			sprintf(instruction, "</DataSource>");
			gen_newIList(instruction);
		}
		else if(currentNode->type == BLOCK_JOIN)
		{
			sprintf(instruction, "</DataSource>");
			gen_newIList(instruction);
		}
		else if(currentNode->type == '=')
		{
			sprintf(instruction, "</DataSource>");
			gen_newIList(instruction);
		}
		else if(currentNode->type == STRING_LITERAL)
		{
		}
	}
	else if(currentNode->type== IDENTIFIER)
	{
		if(currentSymbol = gen_lookup(gen_newSymbol(currentNode->tokenString, tab, TYPE_DATASET, 0, currentNode->lineno, 0)))
		{
			sprintf(instruction, "<DataSource dsName='%s' />", currentNode->tokenString);
			gen_newIList(instruction);
		}
	}
	else if(currentNode->type==PAR)
	{
		if(currentSymbol = gen_lookup(gen_newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 1, currentNode->left->lineno, 0)))
		{
			paramnum=0;
			t1 = currentNode->right;
			while(t1)
			{
				paramnum++;
				t2=t1->sibling;
				t1=t2;
			}
			sprintf(instruction, "<DataSource dsName='%s' type='composite_function_call' params='%d'>", currentNode->left->tokenString, paramnum);
			gen_newIList(instruction);

			t1 = currentNode->right;
			while(t1)
			{
				sprintf(instruction, "<DataSource dsName='%s' />", t1->tokenString);
				gen_newIList(instruction);

				t2=t1->sibling;
				t1=t2;
			}
			sprintf(instruction, "<DataSource />");
			gen_newIList(instruction);
		}
	}
	if(verbose1){puts("Leaving gen_subDataset\n");}

	return 1;
}

void gen_block(TreeNode * root, int tab)
{
	if(verbose1){puts("Entering gen_block\n");}
	TreeNode * currentNode;
	
	gen_setCurrentScope(tab-1);
	if(current_offset)
	{
		current_offset->next = gen_newOffset(tab);
	}
	else
	{
		printf("Scope overrun");
	}

	currentNode = root;
	if(currentNode)
	{
		if(!strcmp(currentNode->tokenString, "variable")
		|| !strcmp(currentNode->tokenString, "function"))
		{
			gen_variables(root, tab);
		}
		gen_traverse(root, tab);
		gen_popSymbolsByScope(tab);
	}
	if(verbose1){puts("Leaving gen_block\n");}
}
void gen_traverse(TreeNode * root, int tab)
{
	if(verbose1){puts("Entering gen_traverse\n");}
	int i;
	int j;
	int passmode;
	int begin;
	int quote;
	char * filename;

	TreeNode * currentNode;	
	TreeNode * tempNode;	
	TreeNode * paramNode;	
	Symbol * current_list;	
	Symbol * temp_list;	
	Symbol * currentSymbol;	
	LL * list;
	LL * temp;

	currentNode = root;
	if(currentNode)
	{
		if(currentNode->type == ATTRIBUTE_JOIN
		|| currentNode->type == BLOCK_JOIN
		|| currentNode->type == '=')
		{
			if(currentNode->type == ATTRIBUTE_JOIN)
			{
				sprintf(instruction, "<DataSource dsName='op%d' type='attribute_joined'>", opcounter);
				gen_newIList(instruction);
				opcounter++;
			}
			else if(currentNode->type == BLOCK_JOIN)
			{
				sprintf(instruction, "<DataSource dsName='op%d' type='block_joined'>", opcounter);
				gen_newIList(instruction);
				opcounter++;
			}
			else if(currentNode->type == '=')
			{
				if(currentNode->left->type==IDENTIFIER && currentNode->right->type==STRING_LITERAL)
				{
					begin=quote=passmode=0;
					for(j=0;j<MAXTOKENLEN+1; j++)
					{
						if(currentNode->right->tokenString[j]=='/')
						{
							if(passmode==0)
							{
								passmode++;
							}
							else if(passmode==1)
							{
								passmode++;
								begin=j+1;
							}
						}
						if(currentNode->right->tokenString[j]=='"')
						{
							quote=j;
						}
					}
					filename= calloc(sizeof(char), quote-begin+1);
					strncpy(filename, &currentNode->right->tokenString[begin], quote-begin);
					sprintf(instruction, "<DataSource dsName='%s' type='physical' fileName='%s'>", currentNode->left->tokenString, filename);
					gen_newIList(instruction);
					free(filename);
				}
				else if(currentNode->left->type==IDENTIFIER)
				{
					sprintf(instruction, "<DataSource dsName='%s' type='composite'>", currentNode->left->tokenString);
					gen_newIList(instruction);
				}
			}
			else if(currentNode->type == STRING_LITERAL)
			{
			}

			if(currentNode->left && currentNode->type != '=')
				gen_subDataset(currentNode->left, tab);
			if(currentNode->right)
				gen_subDataset(currentNode->right, tab);

			if(currentNode->type == ATTRIBUTE_JOIN)
			{
				sprintf(instruction, "</DataSource>");
				gen_newIList(instruction);
			}
			else if(currentNode->type == BLOCK_JOIN)
			{
				sprintf(instruction, "</DataSource>");
				gen_newIList(instruction);
			}
			else if(currentNode->type == '=')
			{
				sprintf(instruction, "</DataSource>");
				gen_newIList(instruction);
			}
			else if(currentNode->type == STRING_LITERAL)
			{
			}
		}
		else if(currentNode->type==RETURN)
		{
			if(return_int)
			{
				if(currentNode->left)
				{
					sprintf(instruction, "<Return>");
					gen_newIList(instruction);
					
					gen_subDataset(currentNode->left, tab);

					sprintf(instruction, "</Return>");
					gen_newIList(instruction);
				}
			}
			else
			{
			}
		}
		else if(currentNode->type==PAR)
		{
			if(currentSymbol = gen_lookup(gen_newSymbol(currentNode->left->tokenString, tab, TYPE_DATASET, 1, currentNode->left->lineno, 0)))
			{
				if(currentSymbol->param_list)
				{
					if(currentNode->right)
					{
						paramNode = currentNode->right;
						current_list = currentSymbol->param_list;
						if(currentSymbol->param_list)
						{
							current_list = currentSymbol->param_list;
							list = temp = 0;
							while(current_list)
							{
								temp = gen_newLL(temp_list);
								if(list)
								{
									temp->next = list;
								}
								list = temp;
								
								temp_list = current_list->next;
								current_list = temp_list;
							}
							while(list)
							{
							}
						}

						while(current_list)
						{
							if(paramNode)
							{
								if(paramNode->type == IDENTIFIER)
								{
									if(currentSymbol = gen_lookup(gen_newSymbol(paramNode->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno, 0)))
									{
										if((currentSymbol->symbolType == TYPE_DATASET && current_list->symbolType == TYPE_DATASET))
										{
										}
									}
								}
								else
								{
									if(((paramNode->type == DATASET || paramNode->type == STRING_LITERAL)&& current_list->symbolType == TYPE_DATASET))
									{
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
				else
				{
				}

			}
			else if(currentSymbol = gen_lookup(gen_newSymbol(currentNode->left->tokenString, tab, TYPE_VOID, 1, currentNode->left->lineno, 0)))
			{
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
									if(currentSymbol = gen_lookup(gen_newSymbol(paramNode->tokenString, tab, TYPE_DATASET, 0, paramNode->lineno, 0)))
									{
										if((currentSymbol->symbolType == TYPE_DATASET && current_list->symbolType == TYPE_DATASET))
										{
										}
									}
								}
								else
								{
									if(((paramNode->type == DATASET || paramNode->type == STRING_LITERAL)&& current_list->symbolType == TYPE_DATASET))
									{
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
				else
				{
				}
			}

		}

		if(currentNode->sibling)
		{
			gen_traverse((currentNode->sibling), tab);
		}	
	} 
	if(verbose1){puts("Leaving gen_traverse\n");}
	
}

int main(int argc, char *argv[], char *envp[])
{
	int holder;
	int i;
int j;
Symbol * s1;
Symbol * s2;
Symbol * s3;

	FILE * input;
	TreeNode * root;
	Symbol * currentSymbol;
	iList * temp;

	verbose1=0;

	for(i=1;i<argc;i++)
	{
		printf("%s:\n", argv[i]);
		input = fopen(argv[i], "r");
		stdin = input;
		setLine();
		set_main_found(0);
		root = analyze();
/*
printTree(root, 0);
*/
		for(j=0;j<26;j++)
		{
			if(!symbolTable[j])
			{
				free(symbolTable[j]);
			}
		}

		currentCodeLine = 0;
	
		global_offset.next = 0;
		global_offset.scope = 0;
		global_offset.positive_offset = 2;
		global_offset.negative_offset = -1;
		current_offset = &global_offset;
	
		/* generate a stub for the instructions to jump to main */
		sprintf(instruction, "<?xml version='1.0' encoding='UTF-8'?>");
		gen_newIList(instruction);
		sprintf(instruction, "<!DOCTYPE DataSourceList PUBLIC '-//SDB//DTD//EN' 'ddl.dtd'>");
		gen_newIList(instruction);
		sprintf(instruction, "<DataSourceList>");
		gen_newIList(instruction);


		gen_variables(root, 0);

		currentSymbol = gen_lookup(gen_newSymbol("main", 0, TYPE_VOID, 1, 0, 0));
	
/*
for(j=0;j<26;j++)
{
s1=symbolTable[j];
while(s1)
{
	printf("%d: %s\n", s1->scope, s1->name);
	if(s1->next)
	{
		s2=s1->next;
		s1=s2;
	}
	else
	{
		break;
	}
}
}
*/
		/* generate a stub for the instructions to jump to main */
		sprintf(instruction, "</DataSourceList>");
		gen_newIList(instruction);
	
		temp = current_ilist = front_ilist;
		while(current_ilist)
		{
			printf("%s", current_ilist->instruction);
			temp = current_ilist->next;
			current_ilist = temp;
		}	

/*
		for(j=0;j<26;j++)
		{
		symbolTable[j]=0;
		}
*/
		fclose(input);
	}
	return 0;
}


