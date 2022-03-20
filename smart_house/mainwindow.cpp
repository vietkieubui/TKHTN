#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

// PIN
int led1 = 26;
int led2 = 6;
int led3 = 5;

// BUTTON
int button1 = 22;
int button2 = 27;
int button3 = 17;

// LED STATE
bool led1State = false;
bool led2State = false;
bool led3State = false;

// LAST LED STATE
bool lastLed1State = false;
bool lastLed2State = false;
bool lastLed3State = false;

// BUTTON STATE
int button1State = 0;
int button2State = 0;
int button3State = 0;

// LAST BUTTON STATE
int lastButton1State = 0;
int lastButton2State = 0;
int lastButton3State = 0;

// CLICKED STATE
bool led1ClickedState = false;
bool led2ClickedState = false;
bool led3ClickedState = false;

// LAST CLICKED STATE
bool lastLed1ClickedState = false;
bool lastLed2ClickedState = false;
bool lastLed3ClickedState = false;

// SWITCH MODE
bool switchMode1 = true;
bool switchMode2 = true;
bool switchMode3 = true;
bool switchMode1State = true;
bool switchMode2State = true;
bool switchMode3State = true;
bool lastSwitchMode1State = true;
bool lastSwitchMode2State = true;
bool lastSwitchMode3State = true;

// AUTO MODE
bool autoMode1 = false;
bool autoMode1State = false;
bool lastAutoMode1State = false;

// PIN OUT 1
int out1 = 16;

