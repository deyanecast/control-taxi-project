#include "utilidades.h"
#include <iostream>
#include <string>
#include <fstream>

void imprimirCentrado(const std::string& texto, int anchoConsola) {
    size_t longitudTexto = texto.length();
    int espacios = (anchoConsola - static_cast<int>(longitudTexto)) / 2;
    std::cout << std::string(espacios, ' ') << texto << "\n";
}


void generarHTMLClientes() {
    std::ifstream archivoClientes("data/clientes.txt");
    std::ofstream archivoHTML("data/clientes.html");

    if (!archivoClientes) {
        std::cerr << "Error al abrir el archivo clientes.txt\n";
        return;
    }

    if (!archivoHTML) {
        std::cerr << "Error al crear el archivo clientes.html\n";
        return;
    }

    archivoHTML << "<!DOCTYPE html>\n";
    archivoHTML << "<html>\n";
    archivoHTML << "<head>\n";
    archivoHTML << "<meta charset='UTF-8'>\n";
    archivoHTML << "<title>Clientes Registrados</title>\n";
    archivoHTML << "<style>\n";
    archivoHTML << "table { width: 50%; border-collapse: collapse; margin: 50px 0; }\n";
    archivoHTML << "th, td { padding: 12px; border: 1px solid #ddd; text-align: left; }\n";
    archivoHTML << "th { background-color: #f2f2f2; }\n";
    archivoHTML << "</style>\n";
    archivoHTML << "</head>\n";
    archivoHTML << "<body>\n";
    archivoHTML << "<h1>Clientes Registrados</h1>\n";
    archivoHTML << "<table>\n";
    archivoHTML << "<tr><th>Nombre</th><th>Telefono</th></tr>\n";

    std::string nombre, telefono;

    while (std::getline(archivoClientes, nombre, ',') && std::getline(archivoClientes, telefono)) {
        archivoHTML << "<tr><td>" << nombre << "</td><td>" << telefono << "</td></tr>\n";
    }

    archivoHTML << "</table>\n";
    archivoHTML << "</body>\n";
    archivoHTML << "</html>\n";

    archivoClientes.close();
    archivoHTML.close();

    std::cout << "Archivo clientes.html generado correctamente.\n";
}


void generarHTMLReservas() {
    std::ifstream archivoReservas("data/reservas.txt");
    std::ofstream archivoHTML("data/reservas.html");

    if (!archivoReservas) {
        std::cerr << "Error al abrir el archivo de reservas.\n";
        return;
    }

    if (!archivoHTML) {
        std::cerr << "Error al crear el archivo reservas.html.\n";
        return;
    }

    // Escribir el encabezado del archivo HTML
    archivoHTML << "<!DOCTYPE html>\n";
    archivoHTML << "<html>\n";
    archivoHTML << "<head>\n";
    archivoHTML << "<meta charset='UTF-8'>\n";
    archivoHTML << "<title>Reservas Realizadas</title>\n";
    archivoHTML << "<style>\n";
    archivoHTML << "table { width: 80%; border-collapse: collapse; margin: 50px 0; }\n";
    archivoHTML << "th, td { padding: 12px; border: 1px solid #ddd; text-align: left; }\n";
    archivoHTML << "th { background-color: #f2f2f2; }\n";
    archivoHTML << "</style>\n";
    archivoHTML << "</head>\n";
    archivoHTML << "<body>\n";
    archivoHTML << "<h1>Reservas Realizadas</h1>\n";
    archivoHTML << "<table>\n";
    archivoHTML << "<tr><th>Cliente</th><th>Origen</th><th>Destino</th><th>Tarifa</th><th>Vehículo</th><th>Conductor</th></tr>\n";

    std::string cliente, origen, destino, marcaVehiculo, modeloVehiculo, matriculaVehiculo, nombreConductor, telefonoConductor;
    float tarifa;
    char delimitador;

    // Leer el archivo de reservas y agregar filas a la tabla HTML
    while (std::getline(archivoReservas, cliente, ',') &&
           std::getline(archivoReservas, origen, ',') &&
           std::getline(archivoReservas, destino, ',') &&
           archivoReservas >> tarifa >> delimitador &&
           std::getline(archivoReservas, marcaVehiculo, ',') &&
           std::getline(archivoReservas, modeloVehiculo, ',') &&
           std::getline(archivoReservas, matriculaVehiculo, ',') &&
           std::getline(archivoReservas, nombreConductor, ',') &&
           std::getline(archivoReservas, telefonoConductor)) {

        archivoHTML << "<tr><td>" << cliente << "</td>"
                    << "<td>" << origen << "</td>"
                    << "<td>" << destino << "</td>"
                    << "<td>" << tarifa << "</td>"
                    << "<td>" << marcaVehiculo << " " << modeloVehiculo << " (Matrícula: " << matriculaVehiculo << ")</td>"
                    << "<td>" << nombreConductor << " (Teléfono: " << telefonoConductor << ")</td></tr>\n";

        // Ignorar el salto de línea final
        archivoReservas.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Cerrar las etiquetas HTML
    archivoHTML << "</table>\n";
    archivoHTML << "</body>\n";
    archivoHTML << "</html>\n";

    archivoReservas.close();
    archivoHTML.close();

    std::cout << "Archivo reservas.html generado correctamente.\n";
}
