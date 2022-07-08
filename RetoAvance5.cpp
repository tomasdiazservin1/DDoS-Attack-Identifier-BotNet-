/*
Tomas Diaz Servin A01637531
Isaac Husny Tuachi A01027140

24/11/2020

Quinto avance de reto. Programa implementado para leer y ordenar datos de un archivo Nuevo1.csv y realizar manipulacion de los datos dentro de el.
Ademas implementa el uso de estructuras de datos como Grafos, listas, vectores y diccionarios para tener mejor ordenamiento de datos.

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;
class Record {
public:
    string fecha;
    string hora;
    string ipFuente;
    string puertoFuente;
    string nombreFuente;
    string ipDestino;
    string puertoDestino;
    string nombreDestino;

    Record(string f, string h, string ipF, string pF, string nF, string ipD, string pD, string nD) {
        fecha = f;
        hora = h;
        ipFuente = ipF;
        puertoFuente = pF;
        nombreFuente = nF;
        ipDestino = ipD;
        puertoDestino = pD;
        nombreDestino = nD;

    }
};

vector<Record> conexiones;
void leerDatos(string path) {
    ifstream fileIn;
    fileIn.open(path);
    string line, partes;
    vector<string> valores;
    while (fileIn.good()) {
        getline(fileIn, line);
        istringstream sIn(line);
        while (getline(sIn, partes, ',')) {
            valores.push_back(partes);
        }
        if (valores[7].find('\r') != valores[7].npos) {
            Record r(valores[0], valores[1], valores[2], valores[3], valores[4], valores[5], valores[6], valores[7].substr(0, valores[7].size() - 1));
        }

        Record r(valores[0], valores[1], valores[2], valores[3], valores[4], valores[5], valores[6], valores[7]); //Aqui cambio para incorporar todos los v alores
        conexiones.push_back(r);
        valores.clear();
    }
}





class infoConexion {
public:
    string puertoRemoto;
    string ipRemota;
    string nombreRemoto;

    infoConexion(string pR, string ipR, string nR) {
        puertoRemoto = pR;
        ipRemota = ipR;
        nombreRemoto = nR;
    }
};


class ConexionesComputadora {
public:
    string nombre;
    string iP;
    list<infoConexion> entrantes;
    list<infoConexion> salientes;
    ConexionesComputadora() {

    }

    ConexionesComputadora(string ip, string nombre) {
        this->iP = ip;
        this->nombre = nombre;
    }

    void nuevaEntrante(string puerto, string ip, string nombre) {
        infoConexion a(puerto, ip, nombre);
        entrantes.push_back(a);
    }

    void nuevaSaliente(string puerto, string ip, string nombre) {
        infoConexion a(puerto, ip, nombre);
        salientes.push_back(a);
    }
};


template <class T>
class Nodo {
public:
	T value;
	unordered_map<Nodo<T>*, int> siguientes;

	Nodo(T val) {
		value = val;
	}

	void agregarArcoDirigidoConPeso(Nodo<T>* sig, int peso) {
		if (siguientes.find(sig) == siguientes.end()) {
			siguientes[sig] = peso;
		}
	}

	void agregarArcoDirigido(Nodo<T>* sig) {
		agregarArcoDirigidoConPeso(sig, 1);
	}
};


template <class T>
class Graph {
public:
    unordered_map<T, Nodo<T>*> nodos;
	void agregarNodo(T value) {
		if (nodos.find(value) == nodos.end()) {
			Nodo<T>* nuevo = new Nodo<T>(value);
			nodos[value] = nuevo;
		}
	}

    void agregarArcoDirigidoConPeso(T nodo1, T nodo2, int peso) {
        if (nodos.find(nodo1) != nodos.end() && nodos.find(nodo2) != nodos.end()) {
            nodos[nodo1]->agregarArcoDirigidoConPeso(nodos[nodo2], peso);
        }
    }


    void agregarArcoDirigido(T nodo1, T nodo2) {
        agregarArcoDirigidoConPeso(nodo1, nodo2, 1);
    }

    int contarSiguente(T value) {
        int contador = 0;
        for (auto zone : nodos) {
            for (auto bots : zone.second->siguientes)
                if (bots.first->value.find(value) == string::npos) {
                    contador++;
                }
        }
        return contador;
    }
    int contarSiguente2(T value) {
        int contador = 0;
        for (auto zone : nodos) {
            for (auto bots : zone.second->siguientes)
                if (bots.first->value.find(value) != string::npos) {
                    contador++;
                }
        }
        return contador;
    }

};


int main() {
    leerDatos("/mnt/c/Users/Tomas/OneDrive/Escritorio/Semestre 3 2020/Semana 10-15/nuevo1.csv");
    Graph<string> red1;
    Graph<string> red2;
    string a = "172.31.90.47";
    string b = "110.174.125.114";
    string c = "68.120.112.100";

    string fecha = "21-8-2020";

    // 1. Utilizando un grafo con las conexiones entre las ip de la red interna, determina la cantidad de computadoras con las que se ha conectado A por día.

    
    for (Record r : conexiones) {
        if (fecha == r.fecha) {
            if (r.ipFuente.find("172.31.90.") != string::npos && r.ipDestino.find("172.31.90.") != string::npos) {
                red1.agregarNodo(r.ipFuente);
                red1.agregarNodo(r.ipDestino);
                red1.agregarArcoDirigido(r.ipFuente, r.ipDestino);
            }
        }
    }

    cout << "Numero de computadoras con las que se ha conectado A: " <<red1.contarSiguente(a) << endl;

   // 2. Utilizando el grafo del punto anterior, ubica la cantidad de computadoras que se han conectado hacía A por día. 
   
    cout << "Numero de computadoras que se conectaron hacia A: " << red1.contarSiguente2(a) << endl;
   
    
    
    //3. Utilizando un grafo de conexiones a sitios web, determina cuántas computadoras se han conectado a B por día

    for (Record r : conexiones) {
        if (fecha == r.fecha) {
            if (r.nombreDestino.find(".reto.com") == string::npos) {
                red2.agregarNodo(r.ipFuente);
                red2.agregarNodo(r.ipDestino);
                red2.agregarArcoDirigido(r.ipFuente, r.ipDestino);
            }
        }
    }
    
    cout << "Numero de computadoras que se conectaron hacia B: " << red2.contarSiguente2(b) << endl;
    
    // 4. Utilizando el mismo grafo del punto anterior, indica cuántas computadoras se han conectado a C por día.

    cout << "Numero de computadoras que se conectaron hacia C: " << red2.contarSiguente2(c) << endl;


    return 0;
}