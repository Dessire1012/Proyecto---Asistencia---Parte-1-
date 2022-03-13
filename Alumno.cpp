#include "Alumno.h"

Alumno::Alumno(string Nombre) {
	this->Nombre = Nombre;
}
void Alumno::AsistenciaAudio() {
	Asistencia++;
	Audio++;
};
void Alumno::AsistenciaNoAudio() {
	Asistencia++;
	No_Audio++;
};
int Alumno::getAsistencia() {
	return Asistencia;
};
int Alumno::getAudio() {
	return Audio;
};
int Alumno::getNo_Audio() {
	return No_Audio;
};