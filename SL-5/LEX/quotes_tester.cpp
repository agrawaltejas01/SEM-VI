#include<bits/stdc++.h>
using namespace std;

int main()
{
  string s;
  cin>>s;

  /*for(int i=0; i<s.length(); i++)
  {
    if(s[i] == '\"')
      cout<<"Yes\n";
  }*/

  if(s == "\"")
    cout<<"Yes\n";

  cout<<s+" "+s<<"\n";
}
