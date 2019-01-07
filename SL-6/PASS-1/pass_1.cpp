#include <bits/stdc++.h>
using namespace std;

/*

validations done : 1. Code should begin with start
                             2. Code should end with END
                             3. Invalid Mnemonics
                             4. Invalid number of operands
                             5. Address of symbol not resolved

*/


int loc = 0;            // location counter
char type_of_instruction[20];
int opcode, length,no_of_operands_needed;         // length = length of instruction
int LTP = 1;                    //  LTP = index of literal table
int PTP = 1;                    // PTP = pooltable pointer handles pool
int pooltab[10] ;

typedef struct SYMTAB
{
    int sr_no ;
    char label_symbol[200];
    char size[200];
    int address;
}SYMTAB;

typedef struct LITTAB
{
    int sr_no;
    int literal;
    int address;
}LITTAB;

SYMTAB symtab[100];
LITTAB littab[100];

void init()
{
    for(int i=0;i<20;i++)
    {
        symtab[i].sr_no = -1;
        littab[i].sr_no = i+1;            // this is handled by LTP
    }

    pooltab[1] = 1;
}

int search_mot(char query[])
{
    FILE *mot;
    mot = fopen("MOT", "r");

    while(!feof(mot))
    {
        char buffer[200];
        char mnemonic[20];
        fscanf(mot,"%s %d %s %d %d", mnemonic, &opcode, type_of_instruction, &length, &no_of_operands_needed);

        //cout<<type_of_instruction<<"\n";

        if(!strcmp(query, mnemonic))
            return 1;
    }

    return 0;
}

int check_SYMTAB(char label[], char mnemonic[], char op2[])     // mnemonic is needed for symbol
{                                                                                                   // address resolving

    int i=0, found = 1, return_value;

    for(i=0;i<100;i++)
    {
        if( !strcmp(symtab[i].label_symbol, label))
        {
            found = 1;

            if(symtab[i].address == -1 && (!strcmp(mnemonic, "ds") || !strcmp(mnemonic, "dc")) ) //// label
                                //will be repeated in case of ds or dc only. When it will be symbol whose address is
                                //to be resolved and hence it has come as label
                symtab[i].address = loc;

            else if(symtab[i].address != -1)    // if address is not -1 then it was never symbol
                symtab[i].address = loc;

            strcpy(symtab[i].size, op2);

            break;
        }

        else if(symtab[i].sr_no == -1)
        {
            found = 0;
            break;
        }
    }

    if(!found)
    {
        symtab[i].sr_no = i+1;
        strcpy(symtab[i].label_symbol,label);

        if( !strcmp(label, op2))            // means symbol is encounterd in imperative statement for 1st time
            symtab[i].address = -1;

        else
            symtab[i].address = loc;
    }

    if(symtab[i].address != -1)
        return symtab[i].address ;       // return adress of entry in case of label or symbol whos address is
                                                        //resolved

    else
        return i+1;  // if symbol's address is not resolved return index
                            // indexing starts from 1 hence i+1
}

int add_in_LITTAB(char literal)
{

    littab[LTP].literal = literal - '0';
    littab[LTP].address = loc;

}

void check_equ(char label[], char OP2[])
{

    int label_index=0, op2_index=0;         //indexes in symtab
    int adding_constant = 0;
    char op2[20];

    int i;
    for( i=0;i<strlen(OP2); i++)
    {
        if(OP2[i] == '+')           // loop+6
        {
            adding_constant = OP2[i+1] - '0';
            break;
        }

        else
            op2[i] = OP2[i];
    }
    op2[i] = '\0';

    for(int i=0;i<20;i++)
    {
        if(symtab[i].sr_no == -1)
            break;

        if( !strcmp(label,symtab[i].label_symbol))
            label_index = i;

        else if ( !strcmp(op2, symtab[i].label_symbol))
            op2_index = i;
    }

    symtab[label_index].address = symtab[op2_index].address + adding_constant;
}

int check_origin(char OP2[])
{

    if(OP2[0]>='0' && OP2[0]<='9') // if direct integer address is given
    {
        return atoi(OP2);

    }

    else
    {
        char op2[20];
        int adding_constant = 0;

        int i;
        for( i=0;i<strlen(OP2); i++)
        {
            if(OP2[i] == '+')           // loop+6
            {
                adding_constant = OP2[i+1] - '0';
                break;
            }

            else
                op2[i] = OP2[i];
        }
        op2[i] = '\0';

        for(int i=0;i<20;i++)
        {
            if(symtab[i].sr_no == -1)
                break;

            else if ( !strcmp(op2, symtab[i].label_symbol))
            {
                return symtab[i].address + adding_constant;
            }
        }

    }
}

void print_in_file()
{
    FILE *symbol_table, *litteral_table ;    // litteral table ????
    symbol_table = fopen("symbol_table", "w");

    for(int i=0;i<30;i++)
    {
        if(symtab[i].sr_no == -1)
            break;

        else
            fprintf(symbol_table, "%d %s %s %d\n",symtab[i].sr_no, symtab[i].label_symbol, symtab[i].size, symtab[i].address );
    }

    fclose(symbol_table);
}

