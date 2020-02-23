#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->texto->setText("INGRESE OPCION: \n \n"

                       "1. INSERTAR UN NODO \n\n"

                       "2. INSERTAR UNA ARISTA \n\n"

                       "3. MOSTRAR  GRAFO \n\n"


                       "4. MOSTRAR ARISTAS DE UN NODO \n\n");



}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::Opciones(){
    ui->Aceptar->setText("Apretado");
    ui->texto->setText("ddddfdfdfdfdfd");
}

/*
INGRESE OPCION:

1. INSERTAR UN NODO

2. INSERTAR UNA ARISTA

3. MOSTRAR  GRAFO

4. MOSTRAR ARISTAS DE UN NODO */
