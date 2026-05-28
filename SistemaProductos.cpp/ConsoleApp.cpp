#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

const int MAX_PROD = 100;

struct Producto {
    int codigo;
    char descripcion[30];
    float precio;
    bool activo;
};

void cargarProducto(Producto productos[], int &cantidad){
    if (cantidad >= MAX_PROD){
        cout << "No Se Pueden Cargar Mas Productos." << endl;
        return;
    }
    cout << "Codigo: ";
    cin >> productos[cantidad].codigo;

    cout << "Descripcion: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(productos[cantidad].descripcion, 30);

    cout << "Precio: ";
    cin >> productos[cantidad].precio;

    productos[cantidad].activo = true;

    cantidad++;

    cout << "Producto cargado Correctamente." << endl;
}

void listarProductos(Producto productos[], int cantidad){
    if (cantidad == 0){
        cout << "No hay Productos Cargados." << endl;
        return;
    }

    cout << "\n--- LISTADO DE PRODUCTOS ---\n";
    for (int i = 0; i < cantidad; i++){
        if (productos[i].activo){
            cout << "Codigo: " << productos[i].codigo << endl;
            cout << "Descripcion: " << productos[i].descripcion << endl;
            cout << "Precio: $" << productos[i].precio << endl;
            cout << "--------------------\n";
        }
    }
}

int buscarProducto(Producto productos[], int cantidad, int codigoBuscado){
    for (int i = 0; i < cantidad; i++){
        if (productos[i].activo && productos[i].codigo == codigoBuscado){
            return i;
        }
    }
    return -1;
}

void modificarPrecio(Producto productos[], int cantidad){
    int codigo;
    cout << "Ingrese el codigo del producto a modificar: ";
    cin >> codigo;

    int pos = buscarProducto(productos, cantidad, codigo);

    if(pos == -1){
        cout << "Producto no encontrado." << endl;
        return;
    }

    cout << "Precio actual: $" << productos[pos].precio << endl;

    float nuevoPrecio;
    cout << "Ingrese el nuevo precio: ";
    cin >> nuevoPrecio;

    productos[pos].precio = nuevoPrecio;

    cout << "Precio modificado correctamente." << endl;
}

void eliminarProducto(Producto productos[], int cantidad){
    int codigo;
    cout << "Ingrese el codigo del producto a eliminar:";
    cin >> codigo;

    int pos = buscarProducto(productos, cantidad, codigo);

    if (pos == -1){
        cout << "Producto no encontrado." << endl;
        return;
    }

    productos[pos].activo = false;

    cout << "Producto eliminado." << endl;
}

void guardarBinario(Producto productos[], int cantidad){
    FILE *f = fopen("productos.dat", "wb");
    if(f == NULL){
        cout << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }
fwrite (productos, sizeof(Producto), cantidad, f);
fclose(f);
cout << "Archivo guardado correctamente." << endl;
}

void cargarBinario(Producto productos[], int &cantidad){
    FILE *f = fopen("productos.dat", "rb");
    if (f == NULL){
        cout << "No existe el archivo. Se creara cuando guardes." << endl;
        return;
    }
cantidad = fread(productos, sizeof(Producto), MAX_PROD, f);
fclose(f);
cout << "Archivo cargado correctamente. Productos leidos." << cantidad << endl;
}

void menu(Producto productos[], int &cantidad){
    int opcion;
    do{
        cout << "\n----- MENU PRINCIPAL -----\n";
        cout << "1) Cargar productos\n";
        cout << "2) Listar productos\n";
        cout << "3) Buscar producto\n";
        cout << "4) Modificar precio\n";
        cout << "5) Eliminar producto\n";
        cout << "6) Guardar archivo binario\n";
        cout << "7) Cargar archivo binario\n";
        cout << "8) Salir\n";
        cout << "Seleccionar una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
            cargarProducto(productos, cantidad);
            break;

            case 2:
            listarProductos(productos, cantidad);
            break;

            case 3: {
                int codigo;
                cout << "Ingrese codigo a buscar: ";
                cin >> codigo;

                int pos = buscarProducto(productos, cantidad, codigo);

                if (pos == -1){
                    cout << "Producto no encontrado." << endl;
                }else{
                    cout << "Descripcion: " << productos[pos].descripcion << endl;
                    cout << "Precio: $" << productos[pos].precio << endl;
                }
               break;
            }

            case 4:
            modificarPrecio(productos, cantidad);
            break;

            case 5:
            eliminarProducto(productos, cantidad);
            break;

            case 6:
            guardarBinario(productos, cantidad);
            break;

            case 7:
            cargarBinario(productos, cantidad);
            break;
            
            case 8:
            cout << "Saliendo del sistema..." << endl;
            break;

            default:
            cout << "Opcion invalida." << endl;
            }
        }while(opcion != 8);
    }


int main() {
    Producto productos[MAX_PROD];
    int cantidad = 0;

menu(productos, cantidad);

return 0;
}

