// Proyecto -  Asistencia - Parte 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Alumno.h"

using namespace std;
string exec(string command) {
    char buffer[128];
    string resultado = "";
    //Open pipe to file
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }
    //read till end of process:
    while (!feof(pipe)) {
        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            resultado += buffer;
    }
    _pclose(pipe);
    return resultado;
}

int main()
{
    vector <Alumno> alumno;
    string dir = exec("dir /s/b \"Contenido del Curso\\2021-*.txt");
    cout << dir << endl;
}
