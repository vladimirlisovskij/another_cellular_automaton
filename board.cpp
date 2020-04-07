#include "board.h"

board::board(QWidget* parent)
    : QTableWidget (parent)
{
    this->setFixedSize(15*30, 30*5);
    for (qint32 i = 0; i < 6; ++i) this->insertColumn(i);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setHorizontalHeaderItem(0, new QTableWidgetItem("Level"));
    this->setHorizontalHeaderItem(1, new QTableWidgetItem("Num"));
    this->setHorizontalHeaderItem(2, new QTableWidgetItem("S"));
    this->setHorizontalHeaderItem(3, new QTableWidgetItem("E"));
    this->setHorizontalHeaderItem(4, new QTableWidgetItem("V"));
    this->setHorizontalHeaderItem(5, new QTableWidgetItem("M"));

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::NoSelection);

    connect(this, &QTableWidget::itemActivated, this, &board::clicked_row);
}

void board::clear()
{
    const qint32 num = this->rowCount() - 1;
    for (qint32 i = num; i >=0; --i) this->removeRow(i);
}

void board::add_row(board::row data)
{
    const qint32 num = this->rowCount();
    this->insertRow(num);
    this->setItem(num, 0, new QTableWidgetItem());
    for (qint32 i = 0; i < 6; ++i)
    {
        this->setItem(num, i, new QTableWidgetItem());
        this->item(num, i)->setText(QString::number(data.stats[i]));
    }
    QTableWidgetItem *col = new QTableWidgetItem(QString::number(num));
    col->setBackground(data.color);
    this->setVerticalHeaderItem(num, col);
}

void board::clicked_row(QTableWidgetItem * data)
{
    if (data->column()) emit change_focus(data->column()-1);
    else emit erased_row(data->row());
}
