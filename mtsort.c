#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int nums[10] = {7, 78, 2, 6, 22, 13, 90, 52, 46, 11};

void *thread_divider(void *ptr);

struct param {
	int start;
	int end;
	int is_sorting_thread;
};

void merger(int start,int mid,int end) {
	//printf("%d *", mid);
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
		//printf("%d \n\n", mid);
		merge_sort(start, mid);
		merge_sort(mid + 1, end);
		merger(start, mid, end);
	}
}

int main(int argc, char** argv)
{

	FILE * fp;
	if (argc>1) {
		fp = fopen(argv[1], "r");
	}
	else {
		fp =fopen("test.txt", "r");
	}

	while (read = getline())

	merge_sort(0, 9);
	int i;
	
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	
	struct param param1;
	struct param param2;
	struct param param3;

	param1.start = 0;
	param1.end = 10 / 2;
	param1.is_sorting_thread = 1;

	param2.start = (10 / 2) + 1;
	param2.end = 10;
	param2.is_sorting_thread = 1;

	param3.start = 0;
	param3.end = 10;
	param3.is_sorting_thread = 0;

	pthread_create(&thread1, NULL, thread_divider, &param1);
	pthread_create(&thread2, NULL, thread_divider, &param2);

	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_create(&thread3, NULL, thread_divider, &param3);
	pthread_join(thread3, NULL);

	for (i=0;i<10;i++){
		printf("%d \n", nums[i]);
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