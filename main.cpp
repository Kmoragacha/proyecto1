#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
using namespace std;

// Constantes
const int MAX = 10;
const float COMISION_LUZ = 0.04;
const float COMISION_TEL = 0.055;
const float COMISION_AGUA = 0.065;

// Vectores para almacenar datos
int numeroPago[MAX];
string fecha[MAX], hora[MAX], cedula[MAX], nombre[MAX], apellido1[MAX], apellido2[MAX];
int numeroCaja[MAX], tipoServicio[MAX], numeroFactura[MAX];
float montoPagar[MAX], montoComision[MAX], montoDeducido[MAX], montoCliente[MAX], vuelto[MAX];
int contador = 0;

// Funciones para interfaz
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Validación tipo de servicio
int leerTipoServicio() {
    int tipo;
    do {
        cout << "Tipo de Servicio [1- Electricidad  2- Telefono  3- Agua]: ";
        cin >> tipo;
        if (cin.fail() || tipo < 1 || tipo > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            setColor(4);
            cout << "Error: opción inválida. Intente de nuevo.\n";
            setColor(7);
        }
    } while (tipo < 1 || tipo > 3);
    return tipo;
}

// Inicializar vectores
void inicializarVectores() {
    for (int i = 0; i < MAX; i++) {
        numeroPago[i] = 0;
        fecha[i] = "";
        hora[i] = "";
        cedula[i] = "";
        nombre[i] = "";
        apellido1[i] = "";
        apellido2[i] = "";
        numeroCaja[i] = 0;
        tipoServicio[i] = 0;
        numeroFactura[i] = 0;
        montoPagar[i] = 0;
        montoComision[i] = 0;
        montoDeducido[i] = 0;
        montoCliente[i] = 0;
        vuelto[i] = 0;
    }
    contador = 0;
    setColor(10);
    cout << "\nVectores inicializados correctamente.\n";
    setColor(7);
    cout << "\n\nPulse cualquier tecla para continuar . . .";
    getch();
}

// Calcular comisión
float calcularComision(int tipo, float monto) {
    switch(tipo) {
        case 1: return monto * COMISION_LUZ;
        case 2: return monto * COMISION_TEL;
        case 3: return monto * COMISION_AGUA;
        default: return 0;
    }
}

// Realizar pagos
void realizarPagos() {
    char continuar = 'S';
    while (continuar == 'S' && contador < MAX) {
        system("cls");
        setColor(11);
        gotoxy(30, 2); cout << "Sistema Pago de Servicios Publicos";
        gotoxy(30, 3); cout << "Tienda La Favorita - Ingreso de Datos";
        setColor(7);

        numeroPago[contador] = contador + 1;
        gotoxy(10, 5); cout << "Numero de Pago: " << numeroPago[contador];

        gotoxy(10, 6); cout << "Fecha: "; cin >> fecha[contador];
        gotoxy(40, 6); cout << "Hora: "; cin >> hora[contador];

        gotoxy(10, 8); cout << "Cedula: "; cin >> cedula[contador];
        gotoxy(40, 8); cout << "Nombre: "; cin >> nombre[contador];

        gotoxy(10, 9); cout << "Apellido1: "; cin >> apellido1[contador];
        gotoxy(40, 9); cout << "Apellido2: "; cin >> apellido2[contador];

        numeroCaja[contador] = rand() % 3 + 1;

        gotoxy(10, 11); tipoServicio[contador] = leerTipoServicio();

        gotoxy(10, 13); cout << "Numero de Factura: "; cin >> numeroFactura[contador];
        gotoxy(40, 13); cout << "Monto Pagar: "; cin >> montoPagar[contador];

        do {
            gotoxy(10, 14); cout << "Paga con: ";
            cin >> montoCliente[contador];
            if (montoCliente[contador] < montoPagar[contador]) {
                setColor(4);
                cout << "Error: el monto pagado no puede ser menor al monto a pagar.";
                setColor(7);
            }
        } while (montoCliente[contador] < montoPagar[contador]);

        montoComision[contador] = calcularComision(tipoServicio[contador], montoPagar[contador]);
        montoDeducido[contador] = montoPagar[contador] - montoComision[contador];
        vuelto[contador] = montoCliente[contador] - montoPagar[contador];

        gotoxy(10, 16); cout << "Comision autorizada: " << montoComision[contador];
        gotoxy(40, 16); cout << "Monto deducido: " << montoDeducido[contador];
        gotoxy(10, 17); cout << "Vuelto: " << vuelto[contador];

        contador++;
        gotoxy(10, 19); cout << "Desea Continuar S/N ? ";
        cin >> continuar;
        continuar = toupper(continuar);
    }
    cout << "\n\nPulse cualquier tecla para continuar . . .";
    getch();
}

