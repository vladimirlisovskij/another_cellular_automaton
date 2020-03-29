#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

/*____G_A_M_E____C_L_A_S_S____*/

game::game(qint32 width, qint32 height):
    QThread(),
    width(width),
    height(height),
    size (width*height),
    grass_deq(new QHash<QPair<qint32,qint32>,Grass>),
    bunny_deq(new QHash<QPair<qint32,qint32>,QVector<Animal>>),
    wolf_deq(new QHash<QPair<qint32,qint32>,QVector<Animal>>)
{
}

game::~game()
{
    clear();
    delete grass_deq;
    delete bunny_deq;
    delete wolf_deq;
}

void game::run()
{
    qsrand(QDateTime::currentDateTime().toTime_t());   /* рандом для генетики и перемещений*/
    move ();   /* движение -> еда -> размножение */
    eat();
    reproduction(bunny_deq);
    reproduction(wolf_deq);
    QThread::sleep(1);  // TODO: заменить на переменную с регулятором
    emit new_data();  /* обабатываем -> высылаем */
}

void game::clear()
{
    for (auto i = bunny_deq->begin(); i != bunny_deq->end(); ++i) {
        i.value().clear();
    }
    for (auto i = wolf_deq->begin(); i != wolf_deq->end(); ++i) {
        i.value().clear();
    }
    bunny_deq->clear();
    grass_deq->clear();
    wolf_deq->clear();
}

void game::move()
{
    QVector<QPair<qint32,qint32>> temp;
    /* рост травы */
    for (auto iter = grass_deq->begin(); iter != grass_deq->end(); ++iter)
    {
        switch (iter.value()) {
            case LITTLE:
                iter.value() = MIDDLE;
                break;
            case MIDDLE:
                iter.value() = BIG;
                break;
            case BIG:   /* ищем свободые соседние клетки */
                for (qint32 x = iter.key().first-1; x < iter.key().first + 2; x++) {
                    for (qint32 y = iter.key().second-1; y < iter.key().second + 2; y++) {
                        if (x == iter.key().first && y == iter.key().second) continue;
                        if (x < height && x >= 0 && y < width && y >= 0 && !grass_deq->contains(QPair<qint32,qint32>{x,y})) temp.push_back(QPair<qint32,qint32>{x,y});
                    }
                }
                break;
        }
    }
    for (auto i: temp) (*grass_deq)[i] = LITTLE;   /* заполняем то что нашли */
    bunny_deq = animal_move(bunny_deq);   /* идентичное поведение для движения животных */
    wolf_deq = animal_move(wolf_deq);
}

void game::eat()
{
    /* кормежка кроликов */
    for (auto bunny_ptr = bunny_deq->begin(); bunny_ptr != bunny_deq->end(); ++bunny_ptr) {   /* итериируемся по словарю кроликов*/
        qint32 point = 0;
        if (grass_deq->contains(bunny_ptr.key())) {   /* если на одной клетке и трава и кролии */
            point = 6 * (static_cast<qint32>((*grass_deq)[bunny_ptr.key()]) + 1) / bunny_ptr.value().size();   /* каждый кролик получит часть энергии травы */
            grass_deq->remove(bunny_ptr.key());   /* удаляем съеденную траву */
        }
        for (auto bunny = bunny_ptr.value().begin(); bunny != bunny_ptr.value().end(); ++bunny) {   /* кормим кроликов */
            bunny->vitality = qMin(bunny->vitality + point, bunny->max_vitality);
        }
    }
    /* кормежка волков */
    for  (auto wolf_ptr = wolf_deq->begin(); wolf_ptr != wolf_deq->end(); ++wolf_ptr){   /*  аналогично для волков */
        qint32 point = 0;
        if (bunny_deq->contains(wolf_ptr.key())) {
            point = 15 * (*bunny_deq)[wolf_ptr.key()].size();
            bunny_deq->remove(wolf_ptr.key());
        }
        for (auto wolf = wolf_ptr.value().begin(); wolf != wolf_ptr.value().end(); ++wolf) {
            wolf->vitality = qMin(wolf->vitality + point, wolf->max_vitality);
        }
    }
}

QPair<qint32, qint32> game::random_pos(qint32 speed)
{
    qint32 x, y;
    do {
        x = qrand() % (2 * speed + 1) - speed;
        y = qrand() % (2 * speed + 1) - speed;
    } while (x == 0 && y == 0); /* мы не можем стоять на месте */
    return QPair<qint32,qint32> {x,y};
}

