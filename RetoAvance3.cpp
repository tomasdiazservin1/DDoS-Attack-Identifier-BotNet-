/*
Tomas Diaz Servin A01637531
Isaac Husny Tuachi A01027140

08/11/2020

Tercer avance de reto. Programa implementado para leer y ordenar datos de un archivo Nuevo1.csv y realizar manipulacion de los datos dentro de el.
Ademas agrega nuevas estrucuras como diccionarios y conjuntos para el almazenamineto de datos filtrados.

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Record{
public:
    string fecha;
    string hora;
    string ipFuente;
    string puertoFuente;
    string nombreFuente;
    string ipDestino;
    string puertoDestino;
    string nombreDestino;

    Record(string f, string h, string ipF, string pF, string nF, string ipD, string pD, string nD){
        fecha=f;
        hora=h;
        ipFuente=ipF;
        puertoFuente=pF;
        nombreFuente=nF;
        ipDestino=ipD;
        puertoDestino=pD;
        nombreDestino=nD;

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
    vector<infoConexion> entrantes;
    vector<infoConexion> salientes;
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


int main(){
    leerDatos("/mnt/c/Users/Tomas/OneDrive/Escritorio/Semestre 3 2020/nuevo1.csv");
    cout<<"Datos leidos"<<endl;
    cout << conexiones.size() << endl;
    unordered_set<string> A;
    unordered_map<string, ConexionesComputadora> B; //Saliente
    unordered_map<string, ConexionesComputadora> C; //Entrante

    // 2a.Diccionarios para conexicones SALIENTES y ENTRANTES separados para los incisos 1-5
    for (Record r : conexiones) {
        if (r.ipDestino != "-") {
            if (B.find(r.ipDestino) == B.end()) {
                ConexionesComputadora a(r.ipDestino, r.nombreDestino);
                B.insert({ r.ipDestino, a });
            }
            B[r.ipFuente].nuevaSaliente(r.puertoDestino, r.ipDestino, r.nombreDestino);



        }
    }

    for (Record r : conexiones) {
        if (r.ipFuente != "-") {
            if (C.find(r.ipFuente) == C.end()) {
                ConexionesComputadora a(r.ipFuente, r.nombreFuente);
                C.insert({ r.ipFuente, a });
            }
            C[r.ipFuente].nuevaEntrante(r.puertoFuente, r.ipFuente, r.nombreFuente);

        }
    }

    // 1a. Conjunto para conexiones que no llevan .reto.com en el dominio
    for (auto set: B) {
        if (set.second.nombre.find(".reto.com") == string::npos) {
            A.insert(set.second.nombre);
        }
    }





    // 1. Hay alguna nombre de dominio que sea anómalo (Esto puede ser con inspección visual.


    for (auto i : B) {
        cout << i.first << " : " << i.second.nombre << endl;
    }


    // 2. Del los nombres de dominio encontrados en el paso anterior, ¿cuál es su ip? ¿Cómo determinarías esta información de la manera más óptima en complejidad temporal?

    for (auto i : B) {
        if (i.second.nombre.find("916t95wtls6d3sie7ew6.net") != string::npos) {
            cout << "Domain: "<< i.second.nombre << endl;
            cout << "IP: " << i.first << endl;
        }
    }

    for (auto i : B) {
        if (i.second.nombre.find("88e9sl86u11nflsir86x.xxx") != string::npos) {
            cout << "Domain: " << i.second.nombre << endl;
            cout << "IP: " << i.first << endl;
        }
    }


    // 3. De las computadoras pertenecientes al dominio reto.com determina la cantidad de ips que tienen al menos una conexión entrante.
    //(Recuerda que ya tienes la dirección de la red y el último octeto puede tener computadoras del .1 al .254. Imprime la cantidad de computadoras.

    int computers = 0;
    for (auto i : C) {
        if (i.second.nombre.find(".reto.com") != string::npos) {
            cout << i.second.nombre << " : " << i.first << endl;
            computers++;
        }
    }

    cout << "Computadoras que tienen por lo menos una entrada: "<< computers << endl;



    // 4. Toma algunas computadoras internas que no sean server.reto.com o el servidor dhcp. Obten las ip unicas de las conexiones entrantes.


    for (auto au : C) {
        cout << au.first << " : " << " : " << au.second.nombre << endl;
    }


    //6. Para las ips encontradas en el paso anterior, determina si se han comunicado con los datos encontrados en la pregunta 1.


    unordered_map<string, ConexionesComputadora> E;
    for (Record r : conexiones) {
        if (r.ipFuente != "-") {
            if (E.find(r.ipFuente) == E.end()) {
                ConexionesComputadora a(r.ipFuente, r.nombreFuente);
                E.insert({ r.ipFuente, a });
            }
            E[r.ipFuente].nuevaSaliente(r.puertoDestino, r.ipDestino, r.nombreDestino);



        }
    }

    for (auto sal : E) {
        for (int tad = 0; tad < sal.second.salientes.size(); tad++) {
            if (sal.second.salientes[tad].ipRemota.find("110.174.125.114") != string::npos) {

                    cout << sal.second.nombre << " se conecto a 916t95wtls6d3sie7ew6.net." << endl;
            }
        }
    }

    for (auto sal : E) {
        for (int tad = 0; tad < sal.second.salientes.size(); tad++) {
            if (sal.second.salientes[tad].ipRemota.find("1.136.108.6") != string::npos) {

                cout << sal.second.nombre << " se conecto a 88e9sl86u11nflsir86x.xxx." << endl;
            }
        }
    }









    return 0;
}