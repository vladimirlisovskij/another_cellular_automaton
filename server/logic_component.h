#ifndef LOGIC_COMPONENT_H
#define LOGIC_COMPONENT_H

#include <QSet>
#include <QDateTime>
#include <QtMath>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QStack>

class logic_component : public QObject
{
/*
    * Реализует компонент содержащий логику игры
*/
    Q_OBJECT
public:
    struct Animal
    {
        qint32 speed;
        qint32 endurance;
        qint32 vitality;
        qint32 max_vitality;
    };
    logic_component(qint32 width, qint32 height, QObject* parent = nullptr);

signals:
    void notify(QJsonObject);

public slots:
    void add_animal (const Animal&, qint32 num, qint32 lvl);
    void add_grass (qint32);
    void remove_animal (qint32);
    void clear ();
    void tik ();

private:
    enum Grass_size {LITTLE, MEDIUM, BIG};
    const qint32 width;
    const qint32 height;
    const qint32 square;
    const qint32 _max_specs;
    qint32 animals_num = 0;
    QStack<qint32> _free_colors;
    QVector<qint32> _colors;
    QVector<qint32> all_animals_levels;
    QHash<QPair<qint32,qint32>,Grass_size> all_grass;
    QVector<QHash<QPair<qint32,qint32>,QVector<Animal>>> all_animals;
    QSet<QPair<qint32,qint32>> all_free_space;
    QPair<qint32,qint32> get_free_pos ();
    Animal new_animal (Animal f, Animal m);
    qint32 new_stat (qint32 f, qint32 m);
    QJsonObject make_data ();
    QJsonArray get_stat ();
    void update ();
    void move ();
    void eat ();
    void reproduction ();
    void animal_move (QHash<QPair<qint32,qint32>,QVector<Animal>>&);
};

#endif // LOGIC_COMPONENT_H