QHash<QPair<qint32,qint32>,QVector<game::Animal>>* game::animal_move(QHash<QPair<qint32,qint32>,QVector<game::Animal>>* animal)
{
    QHash<QPair<qint32,qint32>,QVector<game::Animal>>* temp = new QHash<QPair<qint32,qint32>,QVector<game::Animal>>;   /* данные для следущего шага */
    for (auto iter = animal->begin(); iter != animal->end(); ++iter)   /* итерируемся по словарю животных */
    {
            QPair<qint32,qint32> pos = iter.key();   /* координаты ячейки на текущей итерации */
            for (Animal zoo: iter.value())   /* итерируемся по животным в этой ячейке */
            {
                if ((zoo.endurance < zoo.vitality))   /* если животному хватит энергии для движения */
                {
                    QPair<qint32,qint32> new_pos = random_pos(zoo.speed);   /* получаем случайный сдвиг координат животного */
                    new_pos.first += pos.first;   /* прибавляем сдвиг к координатам */
                    new_pos.first = qMax(0, new_pos.first);   /* смотрим, чтобы не выйти за рамки */
                    new_pos.first = qMin(height - 1, new_pos.first);
                    new_pos.second += pos.second;
                    new_pos.second = qMax(0, new_pos.second);
                    new_pos.second = qMin(width - 1, new_pos.second);
                    zoo.vitality -= zoo.endurance;   /* отнимаем энергию на перемещение */
                    if (!temp->contains(new_pos)) (*temp)[new_pos] = QVector<Animal> ();   /* создадим массив, если до этого в словаре его не было */
                    (*temp)[new_pos].push_back(zoo);   /* переместим результат в словарь данных для следующего шага */
                }
            }

        }
    delete animal;  /* удаляем старые данные */
    return temp;
}

void game::generate()
{
    clear();
    const qint32 grass = size/2;   /* трава занимает 50%, клролики 25%, волки 12% % */
    const qint32 bunny = grass/2;
    const qint32 wolfs = bunny/2;
    for (qint32 i = 0; i < bunny; i++) {   /* заполняем массивы зверями и травой */
        (*bunny_deq)[random_cell()] = QVector<Animal>{Animal{5,10,50,50}};   /* волки теряют энергию в два раза медленнее */
    }
    for (qint32 i = 0; i < wolfs; i ++){
        (*wolf_deq)[random_cell()] = QVector<Animal>{Animal{5,5,50,50}};
    }
    for (qint32 i = 0; i < grass; i++) {
        (*grass_deq).insert(random_cell(),LITTLE);
    }
    emit new_data();   /* говорим, что можно забрать данные */
}

QVector<QHash<QPair<qint32,qint32>,qint32>>* game::get_data()
{
    QVector<QHash<QPair<qint32,qint32>,qint32>>* data = new QVector<QHash<QPair<qint32,qint32>,qint32>>;  /* массив-ответ */
    QHash<QPair<qint32,qint32>,qint32> grass_temp;  /* заполняем по типу { координаты ячейки | возраст травы } */
    for (auto iter = grass_deq->begin(); iter != grass_deq->end(); ++iter) {
        grass_temp[iter.key()] = static_cast<qint32>(iter.value());
    }
    data->push_back(grass_temp);
    QHash<QPair<qint32,qint32>,qint32> bunny_temp;   /* заполняем по типу { координаты ячейки | количество зверей } */
    for (auto iter = bunny_deq->begin(); iter != bunny_deq->end(); ++iter) {
        bunny_temp[iter.key()] = iter.value().size();
    }
    data->push_back(bunny_temp);
    QHash<QPair<qint32,qint32>,qint32> wolf_temp;
    for (auto iter = wolf_deq->begin(); iter != wolf_deq->end(); ++iter) {
        wolf_temp[iter.key()] = iter.value().size();
    }
    data->push_back(wolf_temp);
    return data;
}

QPair<qint32, qint32> game::random_cell()
{
    QPair<qint32,qint32> pos;
    do {   /* берем рандомные координаты; повторяем если видели их до этого */
        pos.first = qrand()%height;
        pos.second = qrand()%width;
    } while (grass_deq->contains(pos) || bunny_deq->contains(pos) || wolf_deq->contains(pos));
    return  pos;
}

game::Animal game::new_animal(Animal papa, Animal mama)
{
    Animal res {
            generic(papa.speed, mama.speed),
            generic(papa.endurance, mama.endurance),
            generic(papa.vitality, mama.vitality),
            generic(papa.max_vitality, mama.max_vitality)
    };
    res.vitality = qMin(res.vitality, res.max_vitality);
    return res;
}

