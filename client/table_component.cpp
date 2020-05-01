#include "table_component.h"

table_component::table_component(QVector<QColor> colors, QVector<QString> labels, QWidget *parent)
    : BaseComponent (parent)
    , size_ (labels.size())
    , colors_ (colors)
    , table_ (new QTableWidget(this))
{
    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (qint32 i = 0; i < labels.size(); ++i)
    {
        table_->insertColumn(i);
        table_->setHorizontalHeaderItem(i, new QTableWidgetItem(labels[i]));
    }
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_->setSelectionMode(QAbstractItemView::NoSelection);
    connect(table_, &QTableWidget::itemActivated, this, &table_component::clicked_row);
    this->setFixedSize(15*5*labels.size(), 30*5);
    table_->setFixedSize(15*5*labels.size(), 30*5);
}

void table_component::clear()
{
    for (qint32 i = table_->rowCount() - 1; i >= 0; --i) table_->removeRow(i);
}

void table_component::set_data(table_component::row data)
{
    const qint32 num = table_->rowCount();
    table_->insertRow(num);
    for (qint32 i = 0; i < size_; ++i)
    {
        table_->setItem(num, i, new QTableWidgetItem());
        table_->item(num, i)->setText(QString::number(data.stats[i]));
    }
    QTableWidgetItem *col = new QTableWidgetItem(QString::number(num));
    col->setBackground(data.color);
    table_->setVerticalHeaderItem(num, col);
}

void table_component::clicked_row(QTableWidgetItem* data)
{
    QJsonObject res;
    if (data->column())
    {
        res["type"] = "select";
        res["num"] = data->column()-1;
    } else
    {
        res["type"] = "delete";
        res["num"] = data->row();
    }
    emit notify(res);
}
