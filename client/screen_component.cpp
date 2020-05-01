#include "screen_component.h"

screen_component::screen_component(qint32 width, qint32 height, QWidget *parent)
    : BaseComponent (parent)
    , width (width)
    , height (height)
    , first_buf (new QTableWidget(height, width, this)), second_buf (new QTableWidget(height, width, this))
{
    first_buf->verticalHeader()->setMinimumSectionSize(15); second_buf->verticalHeader()->setMinimumSectionSize(15);   /* задаем длину и ширину ячеек */
    first_buf->verticalHeader()->setMaximumSectionSize(15); second_buf->verticalHeader()->setMaximumSectionSize(15);
    first_buf->verticalHeader()->setDefaultSectionSize(15); second_buf->verticalHeader()->setDefaultSectionSize(15);
    first_buf->horizontalHeader()->setMinimumSectionSize(15); second_buf->horizontalHeader()->setMinimumSectionSize(15);
    first_buf->horizontalHeader()->setMaximumSectionSize(15); second_buf->horizontalHeader()->setMaximumSectionSize(15);
    first_buf->horizontalHeader()->setDefaultSectionSize(15); second_buf->horizontalHeader()->setDefaultSectionSize(15);
    first_buf->verticalHeader()->setVisible(false); second_buf->verticalHeader()->setVisible(false);   /* убираем подписи столбиков и строчек */
    first_buf->horizontalHeader()->setVisible(false); second_buf->horizontalHeader()->setVisible(false);
    first_buf->setStyleSheet(QString("border: 0")); second_buf->setStyleSheet(QString("border: 0"));   /* уменьшаем границы между клетками */
    first_buf->setSelectionMode(QAbstractItemView::NoSelection); second_buf->setSelectionMode(QAbstractItemView::NoSelection);   /* убираем возможности выделения */
    first_buf->setEditTriggers(QAbstractItemView::NoEditTriggers); second_buf->setEditTriggers(QAbstractItemView::NoEditTriggers);   /* запрещаем редактирование ячеек */
    first_buf->setFixedWidth(15*width); second_buf->setFixedWidth(15*width);   /* устанавливаем точные размеры таблицы */
    first_buf->setFixedHeight(15*height); second_buf->setFixedHeight(15*height);
    /* создаем объеты ячеек таблицы */
    for (qint32 x = 0; x < height; x++)
    {
        for (qint32 y = 0; y < width; y++)
        {
            first_buf->setItem(x,y, new QTableWidgetItem());
            second_buf->setItem(x,y, new QTableWidgetItem());
        }
    }
    second_buf->hide();
    this->setFixedSize(15*width, 15*height);
}

void screen_component::set_data(QHash<QPair<qint32,qint32>,QPair<QColor,QString>> data)
{
    for (qint32 x = 0; x < height; x++)
    {
        for (qint32 y = 0; y < width; y++)
        {
            second_buf->item(x,y)->setBackground(Qt::white);
            second_buf->item(x,y)->setText("");
        }
    }
    for (auto cell = data.begin(); cell != data.end(); ++cell)
    {
        second_buf->item(cell.key().first, cell.key().second)->setBackground(cell.value().first);
        second_buf->item(cell.key().first, cell.key().second)->setText(cell.value().second);
    }
    qSwap(first_buf, second_buf);
    first_buf->show(); second_buf->hide();
}
