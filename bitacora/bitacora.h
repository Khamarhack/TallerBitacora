/********************************
*Fecha: 2 de febrero 2026       *
*Autor: Santiago Camargo        *
*Tema: Taller 0/ Bitacora       *
*Estructuras de datos           *
********************************/

#ifndef BITACORA_H
#define BITACORA_H
#include <string>
#include <cstdint>
using namespace std;

struct registro {
	string nombre;
    	uint8_t emocion;
    	uint8_t felicidad;
    	uint8_t energia;
    	uint8_t horas_sueno;
    	uint8_t aguacate;
};

bool validarRegistro(const registro& r);
void agregarRegistro(registro*& arr, int& n, const registro& nuevo);
bool cargarBD(const string& ruta, registro*& arr, int& n);
bool guardarBD(const string& ruta, registro* arr, int n);

registro* buscarPorNombre(registro* arr, int n, const string& nombre);

int nivelAndoriano(const registro& r);
double promedioUltimosK(registro* arr, int n, int k);

#endif
