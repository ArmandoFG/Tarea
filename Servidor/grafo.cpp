#include "grafo.h"
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <curses.h>

#include <QCoreApplication>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <grafo.h>
#include "grafo.h"
#define PORT 8080

string llamada;
string respuesta;

using namespace std;

struct nodo{
            char* nombre = new char[10];//nombre del vertice o nodo
            struct nodo *sgte;
            struct arista *ady;//puntero hacia la primera arista del nodo
            };
struct arista{
              struct nodo *destino;//puntero al nodo de llegada
              struct arista *sgte;
              int *pso = new int[10];
              };
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista


Tnodo p;//puntero cabeza

void menu();
void insertar_nodo(char nombre);
void agrega_arista(Tnodo &, Tnodo &, Tarista &);
void insertar_arista();
void mostrar_grafo();
void mostrar_aristas();
void crear_grafo();
void servidor();

 Grafo::Grafo(void)
{
        p=NULL;
        servidor();
        if (respuesta == "Generar"){
            crear_grafo();
            mostrar_grafo();
        }








    }


/*                      INSERTAR NODO AL GRAFO
---------------------------------------------------------------------*/
void insertar_nodo(char nombre)
{
    Tnodo t,nuevo=new struct nodo;

    *nuevo->nombre = nombre;

    nuevo->sgte = NULL;
    nuevo->ady=NULL;

    if(p==NULL)
     {
        p = nuevo;

      }
    else
     {
        t = p;
        while(t->sgte!=NULL)
         {
            t = t->sgte;
          }
        t->sgte = nuevo;
        cout<<"NODO INGRESADO...!!!";
      }

 }

/*                      AGREGAR ARISTA
    funcion que utilizada para agregar la arista a dos nodos
---------------------------------------------------------------------*/
void agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo, int *Peso)
{
    Tarista q;
    if(aux->ady==NULL)
    {   aux->ady=nuevo;
        nuevo->destino=aux2;
        *nuevo->pso= *Peso;
        cout<<"PRIMERA ARISTA....!";
    }
    else
    {   q=aux->ady;
        while(q->sgte!=NULL)
            q=q->sgte;
        nuevo->destino=aux2;
        q->sgte=nuevo;
        *nuevo->pso= *Peso;

        cout<<"ARISTA AGREGADA...!!!!";
    }

}
/*                      INSERTAR ARISTA
    funcion que busca las posiciones de memoria de los nodos
    y hace llamado a agregar_arista para insertar la arista
---------------------------------------------------------------------*/
void insertar_arista(char inicio, char final, int peso)
{   char* ini = new char[2], *fin = new char[2];
    int *Peso = new int[2];
    Tarista nuevo=new struct arista;
    Tnodo aux, aux2;

    if(p==NULL)
     {
         cout<<"GRAFO VACIO...!!!!";
         return;
     }
    nuevo->sgte=NULL;
    *ini = inicio;
    *fin = final;
    *Peso = peso;
    aux=p;
    aux2=p;
    while(aux2!=NULL)
    {
        if(*aux2->nombre==*fin)
        {

            delete [] fin;
            break;
        }

        aux2=aux2->sgte;
    }
    while(aux!=NULL)
    {
        if(*aux->nombre==*ini)
        {
            agrega_arista(aux, aux2, nuevo, Peso);
            delete[] ini;
            delete [] Peso;
            return;
        }

        aux = aux->sgte;
    }
}




/*                      MOSTRAR GRAFO
    funcion que imprime un grafo en su forma enlazada
---------------------------------------------------------------------*/
void mostrar_grafo()
{   Tnodo ptr;
    Tarista ar;
    ptr=p;
    cout<<"NODO|LISTA DE ADYACENCIA\n";

    while(ptr!=NULL)
    {   cout<<"   "<<ptr->nombre<<"|";
        if(ptr->ady!=NULL)
        {
            ar=ptr->ady;
            while(ar!=NULL)
            {   cout<<" "<<ar->destino->nombre<<" Peso";
                cout << " "<<*ar->pso;
                ar=ar->sgte;
             }

        }
        ptr=ptr->sgte;
        cout<<endl;
    }
}

/*                      MOSTRAR ARISTAS
    funcion que muestra todas las aristas de un nodo seleccionado
---------------------------------------------------------------------*/
void mostrar_aristas()
{
    Tnodo aux;
    Tarista ar;

    char *var = new char[2];
    cout<<"MOSTRAR ARISTAS DE NODO\n";
    cout<<"INGRESE NODO:";
    cin>>*var;
    aux=p;
    while(aux!=NULL)
    {
        if(*aux->nombre==*var)
        {
            if(aux->ady==NULL)
            {   cout<<"EL NODO NO TIENE ARISTAS...!!!!";
                return;
             }
            else
            {
                cout<<"NODO|LISTA DE ADYACENCIA\n";


                ar=aux->ady;

                while(ar!=NULL)
                {
                    cout<<*ar->destino->nombre<<" peso: ";
                    cout<<"   "<<*ar->pso<<"|";
                    ar=ar->sgte;
                }
                cout<<endl;
                delete [] var;
                return;
            }
        }
        else
        aux=aux->sgte;
        delete [] var;
    }
}



void crear_grafo(){
    string nombre1 = "A";
    string nombre2 = "B";
    string nombre3 = "C";
    string nombre4 = "D";
    string nombre5 = "E";
    insertar_nodo(*nombre1.c_str());
    insertar_nodo(*nombre2.c_str());
    insertar_nodo(*nombre3.c_str());
    insertar_nodo(*nombre4.c_str());
    insertar_nodo(*nombre5.c_str());
    insertar_arista(*nombre1.c_str(), *nombre3.c_str(), 49);
    insertar_arista(*nombre1.c_str(), *nombre2.c_str(), 12);
    insertar_arista(*nombre5.c_str(), *nombre4.c_str(), 1);
    insertar_arista(*nombre2.c_str(), *nombre3.c_str(), 43);
    insertar_arista(*nombre4.c_str(), *nombre1.c_str(), 23);
    insertar_arista(*nombre3.c_str(), *nombre4.c_str(), 10);
}
void servidor(){
    int server_fd, new_socket, valread, n;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0};
        string respuesta2;
        char* cadena;
        cadena = (char *)respuesta2.c_str();

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                      &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address,
                                     sizeof(address))<0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t*)&addrlen))<0)
        {

            perror("accept");
            exit(EXIT_FAILURE);
        }
        listen(server_fd, 5);
        //n = strlen(cadena);


        valread = read( new_socket , cadena, 1024);

        while(valread>0){
            respuesta = cadena;
            llamada= printf("%s", cadena);
            valread = 0;
            close(new_socket);
            close(server_fd);
        }

}



