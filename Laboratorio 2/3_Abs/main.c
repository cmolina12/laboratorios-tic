#include <stdio.h>

/* -------------------------------------------------
 * Pure C reference implementation
 * ------------------------------------------------- */
int c_absolute(int x)
{
    if (x < 0) {
        x = -x;
    }
    return x;
}

/* -------------------------------------------------
 * C + inline ASM implementation
 * ------------------------------------------------- */
int c_asm_absolute(int x)
{
    int result;

    __asm {

        mov eax, x ; eax = x
        cmp eax, 0 ; eax - 0

        // si 0 es mayor podemos entrar en el if, entonces saltamos al fin del if si mayor igual

        jge fin_if ; if eax >= 0 jump fin_if

            neg eax ; eax = -eax

        fin_if:

        mov result, eax ; result = eax

    }

    return result;
}

/* -------------------------------------------------
 * Fully assembly implementation (naked)
 * ------------------------------------------------- */
__declspec(naked) int asm_absolute(int x)
{
    __asm {
        ; Prologue
        push ebp
        mov ebp, esp

        ; Program

        // x esta en [ebp+8]

        mov eax, [ebp+8] ; eax = x
        cmp eax, 0 ; eax - 0

        jge fin_if ; if eax >= 0 jump fin_if

            neg eax

        fin_if:
            ; Epilogue
            mov esp, ebp
            pop ebp
            ret
    }
}

/* -------------------------------------------------
 * Test helper
 * ------------------------------------------------- */
void run_test(const char *impl_name,
              int (*func)(int),
              int x,
              int test_id)
{
    int ref = c_absolute(x);
    int res = func(x);

    printf("Test %d [%s]: %s (x=%d)\n",
           test_id,
           impl_name,
           (ref == res) ? "PASS" : "FAIL",
           x);
}

/* -------------------------------------------------
 * Main
 * ------------------------------------------------- */
int main(void)
{
    printf("=== Testing c_asm_absolute ===\n");
    run_test("c_asm_absolute", c_asm_absolute, 0,     1);
    run_test("c_asm_absolute", c_asm_absolute, 10,    2);
    run_test("c_asm_absolute", c_asm_absolute, -10,   3);
    run_test("c_asm_absolute", c_asm_absolute, -1000, 4);
    run_test("c_asm_absolute", c_asm_absolute, 1000,  5);

    printf("\n=== Testing asm_absolute ===\n");
    run_test("asm_absolute", asm_absolute, 0,     1);
    run_test("asm_absolute", asm_absolute, 10,    2);
    run_test("asm_absolute", asm_absolute, -10,   3);
    run_test("asm_absolute", asm_absolute, -1000, 4);
    run_test("asm_absolute", asm_absolute, 1000,  5);

    return 0;
}
