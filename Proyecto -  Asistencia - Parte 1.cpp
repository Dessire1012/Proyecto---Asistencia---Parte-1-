//Proyecto -  Asistencia - Parte 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Alumno.h"

using namespace std;
vector <Alumno> alumno;

//Detecta cualquiera de los indicadores en el proyecto;
int textoEspecial(string linea)
{
    // Primer caso: fecha (1)
    if (linea[0] == '2')
        return 1;
    //Segundo caso: ""
    else if (!linea.length())
        return 3;
    // Tercer caso: casos especiales
    else if (linea == "EXAMEN I" || linea == "ASISTIERON TODOS")
        return 4;
    // Cuarto caso: no_audio (2)
    else if (linea.length() > 10) {
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
        string NameAlumno = "";
        cout << "    ";
        while (getline(txt, linea))
        {
            if (textoEspecial(linea) == 1 || textoEspecial(linea) == 3 || textoEspecial(linea) == 4) // Ignorar "" � Fecha
            {
                cout << "I";
            }
            else if (textoEspecial(linea) == 2) // No tienen audio
            {
                NameAlumno = obtenerNombre(linea);
                cout << "[" << NameAlumno << "][A]";
                if (buscarAlumno(NameAlumno)) {
                    cout << "FU,";
                    agregarAsistencia(NameAlumno, false);
                }
                else {
                    alumno.push_back(NameAlumno);
                    cout << "NC,";
                    agregarAsistencia(NameAlumno, false);
                }

            }
            else // Si tienen audio
            {
                NameAlumno = obtenerNombre(linea);
                cout << "[" << NameAlumno << "][A]";
                if (buscarAlumno(NameAlumno)) {
                    cout << "FU,";
                    agregarAsistencia(NameAlumno, true);
                }
                else {
                    alumno.push_back(NameAlumno);
                    cout << "NC,";
                    agregarAsistencia(NameAlumno, true);
                }
            }
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
            cout << "\n";
            leerArchivo(resultado);
            contador = 0;
            resultado = "";
        }
    }
    _pclose(pipe);
}

// Ordenar el vector de alumnos segun asistencias con audios
//void ordenarAlumnos() {
//    Alumno aux; // auxiliar
//    for (int i = 0; i < alumno.size(); i++){
//        for (int j = 0; j < alumno.size()-1; j++){
//            if (alumno.at(j + 1).getAsistencia() > alumno.at(i).getAsistencia()) {
//                aux = alumno.at(j + 1);
//                alumno.at(j + 1) = alumno.at(j);
//                alumno.at(j) = aux;
//            }
//        }
//    }
//}


void mostrarAsistencia() {
    // Titulo y titulos de tablas
    cout << "\n\nLISTADO:\n=========\n\n";
    cout << setw(16) << "ALUMNO" << setw(8) << "AUDIO" << setw(9) << "NO-AUDIO"
        << setw(12) << "ASISTENCIAS" << setw(11) << "PORCENTAJE" << endl;
    cout << setw(16) << "------" << setw(8) << "-----" << setw(9) << "--------"
        << setw(12) << "-----------" << setw(11) << "----------" << endl;
    // ordenarAlumnos();
    // Imprimir alumnos
    for (int i = 0; i < alumno.size(); i++) {
        cout << setw(16) << alumno.at(i).getNombre() << setw(8) << alumno.at(i).getAudio() << setw(9) << alumno.at(i).getNo_Audio()
            << setw(12) << alumno.at(i).getAsistencia() << setw(10) << setprecision(2) << fixed <<
            (double)(alumno.at(i).getAudio() / alumno.at(i).getAsistencia()) * 100
            << "%" << endl;
    }
}
int main()
{
    exec("dir /s/b \"Contenido del Curso\\2021-*.txt");
    mostrarAsistencia();
}