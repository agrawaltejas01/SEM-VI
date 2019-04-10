#include<bits/stdc++.h>
using namespace std;

typedef struct min_max
{
  int min;
  int max;
}min_max;

min_max find_min_max(int arr[], int low, int high)
{
  min_max curr;

  if(low == high)       // only 1 element
  {
    curr.min = curr.max =  arr[low];
    return curr;
  }

  if(low +1 == high)    // 2 element
  {
    if(arr[low] < arr[high])
    {
      curr.min = arr[low];
      curr.max = arr[high];
    }

    else
    {
      curr.min = arr[high];
      curr.max = arr[low];
    }

    return curr;
  }

  int mid = (low + high)/2;

  min_max left = find_min_max(arr, low, mid);

  min_max right = find_min_max(arr, mid, high);

  if(left.min < right.min)
    curr.min = left.min;

  else
    curr.min = right.min;

  if(left.max > right.max)
    curr.max = left.max;

  else
    curr.max = right.max;

  return curr;
}

int main()
{
  int n;
  cin>>n;

  int arr[n];
  for(int i=0; i<n; i++)
    cin>>arr[i];

  min_max ans = find_min_max(arr,0,n-1);

  cout<<ans.min<<" "<<ans.max<<"\n";

}
