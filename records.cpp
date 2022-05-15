#include "records.h"
#include <QHeaderView>


Records::Records(){
    resize(400,350);
    setMaximumSize(400,400);
    setMinimumSize(120,120);
    setColumnCount(2);
    QStringList strlist;
    strlist << "Turns" << "Names";
    setHorizontalHeaderLabels(strlist);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setWindowTitle("Top-10 players");
    addItem(4, "ProGamer");
    addItem(24, "Noobie");
    addItem(11, "misha2007");
    addItem(8, "AMOGUS");
    addItem(18, "fluffew");
    addItem(20, "jacub rozalski");
    addItem(13, "Darril");
    addItem(2, "凝固汽油弹");
    addItem(27, "unknow_player_20494621");
    addItem(45, "kfmvkhhgg");
}
void Records::addItem(int turns, QString name){
    QString str;
    insertRow(rowCount());
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setData(Qt::EditRole, turns);

    setItem(rowCount()-1, 0, item);
    setItem(rowCount()-1, 1, new QTableWidgetItem(name));
    sortItems(0);
    if (rowCount()>10) {
        removeRow(10);
    }


}

