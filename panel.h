// ************************
// Отвечает за ввод данных
// ************************

#ifndef PANEL_H
#define PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVector>

class panel : public QWidget
{
    Q_OBJECT
public:
    panel(qint32 max_size, QWidget *parent = nullptr);

private:
    const qint32 max_size;
    QHash<QString,QPushButton*> buts;
    QHash<QString,QLabel*> labs;
    QHash<QString,QSpinBox*> rows;
    QGridLayout* panel_lay;
    QWidget* main;

private slots:
    void get_animal ();
    void get_grass ();
    void get_next ();
    void get_clear ();

signals:
    void new_animal (QVector<qint32>, qint32, qint32);
    void new_grass (qint32);
    void next ();
    void clear ();

};

#endif // PANEL_H