//HC-SR501
int pir1 = 25;
bool pir1State = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wiringPiSetupGpio();
    ui->led1Button->setEnabled(true);
    initActionsConnections();
    pinMode(led1,OUTPUT); //LED1
    pinMode(led2,OUTPUT); //LED2
    pinMode(led3,OUTPUT); //LED3
    pinMode(out1,OUTPUT); //always out 1
    pinMode(22,INPUT);
    pinMode(17,INPUT);
    pinMode(27,INPUT);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkLedState()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkPhysicButtonState()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkSwitchMode()));
    connect(timer,SIGNAL(timeout()),this,SLOT(checkAutoMode()));
    timer->start(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initActionsConnections(){
    ui->led1Button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->led2Button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->led3Button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->autoMode1Button->setIcon(QIcon(":/images/manual.png"));
    ui->pir1->setIcon(QIcon(":/images/grey.png"));
    connect(ui->led1Button, &QToolButton::clicked, this, &MainWindow::on_led1Button_clicked);
    connect(ui->led2Button, &QToolButton::clicked, this, &MainWindow::on_led2Button_clicked);
    connect(ui->led3Button, &QToolButton::clicked, this, &MainWindow::on_led3Button_clicked);
    connect(ui->switchMode1Button, &QToolButton::clicked, this, &MainWindow::on_switchMode1Button_clicked);
    connect(ui->switchMode2Button, &QToolButton::clicked, this, &MainWindow::on_switchMode2Button_clicked);
    connect(ui->switchMode3Button, &QToolButton::clicked, this, &MainWindow::on_switchMode3Button_clicked);
    connect(ui->autoMode1Button, &QToolButton::clicked, this, &MainWindow::on_autoMode1Button_clicked);

}

void MainWindow::checkLedState(){
    digitalWrite(out1,1);
    if(led1State==true){
        digitalWrite(led1,1);
        ui->led1Button->setIcon(QIcon(":/images/ledOn.png"));
        ui->led1Button->setToolTip("Turn OFF");
        ui->label1->setText("ĐÈN 1 BẬT");
    }else{
        digitalWrite(led1,0);
        ui->led1Button->setIcon(QIcon(":/images/ledOff.png"));
        ui->led1Button->setToolTip("Turn ON");
        ui->label1->setText("ĐÈN 1 TẮT");
    }
    if(led2State==true){
        digitalWrite(led2,1);
        ui->led2Button->setIcon(QIcon(":/images/ledOn.png"));
        ui->led2Button->setToolTip("Turn OFF");
        ui->label2->setText("ĐÈN 2 BẬT");
    }else{
        digitalWrite(led2,0);
        ui->led2Button->setIcon(QIcon(":/images/ledOff.png"));
        ui->led2Button->setToolTip("Turn ON");
        ui->label2->setText("ĐÈN 2 TẮT");
    }
    if(led3State==true){
        digitalWrite(led3,1);
        ui->led3Button->setIcon(QIcon(":/images/ledOn.png"));
        ui->led3Button->setToolTip("Turn OFF");
        ui->label3->setText("ĐÈN 3 BẬT");
    }else{
        digitalWrite(led3,0);
        ui->led3Button->setIcon(QIcon(":/images/ledOff.png"));
        ui->led3Button->setToolTip("Turn ON");
        ui->label3->setText("ĐÈN 3 TẮT");
    }
}

void MainWindow::checkPhysicButtonState(){
    if(switchMode1==true){
        button1State = digitalRead(button1);
        if(button1State!=lastButton1State){
            if(button1State==1){
                led1State =! led1State;
            }
        }
        lastButton1State = button1State;
    }

    if(switchMode2==true){
        button2State = digitalRead(button2);
        if(button2State!=lastButton2State){
            if(button2State==1){
                led2State =! led2State;
            }
        }
        lastButton2State = button2State;
    }
    if(switchMode3==true){
        button3State = digitalRead(button3);
        if(button3State!=lastButton3State){
            if(button3State==1){
                led3State =! led3State;
            }
        }
        lastButton3State = button3State;
    }
}

void MainWindow::checkSwitchMode(){
    if(switchMode1 == true){
        ui->switchMode1Button->setIcon(QIcon(":/images/enable.png"));
    }else{
        ui->switchMode1Button->setIcon(QIcon(":/images/disable.png"));
    }
    if(switchMode2 == true){
        ui->switchMode2Button->setIcon(QIcon(":/images/enable.png"));
    }else{
        ui->switchMode2Button->setIcon(QIcon(":/images/disable.png"));
    }
    if(switchMode3 == true){
        ui->switchMode3Button->setIcon(QIcon(":/images/enable.png"));
    }else{
        ui->switchMode3Button->setIcon(QIcon(":/images/disable.png"));
    }
}

void MainWindow::checkAutoMode(){
    pir1State = digitalRead(pir1);
    if(autoMode1 == true){
        ui->autoMode1Button->setIcon(QIcon(":/images/auto.png"));
        if(pir1State==true){
            led1State = true;
            ui->pir1->setIcon(QIcon(":/images/red.png"));
        }else{
            led1State = false;
            ui->pir1->setIcon(QIcon(":/images/grey.png"));
        }
    }else{
        ui->autoMode1Button->setIcon(QIcon(":/images/manual.png"));
    }
    if(autoMode1 == false){
        ui->pir1->setIcon(QIcon(":/images/grey.png"));
    }
}

void MainWindow::on_led1Button_clicked()
{
    led1ClickedState = !led1ClickedState;
    if(led1ClickedState!=lastLed1ClickedState){
        if(led1ClickedState==true){
            led1State = !led1State;
        }
    }
    lastLed1ClickedState = led1ClickedState;
    autoMode1 = false;
}

void MainWindow::on_led2Button_clicked()
{
    led2ClickedState = !led2ClickedState;
    if(led2ClickedState!=lastLed2ClickedState){
        if(led2ClickedState==true){
            led2State = !led2State;
        }
    }
    lastLed2ClickedState = led2ClickedState;
}

void MainWindow::on_led3Button_clicked()
{
    led3ClickedState = !led3ClickedState;
    if(led3ClickedState!=lastLed3ClickedState){
        if(led3ClickedState==true){
            led3State = !led3State;
        }
    }
    lastLed3ClickedState = led3ClickedState;
}


void MainWindow::on_switchMode1Button_clicked()
{
    switchMode1State = !switchMode1State;
    if(switchMode1State!=lastSwitchMode1State){
        if(switchMode1State==true){
            switchMode1 = !switchMode1;
        }
    }
    lastSwitchMode1State = switchMode1State;
}

void MainWindow::on_switchMode2Button_clicked()
{
    switchMode2State = !switchMode2State;
    if(switchMode2State!=lastSwitchMode2State){
        if(switchMode2State==true){
            switchMode2 = !switchMode2;
        }
    }
    lastSwitchMode2State = switchMode2State;
}

void MainWindow::on_switchMode3Button_clicked()
{
    switchMode3State = !switchMode3State;
    if(switchMode3State!=lastSwitchMode3State){
        if(switchMode3State==true){
            switchMode3 = !switchMode3;
        }
    }
    lastSwitchMode3State = switchMode3State;
}

void MainWindow::on_autoMode1Button_clicked()
{
    autoMode1State = !autoMode1State;
    if(autoMode1State!=lastAutoMode1State){
        if(autoMode1State == true){
            autoMode1 = !autoMode1;
        }
    }
    lastAutoMode1State = autoMode1State;    
}
