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

/**
 *
 * @author Armando Fallas
 * @version 1.0
 */



string respuesta;   //Mensaje del cliente

using namespace std;

/**
 * @brief The nodo struct Estructura del nodo
 */

struct nodo{

            char* nombre = new char[10];//Puntero nombre del nodo
            struct nodo *sgte;  //Puntero hacia Nodo siguiente
            struct arista *ady;//puntero hacia la primera arista del nodo
            };
/**
 * @brief The arista struct Estructura de la arista
 */
struct arista{
              struct nodo *destino;//puntero al nodo de llegada
              struct arista *sgte;  //Puntero a la arista siguiente
              int *pso = new int[10];   //Puntero hacia el peso de la arista
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
        servidor(); //Metodo del servidor
        if (respuesta == "Generar"){
            crear_grafo();  //se crea el grafo
            mostrar_grafo();    //Se muestra el grafo
        }








    }


/*                      INSERTAR NODO AL GRAFO
---------------------------------------------------------------------*/

 /**
 * @brief insertar_nodo Metodo para ingresar un nodo
 * @param nombre    Nombre del nodo
 */
void insertar_nodo(char nombre)
{
    Tnodo t,nuevo=new struct nodo;

    *nuevo->nombre = nombre;    //Se le asigna el nombre del nodo al puntero

    nuevo->sgte = NULL;
    nuevo->ady=NULL;

    if(p==NULL) //Si p es igual a nulo, no hay ningun nodo almacenado
     {
        p = nuevo;  // Se ingresa el nodo

      }
    else
     {
        t = p;  //Se le asigna el puntero a cabecera a t
        //Mientras el siguiente nodo de t sea diferente a null recorrera todos los nodos ecistentes
        while(t->sgte!=NULL)
         {
            t = t->sgte;
          }
        //Se ingresa el nodo
        t->sgte = nuevo;

      }

 }

/*                      AGREGAR ARISTA
    funcion que utilizada para agregar la arista a dos nodos
---------------------------------------------------------------------*/
/**
 * @brief agrega_arista Metodo para la insercion de aristas
 * @param aux   Nodo auxiliar para ingresar arista
 * @param aux2  Nodo auxiliar para ingresar arist
 * @param nuevo Arista ingresada
 * @param Peso  Peso de la arista
 */
void agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo, int *Peso)
{
    Tarista q;  //Arista auxiliar
    //Si el nodo no tiene arista la ingresa
    if(aux->ady==NULL)
    {   aux->ady=nuevo;
        nuevo->destino=aux2;
        *nuevo->pso= *Peso;

    } // si no esta vacía recorre todas las aristas hasta llegar a null
    else
    {   q=aux->ady;
        while(q->sgte!=NULL)
            q=q->sgte;
        nuevo->destino=aux2;
        q->sgte=nuevo;
        *nuevo->pso= *Peso;


    }

}
/*
---------------------------------------------------------------------*/
/**
 * @brief insertar_arista   Metodo para insertar arista
 * @param inicio    Nombre del nodo inicio
 * @param final     Nombre del nodo final
 * @param peso      Peso de la arista
 */
void insertar_arista(char inicio, char final, int peso)
{   char* ini = new char[2], *fin = new char[2];    //Punteros de nombre de inicio y final de los nodos de la arista
    int *Peso = new int[2]; //Puntero del peso de la arista
    Tarista nuevo=new struct arista;    //Se crea la variable de la nueva arista
    Tnodo aux, aux2;

    //Si no hay nodos no puede ingresar la arista
    if(p==NULL)
     {

         return;
     }
    nuevo->sgte=NULL;
    *ini = inicio;
    *fin = final;
    *Peso = peso;
    aux=p;
    aux2=p;
    //Se recorre los nodos para verificar que existan y para agregarle la arista
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




/*
---------------------------------------------------------------------*/
/**
 * @brief mostrar_grafo Metodo para mostrar grafo de la lista enlazada
 */
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

/**
 * @brief crear_grafo   Metodo para crear un grafo predeterminado
 */

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

/**
 * @brief servidor  Metodo para crear conexion con los sockets
 */
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
            valread = 0;
            close(new_socket);
            close(server_fd);
        }

}



