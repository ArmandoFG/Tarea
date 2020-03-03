#include "mainwindow.h"

#include <QApplication>

/**
 * @brief main  Funcion principal
 * @param argc  contiene el número de argumentos que se han introducido.
 * @param argv  array de punteros a caracteres.

 * @return
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; //Variable de la ventana

    w.show();   //Se muestra la ventana

    return a.exec();
}
