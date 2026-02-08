#include <stdio.h>

/* -------------------------------------------------
 * Pure C reference implementation
 * ------------------------------------------------- */
int c_strlen(char *p)
{
    int length = 0;

    while (*p != 0) {
        length++;
        p++;
    }

    return length;
}

/* -------------------------------------------------
 * C + inline ASM implementation (FIXED)
 * ------------------------------------------------- */
int c_asm_strlen(char *p)
{
    int len;

    __asm {

        mov ecx, 0 // contador
        mov ebx, p // puntero p

        mientras:
            cmp byte ptr [ebx], 0
            je fin_mientras
            inc ecx
            inc ebx
            jmp mientras

        fin_mientras:
            mov len, ecx

    }

    return len;
}

/* -------------------------------------------------
 * Fully assembly implementation (naked) (FIXED)
 * ------------------------------------------------- */
__declspec(naked) int asm_strlen(char *p)
{
    __asm {
        // Prologo
        push ebp
        mov ebp, esp

        // Main
        mov ecx, 0 // Contador
        mov ebx, [ebp+8]     // Puntero p

        mientras:
            cmp byte ptr [ebx], 0
            je fin_mientras
            inc ecx
            inc ebx
            jmp mientras

        fin_mientras:
            mov eax, ecx // Mover a eax el resultado final

            // Epilogo
            mov esp, ebp
            pop ebp

            ret
    }
}

/* -------------------------------------------------
 * Test helper
 * ------------------------------------------------- */
void run_test(const char *impl_name,
              int (*func)(char *),
              char *str,
              int test_id)
{
    int ref = c_strlen(str);
    int res = func(str);

    printf("Test %d [%s]: %s (string=\"%s\")\n",
           test_id,
           impl_name,
           (ref == res) ? "PASS" : "FAIL",
           str);
}

/* -------------------------------------------------
 * Main
 * ------------------------------------------------- */
int main(void)
{
    char *str1 = "Hello, World!";
    char *str2 = "";
    char *str3 = "OpenAI";

    printf("=== Testing c_asm_strlen ===\n");
    run_test("c_asm_strlen", c_asm_strlen, str1, 1);
    run_test("c_asm_strlen", c_asm_strlen, str2, 2);
    run_test("c_asm_strlen", c_asm_strlen, str3, 3);

    printf("\n=== Testing asm_strlen ===\n");
    run_test("asm_strlen", asm_strlen, str1, 1);
    run_test("asm_strlen", asm_strlen, str2, 2);
    run_test("asm_strlen", asm_strlen, str3, 3);

    return 0;
}
