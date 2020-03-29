#include "animal.h"

Animal::Animal(qint8 speed, qint8 reaction, qint8 endurance, qint8 vitality, qint8 max_vitality, QWidget *parent) :
    QLabel(parent),
    speed(speed),
    reaction(reaction),
    endurance(endurance),
    vitality(vitality),
    max_vitality(max_vitality)
{   /* устанавливаем надпись на ярлык */
    this->setText(
                QString::number(speed) + QString(" ") +
                QString::number(reaction) + QString(" ") +
                QString::number(endurance) + QString(" ") +
                QString::number(vitality) + QString(" ") +
                QString::number(max_vitality)
                );
}

Animal::SPECIAL* Animal::get_data() const{
    /* возвращаем характеристики животного */
    return new SPECIAL{speed, reaction, endurance, vitality, max_vitality};
}
