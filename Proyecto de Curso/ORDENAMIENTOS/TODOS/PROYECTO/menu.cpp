#include <iostream>
#include <vector>
#include <conio.h>
#include "ListaPropietarios.h"
#include "Coche.h"
#include "Lista.h"
#include "Validaciones.h"
#include "ValidacionPlaca.h"
#include "Menu.h"
#include "Ordenamiento.cpp"

using namespace std;

Coche coche;
int menuInteractivo(const vector<string> &opciones, const string &titulo)
{
    int seleccion = 0;
    const int numOpciones = opciones.size();

    while (true)
    {
        system("cls");

        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        " << titulo << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        for (int i = 0; i < numOpciones; ++i)
        {
            if (i == seleccion)
            {
                cout << " > " << opciones[i] << " < " << endl;
            }
            else
            {
                cout << "   " << opciones[i] << endl;
            }
        }

        cout << "========================================" << endl;

        char tecla = _getch();

        if (tecla == 'a' || tecla == 72)
        {
            seleccion = (seleccion - 1 + numOpciones) % numOpciones;
        }
        else if (tecla == 's' || tecla == 80)
        {
            seleccion = (seleccion + 1) % numOpciones;
        }
        else if (tecla == 13)
        {
            return seleccion;
        }
    }
}


void menuGestionPropietarios(ListaPropietarios &listaPropietarios)
{
    bool salirSubmenu = false;
    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "      Menu de Gestion de Propietarios   " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesPropietarios = {
            "Agregar Propietario",
            "Mostrar Propietarios",
            "Buscar Propietario por Cedula",
            "Eliminar Placa de Propietario", 
            "Volver al Menu Principal"};

        int seleccionPropietarios = menuInteractivo(opcionesPropietarios, "Menu de Gestion de Propietarios");

        switch (seleccionPropietarios)
        {
        case 0:
            agregarPropietario(listaPropietarios);
            listaPropietarios.guardarArchivo("propietarios.txt");
            break;
        case 1:
            listaPropietarios.mostrarPropietarios();
            system("pause");
            break;
        case 2:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   BUSQUEDA DE PROPIETARIO POR CEDULA   " << endl;
            cout << "========================================" << endl;
            string cedula;
            cout << "Ingrese la cedula a buscar: ";
            cin >> cedula;
            Propietario* propietario = listaPropietarios.buscarPropietarioPorCedula(cedula);
            if (propietario)
            {
                cout << "Propietario encontrado: " << propietario->toString() << endl;
            }
            else
            {
                cout << "Propietario no encontrado." << endl;
            }
            system("pause");
            break;
        }
        case 3:
            eliminarPlacaPropietario(listaPropietarios);
            listaPropietarios.guardarArchivo("propietarios.txt");
            break;
        case 4:
            salirSubmenu = true;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }
}

