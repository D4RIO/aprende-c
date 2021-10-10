En C++, igual que en C, la compilación se hace en varias etapas:

 - Preprocesado
 - Compilación
 - Ensamblado
 - Enlazado

La modularización se da en las etapas de **preprocesado** mediante la inclusión de cabeceras, y de **enlazado**, ya sea que el linker sea estático o dinámico, cuando se enlazan efectivamente módulos compilados por separado.

# Modularización con enlazado estático

El caso más sencillo es compilar cada módulo `*.cpp` en archivos `*.o` diferentes, y luego enlazarlos en un ejecutable. Para esto se requiere que las funciones que se usan en un módulo sean conocidas por el otro, y acá entra en juego el uso de las cabeceras para compartir declaraciones. Por ejemplo:

**modulo.hpp**
``` cpp
#ifndef _MODULO_HEADER_
#define _MODULO_HEADER_

/* Acá hay una declaración (prototipo), pero no una definición.
 * Sólo hace que la función sea conocida, pero no define
 * el código de la función (sólo promete que existirá al final).
 * El linker fallará si esto no se define en el enlazado final.
 */
extern void hola(void);

#endif
```

**modulo.cpp:**
``` cpp
#include<iostream>

/* En este caso no es necesario incluir la cabecera en el propio
 * módulo, pero como las structs y clases se declaran también en
 * la cabecera, es una práctica común. Además, el compilador te
 * puede advertir si tenés diferencias entre cabecera y fuente.
 */
#include "modulo.hpp"

/* Definición de la función */
void hola(void) {
  std::cout << "Hola" << std::endl;
}
```

**main.cpp**
``` cpp
#include "modulo.hpp"

int main(void) {
  hola ();
  return 0;
}
```

Como la directiva `#include` funciona copiando un archivo dentro de otro, y `modulo.hpp` es incluído en `modulo.cpp` y en `main.cpp`, entonces hay dos archivos reales a compilar. Por conveniencia, en este repositorio se incluye el código del ejemplo:

``` bash
g++ -Wall -c main.cpp              # preprocesa, compila y ensambla a main.o
g++ -Wall -c modulo.cpp            # preprocesa, compila y ensambla a modulo.o
g++ -o ejecutable modulo.o main.o  # enlaza y crea un ejecutable
```
