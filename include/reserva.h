#ifndef RESERVA_H
#define RESERVA_H
#include <string>

struct Reserva {
    std::string cliente;
    std::string origen;
    std::string destino;
    float tarifa;
    
    // Información del vehículo y conductor
    std::string marcaVehiculo;
    std::string modeloVehiculo;
    std::string matriculaVehiculo;
    std::string nombreConductor;
    std::string telefonoConductor;
};

void hacerReserva();
void mostrarReservas();
void actualizarReserva(const std::string& nombreCliente);
void borrarReserva(const std::string& nombreCliente);
void borrarTodasLasReservas();
float calcularTarifa(const std::string& origen, const std::string& destino);

#endif
