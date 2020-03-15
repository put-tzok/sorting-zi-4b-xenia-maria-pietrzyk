#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Project made by Jacek Nowak 4B and Xenia Pietrzyk 4B.

unsigned int ns[] = { 10, 25, 50, 75, 250, 400, 450, 600, 650, 800};

void fill_increasing(int *t, unsigned int n) 
{
	int i;
	for (i = 0; i < n; i++) 
	{
		t[i] = i;
	}
}

void fill_decreasing(int *t, unsigned int n) 
{	
	int i;
	for (i = 0; i < n; i++)
	{		
		t[i] = -i;
	}
}

void fill_vshape(int *t, unsigned int n) {

	int *beg;
	int *end;
	beg = t;
	end = t + n - 1;
	int k = n;
	while (end - beg > 1)
	{
		*beg = k;
		k--;
		*end = k;
		k--;
		beg++;
		end--;
	}
}

void selection_sort(int *t, unsigned int n) 
{
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


void insertion_sort(int *t, unsigned int n) 
{
	int i, k, j;

	for (i = 1; i < n; i++) 
	{
		k = t[i];
		j = i - 1;

		while (j >= 0 && t[j] > k) 
		{
			t[j + 1] = t[j];
			j = j - 1;
		}

		t[j + 1] = k;
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int part(int *t, int low, int high) 
{
	int j;
	int pivot = t[high];
	int i = (low - 1);

	for (j = low; j <= high - 1; j++) 
	{
		if (t[j] <= pivot) {
			i++;
			swap(&t[i], &t[j]);
		}
	}

	swap(&t[i + 1], &t[high]);
	return (i + 1);
}

int rdm_part(int *t, int low, int high) 
{
	int pivot = low + rand() % high;
	swap(&t[pivot], &t[high]);
	return part(t, low, high);
}


void q_s(int *t, int low, int high) 
{
	if (low < high) 
	{
		int pi = part(t, low, high);
		q_s(t, low, pi - 1);
		q_s(t, pi + 1, high);
	}
}

void quick_sort(int *t, unsigned int n) 
{
	q_s(t, 0, n - 1);
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
