#include <stdio.h>

/* -------------------------------------------------
 * Pure C reference implementation
 * ------------------------------------------------- */
short c_max(short x, short y)
{
    short max;

    if (x > y) {
        max = x;
    } else {
        max = y;
    }

    return max;
}

/* -------------------------------------------------
 * C + inline ASM implementation
 * ------------------------------------------------- */
short c_asm_max(short x, short y)
{
    short max;

    __asm {

        mov ax, x ; ax = x
        cmp ax, y ; ax - y

        // si ax es menor o igual al else
        jle menor_igual
            mov max, ax
            jmp fin

        menor_igual:
            mov ax, y
            mov max, ax

        fin: 

    }

    return max;
}

/* -------------------------------------------------
 * Fully assembly implementation (naked)
 * ------------------------------------------------- */
__declspec(naked) short asm_max(short x, short y)
{
    __asm {

        // prologo
        push ebp
        mov ebp, esp 

        // x en [ebp+8], y en [ebp+12]
        mov ax, [ebp+8] ; ax = x
        cmp ax, [ebp+12] ; ax - y

        // si ax es menor o igual salto

        jle menor_igual
            jmp fin

        menor_igual:
            mov ax, [ebp+12]

        fin:
            // epilogo
            mov esp, ebp
            pop ebp

            ret
        
    }
}

/* -------------------------------------------------
 * Test helper
 * ------------------------------------------------- */
void run_test(const char *impl_name,
              short (*func)(short, short),
              short x, short y,
              int test_id)
{
    short ref = c_max(x, y);
    short res = func(x, y);

    printf("Test %d [%s]: %s (x=%d, y=%d)\n",
           test_id,
           impl_name,
           (ref == res) ? "PASS" : "FAIL",
           x, y);
}

/* -------------------------------------------------
 * Main
 * ------------------------------------------------- */
int main(void)
{
    printf("=== Testing c_asm_max ===\n");
    run_test("c_asm_max", c_asm_max, 10,   20,   1);
    run_test("c_asm_max", c_asm_max, -5,   -10,  2);
    run_test("c_asm_max", c_asm_max, 30,   30,   3);
    run_test("c_asm_max", c_asm_max, 0,    15,   4);
    run_test("c_asm_max", c_asm_max, 100,  50,   5);

    printf("\n=== Testing asm_max ===\n");
    run_test("asm_max", asm_max, 10,   20,   1);
    run_test("asm_max", asm_max, -5,   -10,  2);
    run_test("asm_max", asm_max, 30,   30,   3);
    run_test("asm_max", asm_max, 0,    15,   4);
    run_test("asm_max", asm_max, 100,  50,   5);

    return 0;
}
