#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPair>
#include <QHash>
#include <QPushButton>
#include <QVector>
#include <QHeaderView>
#include <QLayout>
#include <QWidget>
#include <QThread>
#include <QDateTime>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class game : public QThread
{
    Q_OBJECT

public:
    game(qint32 width, qint32 height);
    void generate ();
    QVector<QHash<QPair<qint32,qint32>,qint32>>*  get_data();
    ~game ();

protected:
    void run () override;

private:
    const qint32 width, height, size;
    struct Animal { qint32 speed, endurance, vitality, max_vitality; };
    enum Grass { LITTLE, MIDDLE, BIG};
    QHash<QPair<qint32,qint32>,Grass>* grass_deq;
    QHash<QPair<qint32,qint32>,QVector<Animal>>* bunny_deq;
    QHash<QPair<qint32,qint32>,QVector<Animal>>* wolf_deq;
    QHash<QPair<qint32,qint32>,QVector<game::Animal>>* animal_move (QHash<QPair<qint32,qint32>,QVector<Animal>>* animal);
    QPair<qint32,qint32> random_pos (qint32 speed);
    QPair<qint32,qint32> random_cell ();
    Animal new_animal (Animal papa, Animal mama);
    qint32 generic (qint32 papa_param, qint32 mama_param);
    void reproduction (QHash<QPair<qint32,qint32>,QVector<Animal>>* animal);
    void clear ();
    void move ();
    void eat ();

signals:
    void new_data ();

};

/*____U_I____C_L_A_S_S____*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow (qint32 width, qint32 height, QWidget* parent = nullptr);
    ~MainWindow ();

private:
    bool is_play = false;
    struct {QColor
            wolf {250,0,0},
            bunny {0,50,255},
            grass_l {0,255,164},
            grass_m {10,255,0},
            grass_b {160,255,0},
            bg {255, 255, 255};
           } colors;
    const qint32 width, height;
    QTableWidget* playground;
    QTableWidget* playground_second;
    game* evolution;
    QPushButton* start_stop_but;
    QPushButton* restart_but;
    QWidget* main_widget;
    QVBoxLayout* total;
    QHBoxLayout* panel;
    void clear ();
    void swap_bufs();
    Ui::MainWindow* ui;

public slots:
    void set_data ();
    void start_stop ();
    void restart ();
};

#endif // MAINWINDOW_H
