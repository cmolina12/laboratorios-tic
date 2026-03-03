#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // para sleep

// .data → Variables globales inicializadas
int g_initialized = 42;

// .bss → Variables globales no inicializadas
int g_uninitialized;

// .rodata → Cadena de solo lectura
const char *g_message = "Hello, sections!\n";

int main() {
    // .stack → Variable local
    int local_var = 7;

    // .heap → Memoria dinámica
    int *heap_var = (int *)malloc(sizeof(int));
    if (heap_var == NULL) {
        return 1;
    }
    *heap_var = 99;

    // Uso de variables
    printf("%s", g_message);
    printf("Initialized global: %d\n", g_initialized);
    printf("Uninitialized global: %d\n", g_uninitialized);
    printf("Local variable: %d\n", local_var);
    printf("Heap variable: %d\n", *heap_var);

    free(heap_var);

    return 0;
}
