#include "reserva.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

void hacerReserva() {
    std::string nombreCliente, origen, destino;
    float tarifa;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Ingrese el nombre del cliente: ";
    std::getline(std::cin, nombreCliente);
    
    std::cout << "Ingrese el origen: ";
    std::getline(std::cin, origen);
    
    std::cout << "Ingrese el destino: ";
    std::getline(std::cin, destino);
    
    tarifa = calcularTarifa(origen, destino);
    
    // Guardar la reserva en el archivo
    std::ofstream archivo("data/reservas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << nombreCliente << "," << origen << "," << destino << "," << tarifa << std::endl;
        archivo.close();
        std::cout << "Reserva realizada con éxito." << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo para guardar la reserva." << std::endl;
    }
}

float calcularTarifa(const std::string& origen, const std::string& destino) {
    return 50.0;
}

void mostrarReservas() {
    std::ifstream archivo("data/reservas.txt");
    std::string linea;
    
    if (archivo.is_open()) {
        std::cout << "Lista de Reservas:" << std::endl;
        std::cout << "-------------------" << std::endl;
        while (std::getline(archivo, linea)) {
            std::istringstream iss(linea);
            std::string nombreCliente, origen, destino;
            float tarifa;
            
            if (std::getline(iss, nombreCliente, ',') &&
                std::getline(iss, origen, ',') &&
                std::getline(iss, destino, ',') &&
                (iss >> tarifa)) {
                std::cout << "Cliente: " << nombreCliente << std::endl;
                std::cout << "Origen: " << origen << std::endl;
                std::cout << "Destino: " << destino << std::endl;
                std::cout << "Tarifa: " << tarifa << std::endl;
                std::cout << "-------------------" << std::endl;
            }
        }
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo de reservas." << std::endl;
    }
}

void actualizarReserva(const std::string& nombreCliente) {
    std::ifstream archivo("data/reservas.txt");
    std::vector<std::string> reservas;
    std::string linea;
    bool encontrado = false;

    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string cliente, origen, destino;
        float tarifa;

        if (std::getline(iss, cliente, ',') &&
            std::getline(iss, origen, ',') &&
            std::getline(iss, destino, ',') &&
            (iss >> tarifa)) {
            
            if (cliente == nombreCliente) {
                encontrado = true;
                std::cout << "Reserva encontrada. Datos actuales:" << std::endl;
                std::cout << "Origen: " << origen << std::endl;
                std::cout << "Destino: " << destino << std::endl;
                std::cout << "Tarifa: " << tarifa << std::endl;

                std::cout << "Ingrese el nuevo lugar de origen: ";
                std::getline(std::cin >> std::ws, origen);

                std::cout << "Ingrese el nuevo lugar de destino: ";
                std::getline(std::cin >> std::ws, destino);

                tarifa = calcularTarifa(origen, destino);

                std::ostringstream oss;
                oss << cliente << "," << origen << "," << destino << "," << tarifa;
                reservas.push_back(oss.str());
            } else {
                reservas.push_back(linea);
            }
        }
    }

    archivo.close();

    if (encontrado) {
        std::ofstream archivoSalida("data/reservas.txt");
        for (const auto& reserva : reservas) {
            archivoSalida << reserva << std::endl;
        }
        archivoSalida.close();
        std::cout << "Reserva actualizada correctamente." << std::endl;
    } else {
        std::cout << "No se encontró una reserva con el nombre del cliente." << std::endl;
    }
}


void borrarReserva(const std::string& nombreCliente) {
    std::ifstream archivo("data/reservas.txt");
    std::ofstream archivoTemporal("data/temp.txt");

    if (!archivo || !archivoTemporal) {
        std::cerr << "Error al abrir los archivos.\n";
        return;
    }

    std::string cliente, origen, destino, marcaVehiculo, modeloVehiculo, matriculaVehiculo, nombreConductor, telefonoConductor;
    float tarifa;
    char delimitador;
    bool encontrado = false;

    while (std::getline(archivo, cliente, ',') &&
           std::getline(archivo, origen, ',') &&
           std::getline(archivo, destino, ',') &&
           archivo >> tarifa >> delimitador &&
           std::getline(archivo, marcaVehiculo, ',') &&
           std::getline(archivo, modeloVehiculo, ',') &&
           std::getline(archivo, matriculaVehiculo, ',') &&
           std::getline(archivo, nombreConductor, ',') &&
           std::getline(archivo, telefonoConductor)) {

        if (cliente == nombreCliente) {
            encontrado = true;
            std::cout << "Reserva para " << nombreCliente << " eliminada correctamente.\n";
            // No escribir esta reserva en el archivo temporal (efectivamente la eliminamos)
        } else {
            // Escribir los otros registros en el archivo temporal
            archivoTemporal << cliente << "," << origen << "," << destino << "," << tarifa << ","
                            << marcaVehiculo << "," << modeloVehiculo << "," << matriculaVehiculo << ","
                            << nombreConductor << "," << telefonoConductor << "\n";
        }

        archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    archivo.close();
    archivoTemporal.close();

    if (encontrado) {
        std::remove("data/reservas.txt");
        std::rename("data/temp.txt", "data/reservas.txt");
    } else {
        std::remove("data/temp.txt");
        std::cerr << "No se encontró una reserva con el nombre del cliente.\n";
    }
}

void borrarTodasLasReservas() {
    std::ofstream archivo("data/reservas.txt", std::ios::trunc);  // Abrir el archivo en modo truncar (eliminar todo)
    if (!archivo) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }
    archivo.close();
    std::cout << "Todas las reservas han sido eliminadas.\n";
}

