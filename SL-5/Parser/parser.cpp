#include<bits/stdc++.h>
using namespace std;

/*
    S -> aAb
    A -> aB
    B -> bB/-           (- == epsilon)

*/

string s;
int curr_ptr = 0;

void B()
{
    if(s[curr_ptr] != 'b')
        return ;

    curr_ptr++;

    B();
}

void A()
{
    if(s[curr_ptr] != 'a')
        return ;

    else
    {
        curr_ptr++;
        B();
    }
}

void S()
{
    if(s[curr_ptr] != 'a')
        return ;

    else
    {
        curr_ptr++;

        A();

        if(s[curr_ptr] != 'b')
        return ;

        else
            curr_ptr++;
    }
}

int main()
{
    int t;
    cin>>t;

    while(t--)
    {
        cout<<"Enter input : ";
        cin>>s;

        S();
        if(curr_ptr == s.length())
            cout<<"Valid String \n\n";

        else
            cout<<"Invalid String \n\n";

        curr_ptr = 0;

    }
}
