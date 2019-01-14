#include<bits/stdc++.h>
using namespace std;

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

int main(int argc, char const *argv[])
{
	int len = 5;
	int arr[5] = {38,27,43,1,57};

	merge_sort(arr,0,len-1);

	for (int i = 0; i < len; i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<"\n";

	return 0;
}