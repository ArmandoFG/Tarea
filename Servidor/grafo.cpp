#include "grafo.h"
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <curses.h>




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
                case 3: mostrar_grafo();
                        break;
                case 4: mostrar_aristas();
                        break;

                default: cout<<"OPCION NO VALIDA...!!!";
                         break;


            }



        }while(op!=7);
   //     getch();

    }

void menu()
{

    cout<<" 1. INSERTAR UN NODO                 "<<endl;
    cout<<" 2. INSERTAR UNA ARISTA              "<<endl;
    cout<<" 3. MOSTRAR  GRAFO                   "<<endl;
    cout<<" 4. MOSTRAR ARISTAS DE UN NODO       "<<endl;
    cout<<" 5. SALIR                            "<<endl;

    cout<<"\n INGRESE OPCION: ";
}

/*                      INSERTAR NODO AL GRAFO
---------------------------------------------------------------------*/
void insertar_nodo()
{
    Tnodo t,nuevo=new struct nodo;
    cout<<"INGRESE VARIABLE: \n";
    cin>>*nuevo->nombre;
    cout<<*nuevo->nombre<<"\n";
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
void insertar_arista()
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
    cout<<"INGRESE NODO DE INICIO:";
    cin>>*ini;
    cout<<"INGRESE NODO FINAL:";
    cin>>*fin;
    cout<<"Ingrese pero arista";
    cin>>*Peso;
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



