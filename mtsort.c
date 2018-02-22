#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* nums;

void merger(int start,int mid,int end) {
	length1 = mid - start;
	length2 = end - (mid + 1);
	
	left = (int *) malloc(length1 * sizeof(int));
	right = (int *) malloc(length2 * sizeof(int));

	int i;
	for (i=0; i<length1; i++) {
		left[i] = nums[i]
	}

	for (i=0; i<length2; i++) {
		right[i] = nums[i]
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
		begin++;
		head1++;
	}
	while (head2 < length2) {
		nums[begin] = right[head2];
		begin++;
		head2++;
	}
}

int* merge_sort(int start, int end) {
	//int length = sizeof(arr) / sizeof(arr[0]);
	//length = length / 2;
	if (start < end) {
		int mid = (end - start) / 2;
		merge_sort(start, mid);
		merge_sort(mid + 1, end);
		merger(start, mid, end);
	}
}