void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaPropietarios &listaPropietarios)
{
    Placa<Coche> validador;
     

    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Busqueda de Coche Por Placa",
        "Busqueda Avanzada",
        "Menu de Gestion de Propietarios",
        "Liberar el parqueadero",
        "Ordenar lista de coches",
        "Ayuda",
        "Salir"};


    string archivo = "autos.txt";
    string archivoHistorial = "autos_historial.txt";

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Parqueadero");

        switch (seleccion)
        {
        case 0:
        {

  if(listaPropietarios.estaVacia()) {
        cout << "No hay propietarios registrados. Por favor, registre un propietario antes de continuar." << endl;
        break ;
    }

            Coche nuevoCoche = nuevoCoche.InsertarDatos(lista, listaHistorial, listaPropietarios);
            lista.insertar(nuevoCoche, "autos.txt");
            listaHistorial.insertar(nuevoCoche, "autos_historial.txt");
            break;
        }
      case 1:
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "         Menu de Lista de Coches        " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesLista = {
            "Mostrar Coches en Parqueadero",
            "Mostrar Historial Completo de Coches",
            "Volver al Menu Principal"};

        int seleccionLista = menuInteractivo(opcionesLista, "Menu de Lista de Coches");

        switch (seleccionLista)
        {
        case 0: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   LISTA DE COCHES EN EL PARQUEADERO    " << endl;
            cout << "========================================" << endl;
            lista.mostrar(lista.getPrimero()); 
            system("pause");
            break; 
        }
        case 1: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   HISTORIAL COMPLETO DE COCHES         " << endl;
            cout << "========================================" << endl;
            listaHistorial.mostrar(listaHistorial.getPrimero()); 
            system("pause");
            break; 
        }
        case 2: 
        {
            cout << "Regresando al menu principal..." << endl;
            salirSubmenu = true; 
            break;
        }
        default:
            cout << "Opción inválida. Inténtelo de nuevo." << endl;
            system("pause");
            break;
        }
    }
    break; 
}
        case 2: 
{
    bool salirSubmenu = false;
    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        Menu de Busqueda por Placa      " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesBusqueda = {
            "Buscar en Parqueadero",
            "Buscar en Historial",
            "Volver al Menu Principal"};

        int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda por Placa");

        switch (seleccionBusqueda)
        {
        case 0: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   BUSQUEDA DE PLACA EN PARQUEADERO     " << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
            cin >> placa;
            lista.buscarPorPlaca(placa);
            system("pause");
            break; 
        }
        case 1: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   BUSQUEDA DE PLACA EN HISTORIAL       " << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
            cin >> placa;
            listaHistorial.buscarPorPlaca(placa);
            system("pause");
            break; 
        }
        case 2: 
        {
            cout << "Regresando al menu principal..." << endl;
            salirSubmenu = true; 
            break;
        }
        default:
            cout << "Opción inválida. Inténtelo de nuevo." << endl;
            system("pause");
            break;
        }
    }
    break; 
}
         case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "     BIENVENIDOS A LA BUSQUEDA AVANZADA  " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;

            menuBusquedaAvanzada(lista, listaHistorial);
            break;
        }
        case 4:
            menuGestionPropietarios(listaPropietarios);
            break;
        case 5:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "  BIENVENIDOS A LA GESTION DE ESTACIONAMIENTO " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa del coche que  va a  dejar el estacionamiento: ";
            cin >> placa;
            listaHistorial.salirDelParqueadero(placa);
            lista.eliminarPorPlaca(placa);
            break;
        }
        case 6:{
            menuOrdenar(lista, listaHistorial);
            break;
        }
        case 7:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "               (i)AYUDA                 " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string archivo = "ayuda.html";
            string comando = "start " + archivo;
            system(comando.c_str());
            break;
        }
        case 8:
        {
            cout << "Saliendo..." << endl;
            return;
        }
        default:
            cout << "Opcion invalida. Inténtelo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}

