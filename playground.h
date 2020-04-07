// ***************************
// Отвечает за вывод картинки
// ***************************

#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

class playground : public QWidget
{
    Q_OBJECT
public:
    playground(qint32 width, qint32 height, QWidget *parent = nullptr);

public slots:
    void set_data (QHash<QPair<qint32,qint32>,QPair<QColor,QString>>);

private:
    const qint32 width;
    const qint32 height;
    QTableWidget* first_buf;
    QTableWidget* second_buf;
};

#endif // PLAYGROUND_H
