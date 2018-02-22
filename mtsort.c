#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int* nums;	/*Global array*/

void *thread_divider(void *ptr);

struct param {
	int start;
	int end;
	int is_sorting_thread;
};

void merger(int start,int mid,int end) {
	/*printf("%d *", mid);*/
	int length1 = (mid - start) + 1;
	int length2 = end - mid;
	
	int* left = (int *) malloc(length1 * sizeof(int));
	int* right = (int *) malloc(length2 * sizeof(int));

	int i;
	for (i=0; i<length1; i++) 
	/*fill array left with the first half from the array nums*/
	{
		left[i] = nums[start + i];
	}

	for (i=0; i<length2; i++) 
	/*fill array right with the other half from the array nums*/
	{
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
	

	while (head1 < length1)
	/*if the array right is shorter than array left, concatanate remainder of left array to the nums array*/
	{
		nums[begin] = left[head1];
		head1++;
		begin++;
	}
	while (head2 < length2) 
	/*if the array left is shorter than array right, concatanate remainder of right array to the nums array*/
	{
		nums[begin] = right[head2];
		head2++;
		begin++;
	}
}

void merge_sort(int start, int end) {
	int mid;
	if (start < end) {
		mid = (end + start) / 2;
		merge_sort(start, mid);				//recursive on left part of array
		merge_sort(mid + 1, end);			//recursive on right part of array
		merger(start, mid, end);			//merging the two sorted arrays
	}
}

int main(int argc, char** argv)
{
	FILE * fp;
	if (argc>1) {
		fp = fopen(argv[1], "r");			//read through user input
	}
	else {
		fp =fopen("test.txt", "r");			//read through text file
	}	

	char * num = NULL;
	size_t len = 0;
	int counter = 0;
	ssize_t read;

	while ((read = getline(&num, &len, fp)) != -1) {
		counter++;
	}

	if (argc>1) {
		fp = fopen(argv[1], "r");
	}
	else {
		fp =fopen("test.txt", "r");
	}

	nums = (int *) malloc(counter * sizeof(int));

	int i = 0;
	printf("This is the unsorted numbers from array: \n");
	while ((read = getline(&num, &len, fp)) != -1) {

		nums[i] = atoi(num);

		printf("%s", num);
		i++;
	}
	
	/*Declare three threads*/
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	/*Three instances of struct for three threads*/
	struct param param1;
	struct param param2;
	struct param param3;

	/*Start and end values for first thread to begin sorting*/
	param1.start = 0;
	param1.end = counter / 2;
	param1.is_sorting_thread = 1;


	/*Start and end values for second thread to begin sorting*/
	param2.start = (counter / 2) + 1;
	param2.end = counter;
	param2.is_sorting_thread = 1;

	/*Start and end values for third thread to merge two other arrays into one*/
	param3.start = 0;
	param3.end = counter;
	param3.is_sorting_thread = 0;

	pthread_create(&thread1, NULL, thread_divider, &param1);

	pthread_create(&thread2, NULL, thread_divider, &param2);

	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_create(&thread3, NULL, thread_divider, &param3);
	pthread_join(thread3, NULL);

	printf("\n\nThis is the sorted integers from array: \n");

	for (i=0;i<=counter;i++){
		printf("%d \n",  nums[i]);
	} 

	return 0;
}

void *thread_divider(void *ptr)
{	
	struct param *data = ptr;
	if (data->is_sorting_thread == 1) {
		merge_sort(data->start, data->end);
	}
	else {
		int mid = (data-> start + data->end) / 2;
		merger(data->start, mid, data->end);
	} 
}