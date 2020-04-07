#include "panel.h"

panel::panel(qint32 max_size, QWidget *parent)
    : QWidget (parent)
    , max_size (max_size)
    , panel_lay (new QGridLayout)
{
    buts["next"] = new QPushButton("Next");
    buts["clear"] = new QPushButton("Clear");
    buts["grass"] = new QPushButton("Add grass");
    buts["animal"] = new QPushButton("Add animal");

    labs["grass_num"] = new QLabel("Grass number");
    labs["animal_num"] = new QLabel("Animal number");
    labs["animal_lvl"] = new QLabel("Animal level");
    labs["animal_s"] = new QLabel("Animal speed");
    labs["animal_e"] = new QLabel("Animal endurance");
    labs["animal_v"] = new QLabel("Animal vitality");
    labs["animal_mv"] = new QLabel("Animal max vitality");

    rows["grass_num"] = new QSpinBox;
    rows["animal_num"] = new QSpinBox;
    rows["animal_lvl"] = new QSpinBox;
    rows["animal_s"] = new QSpinBox;
    rows["animal_e"] = new QSpinBox;
    rows["animal_v"] = new QSpinBox;
    rows["animal_mv"] = new QSpinBox;

    for (auto i : buts) i->setFixedHeight(30);
    for (auto i : labs) i->setFixedHeight(30);
    for (auto i : rows)
    {
        i->setFixedHeight(30);
        i->setMinimum(1);
        i->setMaximum(max_size);
    }
    rows["animal_lvl"]->setMinimum(0);

    panel_lay->addWidget(buts["next"], 0, 0, 1, 1);
    panel_lay->addWidget(buts["clear"], 0, 1, 1, 1);
    panel_lay->addWidget(labs["grass_num"], 1, 0, 1, 1);
    panel_lay->addWidget(rows["grass_num"], 1, 1, 1, 1);
    panel_lay->addWidget(buts["grass"], 2, 0, 1, 2);
    panel_lay->addWidget(labs["animal_num"], 3, 0, 1, 1);
    panel_lay->addWidget(rows["animal_num"], 3, 1, 1, 1);
    panel_lay->addWidget(labs["animal_s"], 4, 0, 1, 1);
    panel_lay->addWidget(rows["animal_s"], 4, 1, 1, 1);
    panel_lay->addWidget(labs["animal_e"], 5, 0, 1, 1);
    panel_lay->addWidget(rows["animal_e"], 5, 1, 1, 1);
    panel_lay->addWidget(labs["animal_v"], 6, 0, 1, 1);
    panel_lay->addWidget(rows["animal_v"], 6, 1, 1, 1);
    panel_lay->addWidget(labs["animal_mv"], 7, 0, 1, 1);
    panel_lay->addWidget(rows["animal_mv"], 7, 1, 1, 1);
    panel_lay->addWidget(labs["animal_lvl"], 8, 0, 1, 1);
    panel_lay->addWidget(rows["animal_lvl"], 8, 1, 1, 1);
    panel_lay->addWidget(buts["animal"], 9, 0, 1, 2);

    this->setLayout(panel_lay);
    panel_lay->setContentsMargins(0,0,0,0);
    panel_lay->setSpacing(0);
    this->setFixedSize(15*30, 30*10);

    connect(buts["grass"], &QPushButton::clicked, this, &panel::get_grass);
    connect(buts["animal"], &QPushButton::clicked, this, &panel::get_animal);
    connect(buts["next"], &QPushButton::clicked, this, &panel::get_next);
    connect(buts["clear"], &QPushButton::clicked, this, &panel::get_clear);
}

void panel::get_animal ()
{
    QVector<qint32> res;
    res.push_back(rows["animal_s"]->value());
    res.push_back(rows["animal_e"]->value());
    res.push_back(rows["animal_v"]->value());
    res.push_back(rows["animal_mv"]->value());
    emit new_animal(res, rows["animal_num"]->value(), rows["animal_lvl"]->value());
}

void panel::get_grass ()
{
    emit new_grass(rows["grass_num"]->value());
}

void panel::get_next()
{
    emit next ();
}

void panel::get_clear()
{
    emit clear ();
}
