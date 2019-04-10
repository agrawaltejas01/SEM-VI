#include<bits/stdc++.h>
using namespace std;

#define pb push_back

int current_pool = 0;

typedef struct SYMTAB
{
  string symbol;
  int address;
  int length;

  SYMTAB()
  {
    symbol = "";
    address = 0;
    length = 0;
  }
}SYMTAB;

typedef struct LITTAB
{
  string value;
  int address;
  LITTAB()
  {
    value = "";
    address = 0;
  }
}LITTAB;

vector<int> pooltab;
vector<LITTAB>littab;
vector<SYMTAB> symtab;

void read_all_files()
{
  FILE *sym = fopen("symtab", "r");

  while(!feof(sym))
  {
    SYMTAB s;
    char symb_c[20];

    fscanf(sym, "%s %d %d ",symb_c, &s.address, &s.length);

    if(s.address == -1)
    {
      cout<<"ERROR : Address resolution of symbol "<<symb_c<<" was not done\n\n";
      exit(0);
    }

    string symb(symb_c);
    s.symbol = symb;

    symtab.pb(s);
  }

  /*if(symtab.size() > 0)
    symtab.pop_back();*/

  fclose(sym);

  FILE *lit = fopen("littab", "r");

  while(!feof(lit))
  {
    LITTAB l;
    char val_c[20];

    fscanf(lit, "%s %d ",val_c, &l.address);

    if(l.address == -1)
    {
      cout<<"ERROR : Address resolution of litteral "<<val_c<<" was not done\n\n";
      exit(0);
    }

    string val(val_c);
    l.value = val;

    littab.pb(l);
  }

  /*if(littab.size() > 0)
    littab.pop_back();*/

  fclose(sym);

  FILE * pool = fopen("pooltab", "r");

  while(!feof(pool))
  {
    int start, len;

    fscanf(pool, "%d %d", &start, &len);

    pooltab.pb(start);
  }

  fclose(pool);
}

int main()
{
  read_all_files();

  /*for(auto i : symtab)
    cout<<i.symbol<<" "<<i.address<<" "<<i.length<<"\n";

  for(auto i : littab)
    cout<<i.value<<" "<<i.address<<"\n";*/

  FILE * source = fopen("intermediate_code", "r");

  while(!feof(source))
  {
    char loc_c[20], operator_c[20], op1_c[20], op2_c[20];

    fscanf(source, "%s %s %s %s", loc_c, operator_c, op1_c, op2_c);

    string loc(loc_c), opa(operator_c), op1(op1_c), op2(op2_c);

    if(opa[1] == 'A' && (opa[5]!='3' && opa[5]!='2') )    // any AD except LTORG and END
      continue;

    if(opa[1] == 'A' && (opa[5]=='3' || opa[5]=='2'))    // LTORG
    {
      int end = -1;
      int start = pooltab[current_pool];

      if(current_pool == pooltab.size() - 1)
        end = littab.size();

      else
        end = pooltab[current_pool + 1];

      for(int i=start; i<end; i++)
        cout<<littab[i].value<<" = "<<littab[i].address<<"\t";

      cout<<"\n";
        current_pool ++;

        continue;
    }

    else if(opa[1] == 'I')   // IS
    {
      if(op1 == "-")    // stop
        cout<<loc<<"  0 0 0\n";

      //extract opcode

      int j = 4, k=0;
      char opcode[20]  ;

      while(opa[j] != ')')
        opcode[k++] = opa[j++];
      opcode[k] = '\0';

      // extract address of symbol/litteral

      j = 3, k=0;
      char symbol[20];

      while(op2[j] != ')')
        symbol[k++] = op2[j++];
      symbol[k] = '\0';

      int ptr = atoi(symbol);
      int address = 0;

      if(op2[1] == 'L')
        address = littab[ptr].address;

      else
        address = symtab[ptr].address;

      cout<<loc<<" "<<opcode<<" "<<op1[3]<<" "<<address<<"\n";
    }

    else if(opa[1] == 'D')
    {
      //extract value

      int j=3, k=0;
      char val[20];

      while(op2[j] != ')')
        val[k++] = op2[j++];
      val[k] = '\0';

      cout<<loc<<" "<<val<<"\n";
    }

    else
    {
      cout<<"Invalid Operand was identified\n";
      exit(0);
    }

  }



  fclose(source);
}
