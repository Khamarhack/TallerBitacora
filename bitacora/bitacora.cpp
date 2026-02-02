/******************************** 
*Fecha: 2 de febrero 2026       *
*Autor: Santiago Camargo        *
*Tema: Taller 0/ Bitacora       *
*Estructuras de datos           *
********************************/

#include "bitacora.h"
#include <fstream>
#include <iostream>

using namespace std;
bool validarRegistro(const registro& r) {
	if (r.emocion > 3)
	return false;
	if (r.felicidad > 100)
	return false;
	if (r.energia > 100)
	return false;
	if (r.horas_sueno > 24)
	return false;
    	if (r.aguacate > 1)
	return false;
    	return true;
}

void agregarRegistro(registro*& arr, int& n, const registro& nuevo) {
    	registro* nuevoArr = new registro[n + 1];
    	for (int i = 0; i < n; ++i){
        	nuevoArr[i] = arr[i];
	}
    	nuevoArr[n] = nuevo;
   	delete[] arr;
    	arr = nuevoArr;
    	n++;
}

bool cargarBD(const string& ruta, registro*& arr, int& n) {
    	ifstream in(ruta, ios::binary);
    	if (!in)
	return false;

    	uint32_t N;
    	if (!in.read(reinterpret_cast<char*>(&N), sizeof(N)))
	return false;

    	arr = new registro[N];
    	n = 0;

    	for (uint32_t i = 0; i < N; ++i) {
        	uint16_t len;
        	if (!in.read(reinterpret_cast<char*>(&len), sizeof(len)) || len > 200)
            	return false;

        	string nombre(len, '\0');
        	if (!in.read(&nombre[0], len)) return false;

        	registro r;
        	r.nombre = nombre;

       		if (!in.read(reinterpret_cast<char*>(&r.emocion), 1))
		return false;
        	if (!in.read(reinterpret_cast<char*>(&r.felicidad), 1))
		return false;
        	if (!in.read(reinterpret_cast<char*>(&r.energia), 1))
		return false;
        	if (!in.read(reinterpret_cast<char*>(&r.horas_sueno), 1))
		return false;
        	if (!in.read(reinterpret_cast<char*>(&r.aguacate), 1))
		return false;

        	if (!validarRegistro(r))
		return false;

        	arr[n++] = r;
    	}
    	return true;
}

bool guardarBD(const string& ruta, registro* arr, int n) {
    	ofstream out(ruta, ios::binary | ios::trunc);
    	if (!out) return false;

    	uint32_t N = n;
    	out.write(reinterpret_cast<char*>(&N), sizeof(N));

    	for (int i = 0; i < n; ++i) {
        	uint16_t len = arr[i].nombre.size();
        	out.write(reinterpret_cast<char*>(&len), sizeof(len));
        	out.write(arr[i].nombre.c_str(), len);

        	out.write(reinterpret_cast<char*>(&arr[i].emocion), 1);
        	out.write(reinterpret_cast<char*>(&arr[i].felicidad), 1);
        	out.write(reinterpret_cast<char*>(&arr[i].energia), 1);
        	out.write(reinterpret_cast<char*>(&arr[i].horas_sueno), 1);
        	out.write(reinterpret_cast<char*>(&arr[i].aguacate), 1);
    	}
    	return true;
}

registro* buscarPorNombre(registro* arr, int n, const string& nombre) {
    	for (int i = 0; i < n; ++i){
        	if (arr[i].nombre == nombre)
            	return &arr[i];
	}
    	return nullptr;
}

int nivelAndoriano(const registro& r) {
   	 int base = (r.felicidad + r.energia) / 2;
    	base += (r.horas_sueno >= 7) ? 10 : -10;
    	if (base < 0) base = 0;
    	if (base > 100) base = 100;
    	return base;
}

double promedioUltimosK(registro* arr, int n, int k) {
    	if (k > n) k = n;
    	int suma = 0;
    	for (int i = n - k; i < n; ++i){
        	suma += nivelAndoriano(arr[i]);
	}
    	return static_cast<double>(suma) / k;
}

