#include <stdio.h>

/* -------------------------------------------------
 * C reference implementation (baseline)
 * ------------------------------------------------- */
short* c_pointer_increment(short *a)
{
    short *p = a;

    /*
     * IMPORTANT FOR STUDENTS:
     * Adding 1 to a pointer is NOT the same as adding 1 to an integer.
     *
     * p + 1 means:
     *   "move to the next element of the type pointed to by p"
     *
     * Since p is a short*, and sizeof(short) = 2 bytes,
     * the address is increased by 2 bytes, not by 1.
     */
    short *w = p + 1;
    return w;
}

/* -------------------------------------------------
 * C + inline ASM implementation
 * ------------------------------------------------- */
short* c_asm_pointer_increment(short *a)
{
    short *p;
    short *w;

    __asm {

        // parametro: puntero a
        // variable local 1: puntero p (en realidad sobra)
        // variable local 2: puntero w

        mov eax, a // Cargar la direccion de a en eax
        add eax, 2 // Cada short son dos bytes, para movernos en una posicion, entonces agregamos dos bytes
        mov w, eax // La direccion de memoria en eax ira directamente a la variable w

    }

    return w;
}

/* -------------------------------------------------
 * ASM-only implementation
 * ------------------------------------------------- */
__declspec(naked) short* asm_pointer_increment(short *a)
{
    __asm {

        // prologo
        push ebp
        mov ebp, esp

        
        mov eax, [ebp+8] // parametro a esta en [ebp+8], movemos la direccion a eax
        add eax, 2 // Le agregamos dos bytes a la direccion en eax

        // epilogo
        mov esp, ebp
        pop ebp
        ret
    }
}

/* -------------------------------------------------
 * Main: validation and standardized output
 * ------------------------------------------------- */
int main(void)
{
    short x = 1;
    short *a = &x;

    short *w_c    = c_pointer_increment(a);
    short *w_casm = c_asm_pointer_increment(a);
    short *w_asm  = asm_pointer_increment(a);

    

    /* -------------------------------------------------
     * Test 1: C vs C+ASM
     * ------------------------------------------------- */
    printf("\n=== Testing c_asm_pointer_increment ===\n");
    printf(
        "Test 1 [c_asm_pointer_increment]: %s (p=%p, w=%p)\n",
        (w_c == w_casm) ? "PASS" : "FAIL",
        (void*)a,
        (void*)w_casm
    );

    /* -------------------------------------------------
     * Test 2: C vs ASM
     * ------------------------------------------------- */
    printf("\n=== Testing asm_pointer_increment ===\n");
    printf(
        "Test 2 [asm_pointer_increment]: %s (p=%p, w=%p)\n",
        (w_c == w_asm) ? "PASS" : "FAIL",
        (void*)a,
        (void*)w_asm
    );

    return 0;
}

