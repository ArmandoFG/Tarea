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

using namespace std;





//int argc, char const *argv[]


int main(void)
{
    Grafo();

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
            printf("hila");
            perror("accept");
            exit(EXIT_FAILURE);
        }
        listen(server_fd, 5);
        n = strlen(cadena);
    /*
        while(n>0){
            send(new_socket , cadena , n, 0 );
            Grafo().mensajeServer = "";
        }*/

        valread = read( new_socket , buffer, 1024);

        while(valread>0){
            respuesta2 = printf("%s", buffer);

            printf("%s", respuesta2.c_str());
            respuesta2 = "";
        }






}
