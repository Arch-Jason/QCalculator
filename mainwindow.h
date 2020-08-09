#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *nu0;

private slots:
    void numbers_clicked();
    void on_decimal_clicked();
    void on_PN_convert_clicked();
    void on_persent_clicked();
    void on_button_ac_clicked();
    void operation_key();
    void on_equal_clicked();
};
#endif // MAINWINDOW_H
