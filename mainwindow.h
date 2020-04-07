// ****************************************
// Главный класс
// Отвечает за управление другими классами
// ****************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include <playground.h>
#include <Ecosystem.h>
#include <panel.h>
#include <board.h>
#include <super_chart.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(qint32 width, qint32 height, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void get_data(QVector<QHash<QPair<qint32,qint32>,qint32>>);
    void get_animal (QVector<qint32>, qint32, qint32);
    void get_stat (QVector<QVector<qint32>>);
    void in_clear ();
    void erase (qint32);
    void erase_row (qint32);

signals:
    void new_data (QHash<QPair<qint32,qint32>,QPair<QColor,QString>>);
    void new_animal (Ecosystem::Animal, qint32, qint32);
    void out_clear ();
    void board_clear ();
    void new_stat (board::row);
    void del_animal (qint32);
    void graph_data (QVector<QPair<QColor,QVector<qint32>>>);

private:
    QVector<QColor> grass_colors {{0,255,164},{10,255,0},{160,255,0}};
    QVector<QColor> free_colors{Qt::red, Qt::blue, Qt::magenta,  Qt::yellow};
    QVector<QColor> animal_colors {};
    bool hide = true;
    const qint32 width;
    const qint32 height;
    playground* screen;
    Ecosystem* ecosys;
    panel* buts;
    super_chart* chart;
    QWidget* main;
    QHBoxLayout* main_lay;
    QVBoxLayout* panel_lay;
    QPushButton* open_close_but;
    board*   scoreboard;
    Ui::MainWindow *ui;

private slots:
    void open_close ();
};
#endif // MAINWINDOW_H
