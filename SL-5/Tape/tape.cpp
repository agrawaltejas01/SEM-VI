#include<bits/stdc++.h>
using namespace std;

void merge(int arr[], int left, int mid, int right)
{
  int left_len = mid - left + 1;
  int right_len = right - mid;

  int left_arr[left_len], right_arr[right_len];

  for(int i=0; i<left_len; i++)
    left_arr[i] = arr[left + i];

  for(int i=0; i<right_len; i++)
    right_arr[i] = arr[mid+1 + i];

  int left_ind = 0, right_ind = 0;
  int current = left;

  while((left_ind < left_len) && (right_ind < right_len))
  {
    if(left_arr[left_ind] <= right_arr[right_ind])
      arr[current++] = left_arr[left_ind++];

    else
      arr[current++] = right_arr[right_ind++];
  }

  while(left_ind < left_len)
    arr[current++] = left_arr[left_ind++];

  while(right_ind < right_len)
    arr[current++] = right_arr[right_ind++];
}

void merge_sort(int arr[], int low, int high)
{
  if(low >= high)
    return;

  int mid = (low+high)/2;

  merge_sort(arr,low,mid);
  merge_sort(arr,mid+1,high);

  merge(arr, low, mid, high);
}

int is_sorted(int arr[], int n)
{
  if(n == 1)
    return 1;

  int increasing_order = 1;   // tells about order of element

  if(arr[0] > arr[1])
    increasing_order = 0;

  for(int i=1; i<n-1; i++)
  {
    if(arr[i] < arr[i+1])
    {
      if(! increasing_order)
        return 0;
    }

    else if(arr[i] > arr[i+1])
    {
      if(increasing_order)
        return 0;
    }
  }

  if(!increasing_order)
  {
    for(int i=0; i<n/2; i++)
    {
      int temp = arr[i];
      arr[i] = arr[n-i-1];
      arr[n-i-1] = temp;
    }
  }

  return 1;
}

int main()
{
  /*int n;
  cin>>n;

  int arr[n];
  for(int i=0; i<n; i++)
    cin>>arr[i];

  //cout<<is_sorted(arr, n)<<"\n";
  merge_sort(arr, 0, n-1);
  for(int i=0; i<n; i++)
    cout<<arr[i]<<" ";

  cout<<"\n";*/
  int n_files, n_tapes, tape_size;

  cout<<"Enter no of files : ";
  cin>>n_files;
  cout<<"\n";

  cout<<"Enter no of tapes : ";
  cin>>n_tapes;
  cout<<"\n";

  cout<<"Enter size of tapes : ";
  cin>>tape_size;
  cout<<"\n";

  int files[n_files];
  cout<<"Enter files : ";

  for(int i=0; i<n_files; i++)
    cin>>files[i];

  vector<int>tapes[n_tapes];
  int sum[n_tapes];

  for(int i=0; i<n_tapes; i++)
    sum[i] = 0;

  if(! is_sorted(files, n_files))
    merge_sort(files, 0, n_files-1);

  int curr_tape = 0;
  int start_tape = 0;

  for(int i=0; i<n_files; i++)
  {
    if(sum[curr_tape] + files[i] > tape_size)
    {
      /*start_tape = curr_tape;

      while(sum[curr_tape] + files[i] > tape_size && curr_tape != start_tape)
      {
        cout<<"File with size cannot be stored on "<<curr_tape<<"\n";
        curr_tape = (curr_tape + 1)%n_tapes;    // check for next tape
        i--;                  // stay on same file
      }*/       // no need of doing this, coz tapes are going to be stored in sorted manner, hence if this cannot be stored in
                // current, it cannot be stored any where,below ones are already bigger than current, above ones have their sum already
                // greater.
      cout<<"File with size "<<files[i]<<" cannot be stored\n\n";
      break;
    }

    tapes[curr_tape].push_back(files[i]);
    sum[curr_tape] += files[i];

    curr_tape = (curr_tape + 1)%n_tapes;
  }

  for(int i=0; i<n_tapes; i++)
  {
    cout<<i<<" : ";
    for(int j=0; j<tapes[i].size(); j++)
      cout<<tapes[i][j]<<" ";

    cout<<"\n";
  }

  // MRT

  for(int i=0; i<n_tapes; i++)
  {
    int ans = 0;
    int size = tapes[i].size();
    int mult_factor = size;

    for(int j=0; j<size; j++)
    {
      ans += tapes[i][j] * mult_factor;
      mult_factor --;
    }

    cout<<"MRT for tape "<<i<<" : "<<double(ans)/double(size)<<"\n";
  }
}
