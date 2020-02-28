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
#include "cliente.h"
#include <cliente.h>

#define PORT 8080
using namespace std;







int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
     MainWindow w;
    w.show();

   return a.exec();
;




}






