// ****************************
// Отвечает за вывод статистики
// ****************************

#ifndef BOARD_H
#define BOARD_H

#include <QTableWidget>
#include <QHeaderView>

class board : public QTableWidget
{
    Q_OBJECT
public:
    struct row {
        QColor color;
        QVector<qint32> stats;
    };
    board (QWidget *parent = nullptr);

public slots:
    void clear ();
    void add_row(row);

private slots:
    void clicked_row (QTableWidgetItem*);

signals:
    void erased_row (qint32);
    void change_focus (qint32);
};

#endif // BOARD_H
