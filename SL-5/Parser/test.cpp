#include<bits/stdc++.h>
using namespace std;

string s;
int curr_ptr = 0;

/*
    E -> TA
    A -> +TA/-
    T -> FB
    B -> FB/-
    F -> (E)+id
*/
void E();
void B();

void F()
{
    if(s[curr_ptr] != '(')
        return;

    curr_ptr ++;

    E();

    //if(s[curr_ptr] != ')' || s[curr_ptr+1] != '+')

    string temp = &s[curr_ptr];

    if(temp == ")+id")
        curr_ptr += 4;
}

void B()
{
    F();
    B();
}

void T()
{
    F();
    B();
}

void A()
{
    if( s[curr_ptr] != '+')
        return ;

    else
    {
        curr_ptr++;

         T();
         A();
    }
}

void E()
{
    T();
    A();
}

int main()
{
    int t;
    cin>>t;

    while(t--)
    {
        cout<<"Enter input : ";
        cin>>s;

        E();
        if( curr_ptr == s.length() )
            cout<<"Valid String \n\n";

        else
            cout<<"Invalid String \n\n";
    }
}
