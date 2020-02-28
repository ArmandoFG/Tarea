#include "cliente.h"
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

cliente::cliente(void)
{
    int sock = 0, n;
        struct sockaddr_in serv_addr;
        string mensaje;
       mensaje = "ffffffff";
        char* cadena;
        cadena = (char *)mensaje.c_str();
       // char buffer[1024] = {0};
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
        {
            printf("\nConnection Failed \n");


        }

        n = strlen(cadena);


        while(n>0){
           send(sock , cadena , n, 0 );
          // MainWindow().mensaje = "";
        }/*
        valread = read( sock , buffer, 1024);
        while(valread>0){
            MainWindow().respuesta = printf("%s\n",buffer );

        }
        */

}
