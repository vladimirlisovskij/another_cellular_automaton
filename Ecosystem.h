// *********************
// Содержит логику игры
// *********************

#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <QVector>
#include <QSet>
#include <QDateTime>
#include <QtMath>
#include <QWidget>

class Ecosystem : public QObject
{
    Q_OBJECT
public:
    struct Animal
    {
        qint32 speed;
        qint32 endurance;
        qint32 vitality;
        qint32 max_vitality;
    };
    Ecosystem (qint32 width, qint32 height, QWidget *parent = nullptr);

public slots:
    void add_animal (Animal, qint32, qint32);
    void add_grass (qint32);
    void remove_animal (qint32);
    void clear ();
    void tik ();

signals:
    void new_data (QVector<QHash<QPair<qint32,qint32>,qint32>>);
    void new_param (QVector<QVector<qint32>>);
    void erase (qint32);

private:
    const qint32 width, height, square;
    enum Grass_size {LITTLE, MEDIUM, BIG};
    qint32 animals_num = 0;
    QVector<qint32> all_animals_levels;
    QHash<QPair<qint32,qint32>,Grass_size> all_grass;
    QVector<QHash<QPair<qint32,qint32>,QVector<Animal>>> all_animals;
    QSet<QPair<qint32,qint32>> all_free_space;
    QPair<qint32,qint32> get_free_pos ();
    Animal new_animal (Animal f, Animal m);
    qint32 new_stat (qint32 f, qint32 m);
    QVector<QHash<QPair<qint32,qint32>,qint32>> get_data ();
    QVector<QVector<qint32>> get_stat ();
    void move ();
    void eat ();
    void reproduction ();
    void animal_move (QHash<QPair<qint32,qint32>,QVector<Animal>>&);
};


#endif // ECOSYSTEM_H
