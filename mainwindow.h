#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "records.h"
#include <map>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Records tableRecords;
    QString key = "1395";
    int turns = 0;
    QString countBulls(QString, QString);
    QString countCows(QString, QString);
    void victory();
    void startGame();
    void restartGame();
    void giveUp();
    bool check(QString str);
    bool gived_up = true;
    QString randomKey();

private slots:
    void on_pbEnter_clicked();
    void on_pbRecords_clicked();
    void on_pbNewGame_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
