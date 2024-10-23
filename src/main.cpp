#include <iostream>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include "reserva.h"
#include "utilidades.h"
#include "cliente.h"
#include <unistd.h>
#include <limits>

// Declaraciones de funciones
void imprimirConColor(const std::string& texto, const std::string& color);
int obtenerAnchoConsola();
void mostrarMenuPrincipal();
void mostrarSubMenuClientes();
void mostrarSubMenuReservas();
void gestionClientes();
void gestionReservas();

// Implementaciones de funciones
void imprimirConColor(const std::string& texto, const std::string& color) {
    std::cout << color << texto << "\033[0m" << "\n"; // \033[0m resetea el color
}

int obtenerAnchoConsola() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void mostrarMenuPrincipal() {
    const std::vector<std::string> opcionesMenu = {
        "Sistema de Control de Rutas de Taxis",
        "1. Gestión de Clientes",
        "2. Gestión de Reservas",
        "3. Salir"
    };

    for (const auto& opcion : opcionesMenu) {
        imprimirCentrado(opcion, obtenerAnchoConsola());
    }

    std::cout << std::string(obtenerAnchoConsola(), '-') << "\n";
}

void mostrarSubMenuClientes() {
    const std::vector<std::string> opcionesMenu = {
        "Gestión de Clientes",
        "1. Registrar Cliente",
        "2. Editar Cliente",
        "3. Eliminar Cliente",
        "4. Mostrar Clientes",
        "5. Regresar al Menú Principal"
    };

    for (const auto& opcion : opcionesMenu) {
        imprimirCentrado(opcion, obtenerAnchoConsola());
    }

    std::cout << std::string(obtenerAnchoConsola(), '-') << "\n";
}

void mostrarSubMenuReservas() {
    const std::vector<std::string> opcionesMenu = {
        "Gestión de Reservas",
        "1. Hacer una Reserva",
        "2. Actualizar Reserva",
        "3. Borrar Reserva",
        "4. Mostrar Reservas",
        "5. Borrar Todas las Reservas",
        "6. Regresar al Menú Principal"
    };

    for (const auto& opcion : opcionesMenu) {
        imprimirCentrado(opcion, obtenerAnchoConsola());
    }

    std::cout << std::string(obtenerAnchoConsola(), '-') << "\n";
}

void gestionClientes() {
    int opcion;
    std::string nombre;
    do {
        mostrarSubMenuClientes();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                registrarCliente();
                break;
            case 2:
                mostrarClientes();
                std::cout << "Ingrese el nombre del cliente cuya reserva desea actualizar: ";
            
                std::getline(std::cin, nombre);
                editarCliente(nombre);
                break;
            case 3:
                // Implementar eliminarCliente()
                std::cout << "Función de eliminar cliente aún no implementada.\n";
                break;
            case 4:
                mostrarClientes();
                generarHTMLClientes();
                break;
            case 5:
                std::cout << "Regresando al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 5);
}

void gestionReservas() {
    int opcion;
    std::string nombreCliente;
    do {
        mostrarSubMenuReservas();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                hacerReserva();
                break;
            case 2:
                mostrarReservas();
                std::cout << "Ingrese el nombre del cliente cuya reserva desea actualizar: ";
                std::getline(std::cin, nombreCliente);
                actualizarReserva(nombreCliente);
                break;
            case 3:
                mostrarReservas();
                std::cout << "Ingrese el nombre del cliente cuya reserva desea borrar: ";
                std::getline(std::cin, nombreCliente);
                borrarReserva(nombreCliente);
                break;
            case 4:
                mostrarReservas();
                generarHTMLReservas();
                break;
            case 5:
                borrarTodasLasReservas();
                break;
            case 6:
                std::cout << "Regresando al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 6);
}

int main() {
    int opcion;

    do {
        mostrarMenuPrincipal();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                gestionClientes();
                break;
            case 2:
                gestionReservas();
                break;
            case 3:
                std::cout << "Saliendo del sistema.\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 3);

    return 0;
}
