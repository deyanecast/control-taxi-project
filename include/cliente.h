#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

struct Cliente {
    std::string nombre;
    std::string telefono;
};

void registrarCliente();
void mostrarClientes();
void generarHTMLClientes();
void editarCliente(const std::string& nombreCliente);


#endif
