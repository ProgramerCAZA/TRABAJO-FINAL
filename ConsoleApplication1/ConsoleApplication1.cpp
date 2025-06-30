#include"pch.h"
#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

// Variables globales
string usuario = "";
string reserva = "";
int sesion = 0;
int pagoReserva = 0;

// Funciones para el sistema de ventas
void LimpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool ValidarDNI(const string& dni) {
    return (dni.length() == 8) && all_of(dni.begin(), dni.end(), ::isdigit);
}

bool ValidarTelefono(const string& telefono) {
    return (telefono.length() >= 9) && all_of(telefono.begin(), telefono.end(), ::isdigit);
}

void VentaProductos() {
    int opcion, cantidad;
    float total = 0;
    string continuar;
    vector<string> productosSeleccionados;
    vector<int> cantidades;
    vector<float> precios;

    // Precios de productos
    map<string, float> preciosCamaras = {
        {"Canon", 2500.00}, {"Sony", 3200.00}, {"Fujifilm", 2800.00},
        {"Olympus", 2100.00}, {"Panasonic", 2300.00}, {"Kodak", 1800.00}
    };

    map<string, float> preciosAccesorios = {
        {"Cargadores", 120.00}, {"Filtros", 85.00},
        {"Protectores", 65.00}, {"Pantallas", 45.00},
        {"KitLimpieza", 75.00}, {"Mochilas", 150.00},
        {"Oculares", 90.00}, {"Baterias", 110.00}
    };

    map<string, float> preciosLuces = {
        {"LuzCalida", 350.00}, {"LuzNeutra", 380.00}, {"LuzFria", 400.00}
    };

    do {
        system("cls");
        cout << "\n----- VENTA DE PRODUCTOS ----\n";
        cout << "Cliente: " << (usuario.empty() ? "Invitado" : usuario) << "\n";
        cout << "Productos seleccionados: " << productosSeleccionados.size() << "\n";
        cout << "Total acumulado: S/" << total << "\n\n";

        cout << "1. Cámaras fotográficas\n2. Accesorios\n";
        cout << "3. Luces\n4. Finalizar compra\n5. Cancelar\n";
        cout << "\nSeleccione: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            system("cls");
            cout << "\n--- CÁMARAS FOTOGRÁFICAS ---\n";
            cout << "1. Canon - S/2500.00\n2. Sony - S/3200.00\n";
            cout << "3. Fujifilm - S/2800.00\n4. Olympus - S/2100.00\n";
            cout << "5. Panasonic - S/2300.00\n6. Kodak - S/1800.00\n7. Volver\n";
            cout << "Seleccione: ";
            cin >> opcion;

            if (opcion >= 1 && opcion <= 6) {
                string camaras[] = { "Canon", "Sony", "Fujifilm", "Olympus", "Panasonic", "Kodak" };
                string producto = camaras[opcion - 1];
                cout << "Cantidad: ";
                while (!(cin >> cantidad) || cantidad <= 0) {
                    cout << "Ingrese cantidad válida (>0): ";
                    LimpiarBuffer();
                }

                productosSeleccionados.push_back(producto);
                cantidades.push_back(cantidad);
                precios.push_back(preciosCamaras[producto]);
                total += preciosCamaras[producto] * cantidad;
            }
            break;
        }
        case 2: {
            system("cls");
            cout << "\n--- ACCESORIOS ---\n";
            cout << "1. Cargadores - S/120.00\n2. Filtros - S/85.00\n";
            cout << "3. Protectores - S/65.00\n4. Pantallas - S/45.00\n";
            cout << "5. KitLimpieza - S/75.00\n6. Mochilas - S/150.00\n";
            cout << "7. Oculares - S/90.00\n8. Baterias - S/110.00\n9. Volver\n";
            cout << "Seleccione: ";
            cin >> opcion;

            if (opcion >= 1 && opcion <= 8) {
                string accesorios[] = { "Cargadores", "Filtros", "Protectores",
                                      "Pantallas", "KitLimpieza", "Mochilas",
                                      "Oculares", "Baterias" };
                string producto = accesorios[opcion - 1];
                cout << "Cantidad: ";
                while (!(cin >> cantidad) || cantidad <= 0) {
                    cout << "Ingrese cantidad válida (>0): ";
                    LimpiarBuffer();
                }

                productosSeleccionados.push_back(producto);
                cantidades.push_back(cantidad);
                precios.push_back(preciosAccesorios[producto]);
                total += preciosAccesorios[producto] * cantidad;
            }
            break;
        }
        case 3: {
            system("cls");
            cout << "\n--- LUCES ---\n";
            cout << "1. LuzCalida - S/350.00\n";
            cout << "2. LuzNeutra - S/380.00\n";
            cout << "3. LuzFria - S/400.00\n4. Volver\n";
            cout << "Seleccione: ";
            cin >> opcion;

            if (opcion >= 1 && opcion <= 3) {
                string luces[] = { "LuzCalida", "LuzNeutra", "LuzFria" };
                string producto = luces[opcion - 1];
                cout << "Cantidad: ";
                while (!(cin >> cantidad) || cantidad <= 0) {
                    cout << "Ingrese cantidad válida (>0): ";
                    LimpiarBuffer();
                }

                productosSeleccionados.push_back(producto);
                cantidades.push_back(cantidad);
                precios.push_back(preciosLuces[producto]);
                total += preciosLuces[producto] * cantidad;
            }
            break;
        }
        case 4: {
            if (productosSeleccionados.empty()) {
                cout << "\nNo ha seleccionado productos.\n";
                system("pause");
                break;
            }

            system("cls");
            cout << "\n--- RESUMEN DE COMPRA ---\n";
            for (size_t i = 0; i < productosSeleccionados.size(); i++) {
                cout << productosSeleccionados[i] << " x" << cantidades[i]
                    << " - S/" << precios[i] * cantidades[i] << endl;
            }
            cout << "\nTOTAL: S/" << total << endl;

            // Datos del cliente
            cout << "\n--- DATOS DEL CLIENTE ---\n";
            string dni, telefono;

            LimpiarBuffer();
            // Validación de DNI
            do {
                cout << "DNI (8 dígitos): ";
                getline(cin, dni);
                if (!ValidarDNI(dni)) {
                    cout << "Error: 8 dígitos numéricos\n";
                }
            } while (!ValidarDNI(dni));

            // Validación de teléfono
            do {
                cout << "Teléfono (mín 9 dígitos): ";
                getline(cin, telefono);
                if (!ValidarTelefono(telefono)) {
                    cout << "Error: Solo dígitos\n";
                }
            } while (!ValidarTelefono(telefono));

            cout << "\n--- CONFIRMACIÓN ---\n";
            cout << "¿Confirmar compra? (S/N): ";
            cin >> continuar;

            if (toupper(continuar[0]) == 'S') {
                cout << "\n¡COMPRA EXITOSA!\n";
                cout << "Se enviará confirmación al teléfono: " << telefono << endl;
                system("pause");
                return;
            }
            break;
        }
        case 5:
            return;
        default:
            cout << "\nOpción no válida\n";
            system("pause");
        }
    } while (true);
}

