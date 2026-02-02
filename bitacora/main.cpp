/********************************
*Fecha: 2 de febrero 2026       *
*Autor: Santiago Camargo        *
*Tema: Taller 0/ Bitacora       *
*Estructuras de datos           *
********************************/
#include "bitacora.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usa: ./bitacora help\n";
        return 1;
    }

    string comando = argv[1];

    if (comando == "help") {
        cout << "Uso:\n"
	<< "./bitacora init <archivo.bd>\n"
	<< "./bitacora add <archivo.bd> --nombre <n> --emocion <feliz|triste|neutral|ansioso>\n"
	<< "./bitacora list <archivo.bd>\n"
	<< "./bitacora find <archivo.bd> --nombre <n>\n"
	<< "./bitacora stats <archivo.bd> --k <entero>\n";
        return 0;
    }

    if (argc < 3) {
        cout << "ERROR: falta archivo BD\n";
       	return 1;
    }

    string ruta = argv[2];
    registro* arr = nullptr;
    int n = 0;

    if (comando == "init") {
       	ifstream test(ruta);
       	if (test) {
            	cout << "BD ya existe\n";
            	return 0;
        }
        ofstream out(ruta, ios::binary);
        uint32_t cero = 0;
        out.write(reinterpret_cast<char*>(&cero), sizeof(cero));
        cout << "BD creada\n";
        return 0;
    }

    if (!cargarBD(ruta, arr, n)) {
        cout << "ERROR: BD corrupta o inexistente\n";
        return 1;
    }

    if (comando == "list") {
	if (n == 0) {
            cout << "BD vacía\n";
        }
        for (int i = 0; i < n; ++i) {
		cout << "[" << i << "] " << arr[i].nombre
		<< " F=" << (int)arr[i].felicidad
		<< " E=" << (int)arr[i].energia << "\n";
        }
    }

    delete[] arr;
    return 0;
}
