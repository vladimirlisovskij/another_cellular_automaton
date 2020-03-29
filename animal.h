#ifndef ANIMAL_H
#define ANIMAL_H

#include <QLabel>

class Animal : public QLabel
{
    Q_OBJECT

public:
    struct SPECIAL {
        qint8 speed, reaction, endurance, vitality, max_vitality;
        SPECIAL(qint8 speed, qint8 reaction, qint8 endurance, qint8 vitality, qint8 max_vitality) :
            speed(speed),
            reaction(reaction),
            endurance(endurance),
            vitality(vitality),
            max_vitality(max_vitality)
        {}
    };
    Animal(qint8 speed, qint8 reaction, qint8 endurance, qint8 vitality, qint8 max_vitality, QWidget* parent = nullptr);
    SPECIAL* get_data() const;
private:
    const qint8 speed, reaction, endurance, vitality, max_vitality;

};

#endif // ANIMAL_H
