#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * @author Armando Fallas
 * @version 1.0
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow    Ventana principal
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;


private:


public slots:
    /**
     * @brief GenerarGrafo Metodo para captar cuando se preciona un botón en la ventana
     */

    void GenerarGrafo();

};
#endif // MAINWINDOW_H
