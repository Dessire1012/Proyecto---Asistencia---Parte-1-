#pragma once
#include <string>
using namespace std;

class Alumno {
	string Nombre;
	int Asistencia;
	int Audio;
	int No_Audio;
public:
	Alumno(string Nombre);
	void AsistenciaAudio();
	void AsistenciaNoAudio();
	int getAsistencia();
	int getAudio();
	int getNo_Audio();
};