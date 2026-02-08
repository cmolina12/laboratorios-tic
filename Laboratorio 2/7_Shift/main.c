#include <stdio.h>

/* -------------------------------------------------
 * Pure C reference implementation
 * ------------------------------------------------- */
void c_vector_shift_left(unsigned char *vec, int size)
{
    /*
     * IMPORTANT FOR STUDENTS:
     * - Each element is an unsigned char (8 bits)
     * - Left shifting by 1 moves all bits to the left
     * - The most significant bit is discarded
     * - A zero enters on the right
     */
    for (int i = 0; i < size; i++) {
        vec[i] <<= 1;
    }
}

/* -------------------------------------------------
 * C + inline ASM implementation
 * ------------------------------------------------- */
void c_asm_vector_shift_left(unsigned char *v, int s)
{
    __asm {
        mov edx, v // vector
        mov ecx, s // size
        mov ebx, 0 // contador i

        bucle:
            cmp ebx, ecx
            jge fin_bucle
            shl byte ptr [edx], 1

            inc ebx
            inc edx
            jmp bucle

        fin_bucle:

    }
}

/* -------------------------------------------------
 * Fully assembly implementation (naked)
 * ------------------------------------------------- */
__declspec(naked) void asm_vector_shift_left(unsigned char *v, int s)
{
    __asm {

        // prologo
        push ebp
        mov ebp, esp

        // main
        mov edx, [ebp+8] // vector
        mov ecx, [ebp+12] // size
        mov ebx, 0 // contador i

        bucle:
            cmp ebx, ecx
            jge fin_bucle
            shl byte ptr [edx], 1

            inc ebx
            inc edx
            jmp bucle

        fin_bucle:
            // epilogo
            pop ebx
            mov esp, ebp
            pop ebp
            ret

    }
}

/* -------------------------------------------------
 * Helper functions (unchanged)
 * ------------------------------------------------- */
void print_vector(unsigned char *vec, int size)
{
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("0x%02X", vec[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]");
}

int validate_vectors(unsigned char *vec1, unsigned char *vec2, int size)
{
    for (int i = 0; i < size; i++) {
        if (vec1[i] != vec2[i]) {
            return 0;
        }
    }
    return 1;
}

/* -------------------------------------------------
 * Main (unchanged logic)
 * ------------------------------------------------- */
int main(void)
{
    unsigned char vec1[] = {0x12, 0x34, 0x56};
    unsigned char vec2[] = {0xFF, 0x80, 0x7F};
    unsigned char vec3[] = {0x01, 0x02, 0x04};

    unsigned char vec1_c[]   = {0x12, 0x34, 0x56};
    unsigned char vec2_c[]   = {0xFF, 0x80, 0x7F};
    unsigned char vec3_c[]   = {0x01, 0x02, 0x04};

    unsigned char vec1_asm[] = {0x12, 0x34, 0x56};
    unsigned char vec2_asm[] = {0xFF, 0x80, 0x7F};
    unsigned char vec3_asm[] = {0x01, 0x02, 0x04};

    c_vector_shift_left(vec1_c, 3);
    c_vector_shift_left(vec2_c, 3);
    c_vector_shift_left(vec3_c, 3);

    asm_vector_shift_left(vec1_asm, 3);
    asm_vector_shift_left(vec2_asm, 3);
    asm_vector_shift_left(vec3_asm, 3);

    printf("Test 1 - C vs ASM Shift (vec1): ");
    print_vector(vec1_c, 3);
    printf(" vs ");
    print_vector(vec1_asm, 3);
    printf(" -> %s\n", validate_vectors(vec1_c, vec1_asm, 3) ? "PASS" : "FAIL");

    printf("Test 2 - C vs ASM Shift (vec2): ");
    print_vector(vec2_c, 3);
    printf(" vs ");
    print_vector(vec2_asm, 3);
    printf(" -> %s\n", validate_vectors(vec2_c, vec2_asm, 3) ? "PASS" : "FAIL");

    printf("Test 3 - C vs ASM Shift (vec3): ");
    print_vector(vec3_c, 3);
    printf(" vs ");
    print_vector(vec3_asm, 3);
    printf(" -> %s\n", validate_vectors(vec3_c, vec3_asm, 3) ? "PASS" : "FAIL");

    return 0;
}
