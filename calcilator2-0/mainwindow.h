#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e) override;

private:
    Ui::MainWindow *ui;
    void setInterfaceStyle();

private slots:

    void digits_numbers();

    void on_pushButton_dot_cliced();
    void operations();
    void math_operations();
    void math_PI();
    void math_e();
    void deleteF();
    void on_pushButton_ravno_clicked();
    void on_pushButton_C_clicked();
    void on_pushButton_sqr_clicked();
    void on_pushButton_ln_clicked();
    void on_pushButton_sin_clicked();
    void on_pushButton_cos_clicked();
    void on_pushButton_tan_clicked();
    void on_pushButton_ctg_clicked();
    void on_pushButton_deg_clicked();

    void on_pushButton_voskl_clicked();

    void on_pushButton_log10_clicked();
    void on_pushButton_modul_clicked();
};
#endif // MAINWINDOW_H
