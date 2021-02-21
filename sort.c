#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define RANDOM_LIMIT 10000

long long select_comp[4];
long long select_swap[4];
long long heap_comp[4];
long long heap_swap[4];

// построение массивов - случайный - неубывающий - невозрастающий
void random_array_generation(long long *array, int size);
void increasing_array_generation(long long *array, int size);
void decreasing_array_generation(long long *array, int size);

// проверка отсортированности массива
// производится по неубыванию
void is_sorted(long long *array, int size, int num, int par);

// компаратор
long long compare(long long a, long long b);

// свап двух элементов массива
void swap(long long *a, long long *b);

// сортировки
void selection_sort(long long *array, int size, int numb);
void heapify(long long *array, int index, int size, int numb);
void heap_sort(long long *array, int size, int numb);

// доп функция для случайного числа
long long random_module(void);

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int n; scanf("%d", &n);
    
    clock_t program_start = clock();
    clock_t select_start[4];
    clock_t select_stop[4];
    clock_t heap_start[4];
    clock_t heap_stop[4];

    long long *select_test1 = calloc(n, sizeof(long long));
    long long *select_test2 = calloc(n, sizeof(long long));
    long long *select_test3 = calloc(n, sizeof(long long));
    long long *select_test4 = calloc(n, sizeof(long long));

    increasing_array_generation(select_test1, n);
    decreasing_array_generation(select_test2, n);
    random_array_generation(select_test3, n);
    random_array_generation(select_test4, n);

    long long *heap_test1 = calloc(n, sizeof(long long));
    long long *heap_test2 = calloc(n, sizeof(long long));
    long long *heap_test3 = calloc(n, sizeof(long long));
    long long *heap_test4 = calloc(n, sizeof(long long));

    for (int i = 0; i < n; ++i) {
        heap_test1[i] = select_test1[i];
        heap_test2[i] = select_test2[i];
    }

    random_array_generation(heap_test3, n);
    random_array_generation(heap_test4, n);

    select_start[0] = clock();
    selection_sort(select_test1, n, 0);
    select_stop[0]  = clock();
    is_sorted(select_test1, n, 1, 1);
    
    select_start[1] = clock();
    selection_sort(select_test2, n, 1);
    select_stop[1]  = clock();
    is_sorted(select_test2, n, 2, 1);
    
    select_start[2] = clock();
    selection_sort(select_test3, n, 2);
    select_stop[2]  = clock();
    is_sorted(select_test3, n, 3, 1);
    
    select_start[3] = clock();
    selection_sort(select_test4, n, 3);
    select_stop[3]  = clock();
    is_sorted(select_test4, n, 4, 1);
    
    puts("");
    
    heap_start[0] = clock();
    heap_sort(heap_test1, n, 0);
    heap_stop[0]  = clock();
    is_sorted(heap_test1, n, 1, 0);
    
    heap_start[1] = clock();
    heap_sort(heap_test2, n, 1);
    heap_stop[1]  = clock();
    is_sorted(heap_test2, n, 2, 0);
    
    heap_start[2] = clock();
    heap_sort(heap_test3, n, 2);
    heap_stop[2]  = clock();
    is_sorted(heap_test3, n, 3, 0);
    
    heap_start[3] = clock();
    heap_sort(heap_test4, n, 3);
    heap_stop[3]  = clock();
    is_sorted(heap_test4, n, 4, 0);
    
    puts("");
    
    clock_t program_stop = clock();

    printf("TEST #      Time (sec)             Comparisons                    Swap\n");
    
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", i + 1);

        printf("Selection : %10.4Lf        %16lld        %16lld\n",
            (long double)(select_stop[i] - select_start[i])/CLOCKS_PER_SEC, select_comp[i], select_swap[i]);
        
        printf("Heap      : %10.4Lf        %16lld        %16lld\n",
            (long double)(heap_stop[i]   - heap_start[i])  /CLOCKS_PER_SEC, heap_comp[i],  heap_swap[i]);
    
        puts("");
    }
    
    printf("Program run time : %.4Lf seconds\n", (long double)(program_stop - program_start)/CLOCKS_PER_SEC);
    
    return 0;
}

long long random_module(void) {
    long long a = rand() % RANDOM_LIMIT;
    return a;
}

void swap(long long *a, long long *b) {
    long long t = *a;
    *a = *b;
    *b = t;
}

long long compare(long long a, long long b) {
    if (a >= 0 && b >= 0) return a > b;
    if (a < 0 && b < 0) return a < b;
    if (a >= 0 && b < 0) return a > -b;
    if (a < 0 && b >= 0) return -a > b;
    return 1;
}

void is_sorted(long long *array, int size, int num, int par) {
    for (int i = 1; i < size; ++i) {
        if (compare(array[i - 1], array[i])) {
            printf("ERROR! Array #%d is not sorted ", num);
            if (par) printf("by Heap sort\n");
            else printf("by Selection sort\n");
            return;
        }
    }
    printf("Array #%d is sorted succesfully ", num);
    if (par) printf("by Heap sort\n");
    else printf("by Selection sort\n");
}

void random_array_generation(long long *array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = random_module() * (random_module()&1 ? -1 : 1); // есть возможность поставить random^4
    }
}

void increasing_array_generation(long long *array, int size) {
    long long first = 0;
    for (int i = 0; i < size; ++i) {
        array[i] = first;
        if (random_module()&1) first++;
    }
}

void decreasing_array_generation(long long *array, int size) {
    long long first = LLONG_MAX;
    for (int i = 0; i < size; ++i) {
        array[i] = first;
        if (random_module()&1) first--;
    }
}

void selection_sort(long long *array, int size, int numb) {
    for (int i = 0; i < size - 1; ++i) {
        long long min = i;
        for (int j = i + 1; j < size; ++j) {
            select_comp[numb]++;
            if (compare(array[min], array[j])) min = j;
        }
        if (min != i) {
            swap(array + i, array + min);
            select_swap[numb]++;
        }
    }
}

void heapify(long long *array, int index, int size, int numb) {
    int max = index;
    int left  = 2 * index + 1;
    int right = 2 * index + 2;

    if (left  < size && compare(array[left],  array[max])) {max = left;  heap_comp[numb]++;}
    if (right < size && compare(array[right], array[max])) {max = right; heap_comp[numb]++;}

    if (max != index) {
        swap(array + index, array + max);
        heap_swap[numb]++;
        heapify(array, max, size, numb);
    }
}

void heap_sort(long long *array, int size, int numb) {
    for (int i = size / 2 - 1; i >= 0; --i) heapify(array, i, size, numb);
    for (int i = size - 1; i > 0; --i) {
        swap(array, array + i);
        heapify(array, 0, i, numb);
    }
}
