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
             << "./bitacora add <archivo.bd> --nombre <n> --emocion <feliz|triste|neutral|ansioso> "
             << "--felicidad <0..100> --energia <0..100> --sueno <0..24> --aguacate <S|N>\n"
             << "./bitacora list <archivo.bd>\n"
             << "./bitacora find <archivo.bd> --nombre <n>\n"
             << "./bitacora stats <archivo.bd> --k <entero>\n\n"
             << "Ejemplos:\n"
             << "./bitacora init bitacora.bd\n"
             << "./bitacora add bitacora.bd --nombre \"Ana\" --emocion feliz --felicidad 80 --energia 75 --sueno 8 --aguacate S\n"
             << "./bitacora stats bitacora.bd --k 7\n";
        return 0;
    }

    if (argc < 3) {
        cout << "ERROR: falta archivo BD\n";
        return 1;
    }

    string ruta = argv[2];
    registro* arr = nullptr;
    int n = 0;

    // Comando INIT
    if (comando == "init") {
        ifstream test(ruta);
        if (test) {
            test.close();
            cout << "BD ya existe: " << ruta << " (no se modificó)\n";
            return 0;
        }
        ofstream out(ruta, ios::binary);
        if (!out) {
            cout << "ERROR: no se pudo crear la BD\n";
            return 1;
        }
        uint32_t cero = 0;
        out.write(reinterpret_cast<char*>(&cero), sizeof(cero));
        out.close();
        cout << "BD creada: " << ruta << " (N=0)\n";
        return 0;
    }

    // Para todos los demás comandos, cargar BD
    if (!cargarBD(ruta, arr, n)) {
        cout << "ERROR: BD no existe o está corrupta. Usa: ./bitacora init " << ruta << "\n";
        return 1;
    }

    // Comando LIST
    if (comando == "list") {
        if (n == 0) {
            cout << "BD vacía\n";
        } else {
            cout << "Bitácora Andoriana — " << n << " registro(s)\n";
            for (int i = 0; i < n; ++i) {
                string emocionStr;
                switch(arr[i].emocion) {
                    case 0: emocionStr = "feliz"; break;
                    case 1: emocionStr = "triste"; break;
                    case 2: emocionStr = "neutral"; break;
                    case 3: emocionStr = "ansioso"; break;
                    default: emocionStr = "???"; break;
                }
                cout << "[" << i << "] " << arr[i].nombre 
                     << " | " << emocionStr
                     << " | F=" << (int)arr[i].felicidad
                     << " E=" << (int)arr[i].energia
                     << " | sueño=" << (int)arr[i].horas_sueno
                     << " | aguacate=" << (arr[i].aguacate ? "S" : "N") << "\n";
            }
        }
        delete[] arr;
        return 0;
    }

    // Comando ADD
    if (comando == "add") {
        registro nuevo;
        nuevo.emocion = 255;  // valor inválido por defecto
        nuevo.felicidad = 255;
        nuevo.energia = 255;
        nuevo.horas_sueno = 255;
        nuevo.aguacate = 255;
        
        // Parsear argumentos
        for (int i = 3; i < argc; i += 2) {
            if (i + 1 >= argc) {
                cout << "ERROR: falta valor para " << argv[i] << "\n";
                delete[] arr;
                return 1;
            }
            
            string param = argv[i];
            string valor = argv[i + 1];
            
            if (param == "--nombre") {
                if (valor.length() > 200) {
                    cout << "ERROR: nombre muy largo (máx 200 caracteres)\n";
                    delete[] arr;
                    return 1;
                }
                nuevo.nombre = valor;
            }
            else if (param == "--emocion") {
                if (valor == "feliz") nuevo.emocion = 0;
                else if (valor == "triste") nuevo.emocion = 1;
                else if (valor == "neutral") nuevo.emocion = 2;
                else if (valor == "ansioso") nuevo.emocion = 3;
                else {
                    cout << "ERROR: emocion inválida (usa: feliz/triste/neutral/ansioso)\n";
                    delete[] arr;
                    return 1;
                }
            }
            else if (param == "--felicidad") {
                int val = atoi(valor.c_str());
                if (val < 0 || val > 100) {
                    cout << "ERROR: felicidad fuera de rango (0..100)\n";
                    delete[] arr;
                    return 1;
                }
                nuevo.felicidad = val;
            }
            else if (param == "--energia") {
                int val = atoi(valor.c_str());
                if (val < 0 || val > 100) {
                    cout << "ERROR: energia fuera de rango (0..100)\n";
                    delete[] arr;
                    return 1;
                }
                nuevo.energia = val;
            }
            else if (param == "--sueno") {
                int val = atoi(valor.c_str());
                if (val < 0 || val > 24) {
                    cout << "ERROR: horas_sueno fuera de rango (0..24)\n";
                    delete[] arr;
                    return 1;
                }
                nuevo.horas_sueno = val;
            }
            else if (param == "--aguacate") {
                if (valor == "S" || valor == "s") nuevo.aguacate = 1;
                else if (valor == "N" || valor == "n") nuevo.aguacate = 0;
                else {
                    cout << "ERROR: aguacate inválido (usa: S o N)\n";
                    delete[] arr;
                    return 1;
                }
            }
            else {
                cout << "ERROR: parámetro desconocido: " << param << "\n";
                delete[] arr;
                return 1;
            }
        }
        
        // Validar que todos los campos estén completos
        if (nuevo.nombre.empty() || nuevo.emocion == 255 || nuevo.felicidad == 255 ||
            nuevo.energia == 255 || nuevo.horas_sueno == 255 || nuevo.aguacate == 255) {
            cout << "ERROR: faltan parámetros obligatorios\n";
            cout << "Usa: ./bitacora help\n";
            delete[] arr;
            return 1;
        }
        
        if (!validarRegistro(nuevo)) {
            cout << "ERROR: registro inválido después de validación\n";
            delete[] arr;
            return 1;
        }
        
        agregarRegistro(arr, n, nuevo);
        
        if (!guardarBD(ruta, arr, n)) {
            cout << "ERROR: no se pudo guardar la BD\n";
            delete[] arr;
            return 1;
        }
        
        cout << "Registro agregado. Total registros: " << n << "\n";
        delete[] arr;
        return 0;
    }

    // Comando FIND
    if (comando == "find") {
        if (argc < 5 || string(argv[3]) != "--nombre") {
            cout << "ERROR: usa --nombre <nombre>\n";
            delete[] arr;
            return 1;
        }
        
        string nombreBuscar = argv[4];
        registro* encontrado = buscarPorNombre(arr, n, nombreBuscar);
        
        if (encontrado == nullptr) {
            cout << "No encontrado\n";
        } else {
            int idx = encontrado - arr;  // calcular índice
            string emocionStr;
            switch(encontrado->emocion) {
                case 0: emocionStr = "feliz"; break;
                case 1: emocionStr = "triste"; break;
                case 2: emocionStr = "neutral"; break;
                case 3: emocionStr = "ansioso"; break;
                default: emocionStr = "???"; break;
            }
            cout << "Encontrado:\n";
            cout << "[" << idx << "] " << encontrado->nombre 
                 << " | " << emocionStr
                 << " | F=" << (int)encontrado->felicidad
                 << " E=" << (int)encontrado->energia
                 << " | sueño=" << (int)encontrado->horas_sueno
                 << " | aguacate=" << (encontrado->aguacate ? "S" : "N") << "\n";
        }
        delete[] arr;
        return 0;
    }

    // Comando STATS
    if (comando == "stats") {
        if (argc < 5 || string(argv[3]) != "--k") {
            cout << "ERROR: usa --k <entero>\n";
            delete[] arr;
            return 1;
        }
        
        int k = atoi(argv[4]);
        if (k <= 0) {
            cout << "ERROR: k debe ser >0\n";
            delete[] arr;
            return 1;
        }
        
        if (n == 0) {
            cout << "BD vacía\n";
            delete[] arr;
            return 0;
        }
        
        int k_usado = (k > n) ? n : k;
        double promedio = promedioUltimosK(arr, n, k);
        
        cout << "Stats Andorianas\n";
        cout << "Registros disponibles: " << n << "\n";
        cout << "K solicitado: " << k;
        if (k > n) {
            cout << " (se usarán " << n << ")\n";
        } else {
            cout << "\n";
        }
        cout << "Promedio nivel andoriano (últimos " << k_usado << "): " << promedio << "\n";
        
        delete[] arr;
        return 0;
    }

    // Comando desconocido
    cout << "ERROR: comando desconocido: " << comando << "\n";
    cout << "Usa: ./bitacora help\n";
    delete[] arr;
    return 1;
}
