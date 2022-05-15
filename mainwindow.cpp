#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QInputDialog>
#include <QDir>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->vlInterface);
    setWindowTitle("Bulls and Cows");
    ui->twResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QAction *foo = new QAction(this);                            //CTRL+E shortcut
    foo->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(foo, SIGNAL(triggered()), this, SLOT(on_pbEnter_clicked()));
    this->addAction(foo);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame(){
    gived_up = false;
    ui->leInput->setEnabled(true);
    ui->pbNewGame->setText("Give up");
    ui->lbStart->setText("Start the game");
    key = randomKey();
    for (int i = ui->twResults->rowCount(); i >= 0; i--) {
        ui->twResults->removeRow(i);
    }
}

void MainWindow::giveUp() {
    gived_up = true;
    ui->leInput->setEnabled(false);
    ui->lbStart->setText("Answer was " + key);
    ui->pbNewGame->setText("Try again");
}

QString MainWindow::randomKey() {
    QRandomGenerator* rnd = new QRandomGenerator;
    QString str = "", result = "";
    int step = 0;
    while (step < 4){
        str.setNum(rnd->global()->bounded(0,9));
        if (!result.contains(str)) {
            ++step;
            result += str;
        }
    }
    return result;
}

QString MainWindow::countBulls(QString key, QString temp) {
    int bulls = 0;
    for (int i = 0; i < 4; i++) {
        if (key.at(i) == temp.at(i)) {
            ++bulls;
        }
    }
    return temp.setNum(bulls);
}

QString MainWindow::countCows(QString key, QString temp) {
    int cows = 0;
    for (int i = 0; i < 4; i++) {
        if (key.contains(temp.at(i),Qt::CaseInsensitive)) {
            ++cows;
        }
    }
    return temp.setNum(cows);
}

bool MainWindow::check(QString str) {
    if (str.length()!=4) {return false;}
    for (int i = 0; i < 4; i++) {
        if ((!str.at(i).isDigit())||(str.count(str.at(i))!=1)) { return false; }
    }
    return true;
}

void MainWindow::on_pbEnter_clicked()
{
    QString str = ui->leInput->text();
    if (check(str)) {
        ui->leInput->clear();
        ui->twResults->insertRow(ui->twResults->rowCount());
        ui->twResults->setItem(ui->twResults->rowCount()-1, 0, new QTableWidgetItem(str));
        turns++;

        QString bulls = countBulls(key, str), cows = countCows(key, str);
        QString answer = bulls + " bulls, " + cows + " cows";
        ui->twResults->setItem(ui->twResults->rowCount()-1, 1, new QTableWidgetItem(answer));
        ui->lbStart->setText(answer);
        if (bulls == "4") {
            victory();
        }
    }
    else {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Information);
        msg.setText("Incorrect input");
        msg.exec();
    }
}

void MainWindow::on_pbRecords_clicked()
{
    tableRecords.show();
}


void MainWindow::on_pbNewGame_clicked()
{
    if (!gived_up) { giveUp();}
    else { startGame();}
}

void MainWindow::victory() {
    ui->pbNewGame->setText("Try again");
    ui->lbStart->setText("VICTORY!");
    bool ok;
    QString text = QInputDialog::getText(this, tr("Input"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    tableRecords.show();
    if (ok && !text.isEmpty()) {
        tableRecords.addItem(turns, text);
    }
    turns = 0;
    ui->leInput->setEnabled(false);
}
