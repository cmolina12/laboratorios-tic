# Taller – Lenguaje Ensamblador (IA-32)

## Objetivo del taller

El objetivo de este taller es **aprender a traducir código C a ensamblador IA-32**, utilizando:

* **C puro** (versión de referencia)
* **C + ensamblador en línea (`c_asm_…`)**
* **Funciones completamente en ensamblador (`asm_…`)**

A lo largo de los ejercicios se refuerzan conceptos como:

* Uso de registros
* Operaciones aritméticas
* Estructuras de control
* Manejo de punteros

---

## Comando de compilación (OBLIGATORIO)

⚠️ **Todos los ejercicios deben compilarse usando exactamente este comando**:

```bash
clang -m32 -masm=intel -fms-extensions -O0 -fno-pic \
      -fno-unwind-tables -fno-asynchronous-unwind-tables \
      -fno-omit-frame-pointer -fno-stack-protector main.c -o main
```

## Comando de ejecución (OBLIGATORIO)

⚠️ **Todos los ejercicios deben ejercutarse usando exactamente este comando**:

```bash
./main
```

### ¿Qué hace este comando?

* `-m32`: fuerza compilación a 32 bits
* `-masm=intel`: sintaxis Intel en ensamblador
* `-fms-extensions`: permite `__asm` estilo MSVC
* `-O0`: sin optimizaciones (clave para aprender)
* Las demás opciones evitan que el compilador modifique la pila

---

## Estructura del taller

En el archivo ZIP encontrarás **8 carpetas**, una por ejercicio:

```
0_Divide
1_Multiply
2_Pointer
3_Abs
4_Max
5_Strlen
6_Reduction
7_Shift
```

---

# Ejercicio 0 – Divide (EJEMPLO COMPLETO)

📂 **Carpeta:** `0_Divide`

Este ejercicio **ya está completamente resuelto** y sirve como **modelo** para los demás.

### Qué debes hacer

* Estudiar cuidadosamente:

  * `c_divide`
  * `c_asm_divide`
  * `asm_divide`
* Entender cómo:

  * Se accede a los parámetros
  * Se usa `idiv`
  * Se retorna un valor

👉 **No debes modificar este ejercicio.**

---

# Ejercicio 1 – Multiply

📂 **Carpeta:** `1_Multiply`

### Objetivo

Implementar la multiplicación usando ensamblador.

### Qué debes completar

Debes completar **dos funciones**:

```c
int c_asm_multiply(int a, int b)
{
    int result;

    __asm {
        // COMPLETAR AQUÍ
    }

    return result;
}
```

```c
__declspec(naked) int asm_multiply(int a, int b)
{
    __asm {
        // COMPLETAR AQUÍ
    }
}
```

### Pasos sugeridos

1. Revisa la función `c_multiply`
2. Identifica qué registros usar
3. Usa `imul`
4. Asegúrate de devolver el resultado en `EAX`

---

# Ejercicio 2 – Pointer Increment

📂 **Carpeta:** `2_Pointer`

### Objetivo

Entender **aritmética de punteros** en C y su traducción a ensamblador.

### Regla clave

```c
p + 1  ≠  p + 1 byte
p + 1  =  p + sizeof(tipo)
```

### Qué debes completar

```c
short* c_asm_pointer_increment(short *a)
{
    // COMPLETAR
}
```

```c
__declspec(naked) short* asm_pointer_increment(short *a)
{
    __asm {
        // COMPLETAR
    }
}
```

⚠️ **Recuerda:** `short` ocupa **2 bytes**

---

# Ejercicio 3 – Absolute Value (Abs)

📂 **Carpeta:** `3_Abs`

⚠️ **Este ejercicio es especial**

### Qué debes hacer

1. **Completar** la función:

```c
int c_asm_absolute(int x)
{
    // COMPLETAR
}
```

2. **Corregir** la función:

```c
__declspec(naked) int asm_absolute(int x)
{
    __asm {
        // ESTA FUNCIÓN TIENE ERRORES
        // DEBES ARREGLARLA
    }
}
```

### Pista

* Debes usar:

  * `cmp`
  * `jge`
  * `neg`

---

# Ejercicio 4 – Max

📂 **Carpeta:** `4_Max`

### Objetivo

