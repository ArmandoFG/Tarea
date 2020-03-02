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

#define PORT 8080
using namespace std;
string mensaje;
char* cadena;



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
void cliente(){
    int sock = 0, n;
        struct sockaddr_in serv_addr;
        cadena = (char *)mensaje.c_str();

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");

        }


        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
        {
            printf("\nInvalid address/ Address not supported \n");

        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        { mensaje = "lsdsdsf";
            cliente();
            printf("\nConnection Failed \n");


        }

        n = strlen(cadena);


       // while(n>0){
           send(sock , cadena , n, 0 );
           mensaje = " ";




           close(sock);
          // MainWindow().mensaje = "";
       // }
        /*
        valread = read( sock , buffer, 1024);
        while(valread>0){
            MainWindow().respuesta = printf("%s\n",buffer );

        }
        */

}



