#include "grafo.h"

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <curses.h>



using namespace std;

struct nodo{
            char nombre;//nombre del vertice o nodo
            struct nodo *sgte;
            struct arista *ady;//puntero hacia la primera arista del nodo
            };
struct arista{
              struct nodo *destino;//puntero al nodo de llegada
              struct arista *sgte;
              };
typedef struct nodo *Tnodo;//  Tipo Nodo
typedef struct arista *Tarista; //Tipo Arista

Tnodo p;//puntero cabeza

void menu();
void insertar_nodo();
void agrega_arista(Tnodo &, Tnodo &, Tarista &);
void insertar_arista();
void mostrar_grafo();
void mostrar_aristas();

 Grafo::Grafo(void)
{
        p=NULL;
        int op;     // opcion del menu




        do
        {
            menu();
            cin>>op;

            switch(op)
            {
                case 1:
                        insertar_nodo();
                        break;
                case 2: insertar_arista();
                        break;
                case 5: mostrar_grafo();
                        break;
                case 6: mostrar_aristas();
                        break;

                default: cout<<"OPCION NO VALIDA...!!!";
                         break;


            }

            cout<<endl<<endl;
            system("pause");  system("cls");

        }while(op!=7);
   //     getch();

    }

void menu()
{

    cout<<" 1. INSERTAR UN NODO                 "<<endl;
    cout<<" 2. INSERTAR UNA ARISTA              "<<endl;
    cout<<" 5. MOSTRAR  GRAFO                   "<<endl;
    cout<<" 6. MOSTRAR ARISTAS DE UN NODO       "<<endl;
    cout<<" 7. SALIR                            "<<endl;

    cout<<"\n INGRESE OPCION: ";
}

/*                      INSERTAR NODO AL GRAFO
---------------------------------------------------------------------*/
void insertar_nodo()
{
    Tnodo t,nuevo=new struct nodo;
    cout<<"INGRESE VARIABLE:";
    cin>>nuevo->nombre;
    nuevo->sgte = NULL;
    nuevo->ady=NULL;

    if(p==NULL)
     {
        p = nuevo;
        cout<<"PRIMER NODO...!!!";
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
void agrega_arista(Tnodo &aux, Tnodo &aux2, Tarista &nuevo)
{
    Tarista q;
    if(aux->ady==NULL)
    {   aux->ady=nuevo;
        nuevo->destino=aux2;
        cout<<"PRIMERA ARISTA....!";
    }
    else
    {   q=aux->ady;
        while(q->sgte!=NULL)
            q=q->sgte;
        nuevo->destino=aux2;
        q->sgte=nuevo;
        cout<<"ARISTA AGREGADA...!!!!";
    }

}
/*                      INSERTAR ARISTA
    funcion que busca las posiciones de memoria de los nodos
    y hace llamado a agregar_arista para insertar la arista
---------------------------------------------------------------------*/
void insertar_arista()
{   char ini, fin;
    Tarista nuevo=new struct arista;
    Tnodo aux, aux2;

    if(p==NULL)
     {
         cout<<"GRAFO VACIO...!!!!";
         return;
     }
    nuevo->sgte=NULL;
    cout<<"INGRESE NODO DE INICIO:";
    cin>>ini;
    cout<<"INGRESE NODO FINAL:";
    cin>>fin;
    aux=p;
    aux2=p;
    while(aux2!=NULL)
    {
        if(aux2->nombre==fin)
        {
            break;
        }

        aux2=aux2->sgte;
    }
    while(aux!=NULL)
    {
        if(aux->nombre==ini)
        {
            agrega_arista(aux,aux2, nuevo);
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
            {   cout<<" "<<ar->destino->nombre;
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
    char var;
    cout<<"MOSTRAR ARISTAS DE NODO\n";
    cout<<"INGRESE NODO:";
    cin>>var;
    aux=p;
    while(aux!=NULL)
    {
        if(aux->nombre==var)
        {
            if(aux->ady==NULL)
            {   cout<<"EL NODO NO TIENE ARISTAS...!!!!";
                return;
             }
            else
            {
                cout<<"NODO|LISTA DE ADYACENCIA\n";
                cout<<"   "<<aux->nombre<<"|";
                ar=aux->ady;

                while(ar!=NULL)
                {
                    cout<<ar->destino->nombre<<" ";
                    ar=ar->sgte;
                }
                cout<<endl;
                return;
            }
        }
        else
        aux=aux->sgte;
    }
}




