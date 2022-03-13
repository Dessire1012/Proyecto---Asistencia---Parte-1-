//Proyecto -  Asistencia - Parte 1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <vector>
#include "Alumno.h"

using namespace std;

void leerArchivo(string nombre) {
    string e = "\\";
    string nombreTxt = e + nombre.substr(nombre.length() - 45, 45);

    ifstream txt (nombreTxt);
    txt.open(nombreTxt, ios::in);
    if (txt.is_open()) {
        string linea;
        while (getline(txt, linea))
            cout << linea << endl;

        txt.close();
    }
    else {
        cout << "\n" << nombreTxt << "\n";
    }
    
}

void exec(string command) {
    char buffer[128];
    int contador = 0;
    string resultado = "";
    
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        cout << "popen failed!";
    }
    
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            resultado += buffer;
            contador++;
        } 
        if (contador == 2) {
            cout << resultado;
            leerArchivo(resultado);
            contador = 0;
            resultado = "";
        }

    }
    _pclose(pipe);
}

int main()
{
    exec("dir /s/b \"Contenido del Curso\\2021-*.txt");
    vector <Alumno> alumno;
    
}
