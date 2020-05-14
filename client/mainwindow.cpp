#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , free_colors_ ({Qt::red, Qt::blue, Qt::magenta, Qt::yellow})
    , grass_colors_ ({{0,255,164},{10,255,0},{160,255,0}})
{
    const qint32 width = 30;
    const qint32 height = 30;

    const QVector<QString> graph_labels {"Number", "Speed", "Endurance", "Vitality", "Max vitality"};
    const QVector<QString> board_labs {"Level", "Num", "S", "E", "V", "Max v"};
    const QVector<QString> panel1_labs {"grass size"};
    const QVector<QString> panel2_labs {"animal number", "animal speed", "animal endurance", "animal vitality", "animal max vitality"};

    QVector<panel_component_leaf*> panel1_leafs;
    QVector<panel_component_leaf*> panel2_leafs;
    for (auto i : panel1_labs) panel1_leafs.push_back(new panel_component_leaf(i, 1, width*height));
    for (auto i : panel2_labs) panel2_leafs.push_back(new panel_component_leaf(i, 1, width*height));
    panel2_leafs.push_back(new panel_component_leaf("animal level", 0, width*height));

    QVector<graph_component_leaf*> graph_leafs;
    for (auto i : graph_labels) graph_leafs.push_back(new graph_component_leaf(i, free_colors_));

    panel1_ = new panel_component(panel1_leafs,"Add grass", this);
    panel2_ = new panel_component(panel2_leafs,"Add animal", this);
    table_ = new table_component(free_colors_, board_labs, this);
    screen_ = new screen_component(width, height, this);
    graph_ = new graph_component(graph_leafs, this);
    start_ = new start_component("Start", "Stop", this);
    restart_ = new restart_component("Clear", this);
    client_ = new client_component(QHostAddress("127.0.0.1"), 4242, this);

    connect(start_, &start_component::notify, this, &MainWindow::next);
    connect(table_, &table_component::notify, this, &MainWindow::change_focus);
    connect(panel1_, &panel_component::notify, this, &MainWindow::add_grass);
    connect(panel2_, &panel_component::notify, this, &MainWindow::add_animal);
    connect(restart_, &restart_component::notify, this, &MainWindow::clear);
    connect(client_, &client_component::notify, this, &MainWindow::change_stats);

    QWidget* main = new QWidget;
    QHBoxLayout* main_lay = new QHBoxLayout;
    QVBoxLayout* editor_lay = new QVBoxLayout;
    QVBoxLayout* panel_lay = new QVBoxLayout;
    QGridLayout* buts_lay = new QGridLayout;
    main_lay->addWidget(screen_);

    editor_lay->addLayout(buts_lay);
    editor_lay->addWidget(panel1_);
    editor_lay->addWidget(panel2_);
    editor_lay->setContentsMargins(0,0,0,0);
    editor_lay->setSpacing(0);

    panel_lay->addWidget(table_);
    panel_lay->addWidget(graph_);
    panel_lay->setContentsMargins(0,0,0,0);
    panel_lay->setSpacing(0);

    buts_lay->addWidget(client_, 0, 0, 1, 2);
    buts_lay->addWidget(start_, 1, 0, 1, 1);
    buts_lay->addWidget(restart_,  1, 1, 1, 1);
    buts_lay->setAlignment(Qt::AlignTop);
    buts_lay->setContentsMargins(0,0,0,0);
    buts_lay->setSpacing(0);

    main_lay->addLayout(panel_lay);
    main_lay->addLayout(editor_lay);
    main->setLayout(main_lay);
    main_lay->setContentsMargins(0,0,0,0);
    main_lay->setSpacing(0);

    this->setCentralWidget(main);
    this->setFixedWidth(1161);
    this->setFixedHeight(15*30);
}

void MainWindow::change_focus(QJsonObject data)
{
    qint32 num = data["num"].toInt();
    if (data["type"] == "select")
    {
        graph_->show(num);
    } else client_->write(data);
}

void MainWindow::clear(QJsonObject data)
{
    client_->write(data);
}

void MainWindow::add_animal(QJsonObject data)
{

    data["type"] = "animal";
    client_->write(data);
}

void MainWindow::add_grass(QJsonObject data)
{
    data["type"] = "grass";
    client_->write(data);
}

void MainWindow::next(QJsonObject data)
{
    client_->write(data);
}

void MainWindow::change_stats(QJsonObject data)
{
    QString type = data["type"].toString();
    if (type != "grass" && type != "next")
    {
        graph_->clear();
    }
    table_->clear();
    QVector<QPair<QColor,QVector<qint32>>> graph_data;
    QJsonArray stats = data["stats"].toArray();
    QJsonArray colors = data["colors"].toArray();
    for (qint32 i = 0; i < stats.size(); ++i)
    {
        table_component::row res;
        res.color = free_colors_[colors[i].toInt()];
        QVector<qint32> animal_stats;
        for (auto j : stats[i].toArray()) animal_stats.push_back(j.toInt());
        res.stats = animal_stats;
        table_->set_data(res);
        animal_stats.pop_front();
        graph_data.push_back(QPair<QColor,QVector<qint32>>{free_colors_[colors[i].toInt()],animal_stats});
    }
    graph_->set_data(graph_data);
    QHash<QPair<qint32,qint32>,QPair<QColor,QString>> screen_data;
    QJsonObject koord = data["koord"].toObject();
    QJsonArray grass = koord["grass"].toArray();
    QJsonArray animals = koord["animals"].toArray();
    for (auto i : grass)
    {
        QJsonObject key_json = i.toObject()["key"].toObject();
        QPair<qint32,qint32> key = {key_json["x"].toInt(),key_json["y"].toInt()};
        qint32 val = i.toObject()["value"].toInt();
        screen_data[key] = QPair<QColor,QString>{grass_colors_[val], " "};
    }
    for (qint32 i = 0; i != animals.size(); ++i)
    {
        QJsonArray spec = animals[i].toArray();
        for (qint32 j = 0; j != spec.size(); ++j)
        {
            QJsonObject key_json = spec[j].toObject()["key"].toObject();
            QPair<qint32,qint32> key = {key_json["x"].toInt(),key_json["y"].toInt()};
            qint32 val = spec[j].toObject()["value"].toInt();
            screen_data[key] = QPair<QColor,QString>{free_colors_[colors[i].toInt()], QString::number(val)};
        }
    }
    screen_->set_data(screen_data);
}
