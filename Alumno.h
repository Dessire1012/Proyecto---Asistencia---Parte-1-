#pragma once
#include <string>
using namespace std;

class Alumno {
	string Nombre;
	int Asistencia = 0;
	int Audio = 0;
	int No_Audio = 0;
public:
	Alumno();
	Alumno(string Nombre);
	void AsistenciaAudio();
	void AsistenciaNoAudio();
	string getNombre();
	int getAsistencia();
	int getAudio();
	int getNo_Audio();
};