// Consultar pagos
void consultarPagos() {
    system("cls");
    setColor(11);
    gotoxy(30, 2); cout << "Sistema Pago de Servicios Publicos";
    gotoxy(30, 3); cout << "Tienda La Favorita - Consulta de Datos";
    setColor(7);

    int num;
    gotoxy(10, 5); cout << "Numero de Pago: ";
    cin >> num;

    int indice = -1;
    for (int i = 0; i < contador; i++) {
        if (numeroPago[i] == num) { indice = i; break; }
    }

    if (indice == -1) {
        gotoxy(10, 8); setColor(4); cout << "Pago no encontrado."; setColor(7);
        cout << "\n\nPulse cualquier tecla para continuar . . .";
        getch();
        return;
    }

    gotoxy(10, 8); setColor(10); cout << "Dato Encontrado Posicion Vector " << indice; setColor(7);
    gotoxy(10, 12); cout << "Presione cualquier tecla para ver Registro";
    getch();

    system("cls");
    setColor(11);
    gotoxy(30, 2); cout << "Sistema Pago de Servicios Publicos";
    gotoxy(30, 3); cout << "Tienda La Favorita - Consulta de Datos";
    setColor(7);

    gotoxy(10, 5); cout << "Numero de Pago: " << numeroPago[indice];
    gotoxy(10, 6); cout << "Fecha: " << fecha[indice];
    gotoxy(40, 6); cout << "Hora: " << hora[indice];
    gotoxy(10, 8); cout << "Cedula: " << cedula[indice];
    gotoxy(40, 8); cout << "Nombre: " << nombre[indice];
    gotoxy(10, 9); cout << "Apellido1: " << apellido1[indice];
    gotoxy(40, 9); cout << "Apellido2: " << apellido2[indice];
    gotoxy(10,11); cout << "Tipo de Servicio: " << tipoServicio[indice] << " [1- Electricidad 2- Telefono 3- Agua]";
    gotoxy(10,13); cout << "Numero de Factura: " << numeroFactura[indice];
    gotoxy(40,13); cout << "Monto Pagar: " << montoPagar[indice];
    gotoxy(10,14); cout << "Comision autorizada: " << montoComision[indice];
    gotoxy(40,14); cout << "Paga con: " << montoCliente[indice];
    gotoxy(10,15); cout << "Monto deducido: " << montoDeducido[indice];
    gotoxy(40,15); cout << "Vuelto: " << vuelto[indice];

    cout << "\n\nPulse cualquier tecla para continuar . . .";
    getch();
}

// Reporte Todos los Pagos
void reporteTodos() {
    system("cls");
    setColor(11);
    gotoxy(30, 2); cout << "Reporte Todos los Pagos";
    setColor(7);
    gotoxy(5,4); cout << "Pago#  Fecha       Hora    Cedula    Nombre    Servicio   Monto   Comision";
    gotoxy(5,5); cout << "--------------------------------------------------------------------------";
    int y = 6;
    for (int i = 0; i < contador; i++) {
        gotoxy(5,y++);
        cout << numeroPago[i] << "   " << fecha[i] << "   " << hora[i] << "   " << cedula[i] << "   "
             << nombre[i] << "   " << tipoServicio[i] << "   " << montoPagar[i] << "   " << montoComision[i];
    }
    cout << "\n\nPulse cualquier tecla para continuar . . .";
    getch();
}

// Reporte por Tipo de Servicio
void reportePorTipoServicio() {
    system("cls");
    int tipo = leerTipoServicio();
    setColor(11);
    gotoxy(30, 2); cout << "Reporte Pagos por Tipo de Servicio";
    setColor(7);
    int y = 6;
    for (int i = 0; i < contador; i++) {
        if (tipoServicio[i] == tipo) {
            gotoxy(5,y++);
            cout << numeroPago[i] << " " << nombre[i] << " " << montoPagar[i];
        }
    }
    cout << "\n\nPulse cualquier tecla para continuar . . .";
    getch();
}

