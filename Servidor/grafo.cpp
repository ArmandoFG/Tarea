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
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#define PORT 8080




/**
 *
 * @author Armando Fallas
 * @version 1.0
 */




string respuesta;   //Mensaje del cliente
string enviar;      //mensaje a enviar al cliente

using namespace std;

/**
 * @brief The nodo struct Estructura del nodo
 */

struct nodo{

            char* nombre = new char[10];//Puntero nombre del nodo
            struct nodo *sgte;  //Puntero hacia Nodo siguiente
            struct arista *ady;//puntero hacia la primera arista del nodo
            int marca;
            };
/**
 * @brief The arista struct Estructura de la arista
 */
struct arista{

              struct nodo *destino;//puntero al nodo de llegada
              struct arista *sgte;  //Puntero a la arista siguiente
              int pso;   //Puntero hacia el peso de la arista
              int marca;
              int suma;;
              };
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista

struct nodo  *aux, *aux2;
struct arista  *auxArc, *arcMen, *auxArc2, *antArc;
char auxNod, ban2, auxfinal;
int ban;


Tnodo p;//puntero cabeza

void menu();
void insertar_nodo(char nombre);
void agrega_arista(Tnodo &, Tnodo &, Tarista &);
void insertar_arista();
void mostrar_grafo();
void mostrar_aristas();
void crear_grafo();
void servidor();
void algoritmoDijkstra ();

 Grafo::Grafo(void)
{
        p=NULL;
        servidor(); //Metodo del servidor
        if (respuesta == "Generar"){
            crear_grafo();  //se crea el grafo
            mostrar_grafo();    //Se muestra el grafo
            algoritmoDijkstra ();
        }









    }


/*
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

/*
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
        nuevo->pso= *Peso;

    } // si no esta vacía recorre todas las aristas hasta llegar a null
    else
    {   q=aux->ady;
        while(q->sgte!=NULL)
            q=q->sgte;
        nuevo->destino=aux2;
        q->sgte=nuevo;
        nuevo->pso= *Peso;


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
                cout << " "<<ar->pso;
                ar=ar->sgte;
             }

        }
        ptr=ptr->sgte;
        cout<<endl;
    }
}

/*
---------------------------------------------------------------------*/


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
    insertar_arista(*nombre1.c_str(), *nombre2.c_str(), 10);
    insertar_arista(*nombre2.c_str(), *nombre3.c_str(), 12);
    insertar_arista(*nombre5.c_str(), *nombre4.c_str(), 15);
    insertar_arista(*nombre4.c_str(), *nombre3.c_str(), 15);
    insertar_arista(*nombre3.c_str(), *nombre4.c_str(), 23);
    insertar_arista(*nombre4.c_str(), *nombre5.c_str(), 10);
    insertar_arista(*nombre2.c_str(), *nombre4.c_str(), 100);
}

/**
 * @brief servidor  Metodo para crear conexion con los sockets
 */
void servidor(){
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        string respuesta2;
        char* cadena;
        cadena = (char *)respuesta2.c_str();

        // Crear descriptor de archivo de socket
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Conexión forzada del zócalo al puerto 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                      &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons( PORT );


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
        listen(server_fd, 5);   //A la escucha para conexiones



        valread = read( new_socket , cadena, 1024); //Leyendo tamaño del mensaje

        while(valread>0){
            respuesta = cadena;
            valread = 0;
            close(new_socket);
            close(server_fd);
        }

}


/*-------------------------------------------------------------------------------------------------------------*/

/**
 * @brief actualizarCampos Este metodo incializa de nuevo las marcas y las sumas para buscar nuevas rutas
 */

void actualizarCampos () {
     aux = p;
     while (aux != NULL){
           auxArc = aux->ady;

           while (auxArc != NULL){
                 auxArc->marca = 0;
                 auxArc->suma = 0;
                 auxArc = auxArc->sgte;
           }
           aux->marca = 0;
           aux = aux->sgte;
     }
}

/**
 * @brief obtenerSumaMenor  Se compara la ruta menor hacia el destino
 */

