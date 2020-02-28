#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <string.h>
#include "mainwindow.h"
#include "cliente.h"
#include <cliente.h>
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

int temporal;
string temporal2;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)



{





}

MainWindow::~MainWindow()
{
    delete ui;


}



void MainWindow::Opciones(){


    if(ui->lineoption->text() != nullptr && ui->lineoption->text() ==  "1" && temporal == 0) {





}

}



