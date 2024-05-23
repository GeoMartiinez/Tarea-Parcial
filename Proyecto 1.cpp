#include <iostream>
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
};

float calcularPromedio(float nota1, float nota2, float nota3, float nota4) {
    return (nota1 + nota2 + nota3 + nota4) / 4.0;
}

int main() {
    int N;
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> N;

    Estudiante estudiantes[N];

    for (int i = 0; i < N; ++i) {
        cout << "Ingrese el ID: ";
        cin >> estudiantes[i].id;
        cin.ignore();
        cout << "Ingrese el nombre: " ;
        cin.getline(estudiantes[i].nombre, 50);
        cout << "Ingrese el apellido: ";
        cin.getline(estudiantes[i].apellido, 50);
        cout << "Ingrese la nota 1: ";
        cin >> estudiantes[i].nota1;
        cout << "Ingrese la nota 2: ";
        cin >> estudiantes[i].nota2;
        cout << "Ingrese la nota 3: ";
        cin >> estudiantes[i].nota3;
        cout << "Ingrese la nota 4: ";
        cin >> estudiantes[i].nota4;
        estudiantes[i].promedio = calcularPromedio(estudiantes[i].nota1, estudiantes[i].nota2, estudiantes[i].nota3, estudiantes[i].nota4);
        cout << "-----------------------------------------------------"<<endl;
    }

    for (int i = 0; i < N; ++i) {
        cout << "\nEstudiante " << i + 1 << " (" << estudiantes[i].id << "): " << estudiantes[i].nombre << " " << estudiantes[i].apellido << endl;
        cout << "Promedio: " << estudiantes[i].promedio << endl;
        if (estudiantes[i].promedio >= 60) {
            cout << "El Estudiante Aprobó" << endl;
        } else {
            cout << "El estudiante a Reprobado" << endl;
        }
        cout << "-----------------------------------------------------"<<endl;
    }

    return 0;
}

