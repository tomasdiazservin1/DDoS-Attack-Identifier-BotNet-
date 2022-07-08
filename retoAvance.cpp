/*
Tomas Diaz Servin A01637531
Isaac Husny Tuachi A01027140

28/09/2020

Primer avance de reto. Programa implementado para leer y ordenar datos de un archivo Equipo1.csv y realizar manipulacion de los datos dentro de el.

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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


    void imprimirRecord(){
        cout<<fecha<<endl;
    }
};

vector<Record> conexiones;
void leerDatos(string path){
    ifstream fileIn;
    fileIn.open(path);
    string line, partes;
    vector<string> valores;
    while(fileIn.good()){
        getline(fileIn, line);
        istringstream sIn(line);
        while(getline(sIn, partes, ',')){
            valores.push_back(partes);
        }
        if(valores[7].find('\r')!=valores[7].npos){
            Record r(valores[0], valores[1], valores[2], valores[3], valores[4], valores[5], valores[6], valores[7].substr(0, valores[7].size()-1));
        }

        Record r(valores[0], valores[1], valores[2], valores[3], valores[4], valores[5], valores[6], valores[7]); //Aqui cambio para incorporar todos los v alores
        conexiones.push_back(r);
        valores.clear();
    }
}

int compararPorFecha(Record a, Record b){
    if(a.fecha<b.fecha){
        return -1;
    }else if (a.fecha==b.fecha){
        return 0;
    }else{
        return 1;
    }
}

int compararPorHora(Record a, Record b){
    if(a.hora<b.hora){
        return -1;
    }else if (a.hora==b.hora){
        return 0;
    }else{
        return 1;
    }
}

int compararPoripFuente(Record a, Record b){
    if(a.ipFuente<b.ipFuente){
        return -1;
    }else if (a.ipFuente==b.ipFuente){
        return 0;
    }else{
        return 1;
    }
}

int compararPorPuertoFuente(Record a, Record b){
    if(a.puertoFuente<b.puertoFuente){
        return -1;
    }else if (a.puertoFuente==b.puertoFuente){
        return 0;
    }else{
        return 1;
    }
}

int compararPorNombreFuente(Record a, Record b){
    if(a.nombreFuente<b.nombreFuente){
        return -1;
    }else if (a.nombreFuente==b.nombreFuente){
        return 0;
    }else{
        return 1;
    }
}

int compararPoripDestino(Record a, Record b){
    if(a.ipDestino<b.ipDestino){
        return -1;
    }else if (a.ipDestino==b.ipDestino){
        return 0;
    }else{
        return 1;
    }
}
int compararPorPuertoDestino(Record a, Record b){
    if(a.puertoDestino<b.puertoDestino){
        return -1;
    }else if (a.puertoDestino==b.puertoDestino){
        return 0;
    }else{
        return 1;
    }
}

int compararPorNombreDestino(Record a, Record b){
    if(a.nombreDestino<b.nombreDestino){
        return -1;
    }else if (a.nombreDestino==b.nombreDestino){
        return 0;
    }else{
        return 1;
    }
}

template <class T>
class Sort{
	public:
	virtual void sort(vector<T> &data,  int comparador(T a, T b))=0;
	void intercambiar(vector<T> &data, int posI, int posJ){
		T temp=data[posI];
		data[posI]=data[posJ];
		data[posJ]=temp;
	}
	
	void imprimir(vector<T> data){
		for(int i=0; i<data.size(); i++){
			cout<<data[i]<<",";
		}
		cout<<endl;
	}
};

template <class T>
class MergeSort: public Sort<T>{
	
	public:
	void sort(vector<T> &data,  int comparador(T a, T b)){
		sortAux(data, 0, data.size()-1, comparador);
	}
	private:
	void sortAux(vector<T> &data, int lo, int hi,  int comparador(T a, T b)){
		if(lo>=hi){
			return;
		}
		int mid=(lo+hi)/2;
		sortAux(data, lo, mid, comparador);
		sortAux(data, mid+1, hi, comparador);
		merge(data, lo, mid, hi, comparador);
	}
	
	
	
	void merge(vector<T> &data, int low, int mid, int hi, int comparador(T a, T b)){
	int sizeA=mid-low+1;
	int sizeB=hi-mid;
	vector<T> copiaA;
	vector<T> copiaB;
	
	for(int i=0; i<sizeA; i++){
		copiaA.push_back(data[low+i]);
	}
	
	for(int i=0; i<sizeB; i++){
		copiaB.push_back(data[mid+i+1]);
	}
	
	int indexA=0;
	int indexB=0;
	int indexData=low;
	while(indexA<sizeA&&indexB<sizeB){
		//if(copiaA[indexA]<copiaB[indexB]){
        if(comparador(copiaA[indexA],copiaB[indexB])<0){
			data[indexData]=copiaA[indexA];
			indexA++;
		}else{
			data[indexData]=copiaB[indexB];
			indexB++;
		}
		indexData++;
    }
	
	
	while(indexA<sizeA){
		data[indexData]=copiaA[indexA];
		indexA++;
		indexData++;
	}
	
	while(indexB<sizeB){
		data[indexData]=copiaB[indexB];
		indexB++;
		indexData++;
	}
}
	
};

template <class T>
int busquedaBinaria(vector<T> elementos, T buscado, int comparador(T a, T b)){
	int inicio=0;
	int fin=elementos.size()-1;
	while(fin>=inicio){
		int medio=(inicio+fin)/2;
		if(comparador(elementos[medio], buscado)==0){
			return medio;
		}else if(comparador(buscado, elementos[medio])>0){
			inicio=medio+1;
		}else{
			fin=medio-1;
		}
	}
	return -1;
}


  
int main(){
    leerDatos("/mnt/c/Users/Tomas/OneDrive/Escritorio/Semestre 3 2020/Semana 5-10/TC1031.100/equipo 1.csv");
    cout<<"Datos leidos"<<endl;
    MergeSort<Record> s;
    cout<<"Datos Ordenados"<<endl;

    /*
    int pos=busquedaBinaria(conexiones, r, compararPorNombreFuente);

    if (pos != -1){
        cout << "encontrado" << endl;
    }
    */
    
    /*
    Pregunta 1.
    cout<<"Numero de Datos"<< conexiones.size()<< endl;
    
    */

     /*
    Pregunta 2.
    Record r ("11-8-2020","","","","","","", "");

    int pos = busquedaBinaria(conexiones, r, compararPorNombreFuente);
    if (pos == -1){
        return 0;
    }

    int count =1;
    int izquierda = pos -1;
    while (left >= 0 && comparador(elementos[izquierda], buscado) == r){
        count++;
        left --;
    }
    
    int derecha = pos +1;
    while(derecha < && comparador(elementos[derecha], buscado) == r){
        count ++;
        right ++;
    }

    return count;
    
    */
    /*

    /* Pregunta 3.
    s.sort(conexiones, compararPorNombreFuente);
    /// Record r ("","","","","jeffrey.reto.com","","", "");
    /// Record r ("","","","","betty.reto.com","","", "");
    ///Record r ("","","","","scott.reto.com","","", "");
    ///Record r ("","","","","benjamin.reto.com","","", "");
    ///Record r ("","","","","raymond.reto.com","","", "");
    */

    /*
    /// Pregrunta 5.
    Record r ("","","","","server.reto.com","","", "");
    */
    



    return 0;
}