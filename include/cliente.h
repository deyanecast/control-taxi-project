#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

struct Cliente {
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string email;
    std::string direccion;
};

void registrarCliente();
void mostrarClientes();
void editarCliente(const std::string& nombre);
void eliminarCliente(const std::string& nombre);
void generarHTMLClientes();
void buscarCliente(const std::string& criterio);

#endif // CLIENTE_H
