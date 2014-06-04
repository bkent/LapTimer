#include "mainwindow.h"
#include "ui_mainwindow.h"

bool        mRunning;
QDateTime   mStartTime;
QLabel *    mLabel;
qint64      mTotalTime;
qint64      mSessionTime;
QStringList mTableHeader;
int         mLaps;
int         mLane1Laps;
int         mLane2Laps;
qint64      mLastLane1Tot;
qint64      mLastLane2Tot;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mLaps=10;
        mLane1Laps=0;
        mLane2Laps=0;

        ui->twLapTimes->setRowCount(10);
        ui->twLapTimes->setColumnCount(2);
        mTableHeader<<"Lane 1"<<"Lane 2";
        ui->twLapTimes->setHorizontalHeaderLabels(mTableHeader);

        startTimer(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbStart_clicked()
{
    mStartTime = QDateTime::currentDateTime();
    mLastLane1Tot=0;
    mLastLane2Tot=0;
    //startTimer(0);
    ui->pbStart->setEnabled(false);
    ui->pbPause->setEnabled(true);
    ui->pbStop->setEnabled(true);
    mRunning = true;
}

void MainWindow::on_pbPause_clicked()
{
    ui->pbStart->setEnabled(true);
    ui->pbPause->setEnabled(false);
    ui->pbStop->setEnabled(true);
    timerEvent(new QTimerEvent(0));
    mTotalTime += mSessionTime;
    mRunning = false;
}

void MainWindow::on_pbStop_clicked()
{
    ui->pbStart->setEnabled(true);
    ui->pbPause->setEnabled(false);
    ui->pbStop->setEnabled(false);
    mTotalTime = 0;
    mRunning = false;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    if(mRunning)
    {
        mSessionTime = mStartTime.msecsTo(QDateTime::currentDateTime());
        qint64 time = mTotalTime + mSessionTime;
        time *= 111;
        ui->mLabel->setText(CalculateTimeStr(time));
    }
}

QString MainWindow::CalculateTimeStr(qint64 time)
{
    unsigned int h = time / 1000 / 60 / 60;
    unsigned int m = (time / 1000 / 60) - (h * 60);
    unsigned int s = (time / 1000) - ((m + (h * 60))* 60);
    unsigned int ms = time - (s + ((m + (h * 60))* 60)) * 1000;
    const QString diff = QString("%1:%2:%3.%4")
                            .arg(h,  2, 10, QChar('0'))
                            .arg(m,  2, 10, QChar('0'))
                            .arg(s,  2, 10, QChar('0'))
                            .arg(ms, 3, 10, QChar('0'));
    return diff;
}

void MainWindow::on_pbLane1Lap_clicked()
{
    qint64 lapTime=0;
    if (mLane1Laps==0)// it's the first lap
        lapTime = mSessionTime*111;
    else
        lapTime = (mSessionTime - mLastLane1Tot)*111;
    ui->twLapTimes->setItem(mLane1Laps, 0, new QTableWidgetItem(CalculateTimeStr(lapTime)));
    mLastLane1Tot=mSessionTime;
    mLane1Laps++;
}

void MainWindow::on_pbLane2Lap_clicked()
{
    qint64 lapTime=0;
    if (mLane2Laps==0)// it's the first lap
        lapTime = mSessionTime*111;
    else
        lapTime = (mSessionTime - mLastLane2Tot)*111;
    ui->twLapTimes->setItem(mLane2Laps, 1, new QTableWidgetItem(CalculateTimeStr(lapTime)));
    mLastLane2Tot=mSessionTime;
    mLane2Laps++;
}

void MainWindow::on_pbSQLTest_clicked()
{
}
