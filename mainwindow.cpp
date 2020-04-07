#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(qint32 width, qint32 height, QWidget *parent)
    : QMainWindow (parent)
    , width (width)
    , height (height)
    , screen (new playground (width, height, this))
    , ecosys (new Ecosystem (width, height))
    , buts (new panel (height*width, this))
    , chart (new super_chart(free_colors))
    , main (new QWidget (this))
    , main_lay (new QHBoxLayout)
    , panel_lay (new QVBoxLayout)
    , open_close_but (new QPushButton (">"))
    , scoreboard (new board)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->hide();
    this->setCentralWidget(main);

    main->setLayout(main_lay);
    main_lay->addWidget(screen);
    panel_lay->addWidget(buts);
    panel_lay->addWidget(scoreboard);
    panel_lay->addWidget(chart);

    main_lay->addLayout(panel_lay);
    main_lay->addWidget(open_close_but);
    main_lay->setContentsMargins(0,0,0,0);
    main_lay->setSpacing(0);
    panel_lay->setContentsMargins(0,0,0,0);
    panel_lay->setSpacing(0);

    panel_lay->setAlignment(Qt::AlignTop);

    open_close_but->setFixedSize(30, 15*qMax(height, 50));
    buts->hide();
    scoreboard->hide();
    chart->hide();

    this->setFixedSize(15*(width + 2), 15*qMax(height, 50));
    connect(open_close_but, &QPushButton::clicked, this, &MainWindow::open_close);

    connect(buts, &panel::next, ecosys, &Ecosystem::tik);

    connect(ecosys, &Ecosystem::erase, this, &MainWindow::erase);

    connect(scoreboard, &board::change_focus, chart, &super_chart::set_visible);

    connect(ecosys, &Ecosystem::new_param, this, &MainWindow::get_stat);
    connect(this, &MainWindow::new_stat, scoreboard, &board::add_row);

    connect(scoreboard, &board::erased_row, this, &MainWindow::erase_row);
    connect(this, &MainWindow::del_animal, ecosys, &Ecosystem::remove_animal);
    connect(this, &MainWindow::del_animal, chart, &super_chart::clear);

    connect(buts, &panel::clear, this, &MainWindow::in_clear);
    connect(this, &MainWindow::out_clear, ecosys, &Ecosystem::clear);
    connect(this, &MainWindow::board_clear, scoreboard, &board::clear);
    connect(this, &MainWindow::board_clear, chart, &super_chart::clear);

    connect(buts, &panel::new_grass, ecosys, &Ecosystem::add_grass);

    connect(buts, &panel::new_animal, this, &MainWindow::get_animal);
    connect(this, &MainWindow::new_animal, ecosys, &Ecosystem::add_animal);
    connect(this, &MainWindow::new_animal, chart, &super_chart::clear);

    connect(ecosys, &Ecosystem::new_data, this, &MainWindow::get_data);
    connect(this, &MainWindow::new_data, screen, &playground::set_data);

    connect(this, &MainWindow::graph_data, chart, &super_chart::set_data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_data(QVector<QHash<QPair<qint32,qint32>,qint32> > data)
{
    QHash<QPair<qint32,qint32>,QPair<QColor,QString>> res;
    for (auto iter = data.begin(); iter != data.end(); ++iter)
    {
        if (iter == data.begin())
        {
            for (auto cell = iter->begin(); cell != iter->end(); ++cell)
            {
                res[cell.key()] = QPair<QColor,QString>{grass_colors[cell.value()], " "};
            }
        }
        else
        {
            for (auto cell = iter->begin(); cell != iter->end(); ++cell)
            {
                qint32 pos = data.indexOf(*iter)-1;
                res[cell.key()] = QPair<QColor,QString>{animal_colors[pos], QString::number(cell.value())};
            }
        }
    }
    emit new_data(res);
}

void MainWindow::get_animal(QVector<qint32> data, qint32 num, qint32 lvl)
{
    if (!free_colors.empty())
    {
        Ecosystem::Animal res;
        res.speed = data[0];
        res.endurance = data[1];
        res.vitality = data[2];
        res.max_vitality = data[3];
        animal_colors.push_back(*free_colors.begin());
        free_colors.pop_front();
        emit new_animal(res, num, lvl);
    }
}

void MainWindow::get_stat(QVector<QVector<qint32>> data)
{
    scoreboard->clear();
    QVector<QPair<QColor,QVector<qint32>>> temp;
    for (qint32 i = 0; i < data.size(); ++i)
    {
        board::row res;
        res.color = animal_colors[i];
        res.stats = data[i];
        emit new_stat(res);

        temp.push_back(QPair<QColor,QVector<qint32>>{animal_colors[i],data[i]});
    }
    emit graph_data(temp);

}

void MainWindow::in_clear()
{
    while (!animal_colors.empty())
    {
        free_colors.push_back(*animal_colors.begin());
        animal_colors.pop_front();
    }
    emit out_clear();
    emit board_clear();
}

void MainWindow::erase(qint32 i)
{
    free_colors.push_back(animal_colors[i]);
    animal_colors.remove(i);
}

void MainWindow::erase_row(qint32 i)
{
    erase(i);
    del_animal(i);
}

void MainWindow::open_close()
{
    if (hide)
    {
        buts->show();
        scoreboard->show();
        chart->show();
        this->setFixedSize(15*(width + 32), 15*qMax(height, 50));
        open_close_but->setText("<");
    } else
    {
        buts->hide();
        scoreboard->hide();
        chart->hide();
        this->setFixedSize(15*(width + 2), 15*qMax(height, 50));
        open_close_but->setText(">");
    }
    hide = !hide;
}
