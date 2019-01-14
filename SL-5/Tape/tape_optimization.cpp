#include<bits/stdc++.h>
using namespace std;

int check_if_sorted(int n, int arr[])
{
    if(n==1 || n==2)
        return 1;

    char initial;
    int curr = 0, next = 1, sorted = 1;

    while(arr[curr] == arr[next] && next < n)
    {
        curr++;
        next++;
    }

    if(next == n)       // all elments are equal
        return sorted;

    if(arr[curr] < arr[next])   // g = next > current i.e, increasing order
        initial = 'g';

    else
         initial = 'l';

    switch (initial)
    {
        case 'l' :
        {
            for(int i=curr;i<n-1;i++)
            {
                if(arr[i] < arr[i+1])
                {
                    return 0;
                    break;
                }
            }

            for(int i=0;i<n/2;i++)
            {
                swap(arr[i],arr[n-i-1]);
            }
            sorted = 1;
            break;
        }

        case 'g' :
        {
            for(int i=curr;i<n-1;i++)
            {
                if(arr[i] > arr[i+1])
                {
                    return 0;
                    break;
                }
            }


        }
    }

    return sorted;
}

void merge(int arr[], int left, int mid, int right)
{
    int len_left = mid - left + 1;
    int len_right = right - mid;

    int left_arr[len_left], right_arr[len_right];

    for(int i=0;i<len_left;i++)
        left_arr[i] = arr[left + i];

    for (int i = 0; i < len_right; ++i)
        right_arr[i] = arr[mid+1 + i];

    int left_ind=0, right_ind=0;
    int current = left;

    while((left_ind < len_left) && (right_ind < len_right))
    {
        if(left_arr[left_ind] <= right_arr[right_ind])
        {
            arr[current] = left_arr[left_ind];
            left_ind++;
            current++;
        }

        else
        {
            arr[current] = right_arr[right_ind];
            right_ind++;
            current++;
        }
    }

    while(left_ind < len_left)
    {
        arr[current] = left_arr[left_ind];
        left_ind++;
        current++;
    }

    while(right_ind < len_right)
    {
        arr[current] = right_arr[right_ind];
        right_ind++;
        current++;
    }
}

void merge_sort(int arr[],int left, int right)
{
    if(left < right)
    {
        int mid = left + (right-left)/2;

        merge_sort(arr,left,mid);
        merge_sort(arr,mid+1,right);

        merge(arr,left,mid,right);
    }
}


int main()
{
    int n=6;
    int arr[6] = {6,5,4,3,2,1};

    int tapes = 0,files = 0, total_tape = 0;

    /*cout<<"Enter number of tapes : ";
    cin>>tapes;
    cout<<endl;*/

    cout<<"Enter number of files : ";
    cin>>files;
    cout<<endl;

    int tape_len[tapes], files_len[files];

    for (int i = 0; i < tapes; i++)
    {
        cout<<"Enter tape size of tape "<<i+1<<" : ";
        cin>>tape_len[i];
        cout<<endl;

        total_tape += tape_len;
    }

    for (int i = 0; i < files; i++)
    {
        cout<<"Enter file size of file "<<i+1<<" : ";
        cin>>files_len[i];
        cout<<endl;
    }

    if( !check_if_sorted(files,files_len))
        merge_sort(files_len,0,files-1);



    for(int i=0;i<files;i++)
        cout<<files_len[i]<<" ";
    cout<<"\n";



}
