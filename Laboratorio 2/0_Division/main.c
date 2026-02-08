#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* -------------------------------------------------
 * Pure C reference implementation
 * ------------------------------------------------- */
int c_divide(int a, int b){
    int result = a / b;
    return result;
}

/* -------------------------------------------------
 * C + inline ASM version
 * ------------------------------------------------- */
int c_asm_divide(int a, int b)
{
    int result;   // Local variable: stored on the stack

    __asm {
        ; Load the first parameter 'a' into EAX
        mov eax, a

        ; Sign-extend EAX into EDX:EAX
        cdq

        ; Perform signed division
        idiv b

        ; Store the quotient in the local variable
        mov result, eax
    }

    return result;
}

/* -------------------------------------------------
 * Fully assembly version (naked function)
 * ------------------------------------------------- */
__declspec(naked) int asm_divide(int a, int b)
{
    __asm {
        ; Prologue
        push ebp
        mov  ebp, esp
        sub  esp, 4              ; int result (local variable)

        ; result = a / b
        mov  eax, [ebp+8]        ; a
        cdq
        idiv dword ptr [ebp+12]  ; b
        mov  [ebp-4], eax        ; result

        ; return result
        mov  eax, [ebp-4]

        ; Epilogue
        mov  esp, ebp
        pop  ebp
        ret
    }
}

/* Helper function to run one test */
void run_test(const char* impl_name,
              int (*func)(int, int),
              int a, int b,
              int test_id)
{
    int ref = c_divide(a, b);
    int res = func(a, b);

    printf("Test %d [%s]: %s (a=%d, b=%d)\n",
           test_id,
           impl_name,
           (ref == res) ? "PASS" : "FAIL",
           a, b);
}

int main(void)
{
    printf("=== Testing c_asm_divide ===\n");
    run_test("c_asm_divide", c_asm_divide, 10,  2, 1);
    run_test("c_asm_divide", c_asm_divide, 15,  1, 2);
    run_test("c_asm_divide", c_asm_divide,  0,  5, 3);
    run_test("c_asm_divide", c_asm_divide, -10, 2, 4);
    run_test("c_asm_divide", c_asm_divide, 10, -2, 5);
    run_test("c_asm_divide", c_asm_divide, -10,-2, 6);
    run_test("c_asm_divide", c_asm_divide,  0, -3, 7);
    run_test("c_asm_divide", c_asm_divide, INT_MAX, 1, 8);

    printf("\n=== Testing asm_divide ===\n");
    run_test("asm_divide", asm_divide, 10,  2, 1);
    run_test("asm_divide", asm_divide, 15,  1, 2);
    run_test("asm_divide", asm_divide,  0,  5, 3);
    run_test("asm_divide", asm_divide, -10, 2, 4);
    run_test("asm_divide", asm_divide, 10, -2, 5);
    run_test("asm_divide", asm_divide, -10,-2, 6);
    run_test("asm_divide", asm_divide,  0, -3, 7);
    run_test("asm_divide", asm_divide, INT_MAX, 1, 8);

    return 0;
}
