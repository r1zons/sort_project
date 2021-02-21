#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define RANDOM_LIMIT 100


/*
    TO DO

    - Дополнительный вывод
    - Пояснительные комментарии
*/

// построение массивов - случайный - неубывающий - невозрастающий
void random_array_generation(long long *array, int size);
void increasing_array_generation(long long *array, int size);
void decreasing_array_generation(long long *array, int size);

// проверка отсортированности массива
// производится по неубыванию
int is_sorted(long long *array, int size);

// компаратор
long long compare(long long a, long long b);

void swap(long long *a, long long *b);

// сортировки
void selection_sort(long long *array, int size, long long *swap_counter, long long *comp_counter);
void heapify(long long *array, int index, int size, long long *swap_counter, long long *comp_counter);
void heap_sort(long long *array, int size, long long *swap_counter, long long *comp_counter);

// доп функция для случайного числа
long long random_module(void);

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int n; scanf("%d", &n);
    
    long long select_comp[4] = {0};
    long long select_swap[4] = {0};
    long long heap_comp[4] = {0};
    long long heap_swap[4] = {0};

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
    selection_sort(select_test1, n, select_swap, select_comp);
    select_stop[0]  = clock();

    select_start[1] = clock();
    selection_sort(select_test1, n, select_swap + 1, select_comp + 1);
    select_stop[1]  = clock();

    select_start[2] = clock();
    selection_sort(select_test1, n, select_swap + 2, select_comp + 2);
    select_stop[2]  = clock();

    select_start[3] = clock();
    selection_sort(select_test1, n, select_swap + 3, select_comp + 3);
    select_stop[3]  = clock();

    heap_start[0] = clock();
    heap_sort(heap_test1, n, heap_swap, heap_comp);
    heap_stop[0]  = clock();

    heap_start[1] = clock();
    heap_sort(heap_test1, n, heap_swap + 1, heap_comp + 1);
    heap_stop[1]  = clock();

    heap_start[2] = clock();
    heap_sort(heap_test1, n, heap_swap + 2, heap_comp + 2);
    heap_stop[2]  = clock();

    heap_start[3] = clock();
    heap_sort(heap_test1, n, heap_swap + 3, heap_comp + 3);
    heap_stop[3]  = clock();



    clock_t program_stop = clock();

    printf("TEST #      Time (sec)          Comparisons                     Swap\n");
    
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", i + 1);

        printf("Selection : %10.4Lf     %16lld         %16lld\n", 
            (long double)(select_stop[i] - select_start[i])/CLOCKS_PER_SEC, select_comp[i], select_swap[i]);
        
        printf("Heap      : %10.4Lf     %16lld         %16lld\n", 
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
    if (abs(a) > abs(b)) return 1;
    else return 0;
}

int is_sorted(long long *array, int size) { 
    for (int i = 1; i < size; ++i) {
        if (compare(array[i - 1], array[i]))
            return 0;
    }
    return 1;
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

void selection_sort(long long *array, int size, long long *swap_counter, long long *comp_counter) { 
    for (int i = 0; i < size - 1; ++i) {
        long long min = i;
        for (int j = i + 1; j < size; ++j) {
            if (compare(array[min], array[j])) {
                min = j;
                (*comp_counter)++;
            }
        }
        if (min != i) {
            swap(array + i, array + min);
            (*swap_counter)++;
        }
    }
}

void heapify(long long *array, int index, int size, long long *swap_counter, long long *comp_counter) { 
    int max = index;
    int left  = 2 * index + 1;
    int right = 2 * index + 2;

    if (left  < size && compare(array[left],  array[max])) {max = left,  (*comp_counter)++;}
    if (right < size && compare(array[right], array[max])) {max = right, (*comp_counter)++;}

    if (max != index) {
        swap(array + index, array + max);
        (*swap_counter)++;
        heapify(array, max, size, swap_counter, comp_counter);
    }
}

void heap_sort(long long *array, int size, long long *swap_counter, long long *comp_counter) { 
    for (int i = size / 2 - 1; i >= 0; --i) heapify(array, i, size, swap_counter, comp_counter);
    for (int i = size - 1; i > 0; --i) { 
        swap(array, array + i);
        heapify(array, 0, i, swap_counter, comp_counter);
    }
}