Seleccionar el mayor de dos valores `short`.

### Qué debes completar

```c
short c_asm_max(short x, short y)
{
    // COMPLETAR
}
```

```c
__declspec(naked) short asm_max(short x, short y)
{
    __asm {
        // COMPLETAR
    }
}
```

### Pista

* Usa `cmp`
* Usa saltos condicionales (`jge`, `jl`)

---

# Ejercicio 5 – Strlen

📂 **Carpeta:** `5_Strlen`

### Objetivo

Recorrer una cadena carácter por carácter hasta encontrar `"\0"`.

### Qué debes completar

```c
int c_asm_strlen(char *p)
{
    // COMPLETAR
}
```

```c
__declspec(naked) int asm_strlen(char *p)
{
    __asm {
        // COMPLETAR
    }
}
```

### Pista

* Usa un bucle
* Accede a memoria con `byte ptr`
* Incrementa el puntero

---

# Ejercicio 6 – Reduction

📂 **Carpeta:** `6_Reduction`

### Objetivo

Trabajar con arreglos y bucles en ensamblador.

### Qué debes completar

```c
unsigned char c_asm_vector_multiply(unsigned char *v, int s)
{
    // COMPLETAR
}
```

```c
__declspec(naked) unsigned char asm_vector_multiply(unsigned char *v, int s)
{
    __asm {
        // COMPLETAR
    }
}
```

### Pista

* Usa un índice
* Recuerda que `unsigned char` ocupa 1 byte
* Usa `imul` o `mul`

---

# Ejercicio 7 – Shift (Desplazamiento de bits)

📂 **Carpeta:** `7_Shift`

---

## Objetivo

El objetivo de este ejercicio es **aprender a manipular datos a nivel de bits** utilizando ensamblador IA-32, específicamente mediante la instrucción de **desplazamiento a la izquierda (`shl`)** aplicada a los elementos de un vector.

Este ejercicio refuerza los siguientes conceptos:

* Uso de bucles en ensamblador
* Acceso a arreglos mediante punteros
* Operaciones bit a bit
* Diferencia entre operaciones aritméticas y operaciones a nivel de bits

---

## Descripción del problema

Se recibe un vector de tipo `unsigned char` y su tamaño. El programa debe recorrer el vector y **desplazar a la izquierda en 1 bit cada uno de sus elementos**.

En C, la operación que se realiza es:

```c
vec[i] <<= 1;
```

Esto implica que:

* Todos los bits se mueven una posición a la izquierda
* El bit más significativo se pierde
* Se introduce un 0 por el bit menos significativo

---

## Qué debes completar

Debes completar **dos funciones**, siguiendo exactamente el estilo de los ejercicios anteriores:

### 1. Función C + ensamblador en línea

```c
void c_asm_vector_shift_left(unsigned char *v, int s)
{
    __asm {
        // COMPLETAR AQUÍ
    }
}
```

### 2. Función completamente en ensamblador

```c
__declspec(naked) void asm_vector_shift_left(unsigned char *v, int s)
{
    __asm {
        // COMPLETAR AQUÍ
    }
}
```

⚠️ **No debes modificar ninguna otra parte del código.**

---

## Pistas importantes

* `unsigned char` ocupa **1 byte**
* Para acceder a un elemento del vector puedes usar:

  ```asm
  byte ptr [base + índice]
  ```
* Debes usar un **registro como contador del bucle**
* La instrucción de desplazamiento es:

  ```asm
  shl reg8, 1
  ```

---

## Validación

* El programa ya incluye funciones para:

  * Imprimir los vectores
  * Comparar el resultado en C y en ASM
* **Si los vectores no coinciden, el test fallará**
* Todos los tests deben mostrar `PASS`

---

## Reglas generales

* No cambies el `main`
* No cambies el comando de compilación
* Todas las validaciones ya están implementadas
* Si un test falla, tu ensamblador es incorrecto
* **El ensamblador debe producir exactamente el mismo efecto que el código C.**
* No se evalúa eficiencia, solo **corrección y comprensión del código**.

---

## Consejo final

👉 **Si tu código C funciona pero el ASM no, el error está en:**

* Registros incorrectos
* Tamaño de datos incorrecto
* Falta de prólogo/epílogo
* No devolver el resultado en `EAX`
