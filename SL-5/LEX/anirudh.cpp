#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define max 500
typedef struct symtab
{
	int srno;
	char sym[10];
}symtab;


typedef struct littab
{
	int srno;
	char sym[100];
}littab;


typedef struct ust
{
	int srno;
	char sym[100];
	char type[100];
	int indexno;

}ust;

int search_terminal(char terminal[],int l)
{
	terminal[l]='\0';
	//printf("Terminal,length: %s,%d\n",terminal,strlen(terminal));
	FILE *fp1 = fopen("terminal","r");
	char record[10];
	int k=1;
	fgets(record,10,fp1);
	while(!feof(fp1))
	{
		if(strncmp(record,terminal,strlen(record)-1)==0)
		{

			printf("\n terminal = %s Matched record is %s %d\n",terminal,record,(strlen(record)-1));
			fclose(fp1);
			return k;
		}
		k++;
		fgets(record,10,fp1);
	}
	return 0;
}


int search_keyword(char keyword[])
{
	FILE *fp1 = fopen("keyword","r");
	char record[10];
	int k=1;
	fgets(record,5,fp1);
	while(!feof(fp1))
	{
		if(strcpy(record,keyword))
		{
			fclose(fp1);
			return k;
		}
		k++;
		fgets(record,60,fp1);
	}
	return 0;
}

int check_if_already_in_symtable(char array[],symtab s[])
{
	int i=1;
	while(s[i].srno!=-0)
	{
		if(strcmp(array,s[i].sym)==0)
		{
			return i;
			break;
		}
		i++;
	}

	return 0;
}
int check_if_already_in_littab(char array[],littab l[])
{
	int i=1;
	while(l[i].srno!=-0)
	{
		if(strcmp(array,l[i].sym)==0)
		{
			return i;
			break;
		}
		i++;
	}

	return 0;
}

int insert_into_symbol(char array[],symtab s[])
{
	int i=1;
	int check=check_if_already_in_symtable(array,s);		// checking to see that duplicate symbols are not inserted into symbol table
	if(check!=0)			// if already present
	{
		return check;		// return the position of the symbol
	}
	else						// if not present
	{
		while(s[i].srno!=0)	// go to empty place in symbol table
		{
			i++;
		}
		s[i].srno=i;				// place the symbol in i-th location
		strcpy(s[i].sym,array);
		return i; 		// return the location
	}
}

int insert_into_littab(char array[],littab l[])
{
	int i=1;
	int check=check_if_already_in_littab(array,l);		// checking to see that duplicate symbols are not inserted into symbol table
	if(check!=0)			// if already present
	{
		return check;		// return the position of the symbol
	}
	else						// if not present
	{
		while(l[i].srno!=0)	// go to empty place in symbol table
		{
			i++;
		}
		l[i].srno=i;				// place the symbol in i-th location
		strcpy(l[i].sym,array);
		return i; 		// return the location
	}
}

void insert_into_ust(char sub_array[],char type[],int pos,ust u[])
{
	int i=1;
	while(u[i].srno!=0)			// search till you find empty place
	{
		i++;
	}
	strcpy(u[i].sym,sub_array);	// insert into ith place
	strcpy(u[i].type,type);
	u[i].srno=pos;
}

int check_string(char arr[])
{
  const int string_len = strlen(arr);
  for(int i = 0; i < string_len; ++i)
  {
    if(arr[i]=='.')
    	continue;
    if(!isdigit(arr[i]))
      return 0;
  }
  return 1;
}



