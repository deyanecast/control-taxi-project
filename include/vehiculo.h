// vehiculo.h
#ifndef VEHICULO_H
#define VEHICULO_H

#include <string>

class Vehiculo {
private:
    std::string marca;
    std::string modelo;
    std::string matricula;
    std::string nombreConductor;
    std::string telefonoConductor;

public:
    // Constructor
    Vehiculo(const std::string& _marca, const std::string& _modelo, const std::string& _matricula,
             const std::string& _nombreConductor, const std::string& _telefonoConductor);

    // Métodos de acceso
    std::string getMarca() const;
    std::string getModelo() const;
    std::string getMatricula() const;
    std::string getNombreConductor() const;
    std::string getTelefonoConductor() const;

    // Métodos para mostrar la información del vehículo y conductor
    void mostrarInformacion() const;
};

#endif
