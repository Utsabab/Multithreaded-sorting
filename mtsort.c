#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nums[10] = {7, 78, 2, 6, 22, 13, 90, 52, 46, 11};

void merger(int start,int mid,int end) {
	int length1 = (mid - start) + 1;
	int length2 = end - mid;
	
	int* left = (int *) malloc(length1 * sizeof(int));
	int* right = (int *) malloc(length2 * sizeof(int));

	int i;
	for (i=0; i<length1; i++) {
		left[i] = nums[start + i];
	}

	for (i=0; i<length2; i++) {
		right[i] = nums[mid + i + 1];
	}
	int begin = start;
	int head1=0, head2=0;
	while (head1 < length1 && head2 < length2){
		if (left[head1] < right[head2]) {
			nums[begin] = left[head1];
			head1++;
		}
		else {
			nums[begin] = right[head2];
			head2++;
		}
		begin++;
	}
	while (head1 < length1) {
		nums[begin] = left[head1];
		head1++;
		begin++;
	}
	while (head2 < length2) {
		nums[begin] = right[head2];
		head2++;
		begin++;
	}
}

void merge_sort(int start, int end) {
	//int length = sizeof(arr) / sizeof(arr[0]);
	//length = length / 2;
	int mid;
	if (start < end) {
		mid = (end + start) / 2;
		merge_sort(start, mid);
		merge_sort(mid + 1, end);
		merger(start, mid, end);
	}
}

int main(int argc, char** argv)
{
	merge_sort(0, 9);
	int i;
	for (i=0;i<10;i++){
		printf("%d \n", nums[i]);
	}
	return 0;
}

