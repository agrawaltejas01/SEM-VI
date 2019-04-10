#include<bits/stdc++.h>
using namespace std;

void NQueens(int,int);
bool place(int,int);
void print(int);

vector<int>x;
int total_ans;

int main()
{
	int n;
	cout<<"\nEnter number of Queens : ";
	cin>>n;
	x.resize(n+1,0);
	NQueens(1,n);
}
void NQueens(int row,int n)
{

    for(int column=1;column<=n;column++)
    {
        if(place(row,column))
        {
            x[row]=column;      //no conflicts so place queen
            if(row==n)          //dead end
                print(n);       //printing the board configuration
            else                //try queen with next position
                NQueens(row+1,n);
        }
    }
}

//Retruns 1 if we can place the queen otherwise returns 0
bool place(int row,int column)
{
    for(int i=1;i<=row-1;i++)       //Check for same row condition
    {
        if(x[i]==column)            //Check for same column condition
            return 0;
        else if(abs(x[i]-column)==abs(i-row))       //Check for same diagonal condition
            return 0;
    }
    return true; //no conflicts
}

void print(int n)
{
	total_ans++;
	cout<<"\nSolution Number "<<total_ans<<"\n";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(x[i]==j)
				cout<<"Q ";
			else cout<<"- ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}