void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial)
{

    Validaciones validaciones;
    vector<string> opciones = {
        "Buscar en Parqueadero",
        "Buscar en Historial de Coches",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Busqueda Avanzada");

        switch (seleccion)
        {
        case 0: 
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Parqueadero");

            switch (seleccionBusqueda)
            {
            case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Modelo" << endl;
                    cout << "========================================" << endl;
                    string modelo;
                    cout << "Ingrese el modelo: ";
                    modelo = validaciones.ingresarString("Ingrese el modelo: ");
                    lista.BusquedaAvanzada("modelo", modelo,"");
                    break;
                }
            case 1:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Color" << endl;
                    cout << "========================================" << endl;
                    string color;
                    cout << "Ingrese el color: ";
                    color = validaciones.ingresarString("Ingrese el color: ");

                    lista.BusquedaAvanzada("color", color,"");
                    break;
                }
            case 2:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Anio/Fecha" << endl;
                    cout << "========================================" << endl;
                    string fecha;
                    cout << "Ingrese la fecha (DD-MM-AAAA): ";
                    cin >> fecha;
                    lista.BusquedaAvanzada("fecha", fecha,"");
                    break;
                }
            case 3:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Marca" << endl;
                    cout << "========================================" << endl;
                    string marca;
                    cout << "Ingrese la marca: ";
                    marca = validaciones.ingresarString("Ingrese la marca: ");
                    
                    lista.BusquedaAvanzada("marca", marca,"");
                    break;
                }
            case 4:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Hora" << endl;
                    cout << "========================================" << endl;
                    string HoraEntrada1, HoraEntrada2;
                    cout << "Ingrese la hora de entrada 1: ";
                    cin >> HoraEntrada1;
                    cout << "Ingrese la hora de entrada 2: ";
                    cin >> HoraEntrada2;
                    lista.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
                    break;
                }
            case 5:
                {
                    cout << "Saliendo..." << endl;
                    return;
                }
            default:
                cout << "Opción invalida. Intentalo de nuevo." << endl;
                break;
            }
            break;
        }

        case 1: 
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Historial");

            switch (seleccionBusqueda)
            {
            case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Modelo" << endl;
                    cout << "========================================" << endl;
                    string modelo;
                    cout << "Ingrese el modelo: ";
                    modelo = validaciones.ingresarString("Ingrese el modelo: ");
                    listaHistorial.BusquedaAvanzada("modelo", modelo,"");
                    break;
                }
            case 1:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Color" << endl;
                    cout << "========================================" << endl;
                    string color;
                    cout << "Ingrese el color: ";
                    color = validaciones.ingresarString("Ingrese el color: ");
                    listaHistorial.BusquedaAvanzada("color", color,"");
                    break;
                }
            case 2:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Año/Fecha" << endl;
                    cout << "========================================" << endl;
                    string fecha;
                    cout << "Ingrese la fecha (DD-MM-AAAA): ";
                    cin >> fecha;
                    listaHistorial.BusquedaAvanzada("fecha", fecha,"");
                    break;
                }
            case 3:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Marca" << endl;
                    cout << "========================================" << endl;
                    string marca;
                    cout << "Ingrese la marca: ";
                    marca = validaciones.ingresarString("Ingrese la marca: ");
                    listaHistorial.BusquedaAvanzada("marca", marca,"");
                    break;
                }
            case 4:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Hora" << endl;
                    cout << "========================================" << endl;
                    string HoraEntrada1, HoraEntrada2;
                    cout << "Ingrese la hora de entrada 1: ";
                    cin >> HoraEntrada1;
                    cout << "Ingrese la hora de entrada 2: ";
                    cin >> HoraEntrada2;
                    listaHistorial.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
                    break;
                }
            case 5:
                {
                    cout << "Saliendo..." << endl;
                    return;
                }
            default:
                cout << "Opción invalida. Intentalo de nuevo." << endl;
                break;
            }
            break;
        }

        case 2: 
            cout << "Saliendo..." << endl;
            return;

        default:
            cout << "Opción invalida. Intentalo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}

