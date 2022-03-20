#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wiringPi.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void initActionsConnections();
    void checkLedState();
    void checkPhysicButtonState();
    void checkSwitchMode();
    void checkAutoMode();

    void on_led1Button_clicked();

    void on_led2Button_clicked();

    void on_led3Button_clicked();


    void on_switchMode1Button_clicked();

    void on_switchMode2Button_clicked();

    void on_switchMode3Button_clicked();

    void on_autoMode1Button_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};
#endif // MAINWINDOW_H
