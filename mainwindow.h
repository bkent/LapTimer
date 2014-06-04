#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbStart_clicked();
    void timerEvent(QTimerEvent *);
    QString CalculateTimeStr(qint64 time);

    void on_pbStop_clicked();

    void on_pbPause_clicked();

    void on_pbLane1Lap_clicked();

    void on_pbLane2Lap_clicked();

    void on_pbSQLTest_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
