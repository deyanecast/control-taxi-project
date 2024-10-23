// vehiculo.cpp
#include "vehiculo.h"
#include <iostream>

// Constructor
Vehiculo::Vehiculo(const std::string& _marca, const std::string& _modelo, const std::string& _matricula,
                   const std::string& _nombreConductor, const std::string& _telefonoConductor)
    : marca(_marca), modelo(_modelo), matricula(_matricula),
      nombreConductor(_nombreConductor), telefonoConductor(_telefonoConductor) {}

// Métodos de acceso
std::string Vehiculo::getMarca() const { return marca; }
std::string Vehiculo::getModelo() const { return modelo; }
std::string Vehiculo::getMatricula() const { return matricula; }
std::string Vehiculo::getNombreConductor() const { return nombreConductor; }
std::string Vehiculo::getTelefonoConductor() const { return telefonoConductor; }

// Mostrar la información del vehículo y conductor
void Vehiculo::mostrarInformacion() const {
    std::cout << "Vehículo: " << marca << " " << modelo << " [Matrícula: " << matricula << "]\n";
    std::cout << "Conductor: " << nombreConductor << " [Teléfono: " << telefonoConductor << "]\n";
}
