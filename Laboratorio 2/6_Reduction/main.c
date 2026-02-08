#include <stdio.h>

/* -------------------------------------------------
 * Pure C reference implementation
 * ------------------------------------------------- */
unsigned char c_vector_multiply(unsigned char *vec, int size)
{
    unsigned char product = 1;

    /*
     * IMPORTANT FOR STUDENTS:
     * - Each element is an unsigned char (1 byte)
     * - The multiplication is done element by element
     * - The final result is stored back into an unsigned char
     */
    for (int i = 0; i < size; i++) {
        product *= vec[i];
    }

    return product;
}

/* -------------------------------------------------
 * C + inline ASM implementation
 * ------------------------------------------------- */
unsigned char c_asm_vector_multiply(unsigned char *v, int s)
{
    unsigned char product;

    __asm {

        // Inicializar producto en 1
        mov al, 1
        // Inicializar size
        mov ecx, s 
        // Inicializar el puntero v
        mov edx, v
        // i
        mov ebx, 0
        bucle:
            cmp ebx, ecx
            // si i = size, chao
            je fin_bucle

            mul byte ptr [edx]

            inc edx
            inc ebx
            jmp bucle

        fin_bucle:
            mov product, al
    
    }

    return product;
}

/* -------------------------------------------------
 * Fully assembly implementation (naked)
 * ------------------------------------------------- */
__declspec(naked) unsigned char asm_vector_multiply(unsigned char *v, int s)
{
    __asm {

        // Prologo
        push ebp
        mov ebp, esp

        // puntero v en [ebp+8], s en [ebp+12]

        mov al, 1 // product
        mov ecx, [ebp+12] // size
        mov edx, [ebp+8] // puntero v
        mov ebx, 0 // i

        bucle:
            cmp ebx, ecx
            je fin_bucle

            mul byte ptr [edx] // multiplica el valor de v con product (al), resultado en ax

            inc edx
            inc ebx
            jmp bucle
        
        fin_bucle:
            // el resultado ya esta en ax, no hay que hacer nada

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
              unsigned char (*func)(unsigned char *, int),
              unsigned char *vec,
              int size,
              int test_id)
{
    unsigned char ref = c_vector_multiply(vec, size);
    unsigned char res = func(vec, size);

    printf("Test %d [%s]: %s (expected: %u, got: %u)\n",
           test_id,
           impl_name,
           (ref == res) ? "PASS" : "FAIL",
           ref,
           res);
}

/* -------------------------------------------------
 * Main
 * ------------------------------------------------- */
int main(void)
{
    unsigned char vec1[] = {2, 3, 4};      // 2*3*4 = 24
    unsigned char vec2[] = {1, 5, 2};      // 1*5*2 = 10
    unsigned char vec3[] = {0, 3, 4};      // 0*3*4 = 0
    unsigned char vec4[] = {7, 8};         // 7*8 = 56

    printf("=== Testing c_asm_vector_multiply ===\n");
    run_test("c_asm_vector_multiply", c_asm_vector_multiply, vec1, 3, 1);
    run_test("c_asm_vector_multiply", c_asm_vector_multiply, vec2, 3, 2);
    run_test("c_asm_vector_multiply", c_asm_vector_multiply, vec3, 3, 3);
    run_test("c_asm_vector_multiply", c_asm_vector_multiply, vec4, 2, 4);

    printf("\n=== Testing asm_vector_multiply ===\n");
    run_test("asm_vector_multiply", asm_vector_multiply, vec1, 3, 1);
    run_test("asm_vector_multiply", asm_vector_multiply, vec2, 3, 2);
    run_test("asm_vector_multiply", asm_vector_multiply, vec3, 3, 3);
    run_test("asm_vector_multiply", asm_vector_multiply, vec4, 2, 4);

    return 0;
}