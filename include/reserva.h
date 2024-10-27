#ifndef RESERVA_H
#define RESERVA_H

#include <string>
#include <vector>

struct Reserva {
    std::string cliente;
    std::string origen;
    std::string destino;
    float tarifa;
};

struct Distancia {
    std::string origen;
    std::string destino;
    float kilometros;
};

extern std::vector<Distancia> distancias;

void hacerReserva();
void mostrarReservas();
void actualizarReserva(const std::string& nombreCliente);
float calcularKilometraje(const std::string& origen, const std::string& destino);
float calcularTarifa(float kilometraje);
float obtenerDistancia(const std::string& origen, const std::string& destino);
void borrarReserva(const std::string& nombreCliente);
void borrarTodasLasReservas();

void buscarReserva(const std::string& criterio);

#endif
