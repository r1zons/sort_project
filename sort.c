#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/*
    TO DO

    - Heap Sort
    - Дополнительный вывод
    - Пояснительные комментарии
*/

// построение массивов - случайный - неубывающий - невозрастающий
void random_array_generation(long long *array, int size);
void increasing_array_generation(long long *array, int size);
void decreasion_array_generation(long long *array, int size);

// проверка отсортированности массива
// производится по неубыванию
int is_sorted(long long *array, int size);

// компаратор
long long compare(long long a, long long b);

void swap(long long *a, long long *b);

// сортировки
void selection_sort(long long *array, int size);

void heapify(long long *array, int index);
void heap_sort(long long *array, int size);


// сделать srand(time(NULL))
// rand() * rand() * rand() * rand() * rand()

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int n; scanf("%d", &n);

    long long *select_test1 = calloc(n, sizeof(long long));
    long long *select_test2 = calloc(n, sizeof(long long));
    long long *select_test3 = calloc(n, sizeof(long long));
    long long *select_test4 = calloc(n, sizeof(long long));

    increasing_array_generation(select_test1, n);
    decreasion_array_generation(select_test2, n);
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

    // random_array_generation(a, n);
    // increasing_array_generation(a, n);
    // decreasion_array_generation(a, n);

    // for (int i = 0; i < n; ++i) { 
    //     printf("%lld ", a[i]);
    // }

    selection_sort(select_test1, n);
    selection_sort(select_test2, n);
    selection_sort(select_test3, n);
    selection_sort(select_test4, n);

    // printf("%d %d %d %d", is_sorted(select_test1, n), is_sorted(select_test2, n), 
    //                       is_sorted(select_test3, n), is_sorted(select_test4, n));
    
    return 0;

}

void swap(long long *a, long long *b) { 
    long long t = *a;
    *a = *b;
    *b = t;
}

long long compare(long long a, long long b) { 
    if (abs(a) >= abs(b)) return 1;
    else return 0;
}

int is_sorted(long long *array, int size) { 
    for (int i = 1; i < size; ++i) {
        if (!(compare(array[i], array[i - 1])))
            return 0;
    }
    return 1;
}

void random_array_generation(long long *array, int size) { 
    for (int i = 0; i < size; ++i) {
        array[i] = rand() * (rand()&1 ? -1 : 1); // есть возможность поставить rand^4
    }
}

void increasing_array_generation(long long *array, int size) { 
    long long first = 0;
    for (int i = 0; i < size; ++i) { 
        array[i] = first;
        if (rand()&1) first++;
    }
}

void decreasion_array_generation(long long *array, int size) { 
    long long first = LLONG_MAX;
    for (int i = 0; i < size; ++i) { 
        array[i] = first;
        if (rand()&1) first--;
    }
}

void selection_sort(long long *array, int size) { 
    for (int i = 0; i < size - 1; ++i) {
        long long min = i;
        for (int j = i + 1; j < size; ++j) {
            if (compare(array[min], array[j])) {
                min = j;
            }
        }
        if (min != i) swap(array + i, array + min);
    }
}

void heapify(long long *array, int index) { 
    
}

void heap_sort(long long *array, int size) { 

}