int main()
{
	char line[max],sub_array[max],sub_sub_array[2],lit_array[max],flag_comments=0; //declaring variables
	symtab s[max];
	littab l[max];
	ust u[max];
	FILE *fp;												// file pointer
	int i,j,k,len,f,terminal_check,terminal_check_1,keyword_check,sym_position,new_line=0;		// declaring integer variables

	for(i=1;i<=max;i++)				// initialising structures
	{
		s[i].srno=0;
		u[i].srno=0;
		l[i].srno=0;
	}

	fp=fopen("input.c","r");				// opening the file containing the keywords
	fgets(line,60,fp);
	while(!feof(fp))
	{
		k=0;
		len=strlen(line);					// storing the length of retrieved line from file
		//printf("%d %s\n",len,line);

				// initialising the sub array
		printf("START OF NEW LINE %d\n",++new_line);
		for(i=0;i<len-1;i++)
		{
			if(line[i]!=' ' && line[i]!='\t')
				sub_array[k++]=line[i];


			printf("FLAG_COMMENTS = %d\n\n",flag_comments);
			terminal_check=0;
			sub_sub_array[0]=line[i];
			sub_sub_array[1]='\0';
			printf("Value of k= %d and line[i]=%c\n",k,line[i]);



			//printf("Sub array is %s\n",sub_array);


				terminal_check=search_terminal(sub_array,k);	// checking if i-th character of line is a terminal or not
				if(terminal_check!=0 && k!=0)				// if the i-th character is not a terminal
				{

					if(line[i+1]!=' ' && line[i+1]=='/' && line[i]=='/' && flag_comments==0)
					{
						break;

					}


					if(line[i+1]!=' ' && line[i+1]==line[i] && flag_comments==0)
					{
						sub_array[k]=line[i+1];
						terminal_check_1=search_terminal(sub_array,k+2);
						if(terminal_check_1!=0)
						{
							sub_array[k+1]='\0';
							insert_into_ust(sub_array,"TERM",terminal_check_1,u);
							i++;
						}
					}

					else if(line[i]=='/' && line[i+1]=='*')
					{
						//printf("hello");
						//exit(0);
						flag_comments=1;
						//sub_array[k]=line[i+1];
						//terminal_check_1=search_terminal(sub_array,k+2);
						//sub_array[k+1]='\0';
						//insert_into_ust(sub_array,"TERM",terminal_check_1,u);
						i++;
						k=0;
						break;
					}

					else if(line[i]=='*' && line[i+1]=='/')
					{
						//printf("hello babumoshai\n");
						//exit(0);
						flag_comments=0;
						//sub_array[k]=line[i+1];
						//terminal_check_1=search_terminal(sub_array,k+2);
						//sub_array[k+1]='\0';
						//insert_into_ust(sub_array,"TERM",terminal_check_1,u);
						i++;
						k=0;
						break;
					}

					else
					{
						//printf("namaskar");
						//exit(0);
						sub_array[k]='\0';
						insert_into_ust(sub_array,"TERM",terminal_check,u);
					}
				k=0;
			}
			else if((line[i]==' ' || search_terminal(sub_sub_array,1)!=0) && k!=0 && line[i-1]!='\"' && flag_comments==0)
			{

				if(search_terminal(sub_sub_array,1)!=0)
				{
						sub_array[k-1]='\0';
						i--;
						if(check_string(sub_array)==1)
						{
							sym_position=insert_into_littab(sub_array,l);		// insert the symbol into symbol table
							insert_into_ust(sub_array,"LIT",sym_position,u);
							k=0;
						}
						else if(check_string(sub_array)==0)
						{
							sym_position=insert_into_symbol(sub_array,s);		// insert the symbol into symbol table
							insert_into_ust(sub_array,"SYM",sym_position,u);			// inserting into uniform symbol table
							k=0;
						}
				}
				else
				{
						sub_array[k]='\0';				// terminate the sub array



						if(check_string(sub_array)==1)							//printf("Sub array is %s\n\n",sub_array);
						{
							sym_position=insert_into_littab(sub_array,l);		// insert the symbol into symbol table
							insert_into_ust(sub_array,"LIT",sym_position,u);
							k=0;
						}
						else if (check_string(sub_array)==0)
						{
							sym_position=insert_into_symbol(sub_array,s);		// insert the symbol into symbol table
							insert_into_ust(sub_array,"SYM",sym_position,u);			// inserting into uniform symbol table
							k=0;
						}
				}

			}

			else if(line[i-1]=='\"' && flag_comments==0)
			{
				int y=0,z;
				for(z=i;line[z]!='\"';z++)
				{
					lit_array[y++]=line[z];
				}
				lit_array[y]='\0';
				sym_position=insert_into_littab(lit_array,l);		// insert the symbol into symbol table
				insert_into_ust(lit_array,"LIT",sym_position,u);
				k=0;
				i=z-1;
			}
		}
		fgets(line,60,fp);
	}
	i=1;
	printf("\nUNIFORM SYMBOL TABLE\n");
	while(u[i].srno!=0)			// search till you find empty place
	{
		printf("%s %s %d\n",u[i].sym,u[i].type,u[i].srno);			// insert into ith place
		i++;
	}
	printf("\nSYMBOL TABLE\n");
	i=1;
	while(s[i].srno!=0)			// search till you find empty place
	{
		printf("%d %s\n",s[i].srno,s[i].sym);			// insert into ith place
		i++;
	}
	i=1;

	printf("\nLITERAL TABLE\n");

	while(l[i].srno!=0)			// search till you find empty place
	{
		printf("%d %s\n",l[i].srno,l[i].sym);			// insert into ith place
		i++;
	}

	return 0;
}
