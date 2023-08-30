#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "metodos.h"

using namespace std;

// Función para convertir el texto en una lista de palabras
vector<string> dividirTexto(const string& texto) {
    vector<string> palabras;
    istringstream iss(texto);
    string palabra;
    
    while (iss >> palabra) {
        // Limpieza básica para eliminar signos de puntuación
        palabra.erase(remove_if(palabra.begin(), palabra.end(), ::ispunct), palabra.end());
        palabras.push_back(palabra);
    }
    
    return palabras;
}

// Función de bucket sort para ordenar las palabras por frecuencia
void ordenarPorFrecuencia(vector<pair<string, int>>& paresPalabraFrecuencia) {
    const int numBuckets = 10; // Puedes ajustar el número de buckets según tu preferencia
    
    vector<vector<pair<string, int>>> buckets(numBuckets);
    
    for (const auto& par : paresPalabraFrecuencia) {
        int indiceBucket = min(par.second / numBuckets, numBuckets - 1);
        buckets[indiceBucket].push_back(par);
    }
    
    paresPalabraFrecuencia.clear();
    
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
        
        for (const auto& par : bucket) {
            paresPalabraFrecuencia.push_back(par);
        }
    }
}

void procesarArchivo(const string & i, const string & o) {
    string rutaArchivoEntrada = i; // Actualiza con la ruta correcta
    string rutaArchivoSalida = o; // Actualiza con la ruta correcta
    
    ifstream archivoEntrada(rutaArchivoEntrada);
    if (!archivoEntrada.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return;
    }
    
    unordered_map<string, int> mapaFrecuenciaPalabra;
    string linea;
    
    // Leer el archivo línea por línea y contar las palabras
    while (getline(archivoEntrada, linea)) {
        vector<string> palabras = dividirTexto(linea);
        for (const string& palabra : palabras) {
            mapaFrecuenciaPalabra[palabra]++;
        }
    }
    
    archivoEntrada.close();
    
    // Crear una lista de pares (palabra, frecuencia)
    vector<pair<string, int>> paresPalabraFrecuencia;
    for (const auto& entrada : mapaFrecuenciaPalabra) {
        paresPalabraFrecuencia.push_back(entrada);
    }
    
    // Ordenar la lista de pares usando bucket sort
    ordenarPorFrecuencia(paresPalabraFrecuencia);
    
    // Escribir los resultados en el archivo de salida
    ofstream archivoSalida(rutaArchivoSalida);
    if (!archivoSalida.is_open()) {
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return;
    }
    
    for (const auto& par : paresPalabraFrecuencia) {
        archivoSalida << par.first << ", " << par.second << endl;
    }
    
    archivoSalida.close();
    
    cout << "Proceso completado. Los resultados se han guardado en el archivo de salida." << endl;
    
    return;
}
