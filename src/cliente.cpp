#include <iostream>
#include <fstream>
#include <iomanip>
#include "cliente.h"
#include "utilidades.h"
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>

void registrarCliente()
{
    Cliente nuevoCliente;

    std::cout << "Ingrese el nombre del cliente: ";
    std::getline(std::cin >> std::ws, nuevoCliente.nombre);

    std::cout << "Ingrese el apellido del cliente: ";
    std::getline(std::cin >> std::ws, nuevoCliente.apellido);

    std::cout << "Ingrese el teléfono del cliente: ";
    std::getline(std::cin, nuevoCliente.telefono);

    std::ofstream archivo("data/clientes.txt", std::ios::app);
    if (!archivo)
    {
        std::cerr << "Error al abrir el archivo clientes.txt\n";
        return;
    }

    archivo << nuevoCliente.nombre << "," << nuevoCliente.apellido << "," << nuevoCliente.telefono << "\n";
    archivo.close();

    std::cout << "Cliente registrado correctamente.\n";
}

void mostrarClientes()
{
    std::ifstream archivo("data/clientes.txt");
    if (!archivo)
    {
        std::cerr << "Error al abrir el archivo clientes.txt\n";
        return;
    }
    std::string nombre, telefono;

    int anchoConsola = 80;

    imprimirCentrado("Clientes Registrados", anchoConsola);
    std::cout << std::string(anchoConsola, '-') << "\n";

    std::cout << std::left << std::setw(20) << "Nombre" << std::setw(20) << "Telefono" << "\n";
    std::cout << std::string(40, '-') << "\n";

    while (std::getline(archivo, nombre, ',') && std::getline(archivo, telefono))
    {
        std::cout << std::left << std::setw(20) << nombre << std::setw(20) << telefono << "\n";
    }
    archivo.close();
}

void editarCliente(const std::string& nombreCliente)
{
    std::ifstream archivo("data/clientes.txt");
    std::vector<std::string> clientes;
    std::string linea;
    bool encontrado = false;

       while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string nombre, telefono;
        float tarifa;

        if (std::getline(iss, nombre, ',') &&
            std::getline(iss, telefono, ',') &&
            (iss >> tarifa)) {
            
            if (nombre ==  nombre) {
                encontrado = true;
                std::cout << "Cliente Encontrado. Datos Actuales:" << std::endl;
                std::cout << "Nombre Cliente: " << nombre << std::endl;
                std::cout << "Telefono: " << telefono << std::endl;

                std::cout << "Ingrese la correccion del nombre: ";
                std::getline(std::cin >> std::ws, nombre);

                std::cout << "Ingrese el nuevo numero de telefono: ";
                std::getline(std::cin >> std::ws, telefono);

                std::ostringstream oss;
                oss << nombre << "," << telefono;
                clientes.push_back(oss.str());
            } else {
                clientes.push_back(linea);
            }
        }
    }

    archivo.close();

    if (encontrado) {
        std::ofstream archivoSalida("data/clientes.txt");
        for (const auto& cliente : clientes) {
            archivoSalida << cliente << std::endl;
        }
        archivoSalida.close();
        std::cout << "Cliente actualizado correctamente." << std::endl;
    } else {
        std::cout << "No se encontró cliente con el nombre: " << std::endl;
    }
}

void buscarCliente(const std::string& criterio) {
    std::ifstream archivo("data/clientes.txt");
    std::string linea;
    bool encontrado = false;

    if (!archivo) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return;
    }

    while (std::getline(archivo, linea) && !encontrado) {
        std::istringstream iss(linea);
        std::string nombre, telefono;
        
        if (std::getline(iss, nombre, ',') && std::getline(iss, telefono)) {
            std::string lineaLower = nombre + telefono;
            std::transform(lineaLower.begin(), lineaLower.end(), lineaLower.begin(), ::tolower);
            std::string criterioLower = criterio;
            std::transform(criterioLower.begin(), criterioLower.end(), criterioLower.begin(), ::tolower);

            if (lineaLower.find(criterioLower) != std::string::npos) {
                encontrado = true;
                std::cout << "\nCliente encontrado:" << std::endl;
                std::cout << "Nombre: " << nombre << std::endl;
                std::cout << "Teléfono: " << telefono << std::endl;
            }
        }
    }
    
    if (!encontrado) {
        std::cout << "No se encontró ningún cliente que coincida con el criterio de búsqueda." << std::endl;
    }
    
    archivo.close();
}
