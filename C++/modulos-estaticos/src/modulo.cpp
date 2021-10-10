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