void menuOrdenar(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial)
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "           Menu de Ordenamiento         " << endl;
        cout << "========================================" << endl;

        vector<string> opcionesMetodo = {
            "Quick Sort",
            "Bucket Sort",
            "Bubble Sort",
            "Volver al Menu Principal"};

        int seleccionMetodo = menuInteractivo(opcionesMetodo, "Seleccione el método de ordenamiento:");

        if (seleccionMetodo == 3) {
            salirSubmenu = true;
            continue;
        }

        vector<string> opcionesOrdenar = {
            "Ordenar por Placa",
            "Ordenar por Apellido del Propietario",
            "Ordenar por Color",
            "Ordenar por Modelo",
            "Ordenar por Marca",
            "Volver al Menu Principal"};

        int seleccionOrdenar = menuInteractivo(opcionesOrdenar, "Seleccione el criterio de ordenamiento:");

        if (seleccionOrdenar == 5) {
            continue; 
        }

        
        if (seleccionMetodo == 0) { // Quick Sort
            switch (seleccionOrdenar) {
                case 0:
                    ordenarLista(lista, [](const Coche &a, const Coche &b) { return a.getPlaca() < b.getPlaca(); });
                    cout << "Lista ordenada por placa y guardada exitosamente." << endl;
                    break;
                case 1:
                    ordenarLista(lista, [](const Coche &a, const Coche &b) { return a.getPropietario().getApellido() < b.getPropietario().getApellido(); });
                    cout << "Lista ordenada por apellido del propietario y guardada exitosamente." << endl;
                    break;
                case 2:
                    ordenarLista(lista, [](const Coche &a, const Coche &b) { return a.getColor() < b.getColor(); });
                    cout << "Lista ordenada por color y guardada exitosamente." << endl;
                    break;
                case 3:
                    ordenarLista(lista, [](const Coche &a, const Coche &b) { return a.getModelo() < b.getModelo(); });
                    cout << "Lista ordenada por modelo y guardada exitosamente." << endl;
                    break;
                case 4:
                    ordenarLista(lista, [](const Coche &a, const Coche &b) { return a.getMarca() < b.getMarca(); });
                    cout << "Lista ordenada por marca y guardada exitosamente." << endl;
                    break;
                default:
                    cout << "Opción inválida. Intente de nuevo." << endl;
            }
        } else if (seleccionMetodo == 1) { // Bucket Sort
            std::function<std::string(const Coche&)> getKey;

            switch (seleccionOrdenar) {
                case 0:
                    getKey = [](const Coche &item) { return item.getPlaca(); };
                    break;
                case 1:
                    getKey = [](const Coche &item) { return item.getPropietario().getApellido(); };
                    break;
                case 2:
                    getKey = [](const Coche &item) { return item.getColor(); };
                    break;
                case 3:
                    getKey = [](const Coche &item) { return item.getModelo(); };
                    break;
                case 4:
                    getKey = [](const Coche &item) { return item.getMarca(); };
                    break;
                default:
                    cout << "Opción inválida. Intente de nuevo." << endl;
                    continue; // Salir del switch si la opción es inválida
            }

            
            ordenarListaBucket(lista, getKey);
            cout << "Lista ordenada por el criterio seleccionado y guardada exitosamente." << endl;
        } else if(seleccionMetodo == 2){
            switch(seleccionOrdenar){
                case 0:
                    ordenarListaBubbleSort(lista, [](const Coche &a, const Coche &b) { return a.getPlaca() < b.getPlaca(); });
                    cout << "Lista ordenada por placa y guardada exitosamente." << endl;
                    break;
                case 1:
                    ordenarListaBubbleSort(lista, [](const Coche &a, const Coche &b) { return a.getPropietario().getApellido() < b.getPropietario().getApellido(); });
                    cout << "Lista ordenada por apellido del propietario y guardada exitosamente." << endl;
                    break;
                case 2:
                    ordenarListaBubbleSort(lista,[](const Coche  &a, const Coche &b){return a.getColor() < b.getColor();});
                    cout << "Lista ordenada por color y guardada exitosamente." << endl;
                    break;
                case 3:
                    ordenarListaBubbleSort(lista,[](const Coche  &a, const Coche &b){return a.getModelo() < b.getModelo();});
                    cout << "Lista ordenada por modelo y guardada exitosamente." << endl;
                    break;
                case 4:
                    ordenarListaBubbleSort(lista,[](const Coche  &a, const Coche &b){return a.getMarca() < b.getMarca();});
                    cout << "Lista ordenada por marca y guardada exitosamente." << endl;
                    break;
                default:
                    cout << "Opción inválida. Intente de nuevo." << endl;
                    break;
            }
        }

        lista.GuardarArchivo("autos.txt");
        system("pause");
    }
}