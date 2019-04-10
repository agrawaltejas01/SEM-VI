#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define fi first
#define se second
#define ios ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define fori(i,start_value, n) for(int i=start_value; i<n; i++)
#define ford(i,start_value, n) for(int i=start_value; i>=n; i--)
#define take_array(arr, len) for(int i=0; i<len; i++) cin>>arr[i];
#define print_array(arr, len) for(int i=0; i<len; i++) cout<<arr[i]<<" "; cout<<"\n";

typedef long long ll ;
typedef long double ld ;
typedef long long int lli;

using namespace std;

int ust_sr_no = 0, symtab_sr_no = 0, littab_sr_no = 0;
int multiline_comment_active = 0;
int double_quotes_activate = 0;

map<string, int>symtab, littab;

typedef struct ust
{
	int sr_no;
	string sym;
	string type;
	int index_no;
}UST;

vector<UST> ust;

int is_terminal(string input)
{
  input += "\n";

  int line_no = 0;
  FILE * TRM = fopen("Terminal_table", "r");
  char buffer[10];

  fgets(buffer, 10, TRM);
  while(!feof(TRM))
  {
    string curr(buffer);

    if(curr == input)
    {
      fclose(TRM);
      return line_no+1;
    }

    else
      line_no++;

    fgets(buffer, 10, TRM);
  }

  fclose(TRM);
  return -1;
}

int is_symbol(string input)
{
  if( isdigit(input[0]) )  // 1st character should not be number
    return 0;

  for(int i=1; i<input.length(); i++)
  {
    if( !isalnum(input[i]) && input[i] != '_' )  // if special character and not '_' return -1
        return 0;
  }

  return 1;
}

vector<string> extract_lexeme(string line)
{
  vector<string> ans;

  string word = "";
  for (auto x : line)
  {
     if (x == ' ')
     {
         ans.pb(word);
         word = "";
     }

     else
     {
         word = word + x;
     }
  }
  ans.pb(word);

  return ans;
}

void process(string line)
{
  int len = line.length();
  int terminal_index, symbol_index, litteral_index;
  string str="";      // used for "" handling

  vector<string> lexeme_array;
  lexeme_array = extract_lexeme(line);

  for(auto i : lexeme_array)
  {
      cout<<i<<" ";
  }
  cout<<"\n";

  for(auto curr : lexeme_array)
  {
    if(curr == "//")
      return;

    else if(curr == "*/")
    {
      multiline_comment_active = 0;
      continue;
    }

    if(multiline_comment_active)
      continue;

    else if(curr == "/*")
    {
      multiline_comment_active = 1;
      continue;
    }

    /*if(curr == " \" " && !double_quotes_activate)  // starting "
    {
      UST u;      // pushing " in ust
      u.sr_no = ust_sr_no++;
      u.sym = curr;
      u.type = "TRM";
      u.index_no = 17;
      ust.pb(u);


      double_quotes_activate = 1;
      continue;
    }

    if(curr != " \" " && double_quotes_activate)  // in between string
    {
      str += curr;
      str += "\0";    // needs to be addes manually
      continue;
    }

    if(curr == " \" " && double_quotes_activate)   // ending "
    {
      double_quotes_activate = 0;       // now add str in litt and reinitialize it with null

      littab[str] = littab_sr_no;

      UST u;      // pushing " in ust
      u.sr_no = ust_sr_no++;
      u.sym = str;
      u.type = "LIT";
      u.index_no = littab_sr_no++;
      ust.pb(u);

      str = "";

      UST v;      // pushing " in ust
      v.sr_no = ust_sr_no++;
      v.sym = curr;
      v.type = "TRM";
      v.index_no = 17;

      ust.pb(v);
      continue;
    }*/

    terminal_index = is_terminal(curr);

    if(terminal_index != -1)   // if terminal, insert in UST and continue
    {
      UST u;
      u.sr_no = ust_sr_no++;
      u.sym = curr;
      u.type = "TRM";
      u.index_no = terminal_index;

      ust.pb(u);
      continue;
    }

    else if(is_symbol(curr))    // if not terminal, check if symmbol
    {
      UST u;
      u.sr_no = ust_sr_no++;
      u.sym = curr;
      u.type = "SYM";

      auto checker = symtab.find(curr); // check if already present in littab
      if(checker == symtab.end())   // if not in litteral table, enter in littab and  UST
      {
        symtab[curr] = symtab_sr_no;

        u.index_no = symtab_sr_no++;

      }

      else      // if already in littab enter in UST
        u.index_no = symtab[curr];

      ust.pb(u);

      continue;
    }

    else    // if not terminal and symbol, it has to be litteral
    {
      UST u;
      u.sr_no = ust_sr_no++;
      u.sym = curr;
      u.type = "LIT";

      auto checker = littab.find(curr); // check if already present in littab
      if(checker == littab.end())   // if not in litteral table, enter in littab and  UST
      {
        littab[curr] = littab_sr_no;

        u.index_no = littab_sr_no++;

      }

      else      // if already in littab enter in UST
        u.index_no = littab[curr];

      ust.pb(u);

      continue;
    }

  }
}

int main()
{

	FILE *source, *destin;
  source = fopen("source_code", "r");

  char buffer[50];
  fgets(buffer, 50, source);

  while(!feof(source))
  {
    int len = strlen(buffer);
    //cout<<buffer<<" "<<len<<"\n";
    string line(buffer);    // converts char array to string
    line.pop_back();
    process(line);

    fgets(buffer, 50, source);
  }

  cout<<"-------------------------UST----------------------------\n";
  for(int i=0; i<ust.size(); i++)
  {
    cout<<ust[i].sr_no<<"  "<<ust[i].sym<<"  "<<ust[i].type<<"  "<<ust[i].index_no<<"  \n";
  }

  cout<<"-------------------------SYMTAB----------------------------\n";
  for(auto i:symtab)
  {
    cout<<i.fi<<"  "<<i.se<<"  \n";
  }

  cout<<"-------------------------LITTAB----------------------------\n";
  for(auto i:littab)
  {
    cout<<i.fi<<"  "<<i.se<<"  \n";
  }

	return 0;
}
