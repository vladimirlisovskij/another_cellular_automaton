#ifndef LOGIC_COMPONENT_H
#define LOGIC_COMPONENT_H

#include "base_component.h"

#include <QWidget>
#include <QSet>
#include <QDateTime>
#include <QtMath>
#include <QWidget>

class logic_component : public BaseLogicComponent
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
    logic_component(qint32 width, qint32 height, QWidget* parent = nullptr);

public slots:
    void add_animal (Animal, qint32, qint32);
    void add_grass (qint32);
    void remove_animal (qint32);
    void clear ();
    void tik ();

private:
    void update ();
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
    QVector<QHash<QPair<qint32,qint32>,qint32>> make_data ();
    QVector<QVector<qint32>> get_stat ();
    void move ();
    void eat ();
    void reproduction ();
    void animal_move (QHash<QPair<qint32,qint32>,QVector<Animal>>&);
};

#endif // LOGIC_COMPONENT_H
