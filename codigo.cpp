#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Estudiante {

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;
};

struct Nodo {

    Estudiante estudiante;
    Nodo* siguiente;
};

class HashTable {

private:

    static const int SIZE = 10;

    Nodo* tabla[SIZE];

    int totalElementos;
    int totalColisiones;

    int funcionHash(int id) {

        return id % SIZE;
    }

public:

    HashTable() {

        for (int i = 0; i < SIZE; i++) {

            tabla[i] = nullptr;
        }

        totalElementos = 0;
        totalColisiones = 0;
    }

    Estudiante* buscar(int id) {

        int indice = funcionHash(id);

        Nodo* actual = tabla[indice];

        while (actual != nullptr) {

            if (actual->estudiante.student_id == id) {

                return &actual->estudiante;
            }

            actual = actual->siguiente;
        }

        return nullptr;
    }

    bool insertar(Estudiante estudiante) {

        int indice = funcionHash(estudiante.student_id);

        // VALIDAR DUPLICADOS
        if (buscar(estudiante.student_id) != nullptr) {

            cout << "Error: ya existe un estudiante con ese ID.\n";
            return false;
        }

        Nodo* nuevo = new Nodo;

        nuevo->estudiante = estudiante;
        nuevo->siguiente = nullptr;

        // COLISION
        if (tabla[indice] != nullptr) {

            totalColisiones++;
        }

        // INSERTAR AL INICIO
        nuevo->siguiente = tabla[indice];
        tabla[indice] = nuevo;

        totalElementos++;

        cout << "Estudiante insertado correctamente en bucket "
             << indice << ".\n";

        return true;
    }

    bool eliminar(int id) {

        int indice = funcionHash(id);

        Nodo* actual = tabla[indice];
        Nodo* anterior = nullptr;

        while (actual != nullptr) {

            if (actual->estudiante.student_id == id) {

                if (anterior == nullptr) {

                    tabla[indice] = actual->siguiente;

                } else {

                    anterior->siguiente = actual->siguiente;
                }

                delete actual;

                totalElementos--;

                cout << "Estudiante eliminado correctamente.\n";

                return true;
            }

            anterior = actual;
            actual = actual->siguiente;
        }

        cout << "No se encontro estudiante.\n";

        return false;
    }

    void mostrarTabla() {

        cout << "\n========== HASH TABLE ==========\n";

        for (int i = 0; i < SIZE; i++) {

            cout << "Bucket [" << i << "]: ";

            Nodo* actual = tabla[i];

            if (actual == nullptr) {

                cout << "vacio";
            }

            while (actual != nullptr) {

                cout << "("
                     << actual->estudiante.student_id
                     << ", "
                     << actual->estudiante.full_name
                     << ") -> ";

                actual = actual->siguiente;
            }

            cout << "NULL\n";
        }
    }

    float calcularFactorCarga() {

        return (float) totalElementos / SIZE;
    }

    void mostrarEstadisticas() {

        cout << "\n========== ESTADISTICAS ==========\n";

        cout << "Total estudiantes: "
             << totalElementos << endl;

        cout << "Total buckets: "
             << SIZE << endl;

        cout << "Total colisiones: "
             << totalColisiones << endl;

        cout << "Factor de carga: "
             << calcularFactorCarga() << endl;
    }

    void cargarCSV(string nombreArchivo) {

        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {

            cout << "Error al abrir el archivo CSV.\n";
            return;
        }

        string linea;

        // SALTAR ENCABEZADO
        getline(archivo, linea);

        while (getline(archivo, linea)) {

            stringstream ss(linea);

            string dato;

            Estudiante estudiante;

            getline(ss, dato, ',');
            estudiante.student_id = stoi(dato);

            getline(ss, estudiante.full_name, ',');

            getline(ss, estudiante.career, ',');

            getline(ss, dato, ',');
            estudiante.semester = stoi(dato);

            getline(ss, dato, ',');
            estudiante.gpa = stof(dato);

            getline(ss, dato, ',');
            estudiante.skill_score = stoi(dato);

            insertar(estudiante);
        }

        archivo.close();

        cout << "CSV cargado correctamente.\n";
    }

    ~HashTable() {

        for (int i = 0; i < SIZE; i++) {

            Nodo* actual = tabla[i];

            while (actual != nullptr) {

                Nodo* temp = actual;

                actual = actual->siguiente;

                delete temp;
            }
        }
    }
};

int main() {

    cout << "=====================================\n";
    cout << "Nombre: Marco Gaytan\n";
    cout << "Carnet: 9941249182\n";
    cout << "=====================================\n";

    HashTable hash;

    int opcion;

    do {

        cout << "\n========== MENU ==========\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Cargar CSV\n";
        cout << "3. Buscar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Mostrar tabla hash\n";
        cout << "6. Mostrar estadisticas\n";
        cout << "7. Salir\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // AGREGAR ESTUDIANTE
        if (opcion == 1) {

            Estudiante estudiante;

            cout << "ID: ";
            cin >> estudiante.student_id;

            cin.ignore();

            cout << "Nombre completo: ";
            getline(cin, estudiante.full_name);

            cout << "Carrera: ";
            getline(cin, estudiante.career);

            cout << "Semestre: ";
            cin >> estudiante.semester;

            cout << "GPA: ";
            cin >> estudiante.gpa;

            cout << "Skill Score: ";
            cin >> estudiante.skill_score;

            hash.insertar(estudiante);
        }

        // CARGAR CSV
        else if (opcion == 2) {

            hash.cargarCSV("estudiantes.csv");
        }

        // BUSCAR
        else if (opcion == 3) {

            int id;

            cout << "Ingrese ID: ";
            cin >> id;

            Estudiante* encontrado = hash.buscar(id);

            if (encontrado != nullptr) {

                cout << "\n=== ESTUDIANTE ENCONTRADO ===\n";

                cout << "ID: "
                     << encontrado->student_id << endl;

                cout << "Nombre: "
                     << encontrado->full_name << endl;

                cout << "Carrera: "
                     << encontrado->career << endl;

                cout << "Semestre: "
                     << encontrado->semester << endl;

                cout << "GPA: "
                     << encontrado->gpa << endl;

                cout << "Skill Score: "
                     << encontrado->skill_score << endl;

            } else {

                cout << "No encontrado.\n";
            }
        }

        // ELIMINAR
        else if (opcion == 4) {

            int id;

            cout << "Ingrese ID a eliminar: ";
            cin >> id;

            hash.eliminar(id);
        }

        // MOSTRAR HASH
        else if (opcion == 5) {

            hash.mostrarTabla();
        }

        // ESTADISTICAS
        else if (opcion == 6) {

            hash.mostrarEstadisticas();
        }

        // SALIR
        else if (opcion == 7) {

            cout << "Saliendo del programa...\n";
        }

        else {

            cout << "Opcion invalida.\n";
        }

    } while (opcion != 7);

    return 0;
}
