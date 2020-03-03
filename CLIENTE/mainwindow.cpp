#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <QApplication>
#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "mainwindow.h"

#define PORT 8080   //Puerto

using namespace std;
string mensaje;     //Mensaje a enviar
char* cadena;       //Variable que almacena el mensaje en tipo char para poder ser enviado




void cliente();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->texto->setText("df");



}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::GenerarGrafo(){


    mensaje = "Generar";
    cliente();





}
/**
 * @brief cliente   Metodo para enviar el mensaje al servidor
 */
void cliente(){
    int sock = 0, n;

        struct sockaddr_in serv_addr; //Contiene una direccion
        cadena = (char *)mensaje.c_str();

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)   //Crea un nuevo socket
        {
            printf("\n Socket creation error \n");

        }


        serv_addr.sin_family = AF_INET;     //contiene un código para la familia de direcciones.
        serv_addr.sin_port = htons(PORT);

        // Convierta direcciones IPv4 e IPv6 de texto a formato binario
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
        {
            printf("\nDirección no válida / Dirección no admitida\n");

        }

        //Conexion con el server
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            cliente();
            printf("Conexion fallida\n");


        }

        n = strlen(cadena); //Tamaño del mensaje



           send(sock , cadena , n, 0 );     //Envío del mensaje
           mensaje = " ";




           close(sock);     //Cierre del socket


}