void obtenerSumaMenor () {
     aux2 = p;
     arcMen = NULL;
     while (aux2 != NULL){
           if (aux2->marca == 1){
                      auxArc = aux2->ady;
                      while (auxArc != NULL){
                            if (auxArc->marca == 1){
                                  if (arcMen == NULL){
                                         arcMen = auxArc;

                                  }
                                  else{
                                       if (auxArc->suma < arcMen->suma){
                                              arcMen = auxArc;
                                       }
                                  }
                            }
                            auxArc = auxArc->sgte;
                      }
           }
           aux2 = aux2->sgte;
     }
     arcMen->marca = 3;
     arcMen->destino->marca = 1;

     auxArc = arcMen->destino->ady;

     while (auxArc != NULL){
           auxArc->suma = (arcMen->suma + auxArc->pso);

           auxArc = auxArc->sgte;
     }

}


/**
 * @brief paso2Dijkstra Metodo de comparaciones de rutas
 */

void paso2Dijkstra () {
    obtenerSumaMenor();

    char *nombre_n = arcMen->destino->nombre;

    int suma_ruta = arcMen->suma;

    stringstream ss;
    ss << suma_ruta;
    if (auxfinal == *nombre_n){
    cout<< nombre_n;
    enviar =  "\nLa sumatoria hasta el arco " + string(nombre_n) + " es: " + ss.str() +"\n";
    cout<<enviar;

    }
    aux = arcMen->destino;
            auxArc = aux->ady;
            while (auxArc != NULL){
                  if (auxArc->destino->marca == 0){
                         aux2 = p;
                         while (aux2 != NULL){
                               if (aux2 != aux && aux2->marca == 1){
                                     auxArc2 = aux2->ady;
                                     while (auxArc2 != NULL){
                                           if (*auxArc->destino->nombre == *auxArc2->destino->nombre){
                                                  if (auxArc->suma  < auxArc2->suma){
                                                         auxArc2->marca = 2;
                                                         auxArc->marca = 1;
                                                  }
                                                  else {
                                                       auxArc->marca = 2;
                                                       auxArc2->marca = 1;
                                                  }
                                           }
                                           auxArc2 = auxArc2->sgte;
                                     }
                               }
                               aux2 = aux2->sgte;
                         }
                         if (auxArc->marca == 0){
                                auxArc->marca = 1;
                                auxArc->suma = (arcMen->suma + auxArc->pso);
                         }
                  }
                  else {
                       auxArc->marca = 2;
                  }
                  auxArc = auxArc->sgte;
            }
}



/**
 * @brief algoritmoDijkstra Metodo para inicializar el nodo de partida y el final
 */

void algoritmoDijkstra () {
     system("cls");
     if (p != NULL){
            actualizarCampos ();
            cout << "Digite el vertice inicial: ";
            cin >> auxNod;
            cout << "Digite el vertice final: ";
            cin >> auxfinal;
            ban = 0;
            while (ban == 0){
                  aux = p;
                  while (aux != NULL){
                        if (*aux->nombre == auxNod){
                               ban = 1;
                        }
                        aux = aux->sgte;
                  }
                  if (ban == 0){
                         cout << "\nNo existe un nodo con esa letra.";
                         aux = p;
                         cout << "\n---Lista de Nodos---\n";
                         while (aux != NULL){
                               cout << aux->nombre << " ";
                               aux = aux->sgte;
                         }
                         cout << "\nDigite uno de los anteriores nodos: ";
                         cin >> auxNod;
                  }
            }
            aux = p;
            while (*aux->nombre != auxNod){
                  aux = aux->sgte;

            }
            aux->marca = 1;
            auxArc = aux->ady;
            while (auxArc != NULL){
                  auxArc->marca = 1;
                  auxArc->suma = auxArc->pso;
                  auxArc = auxArc->sgte;
            }
            cout << "\nSe han trazado todos los arcos para el vertice elegido.";
            ban2 = 1;
            while (ban2 == 1){
                  paso2Dijkstra();
                  ban2 = 0;
                  aux = p;
                  while (aux != NULL){
                        if (aux->marca == 0){
                               ban2 = 1;
                        }
                        aux = aux->sgte;
                  }
            }

     }

}




