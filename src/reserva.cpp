#include "reserva.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<Distancia> distancias = {
    {"Ciudad A", "Ciudad B", 100},
    {"Ciudad A", "Ciudad C", 150},
    {"Ciudad B", "Ciudad C", 80},
};

float obtenerDistancia(const std::string& origen, const std::string& destino) {
    for (const auto& d : distancias) {
        if ((d.origen == origen && d.destino == destino) ||
            (d.origen == destino && d.destino == origen)) {
            return d.kilometros;
        }
    }
    return -1; 
}

void hacerReserva() {
    std::string nombreCliente, origen, destino;
    float tarifa, kilometraje;
    
    std::cout << "Ingrese el nombre del cliente: ";
    std::getline(std::cin >> std::ws, nombreCliente);
    
    std::cout << "Ingrese el origen: ";
    std::getline(std::cin >> std::ws, origen);
    
    std::cout << "Ingrese el destino: ";
    std::getline(std::cin >> std::ws, destino);
    
    std::cout << "Ingrese los kilómetros aproximados: ";
    std::cin >> kilometraje;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (kilometraje <= 0) {
        std::cout << "Kilometraje inválido. No se puede realizar la reserva." << std::endl;
        return;
    }

    tarifa = calcularTarifa(kilometraje);
    
    std::cout << "La tarifa calculada es: $" << tarifa << std::endl;

    std::ofstream archivo("data/reservas.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << nombreCliente << "," << origen << "," << destino << "," << kilometraje << "," << tarifa << std::endl;
        archivo.close();
        std::cout << "Reserva realizada con éxito." << std::endl;
        std::cout << "Datos guardados: " << nombreCliente << "," << origen << "," << destino << "," << kilometraje << "," << tarifa << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo para guardar la reserva." << std::endl;
        std::cout << "Intentando crear el directorio 'data'..." << std::endl;
        system("mkdir -p data");
        std::ofstream archivoNuevo("data/reservas.txt", std::ios::app);
        if (archivoNuevo.is_open()) {
            archivoNuevo << nombreCliente << "," << origen << "," << destino << "," << kilometraje << "," << tarifa << std::endl;
            archivoNuevo.close();
            std::cout << "Reserva realizada con éxito después de crear el directorio." << std::endl;
        } else {
            std::cout << "Fallo al crear el archivo incluso después de crear el directorio." << std::endl;
        }
    }
}

float calcularTarifa(float kilometraje) {
    return kilometraje * 10.0;
}

float calcularKilometraje(const std::string& origen, const std::string& destino) {
    float distancia = obtenerDistancia(origen, destino);
    if (distancia >= 0) {
        return distancia;
    } else {
        std::cout << "Advertencia: No se encontró la distancia entre " << origen << " y " << destino << ". Usando valor predeterminado." << std::endl;
        return 100.0;
    }
}

