#include <iostream>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include "reserva.h"
#include "utilidades.h"
#include "cliente.h"
#include <unistd.h>
#include <limits>
#include <cstdlib>

// Declaraciones de funciones
void imprimirConColor(const std::string& texto, const std::string& color);
int obtenerAnchoConsola();
void mostrarMenuPrincipal();
void mostrarSubMenuClientes();
void mostrarSubMenuReservas();
void gestionClientes();
void gestionReservas();
void limpiarPantalla();

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
    std::cout << "\n--- Menú Principal ---" << std::endl;
    std::cout << "1. Gestionar Reservas" << std::endl;
    std::cout << "2. Gestionar Clientes" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void mostrarSubMenuClientes() {
    const std::vector<std::string> opcionesMenu = {
        "Gestión de Clientes",
        "1. Registrar Cliente",
        "2. Editar Cliente",
        "3. Eliminar Cliente",
        "4. Mostrar Clientes",
        "5. Buscar Cliente",  // Nueva opción
        "6. Regresar al Menú Principal"
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
        "6. Buscar Reserva",  // Nueva opción
        "7. Regresar al Menú Principal"
    };

    for (const auto& opcion : opcionesMenu) {
        imprimirCentrado(opcion, obtenerAnchoConsola());
    }

    std::cout << std::string(obtenerAnchoConsola(), '-') << "\n";
}

void gestionClientes() {
    int opcion;
    std::string nombre, criterioBusqueda;
    do {
        limpiarPantalla();
        mostrarSubMenuClientes();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        limpiarPantalla();
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
                std::cout << "Ingrese el criterio de búsqueda: ";
                std::getline(std::cin, criterioBusqueda);
                buscarCliente(criterioBusqueda);
                break;
            case 6:
                std::cout << "Regresando al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
        if (opcion != 6) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
        }
    } while (opcion != 6);
}

void gestionReservas() {
    int opcion;
    std::string nombreCliente, criterioBusqueda;
    do {
        limpiarPantalla();
        mostrarSubMenuReservas();
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        limpiarPantalla();
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
                std::cout << "Ingrese el criterio de búsqueda: ";
                std::getline(std::cin, criterioBusqueda);
                buscarReserva(criterioBusqueda);
                break;
            case 7:
                std::cout << "Regresando al menú principal...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
        if (opcion != 7) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
        }
    } while (opcion != 7);
}

void limpiarPantalla() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

int main() {
    int opcion;
    do {
        limpiarPantalla();
        mostrarMenuPrincipal();
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        limpiarPantalla();
        switch(opcion) {
            case 1:
                gestionReservas();
                break;
            case 2:
                gestionClientes();
                break;
            case 3:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
        if (opcion != 3) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
        }
    } while (opcion != 3);

    return 0;
}
