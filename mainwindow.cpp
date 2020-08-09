#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
using namespace std;

double firstNum;
bool plusStatus=true, subtractStatus=true, multiplyStatus=true, divideStatus=true; //用於判斷等於號前那個運算符被點擊，false爲按下
bool secondNumTyping = false; //用於檢測是否在輸入第二個數
double lastNum;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->output->setText("0");
    //讓數字鍵接受滑鼠點擊，一堆connect……
    connect (ui->nu0, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu1, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu2, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu3, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu4, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu5, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu6, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu7, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu8, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    connect (ui->nu9, SIGNAL(clicked()), this, SLOT(numbers_clicked()));
    //operation keys
    connect (ui->plus, SIGNAL(clicked()), this, SLOT(operation_key())); //加
    connect (ui->subtract, SIGNAL(clicked()), this, SLOT(operation_key())); //減
    connect (ui->multiply, SIGNAL(clicked()), this, SLOT(operation_key())); //乘
    connect (ui->divide, SIGNAL(clicked()), this, SLOT(operation_key())); //除
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::numbers_clicked() {
    QPushButton *keyValue = (QPushButton*)sender(); //讓我看看，是誰被click了？
//    qDebug () << keyValue->text() + " clicked" << Qt::endl; //無聊
    double outSet;
    QString outSetString;
    if ((!plusStatus || !subtractStatus || !multiplyStatus || !divideStatus) && !secondNumTyping) {
        outSet = (keyValue->text()).toDouble();
        outSetString = QString::number(outSet, 'g', 15);
        secondNumTyping = true;
    } else {
        if (ui->output->text().contains('.') && keyValue->text() == "0") {
            outSetString = ui->output->text() + keyValue->text();
        } else {
            outSet = (ui->output->text() + keyValue->text()).toDouble(); //組成數字
            outSetString = QString::number(outSet, 'g', 15);
        }
    }

    ui->output->setText(outSetString); //顯示出來
}


void MainWindow::on_decimal_clicked() { //當小數點鍵被人按住後的舉動
//    qDebug() << "decimal key clicked" << Qt::endl;
    ui->output->setText(ui->output->text() + "."); //在後面追加小數點
}

void MainWindow::on_PN_convert_clicked() { //當正負轉換鍵被人按住後的舉動
//    qDebug() << "PN_convert key clicked" << Qt::endl;
    double outSet = ui->output->text().toDouble(); //讓我看看顯示的都有什麼
    outSet *= -1; //轉換正負
    QString outSetString = QString::number(outSet, 'g', 15);
    ui->output->setText(outSetString); //顯示出來
}

void MainWindow::on_persent_clicked() { //當百分號鍵被人按住後的舉動
//    qDebug() << "persent key clicked" << Qt::endl;
    double outSet = ui->output->text().toDouble(); //讓我看看顯示的都有什麼
    outSet *= 0.01;
    QString outSetString = QString::number(outSet, 'g', 15);
    ui->output->setText(outSetString);
}

void MainWindow::on_button_ac_clicked() { //AC key
    plusStatus = true;
    subtractStatus = true;
    multiplyStatus = true;
    divideStatus = true;
    secondNumTyping = false;
    firstNum = 0;
    ui->output->setText("0");
}

void MainWindow::on_equal_clicked() { //當等於號鍵被人按住後的舉動
//    qDebug() << "equal key clicked" << Qt::endl;
    QString outSetString;
    double outputNum;
    double secondNum = ui->output->text().toDouble();
//    qDebug() << "firstNum = " << firstNum << " and secondNum = " << secondNum << Qt::endl;


    if (plusStatus == false) {
//        qDebug() << "plus" << Qt::endl;
        outputNum = firstNum + secondNum;
        lastNum = outputNum;
        outSetString = QString::number(outputNum, 'g', 15);
//        plusStatus = true;
    }

    if (subtractStatus == false) {
//        qDebug() << "subtract" << Qt::endl;
        outputNum = firstNum - secondNum;
        lastNum = outputNum;
        outSetString = QString::number(outputNum, 'g', 15);
        subtractStatus = true;
    }

    if (multiplyStatus == false) {
//        qDebug() << "multiply" << Qt::endl;
        outputNum = firstNum * secondNum;
        lastNum = outputNum;
        outSetString = QString::number(outputNum, 'g', 15);
        multiplyStatus = true;
    }

    if (divideStatus == false) {
//        qDebug() << "divide" << Qt::endl;
        outputNum = firstNum / secondNum;
        lastNum = outputNum;
        outSetString = QString::number(outputNum, 'g', 15);
        divideStatus = true;
    }
//    lastNum = (ui->output->text()).toDouble();
//    qDebug() << plusStatus << "\n" << subtractStatus << "\n" << multiplyStatus << "\n" << divideStatus << Qt::endl;
    if (plusStatus && subtractStatus && multiplyStatus && divideStatus) {
        QString lastNumString = QString::number(lastNum, 'g', 15);
        ui->output->setText(lastNumString);
//        qDebug() << "lastNumString is " << lastNumString << Qt::endl;
    } else {
        ui->output->setText(outSetString);
    }
    secondNumTyping = false;
}

void MainWindow::operation_key() {
    QPushButton *keyValue = (QPushButton*)sender(); //讓我看看，是誰被click了？
//    qDebug() << keyValue->text() + " clicked" << Qt::endl; //無聊
    firstNum = ui->output->text().toDouble();
    if (keyValue->text() == "+") {
        plusStatus = false;
        subtractStatus = true;
        multiplyStatus = true;
        divideStatus = true;
    }
    if (keyValue->text() == "-") {
        subtractStatus = false;
        plusStatus = true;
        multiplyStatus = true;
        divideStatus = true;
    }
    if (keyValue->text() == "×") {
        multiplyStatus = false;
        plusStatus = true;
        subtractStatus = true;
        divideStatus = true;
    }
    if (keyValue->text() == "÷") {
        divideStatus = false;
        plusStatus = true;
        subtractStatus = true;
        multiplyStatus = true;
    }
}