// Reporte por Código de Caja
void reportePorCodigoCaja() {
    system("cls");
    int caja;
    do {
        cout << "Ingrese codigo de caja (1-3): ";
        cin >> caja;
    } while (caja < 1 || caja > 3);
    setColor(11);
    gotoxy(30, 2); cout << "Reporte Pagos por Codigo de Caja";
    setColor(7);
    int y = 6;
    for (int i = 0; i < contador; i++) {
        if (numeroCaja[i] == caja) {
            gotoxy(5,y++);
            cout << numeroPago[i] << " " << nombre[i] << " " << montoPagar[i];
        }
    }
    cout << "\n\nPulse cualquier tecla para continuar . . .";
    getch();
}

// Reporte Dinero Comisionado
void reporteComisiones() {
    system("cls");

    float totalLuz = 0, totalTel = 0, totalAgua = 0;
    int contLuz = 0, contTel = 0, contAgua = 0;

    for (int i = 0; i < contador; i++) {
        if (tipoServicio[i] == 1) { totalLuz += montoComision[i]; contLuz++; }
        else if (tipoServicio[i] == 2) { totalTel += montoComision[i]; contTel++; }
        else if (tipoServicio[i] == 3) { totalAgua += montoComision[i]; contAgua++; }
    }

    int totalTransacciones = contLuz + contTel + contAgua;
    float totalComisionado = totalLuz + totalTel + totalAgua;

    setColor(11);
    gotoxy(25, 2); cout << "Reporte Dinero Comisionado - Desglose por Tipo de Servicio";
    setColor(7);

    gotoxy(20, 4); cout << "==============================================================";
    gotoxy(20, 5); cout << "ITEM                Cant. Transacciones      Total Comisionado";
    gotoxy(20, 6); cout << "==============================================================";

    gotoxy(20, 8); cout << "1-Electricidad      " << contLuz << "                      " << totalLuz;
    gotoxy(20, 9); cout << "2-Telefono          " << contTel << "                      " << totalTel;
    gotoxy(20,10); cout << "3-Agua              " << contAgua << "                      " << totalAgua;

    gotoxy(20,12); cout << "--------------------------------------------------------------";
    gotoxy(20,13); cout << "Total               " << totalTransacciones << "                      " << totalComisionado;
    gotoxy(20,14); cout << "==============================================================";

    cout << "\n\nPulse cualquier tecla para continuar . . .";
    getch();
}

// Submenú Reportes
void subMenuReportes() {
    int opcion;
    do {
        system("cls");
        setColor(11);
        gotoxy(30, 2); cout << "Sistema Pago de Servicios Publicos";
        gotoxy(30, 3); cout << "Tienda La Favorita - Submenu Reportes";
        setColor(7);
        gotoxy(10, 6); cout << "1. Reporte Todos los Pagos";
        gotoxy(10, 7); cout << "2. Reporte por Tipo de Servicio";
        gotoxy(10, 8); cout << "3. Reporte por Codigo de Caja";
        gotoxy(10, 9); cout << "4. Ver Dinero Comisionado por Servicios";
        gotoxy(10,10); cout << "5. Regresar";
        gotoxy(10,12); cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch(opcion) {
            case 1: reporteTodos(); break;
            case 2: reportePorTipoServicio(); break;
            case 3: reportePorCodigoCaja(); break;
            case 4: reporteComisiones(); break;
            case 5: return;
            default: gotoxy(10,14); setColor(4); cout << "Opcion invalida."; setColor(7);
        }
    } while(opcion != 5);
}

// MAIN
int main() {
    srand(time(0));
    int opcion;
    do {
        system("cls");
        setColor(11);
        gotoxy(35, 5); cout << "=== SISTEMA DE PAGOS ===";
        setColor(10);
        gotoxy(35, 7); cout << "1. Inicializar vectores";
        gotoxy(35, 8); cout << "2. Realizar pagos";
        gotoxy(35, 9); cout << "3. Consultar pagos";
        gotoxy(35,10); cout << "6. Submenu reportes";
        gotoxy(35,11); cout << "7. Salir";
        gotoxy(35,13); setColor(14); cout << "Seleccione una opcion: "; setColor(7);
        cin >> opcion;
        system("cls");
        switch(opcion) {
            case 1: inicializarVectores(); break;
            case 2: realizarPagos(); break;
            case 3: consultarPagos(); break;
            case 6: subMenuReportes(); break;
            case 7: setColor(14); cout << "Saliendo...\n"; setColor(7); break;
            default: cout << "Opcion invalida.\n";
        }
        if(opcion != 7){
            cout << "\n\nPulse cualquier tecla para continuar . . .";
            getch();
        }
    } while(opcion != 7);
    return 0;
}                               