qint32 game::generic(qint32 papa_param, qint32 mama_param)
{
    /* кроссовер */
    qint32 max_binary_len = qMax(qLn(papa_param)/qLn(2), qLn(mama_param)/qLn(2));
    qint32 num = qrand() % (max_binary_len + 1);
    qint32 two = qPow(2, num);
    int result = papa_param - (papa_param%two) + (mama_param%two);
    /* мутация  */
    if (qrand() % 4 == 0) {
        num = qrand() % (max_binary_len + 1);
        result += qPow(2, num) * ((result>>num)&1 ? -1 : 1);
    }
    return qMax(1, result);
}

void game::reproduction(QHash<QPair<qint32,qint32>,QVector<Animal>>* animal)
{
    for (auto iter = animal->begin(); iter != animal->end(); ++iter) {
        qint32 size = iter.value().size() / 2;
        for (qint32 i = 0; i < size; ++i) {
            iter.value()[i].vitality /= 2;   /* убавляем энерги после размножения */
            iter.value()[i+size].vitality /= 2;
            Animal zoo = new_animal(iter.value()[i],iter.value()[i+size]);
            iter.value().push_back(zoo);
        }
    }
}

/*____U_I____C_L_A_S_S____*/

MainWindow::MainWindow(qint32 width, qint32 height, QWidget *parent):
    QMainWindow(parent),
    width(width), height(height),
    playground(new QTableWidget(height, width)),
    playground_second(new QTableWidget(height, width)),
    evolution(new game(width, height)),
    start_stop_but(new QPushButton("START")),
    restart_but(new QPushButton("RESTART")),
    main_widget(new QWidget),
    total(new QVBoxLayout),
    panel(new QHBoxLayout),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Lisovskij`s game of live"));
    playground_second->hide();

    QDateTime cd = QDateTime::currentDateTime();
    qsrand(cd.toTime_t());

    restart_but->setFlat(true);
    start_stop_but->setFlat(true);

    /* настройка кнопок */
    start_stop_but->setFixedSize(15*width/2, 30);
    restart_but->setFixedSize(15*width/2, 30);

    /* настройки игрового поля */
    playground->verticalHeader()->setMinimumSectionSize(15);   /* задаем длину и ширину ячеек */
    playground->verticalHeader()->setMaximumSectionSize(15);
    playground->verticalHeader()->setDefaultSectionSize(15);
    playground->horizontalHeader()->setMinimumSectionSize(15);
    playground->horizontalHeader()->setMaximumSectionSize(15);
    playground->horizontalHeader()->setDefaultSectionSize(15);
    playground->verticalHeader()->setVisible(false);   /* убираем подписи столбиков и строчек */
    playground->horizontalHeader()->setVisible(false);
    playground->setStyleSheet(QString("border: 0"));   /* уменьшаем границы между клетками */
    playground->setSelectionMode(QAbstractItemView::NoSelection);   /* убираем возможности выделения */
    playground->setEditTriggers(QAbstractItemView::NoEditTriggers);   /* запрещаем редактирование ячеек */
    playground->setFixedWidth(15*width);   /* устанавливаем точные размеры таблицы */
    playground->setFixedHeight(15*height);
    playground_second->verticalHeader()->setMinimumSectionSize(15);   /* повторяем для второго буфера */
    playground_second->verticalHeader()->setMaximumSectionSize(15);
    playground_second->verticalHeader()->setDefaultSectionSize(15);
    playground_second->horizontalHeader()->setMinimumSectionSize(15);
    playground_second->horizontalHeader()->setMaximumSectionSize(15);
    playground_second->horizontalHeader()->setDefaultSectionSize(15);
    playground_second->verticalHeader()->setVisible(false);
    playground_second->horizontalHeader()->setVisible(false);
    playground_second->setStyleSheet(QString("border: 0"));
    playground_second->setSelectionMode(QAbstractItemView::NoSelection);
    playground_second->setEditTriggers(QAbstractItemView::NoEditTriggers);
    playground_second->setFixedWidth(15*width);
    playground_second->setFixedHeight(15*height);   /* создаем объеты ячеек таблицы */
    for (qint32 x = 0; x < height; x++){
        for (qint32 y = 0; y < width; y++) {
            playground->setItem(x,y, new QTableWidgetItem());
            playground_second->setItem(x,y, new QTableWidgetItem());
        }
    }

    /* позицирование */
    total->setContentsMargins(0,0,0,0);   /* убираем лишние отсупы */
    panel->setContentsMargins(0,0,0,0);
    panel->setSpacing(0);
    total->setSpacing(0);
    this->statusBar()->hide();
    panel->addWidget(start_stop_but);   /* размещаем элементы */
    panel->addWidget(restart_but);
    total->addLayout(panel);
    total->addWidget(playground);
    total->addWidget(playground_second);
    main_widget->setLayout(total);
    this->setCentralWidget(main_widget);

    /* подключаем сигналы к слотам */
    connect(restart_but, &QPushButton::clicked, this, &MainWindow::restart);
    connect(start_stop_but, &QPushButton::clicked, this, &MainWindow::start_stop);
    connect(evolution, &game::new_data, this, &MainWindow::set_data);

    /*  запрещаем изменять размеры окна */
    this->setFixedWidth(15*width);
    this->setFixedHeight(15*height + 30);

    /* начальная генерация */
    evolution->generate();
}

void MainWindow::clear(){
    /* убираем цвет и надписи */
    for (qint32 x = 0; x < height; x++){
        for (qint32 y = 0; y < width; y++) {
            playground_second->item(x,y)->setBackground(colors.bg);
            playground_second->item(x,y)->setText("");
        }
    }
}

void MainWindow::swap_bufs()
{
    qSwap(playground, playground_second);
    playground_second->hide();
    playground->show();
}

void MainWindow::set_data()
{
    clear();
    QVector<QHash<QPair<qint32,qint32>,qint32>>* data = evolution->get_data();   /* получаем массив данных */
    /* grass */
    for (auto iter = data->at(0).begin(); iter != data->at(0).end(); ++iter){   /* согласно возрасту травы устанавливаем цвет */
        switch (iter.value()) {
            case 0:
                playground_second->item(iter.key().first,iter.key().second)->setBackground(colors.grass_l);
                playground_second->item(iter.key().first,iter.key().second)->setText(QString("L"));
                break;
            case 1:
                playground_second->item(iter.key().first,iter.key().second)->setBackground(colors.grass_m);
                playground_second->item(iter.key().first,iter.key().second)->setText(QString("M"));
                break;
            case 2:
                playground_second->item(iter.key().first,iter.key().second)->setBackground(colors.grass_b);
                playground_second->item(iter.key().first,iter.key().second)->setText(QString("B"));
                break;
        }
    }
    /* bunny */
    for (auto iter = data->at(1).begin(); iter != data->at(1).end(); ++iter){   /* устанавливаем цвета и колличество животных в ячейках */
        QPair<qint32,qint32> pos = iter.key();
        playground_second->item(pos.first,pos.second)->setBackground(colors.bunny);
        playground_second->item(pos.first,pos.second)->setText(iter.value() > 9 ? "*" : QString::number(iter.value()));  /* отображаются только цифры */
    }
    /* wolf */
    for (auto iter = data->at(2).begin(); iter != data->at(2).end(); ++iter){
        QPair<qint32,qint32> pos = iter.key();
        playground_second->item(pos.first,pos.second)->setBackground(colors.wolf);
        playground_second->item(pos.first,pos.second)->setText(iter.value() > 9 ? "*" : QString::number(iter.value()));
    }
    swap_bufs();
    delete data;  /* освобождаем память */
    if (is_play) {   /* если dигра не стоит на паузе */
        evolution->start();
    }
}

void MainWindow::start_stop()
{
    is_play = !is_play;  /* меняем true на false и наоборот */
    start_stop_but->setText(is_play ? QString("STOP") : QString("START"));   /* устанавливаем надпись соответственно следующему нажатию кнопки */
    if (is_play && !evolution->isRunning()) evolution->start();   /* если нужно начать и поток не работает */
}

void MainWindow::restart()
{
    is_play = false;   /* ставим на паузу */
    start_stop_but->setText(QString("START"));
    clear();   /* очищаем экран */
    evolution->generate();   /* заполняем экран данными новой генерации */
}

MainWindow::~MainWindow()
{
    delete start_stop_but;
    delete restart_but;
    delete main_widget;
    delete panel;
    delete total;
    for (qint32 x = 0; x < height; x++){
        for (qint32 y = 0; y < width; y++) {
            delete playground->item(x,y);
            delete playground_second->item(x,y);
        }
    }
    delete evolution;
    delete ui;
}