int main()
{
    FILE *source, *destin;
    source = fopen("source_code", "r");
    destin = fopen("intermediate_code", "w");

    char mnemonic[20],label[20],op1[20],op2[20];

    init();

    int label_return;
    int end = 0;
    int no_of_operands_present = 0;

    fscanf(source, "%s %s %s %s", label, mnemonic, op1, op2);

    if(strcmp(mnemonic,"START"))
    {
        cout<<"Code should start with START !!!\n";
        return 0;
    }

    while(!feof(source))
    {
        no_of_operands_present = 0;

        char buffer[200];
        fgets(buffer,300,source);

        sscanf(buffer, "%s %s %s %s", label, mnemonic, op1, op2);   // for now give -

        for(int i=0;i<strlen(mnemonic);i++)
            mnemonic[i] = tolower(mnemonic[i]);

        for(int i=0 ;i<strlen(label);i++)
            label[i] = tolower(label[i]);

        for(int i=0; i<strlen(op2); i++)
            op2[i] = tolower(op2[i]);

        if( strcmp(op1,"-"))
            no_of_operands_present++;

        if( strcmp(op2,"-"))
            no_of_operands_present++;

        int mnemonic_check = search_mot(mnemonic);

        if(mnemonic_check == 0)         // invalid mnemonic check
        {
            end = 0;
            cout<<"Invalid mnemonic was found !!!!"<<endl;
            cout<<mnemonic<<endl;
            return 0;
        }

        if(no_of_operands_present != no_of_operands_needed)
        {
            end = 0;
            cout<<"Invalid number of operands \n";
            cout<<mnemonic<<" "<<no_of_operands_present<<" "<<no_of_operands_needed<<endl;
            return 0;
        }

        if( !strcmp(mnemonic, "end"))       // if end break
        {
            end = 1;
    break;
        }

        if( strcmp(label, "-"))
        {
            label_return=check_SYMTAB(label,mnemonic,op2);
        }

      if(!strcmp(mnemonic, "ds"))
        {
            fprintf(destin,"%d (DL,02)(c,%s)\n",loc,op2);
            loc += atoi(op2);
        }

     else if(!strcmp(mnemonic, "dc"))
        {
            fprintf(destin,"%d (DC,01)(c,%s)\n",loc,op2);
            loc++;
        }


       else if( !strcmp(mnemonic, "ltorg"))
        {
            PTP ++;         // start new pool
            pooltab[PTP] = LTP; // pool ends at current value of ltp
            fprintf(destin,"%d (AD,03)\n",loc);
        }

        else if( !strcmp(mnemonic, "start"))
        {
            sscanf(op2, "%d", &loc);
            fprintf(destin,"0 (%s,%d)(C,%s)\n",type_of_instruction, opcode, op2);
        }

        else if(!strcmp(mnemonic, "origin"))    // updates loc
        {
            int new_loc = check_origin(op2);

            fprintf(destin,"%d (AD,04)(c,%d)\n",loc,new_loc);

            loc = new_loc;
        }

        else if( !strcmp(mnemonic, "equ") )
        {
            check_equ(label,op2);       // equ will ALWAYS have label
        }

        else if( !strcmp(mnemonic, "stop"))
        {
            fprintf(destin, "(IS,00)\n" );
            loc += length;
        }

        else
        {
            int reg_value,address;          // there will always be op1 and it will always be register
            char S_or_L;

            if( !strcmp(op1,"AREG") || !strcmp(op1,"areg"))
                reg_value = 1;

            else if( !strcmp(op1,"BREG") || !strcmp(op1,"breg"))
                reg_value = 2;

            else
                reg_value = 3;

            if(op2[0] == '=')       // literal looks like ='5'
            {
                S_or_L = 'L';
                add_in_LITTAB(op2[2]);

                address = LTP;
                LTP++;
            }

            else
            {
                S_or_L = 'S';
                address = check_SYMTAB(op2,mnemonic,op2);
            }

            fprintf(destin,"%d (%s,%d)(R,%d)(%c,%d)\n",loc,type_of_instruction, opcode, reg_value,S_or_L,address);

            loc += length;

        }

    }

    if(end)             // END has been encouterd
    {
        PTP ++;
        pooltab[PTP] = LTP;
        fprintf(destin,"%d (AD,01)\n",loc);

        print_in_file();        // symbol table and litteral table is written in files

         for(int i=0;i<20;i++)           // checking address resolution
        {
            if(symtab[i].sr_no == -1)
                break;

            else if(symtab[i].address == -1)
            {
                cout<<"Address of "<<symtab[i].label_symbol<<" was not resolved !!!!"<<endl;
                return 0;
            }
        }
    }

    else            // END was not encounterd
    {
       /* fclose(destin);                                                   // if output is not to be given
        destin = fopen("intermediate_code", "w");

        fprintf(destin, "Error was encounterd !!!\n" );*/

        cout<<"Error : End was not encounterd !!!"<<endl;
        return 0;



    }

    fclose(source);
    fclose(destin);

}
