#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Estudiante {
    int id;
    char nombre[50];
    char apellido[50];
    float nota1;
    float nota2;
    float nota3;
    float nota4;
    float promedio;
    char resultado[10];
};

float calcularPromedio(float nota1, float nota2, float nota3, float nota4) {
    return (nota1 + nota2 + nota3 + nota4) / 4.0;
}

void agregar(fstream &file) {
    Estudiante est;
    
    cout << "Ingrese el ID del estudiante: ";
    cin >> est.id;
    cin.ignore();
    cout << "Ingrese el nombre del estudiante: ";
    cin.getline(est.nombre, 50);
    cout << "Ingrese el apellido del estudiante: ";
    cin.getline(est.apellido, 50);
    cout << "Ingrese la nota 1 del estudiante: ";
    cin >> est.nota1;
    cout << "Ingrese la nota 2 del estudiante: ";
    cin >> est.nota2;
    cout << "Ingrese la nota 3 del estudiante: ";
    cin >> est.nota3;
    cout << "Ingrese la nota 4 del estudiante: ";
    cin >> est.nota4;
    
    est.promedio = calcularPromedio(est.nota1, est.nota2, est.nota3, est.nota4);
    strcpy(est.resultado, (est.promedio > 60) ? "Aprobado" : "Reprobado");
    
    file.write(reinterpret_cast<char*>(&est), sizeof(Estudiante));
}

void leer(fstream &file) {
    Estudiante est;
    file.seekg(0, ios::beg);
    
    while(file.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        cout << "ID: " << est.id << "\nNombre: " << est.nombre << "\nApellido: " << est.apellido
             << "\nNota1: " << est.nota1 << "\nNota2: " << est.nota2 << "\nNota3: " << est.nota3
             << "\nNota4: " << est.nota4 << "\nPromedio: " << est.promedio << "\nResultado: " << est.resultado << "\n\n";
    }
}

void actualizar(fstream &file, int id) {
    Estudiante est;
    file.seekg(0, ios::beg);
    
    while(file.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        if(est.id == id) {
            file.seekp(-static_cast<int>(sizeof(Estudiante)), ios::cur);
            
            cout << "Ingrese el nuevo nombre: ";
            cin.ignore();
            cin.getline(est.nombre, 50);
            cout << "Ingrese el nuevo apellido: ";
            cin.getline(est.apellido, 50);
            cout << "Ingrese la nueva nota 1: ";
            cin >> est.nota1;
            cout << "Ingrese la nueva nota 2: ";
            cin >> est.nota2;
            cout << "Ingrese la nueva nota 3: ";
            cin >> est.nota3;
            cout << "Ingrese la nueva nota 4: ";
            cin >> est.nota4;
            
            est.promedio = calcularPromedio(est.nota1, est.nota2, est.nota3, est.nota4);
            strcpy(est.resultado, (est.promedio >= 60) ? "Aprobado" : "Reprobado");
            
            file.write(reinterpret_cast<char*>(&est), sizeof(Estudiante));
            break;
        }
    }
}

void eliminar(fstream &file, const char* filename, int id) {
    fstream tempFile("temp.dat", ios::out | ios::binary);
    Estudiante est;
    file.seekg(0, ios::beg);
    
    while(file.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        if(est.id != id) {
            tempFile.write(reinterpret_cast<char*>(&est), sizeof(Estudiante));
        }
    }
    
    file.close();
    tempFile.close();
    
    remove(filename);
    rename("temp.dat", filename);
    file.open(filename, ios::in | ios::out | ios::binary | ios::app);
}

int main() {
    fstream file("notas.dat", ios::in | ios::out | ios::binary | ios::app);
    if (!file) {
        cerr << "Error al abrir el archivo!" << endl;
        return 1;
    }

    int opcion, id;
    do {
        cout << "1. Agregar"<<endl;
        cout << "2. Leer"<<endl;
        cout << "3. Actualizar"<<endl;
        cout << "4. Eliminar"<<endl;
        cin >> opcion;

        switch(opcion) {
            case 1:
                agregar(file);
                break;
            case 2:
                leer(file);
                break;
            case 3:
                cout << "Ingrese el ID del estudiante a actualizar: ";
                cin >> id;
                actualizar(file, id);
                break;
            case 4:
                cout << "Ingrese el ID del estudiante a eliminar: ";
                cin >> id;
                eliminar(file, "notas.dat", id);
                break;
            case 5:
                cout << "salir" << endl;
                break;
            default:
                cout << "Opcion invalida!" << endl;
        }
    } while(opcion != 5);

    file.close();
    return 0;
}

