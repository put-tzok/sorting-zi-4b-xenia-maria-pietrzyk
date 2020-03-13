#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

unsigned int ns[] = { 10, /* TODO: fill in "n" i.e. instance sizes */ };

void fill_increasing(int *t, unsigned int n) {
    // TODO: implement 
}

void fill_decreasing(int *t, unsigned int n) {
    // TODO: implement
}

void fill_vshape(int *t, unsigned int n) {
    // TODO: implement
}

void selection_sort(int *t, unsigned int n) {
    // TODO: implement
	
	int position, swap;

	for (int c = 0; c < (n); c++)

		for (int c = 0; c < (n - 1); c++)
		{
			position = c;
			for (int d = c + 1; d < n; d++)
			{
				if (t[position] > t[d])
					position = d;
			}
			if (position != c)
			{
				swap = t[c];
				t[c] = t[position];
				t[position] = swap;
			}
		}
}

void insertion_sort(int *t, unsigned int n) {
    // TODO: implement

	int d, c;

	for (int i = 1; i < n - 1; i++)
	{
		d = i;
	}
	while (d > 0 && t[d] < t[d - 1])
	{
		c = t[d];
		t[d] = t[d - 1];
		t[d - 1] = c;
		d--;
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int piv_l_partition(int *t, int low, int high)
{
	int pivot = t[high];
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++)
	{		 
		if (t[j] < pivot)
		{
			i++; 
			swap(&t[i], &t[j]);
		}
	}
	swap(&t[i + 1], &t[high]);
	return (i + 1);
}


void quick_sort(int *t, int low, int high) {
	// TODO: implement

	if (low < high)
	{		
		int pivot = piv_l_partition(t, low, high);
				 
		quick_sort(t, low, pivot - 1);
		quick_sort(t, pivot + 1, high);
	}
}

int piv_2_partition(int *t, int low, int high, unsigned int n)
{
	int pivot = rand() % n;
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++)
	{	  
		if (t[j] < pivot)
		{
			i++; 
			swap(&t[i], &t[j]);
		}
	}
	swap(&t[i + 1], &t[high]);
	return (i + 1);
}
void quick_sort_rdm(int *t, int low, int high, unsigned int n) {
	// TODO: implement

	if (low < high)
	{
		int pivot = piv_2_partition(t, low, high, n);
	
		quick_sort_rdm(t, low, pivot - 1, n);
		quick_sort_rdm(t, pivot + 1, high, n);
	}
}

void heap_heapify(int *t, unsigned int n, int i)
{
	int larg = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && t[l] > t[larg])
		larg = l;

	if (r < n && t[r] > t[larg])
		larg = r;

	if (larg != i)
	{
		swap(t[i], t[larg]);
		heap_heapify(t, n, larg);
	}
}


void heap_sort(int *t, unsigned int n) {
	// TODO

	for (int i = n / 2 - 1; i >= 0; i--)
		heap_heapify(t, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(t[0], t[i]);
		heap_heapify(t, i, 0);
	}
}

void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
