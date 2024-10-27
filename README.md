# Sistema de Gestión de Reservas y Clientes

Sistema de gestión desarrollado en C++ que permite administrar reservas y clientes, calculando tarifas basadas en distancias.

## Requisitos del Sistema

1. Sistema Operativo:
   - Linux/Unix
   - Windows (con WSL - Windows Subsystem for Linux)
   - macOS

2. Herramientas necesarias:
   - G++ (versión 4.8.5 o superior)
   - Make
   - Git

## Instalación Paso a Paso

1. Instalar las herramientas necesarias:

En Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install -y g++ make git
```

## Uso del Sistema

### Menú Principal
El sistema presenta tres opciones principales:
1. Gestionar Reservas
2. Gestionar Clientes
3. Salir

### Gestión de Reservas
Para crear una nueva reserva:
1. Seleccionar opción 1 en el menú principal
2. Seleccionar opción 1 "Hacer una Reserva"
3. Ingresar:
   - Nombre del cliente
   - Origen
   - Destino
   - Kilómetros aproximados

### Gestión de Clientes
Para registrar un nuevo cliente:
1. Seleccionar opción 2 en el menú principal
2. Seleccionar opción 1 "Registrar Cliente"
3. Ingresar:
   - Nombre
   - Apellido
   - Teléfono

## Estructura de Archivos

Los datos se almacenan en el directorio `data/`:
- `data/clientes.txt`: Almacena información de clientes
- `data/reservas.txt`: Almacena información de reservas

## Contacto y Soporte

Para reportar problemas o sugerir mejoras:
- Crear un issue en el repositorio
- Contactar al desarrollador: deyanecast@gmail.com

## Notas Importantes

- La tarifa se calcula automáticamente ($10 por kilómetro)
- Los archivos se crean automáticamente al primer uso
- Todas las búsquedas son insensibles a mayúsculas/minúsculas
- La pantalla se limpia automáticamente entre menús para mejor navegación
- Se requiere presionar Enter para continuar después de cada operación

## Mantenimiento Regular

1. Limpieza de archivos temporales:
   - `make clean`

## Compilar el proyecto
   - `make`

5. Ejecutar el programa:
   - `./programa`

Si estás en Windows usando WSL, asegúrate de:
1. Tener WSL instalado y actualizado
2. Estar en el directorio correcto dentro de WSL
3. Tener los permisos necesarios

En caso de errores de compilación:

Verificar versiones de G++:
- `g++ --version`

Verificar que make está instalado
- `make --version`

Verificar permisos del directorio
- `ls -l`


