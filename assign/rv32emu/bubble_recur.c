// Task2: bubble_recur.c

// A function to implement recursive bubble sort
// Assume all the elements in arr[] is less than 100
void bubble_sort_recur(int arr[], int n)
{
  // Task2 TODO: Fill this function
	if(n <= 1) return;
	int t = 0;
	for (int i = 0; i < n - 1; ++i){
	   if(arr[i] > arr[i + 1]){
	       	t = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = t;
	   }
	}
	bubble_sort_recur(arr, n - 1);
}

// A function to print an array
void print_array(int arr[], int size)
{
	volatile char* tx = (volatile char*) 0x40002000;
	
  // Task2 TODO: Fill this function
	int t = 0; int q = 0; int r = 0;
	for(; size > 0; --size){
		r = *arr; ++arr;
		q = 0;
		while(r >= 10){
			t = 0;
			while(r >= (10 << t)) ++t;
			--t;
			q = q | (1 << t);
			r = r - (10 << t);
			}
		if (q != 0) *tx = (char) q + '0';
		*tx = (char) r + '0';
		*tx = ' ';
	}
}


// Entry point
// DO NOT CHANGE THIS FUNCTION
void _start()
{
  static int arr[] = {38, 64, 61, 86, 8, 16, 36, 88, 2, 29,
                      91, 48, 39, 69, 68, 13, 23, 6, 35, 90,
                      47, 74, 19, 76, 85, 70, 49, 27, 99, 57,
                      93, 26, 24, 9, 84, 87, 22, 75, 33, 53,
                      52, 45, 60, 42, 30, 62, 51, 37, 1, 89,
                      66, 59, 77, 21, 28, 10, 82, 67, 4, 50,
                      40, 20, 41, 98, 92, 58, 43, 78, 46, 96,
                      65, 83, 54, 32, 72, 81, 3, 31, 44, 63,
                      71, 18, 73, 11, 14, 25, 94, 34, 7, 15,
                      97, 12, 56, 95, 55, 79, 5, 17, 80};

  int n = sizeof(arr)/sizeof(arr[0]);
  bubble_sort_recur(arr, n);
  print_array(arr, n);
}