void mostrarReservas() {
    std::ifstream archivo("data/reservas.txt");
    std::string linea;
    
    if (archivo.is_open()) {
        std::cout << "Archivo abierto correctamente." << std::endl;
        std::cout << "Lista de Reservas:" << std::endl;
        std::cout << std::string(110, '-') << std::endl;
        
        // Imprimir encabezados
        std::cout << std::left 
                  << std::setw(25) << "Nombre" 
                  << std::setw(20) << "Origen" 
                  << std::setw(20) << "Destino" 
                  << std::setw(15) << "Precio/km" 
                  << std::setw(15) << "Km Aprox." 
                  << std::setw(15) << "Tarifa Final" << std::endl;
        std::cout << std::string(110, '-') << std::endl;

        int contadorLineas = 0;
        while (std::getline(archivo, linea)) {
            contadorLineas++;
            std::istringstream iss(linea);
            std::string nombreCliente, origen, destino, kmStr, tarifaStr;
            
            if (std::getline(iss, nombreCliente, ',') &&
                std::getline(iss, origen, ',') &&
                std::getline(iss, destino, ',') &&
                std::getline(iss, kmStr, ',') &&
                std::getline(iss, tarifaStr)) {
                
                float kilometraje = std::stof(kmStr);
                float tarifa = std::stof(tarifaStr);
                float precioPorKm = tarifa / kilometraje;

                std::cout << std::left 
                          << std::setw(25) << std::setfill(' ') << nombreCliente 
                          << std::setw(20) << std::setfill(' ') << origen 
                          << std::setw(20) << std::setfill(' ') << destino 
                          << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << precioPorKm
                          << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << kilometraje 
                          << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << tarifa << std::endl;
            } else {
                std::cout << "Error al leer la línea " << contadorLineas << ". Formato incorrecto." << std::endl;
            }
        }
        std::cout << std::string(110, '-') << std::endl;
        std::cout << "Total de líneas leídas: " << contadorLineas << std::endl;
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

    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo de reservas." << std::endl;
        return;
    }

    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string cliente, origen, destino, kmStr, tarifaStr;

        if (std::getline(iss, cliente, ',') &&
            std::getline(iss, origen, ',') &&
            std::getline(iss, destino, ',') &&
            std::getline(iss, kmStr, ',') &&
            std::getline(iss, tarifaStr)) {
            
            if (cliente == nombreCliente) {
                encontrado = true;
                std::cout << "Reserva encontrada. Datos actuales:" << std::endl;
                std::cout << "Cliente: " << cliente << std::endl;
                std::cout << "Origen: " << origen << std::endl;
                std::cout << "Destino: " << destino << std::endl;
                std::cout << "Kilometraje: " << kmStr << " km" << std::endl;
                std::cout << "Tarifa: $" << tarifaStr << std::endl;

                std::cout << "Ingrese el nuevo lugar de origen (o presione Enter para mantener el actual): ";
                std::string nuevoOrigen;
                std::getline(std::cin, nuevoOrigen);
                if (!nuevoOrigen.empty()) origen = nuevoOrigen;

                std::cout << "Ingrese el nuevo lugar de destino (o presione Enter para mantener el actual): ";
                std::string nuevoDestino;
                std::getline(std::cin, nuevoDestino);
                if (!nuevoDestino.empty()) destino = nuevoDestino;

                float kilometraje = std::stof(kmStr);
                float tarifa = std::stof(tarifaStr);

                std::cout << "Ingrese los nuevos kilómetros aproximados (o 0 para mantener los actuales): ";
                float nuevoKilometraje;
                std::cin >> nuevoKilometraje;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (nuevoKilometraje > 0) {
                    kilometraje = nuevoKilometraje;
                    tarifa = calcularTarifa(kilometraje);
                }

                std::ostringstream oss;
                oss << cliente << "," << origen << "," << destino << "," << kilometraje << "," << tarifa;
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
        std::cout << "No se encontró una reserva con el nombre del cliente: " << nombreCliente << std::endl;
    }
}


void borrarReserva(const std::string& nombreCliente) {
    std::ifstream archivoEntrada("data/reservas.txt");
    std::vector<std::string> reservas;
    std::string linea;

    while (std::getline(archivoEntrada, linea)) {
        std::istringstream iss(linea);
        std::string cliente;
        if (std::getline(iss, cliente, ',') && cliente != nombreCliente) {
            reservas.push_back(linea);
        }
    }

    archivoEntrada.close();

    std::ofstream archivoSalida("data/reservas.txt");
    for (const auto& reserva : reservas) {
        archivoSalida << reserva << std::endl;
    }
    archivoSalida.close();

    std::cout << "Reserva borrada (si existía)." << std::endl;
}

void borrarTodasLasReservas() {
    std::ofstream archivo("data/reservas.txt", std::ios::trunc);
    archivo.close();
    std::cout << "Todas las reservas han sido borradas." << std::endl;
}

void buscarReserva(const std::string& criterio) {
    std::ifstream archivo("data/reservas.txt");
    std::string linea;
    bool encontrado = false;

    if (archivo.is_open()) {
        std::cout << "Resultados de la búsqueda:" << std::endl;
        std::cout << std::string(110, '-') << std::endl;
        
        // Imprimir encabezados
        std::cout << std::left 
                  << std::setw(25) << "Nombre" 
                  << std::setw(20) << "Origen" 
                  << std::setw(20) << "Destino" 
                  << std::setw(15) << "Precio/km" 
                  << std::setw(15) << "Km Aprox." 
                  << std::setw(15) << "Tarifa Final" << std::endl;
        std::cout << std::string(110, '-') << std::endl;

        while (std::getline(archivo, linea)) {
            std::istringstream iss(linea);
            std::string nombreCliente, origen, destino, kmStr, tarifaStr;
            
            if (std::getline(iss, nombreCliente, ',') &&
                std::getline(iss, origen, ',') &&
                std::getline(iss, destino, ',') &&
                std::getline(iss, kmStr, ',') &&
                std::getline(iss, tarifaStr)) {
                
                // Convertir todo a minúsculas para una búsqueda insensible a mayúsculas/minúsculas
                std::string lineaLower = nombreCliente + origen + destino;
                std::transform(lineaLower.begin(), lineaLower.end(), lineaLower.begin(), ::tolower);
                std::string criterioLower = criterio;
                std::transform(criterioLower.begin(), criterioLower.end(), criterioLower.begin(), ::tolower);

                if (lineaLower.find(criterioLower) != std::string::npos) {
                    encontrado = true;
                    float kilometraje = std::stof(kmStr);
                    float tarifa = std::stof(tarifaStr);
                    float precioPorKm = tarifa / kilometraje;

                    std::cout << std::left 
                              << std::setw(25) << std::setfill(' ') << nombreCliente 
                              << std::setw(20) << std::setfill(' ') << origen 
                              << std::setw(20) << std::setfill(' ') << destino 
                              << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << precioPorKm
                              << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << kilometraje 
                              << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << tarifa << std::endl;
                }
            }
        }
        
        if (!encontrado) {
            std::cout << "No se encontraron reservas que coincidan con el criterio de búsqueda." << std::endl;
        }
        
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo de reservas." << std::endl;
    }
}
