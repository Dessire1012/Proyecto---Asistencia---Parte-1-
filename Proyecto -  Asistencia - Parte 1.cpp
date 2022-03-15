//Proyecto -  Asistencia - Parte 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <vector>
#include "Alumno.h"

using namespace std;
vector <Alumno> alumno;

//Detecta cualquiera de los indicadores en el proyecto;
int textoEspecial(string linea)
{
    // Primer caso: fecha (1)
    if (linea[0] == '2')
        return 1;
    else if (!linea.length())
        //Tercer caso: ""
        return 3;
    else if (linea.length() > 20) {
        // Segundo caso: no_audio (2)
        string lineaC = linea.substr(linea.length() - 10, 10);
        if (lineaC[0] == '-')
            return 2;
    }
}

// Imprime los nombres de los estudiantes
string obtenerNombre(string linea)
{
    string nombre;
    for (int i = 0; i < linea.length(); i++)
    {
        if (linea[i] == ' ')
            break;
        nombre += linea[i];
    }
    return nombre;
}

// Busca el alumno en el vector
bool buscarAlumno(string nombre)
{
    for (int i = 0; i < alumno.size(); i++)
        if (alumno.at(i).getNombre() == nombre)
            return true;
    return false;
}

// Agrega la asistencia dependiendo si tien o no audio
void agregarAsistencia(string nombre, bool audio_noaudio)
{
    for (int i = 0; i < alumno.size(); i++)
    {
        if (alumno.at(i).getNombre() == nombre)
        {
            if (audio_noaudio)
                alumno.at(i).AsistenciaAudio();
            else
                alumno.at(i).AsistenciaNoAudio();
        }
    }
}

// Leer archivos en las carpetas
void leerArchivo(string nombre) {
    string nombreTxt = nombre.substr(nombre.length() - 45, 44);
    fstream txt;
    txt.open(nombreTxt, ios::in);
    if (txt.is_open()) {
        string linea;
        while (getline(txt, linea))
        {
            if (textoEspecial(linea) == 1 || textoEspecial(linea) == 3) // Ignorar "" � Fecha
            {
                cout << "I";
            }
            else if (textoEspecial(linea) == 2) // No tienen audio
            {
                cout << "["  << obtenerNombre(linea) << "][A]";
                if (buscarAlumno(linea)){
                    cout << "FU";
                    agregarAsistencia(linea, false);
                    
                }
                else {
                    alumno.push_back(linea);
                    cout << "NC";
                    agregarAsistencia(linea, false);
                }
                
            }
            else // Si tienen audio
            {
                cout << "[" << obtenerNombre(linea) << "][A]";
                if (buscarAlumno(linea)) {
                    cout << "FU";
                    agregarAsistencia(linea, true);

                }
                else {
                    alumno.push_back(linea);
                    cout << "NC";
                    agregarAsistencia(linea, true);
                }
            }
            cout << ",";
        }
        txt.close();
    }
}

void exec(string command) {
    char buffer[128];
    int contador = 0;
    string resultado = "";

    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe)
        cout << "popen failed!";


    while (!feof(pipe)) {
        if (contador == 1)
            cout << "\n\n*REVISANDO EL ARCHIVO: " << endl;

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
}