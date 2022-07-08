/*
Tomas Diaz Servin A01637531
Isaac Husny Tuachi A01027140

19/11/2020

Cuarto avance de reto. Programa implementado para leer y ordenar datos de un archivo Equipo1.csv y realizar manipulacion de los datos dentro de el.
Ademas implementa el uso de Arboles BST para tener mejor ordenamiento de datos.

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
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

/*
    1.
    Contenga una función llamada conexionesPorDia, la cual reciba una fecha(puede ser string,
    int o un objeto que hayas definido tu en la primera etapa del reto). 
    Dicha función debe regresar un  las conexiones entrantes a cada sitio/página que no sea "-" y que no pertenezca al dominio "reto.com" de ese día. 
    Se puede regresar un unordered_map o map >string, int>, donde el string es el sitio y el int sea la cantidad de conexiones entrantes.

*/
map<string, int> F;
auto conexionesPorDia(string fecha) {
    F.clear();
    unordered_map<string, ConexionesComputadora> B;
    for (Record r : conexiones) {
        if (fecha == r.fecha) {
            if (r.ipDestino != "-") {
                if (B.find(r.ipDestino) == B.end()) {
                    ConexionesComputadora a(r.ipDestino, r.nombreDestino);
                    B.insert({ r.ipDestino, a });
                }
                B[r.ipDestino].nuevaEntrante(r.puertoDestino, r.ipDestino, r.nombreDestino);
            }

        }
    }

    for (auto zone : B) {
        int contado = 0;
        if (zone.second.nombre.find("reto.com") == string::npos) {
            if ((zone.second.nombre.find("-") == string::npos)) {
                F.insert({ zone.second.nombre, zone.second.entrantes.size() });
            }
        }
    }

    return F;
}

template <class T, class L>
class Nodo {
public:
    T value;
    L key;
    Nodo<T, L>* izq;
    Nodo<T, L>* der;

    Nodo() {
        value = NULL;
        key = NULL;
        izq = NULL;
        der = NULL;
    }

    Nodo(T val,L k) {
        key = k;
        value = val;
        izq = NULL;
        der = NULL;
    }
};

template <class T, class L>
class BST {
public:
    int contador;
    Nodo<T, L>* root;

    BST() {
        root = NULL;
    }


 
    void reverse(int contador) {
        this->contador = contador;
        reverse(root);
        cout << endl;
    }


    void reverse(Nodo<T, L>* temp) {
        if (temp != NULL && contador > 0) {
            contador--;
            reverse(temp->der);
            cout << temp->key << endl;
            cout << temp->value << endl;
            cout << " " << endl;
            reverse(temp->izq);
        }
    }

    void insertar(T value, L key) {
        Nodo<T, L>* nuevo = new Nodo<T, L>(value, key);
        if (root == NULL) {
            root = nuevo;
        }
        else {
            insertar(nuevo, root);
        }
    }

    void insertar(Nodo<T, L>* nuevo, Nodo<T, L>* temp) {
        if (nuevo->value == temp->value) {	//si el valor es igual, terminamos
            return;
        }
        else if (nuevo->value < temp->value) {//si el valor es menor que el valor de temp
            if (temp->izq == NULL) {//si el izquierdo es nulo, ahi agregamos
                temp->izq = nuevo;
            }
            else {
                insertar(nuevo, temp->izq);//sino, temp=temp->izq
            }
        }
        else {//si el valor es mayor que el valor de temp
            if (temp->der == NULL) {	//si el derecho es nulo, ahi agregamos
                temp->der = nuevo;
            }
            else {
                insertar(nuevo, temp->der);//sino, temp=temp->der
            }
        }
    }
};
/*
    2.
    Contiene una función llamada top, la cual recibe un parámetro n de tipo int y una fecha. 
    Esta función debe imprimir los n sitios con más accesos en esa fecha. Para ello,
    puedes usar la función conexionesPorDia y debes agregar los sitios a un BST utilizando 
    como parámetro de ordenamiento la cantidad de conexiones entrantes.

*/
void top(int n, string fecha) {
    conexionesPorDia(fecha);
    BST<int, string> tree;

    for (auto bots : F) {
        tree.insertar(bots.second, bots.first);
    };

    tree.reverse(n);

};


int main() {
   leerDatos("/mnt/c/Users/Tomas/OneDrive/Escritorio/Semestre 3 2020/Semana 10-15/nuevo1.csv");
   /*
    Utiliza estas funciones para imprimir por cada día de las bitácoras el top 5. 
   */

   cout << "10-8-2020" << endl;
   top(5, "10-8-2020");
   cout << "*******************************" << endl;
   cout << "11-8-2020" << endl;
   top(5, "11-8-2020");
   cout << "*******************************" << endl;
   cout << "12-8-2020" << endl;
   top(5, "12-8-2020");
   cout << "*******************************" << endl;
   cout << "13-8-2020" << endl;
   top(5, "13-8-2020");
   cout << "*******************************" << endl;
   cout << "14-8-2020" << endl;
   top(5, "14-8-2020");
   cout << "*******************************" << endl;
   cout << "15-8-2020" << endl;
   top(5, "15-8-2020");
   cout << "*******************************" << endl;
   cout << "16-8-2020" << endl;
   top(5, "16-8-2020");
   cout << "*******************************" << endl;
   cout << "17-8-2020" << endl;
   top(5, "17-8-2020");
   cout << "*******************************" << endl;
   cout << "18-8-2020" << endl;
   top(5, "18-8-2020");
   cout << "*******************************" << endl;
   cout << "19-8-2020" << endl;
   top(5, "19-8-2020");
   cout << "*******************************" << endl;
   cout << "20-8-2020" << endl;
   top(5, "20-8-2020");
   cout << "*******************************" << endl;
   cout << "21-8-2020" << endl;
   top(5, "21-8-2020");
   cout << "*******************************" << endl;




    return 0;
}

