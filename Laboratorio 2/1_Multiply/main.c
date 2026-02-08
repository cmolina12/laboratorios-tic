#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* -------------------------------------------------
 * Pure C reference implementation
 * ------------------------------------------------- */
int c_multiply(int a, int b)
{
    int result = a * b;
    return result;
}

/* -------------------------------------------------
 * C + inline ASM version
 * ------------------------------------------------- */
int c_asm_multiply(int a, int b)
{
    int result;   // Local variable stored on the stack

    __asm {
        mov eax, a
        imul eax, b
        mov result, eax
    }

    return result;
}

/* -------------------------------------------------
 * Fully assembly version (naked function)
 * ------------------------------------------------- */
__declspec(naked) int asm_multiply(int a, int b)
{
    __asm {
        push ebp
        mov ebp, esp

        mov eax, [ebp+8]    // a
        imul eax, [ebp+12]  // b (el resultado ya queda en EAX)

        pop ebp             // Restauramos ebp
        ret                 // Retornamos (EAX ya tiene el resultado)
    }
}

/* -------------------------------------------------
 * Test helper
 * ------------------------------------------------- */
void run_test(const char* impl_name,
              int (*func)(int, int),
              int a, int b,
              int test_id)
{
    int ref = c_multiply(a, b);
    int res = func(a, b);

    printf("Test %d [%s]: %s (a=%d, b=%d)\n",
           test_id,
           impl_name,
           (ref == res) ? "PASS" : "FAIL",
           a, b);
}

/* -------------------------------------------------
 * Main
 * ------------------------------------------------- */
int main(void)
{
    printf("=== Testing c_asm_multiply ===\n");
    run_test("c_asm_multiply", c_asm_multiply, 10,  2, 1);
    run_test("c_asm_multiply", c_asm_multiply, 15,  1, 2);
    run_test("c_asm_multiply", c_asm_multiply,  0,  5, 3);
    run_test("c_asm_multiply", c_asm_multiply, -10, 2, 4);
    run_test("c_asm_multiply", c_asm_multiply, 10, -2, 5);
    run_test("c_asm_multiply", c_asm_multiply, -10,-2, 6);
    run_test("c_asm_multiply", c_asm_multiply, 10000, 20000, 7);
    run_test("c_asm_multiply", c_asm_multiply, INT_MAX, 2, 8);

    printf("\n=== Testing asm_multiply ===\n");
    run_test("asm_multiply", asm_multiply, 10,  2, 1);
    run_test("asm_multiply", asm_multiply, 15,  1, 2);
    run_test("asm_multiply", asm_multiply,  0,  5, 3);
    run_test("asm_multiply", asm_multiply, -10, 2, 4);
    run_test("asm_multiply", asm_multiply, 10, -2, 5);
    run_test("asm_multiply", asm_multiply, -10,-2, 6);
    run_test("asm_multiply", asm_multiply, 10000, 20000, 7);
    run_test("asm_multiply", asm_multiply, INT_MAX, 2, 8);

    return 0;
}