// Funciones originales del estudio fotográfico
void mostrarMenu() {
    cout << R"(
                           *%%%%                                         
                    +%:%%#%%%%%%% #%%                                    
                    # #%%%.  =   %%-%:                                   
                    #%%%% .*+#*%. *%%:                                   
                    #%%%. **   %=. %%:                                   
                    #%%%+  *%#%*: +%%:                                   
                    #%%%%*  : :  #%%%:                                   
                    :================                                   

   #%%%:%  %: +%%  %%%% *%%  #%% %%%% %  % %%%  #  %%*                   
   #==  %%%% #   #  +  #.  # #%%  #   #  # #  % # %   %                  
   #%  :%  %: *%%.  %%  *%%. #%%  %   *%%* %%#  %  %%#                   
    )";

    cout << "\n\t ===== MENU ESTUDIO FOTOGRAFICO =====" << endl;
    cout << "\t 1. Servicios disponibles" << endl;
    cout << "\t 2. Reservar una sesion" << endl;
    cout << "\t 3. Pagar reserva" << endl;
    cout << "\t 4. Ver mi reserva" << endl;
    cout << "\t 5. Ver productos a la venta" << endl;
    cout << "\t 6. Comprar producto" << endl;
    cout << "\t 7. Contactenos" << endl;
    cout << "\t 8. Iniciar sesion" << endl;
    cout << "\t 0. Salir" << endl;
}

void mostrarServicios() {
    cout << "\nServicios disponibles:\n- Sesion de fotos personal\n- Sesion de fotos familiar\n- Sesion profesional para CV o redes\n- Sesion en exteriores" << endl;
}
        
void hacerReserva() {
    if (sesion == 0) {
        cout << "Debe iniciar sesion primero para reservar.\n";
        return;
    }
    cout << "Ingrese el tipo de sesion que desea reservar: ";
    cin >> reserva;
    pagoReserva = 0;
    cout << "Reserva registrada: " << reserva << endl;
}

void pagarReserva() {
    if (sesion == 0) {
        cout << "Debe iniciar sesion para pagar una reserva.\n";
        return;
    }
    if (reserva == "") {
        cout << "No hay ninguna reserva registrada.\n";
        return;
    }
    if (pagoReserva == 1) {
        cout << "La reserva ya fue pagada.\n";
        return;
    }
    cout << "Pago realizado para la reserva: " << reserva << endl;
    pagoReserva = 1;
}

void verReserva() {
    if (reserva == "") {
        cout << "No hay reservas registradas.\n";
    }
    else {
        cout << "Reserva actual: " << reserva << endl;
        if (pagoReserva == 1)
            cout << "Estado: Pagada" << endl;
        else
            cout << "Estado: Pendiente de pago" << endl;
    }
}

void verProductos() {
    cout << "\nProductos disponibles:\n- Marcos para fotos\n- Impresiones en lienzo\n- Álbumes personalizados\n- USB con todas tus fotos" << endl;
}

void comprarProducto() {
    cout << "\nRedirigiendo al sistema de ventas...\n";
    system("pause");
    VentaProductos();
}

void contactar() {
    cout << "\nContáctenos al 987-654-321 o por email a estudio@fotos.pe" << endl;
}

void iniciarSesion() {
    if (sesion == 1) {
        cout << "Ya hay una sesion iniciada como: " << usuario << endl;
        return;
    }
    cout << "Ingrese su nombre de usuario: ";
    cin >> usuario;
    sesion = 1;
    cout << "Sesion iniciada correctamente. Bienvenido, " << usuario << "!" << endl;
}

int main() {
    int opcion;
    do {
        system("cls");
        mostrarMenu();
        cout << "\t Seleccione una opcion (0 para salir): ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: mostrarServicios(); break;
        case 2: hacerReserva(); break;
        case 3: pagarReserva(); break;
        case 4: verReserva(); break;
        case 5: verProductos(); break;
        case 6: comprarProducto(); break;
        case 7: contactar(); break;
        case 8: iniciarSesion(); break;
        case 0: cout << "Gracias por visitar el estudio fotografico." << endl; break;
        default: cout << "Opción no valida. Intente de nuevo.\n";
        }
        system("pause");
    } while (opcion != 0);

    return 0;
}
