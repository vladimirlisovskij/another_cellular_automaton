#include "logic_component.h"
#include <QDebug>

logic_component::logic_component(qint32 width, qint32 height, QObject *parent)
    : QObject(parent)
    , width(width)
    , height(height)
    , square(height*width)
    , _max_specs(4)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    _free_colors.reserve(_max_specs);
    _colors.reserve(_max_specs);
    all_free_space.reserve(square);
    all_grass.reserve(square);
    all_animals.reserve(_max_specs);
    clear();
}

void logic_component::add_animal(const logic_component::Animal& animal, qint32 num, qint32 level)
{
    if (all_free_space.size() >= num && !_free_colors.empty())
    {
        _colors.push_back(_free_colors.takeLast());
        QHash<QPair<qint32,qint32>,QLinkedList<Animal>> spec;
        spec.reserve(square);
        for (qint32 i = 0; i < num; ++i) spec[get_free_pos()] = QLinkedList<Animal>{animal};
        all_animals.append(spec);
        all_animals_levels.push_back(level);
    }
    update();
}

void logic_component::add_grass(qint32 num)
{
    if (all_free_space.size() >= num)
    {
        for (qint32 i = 0; i < num; ++i) all_grass[get_free_pos()] = LITTLE;
    }
    update();
}

QJsonObject logic_component::make_data()
{
    QJsonObject res;

    QJsonArray grass;
    for (auto cell = all_grass.begin(); cell != all_grass.end(); ++ cell)
    {
        QJsonObject grass_cell;
        grass_cell["key"] = cell.key().first*30 + cell.key().second;
        grass_cell["value"] = cell.value();
        grass.push_back(grass_cell);
    }
    res["grass"] = grass;

    QJsonArray animals;
    for (auto spec: all_animals)
    {
        QJsonArray spec_res;
        for (auto cell = spec.begin(); cell != spec.end(); ++cell)
        {
            QJsonObject spec_cell;
            spec_cell["key"] = cell.key().first*30 + cell.key().second;
            spec_cell["value"] = cell.value().size();
            spec_res.push_back(spec_cell);
        }
        animals.push_back(spec_res);
    }
    res["animals"] = animals;
    return res;
}

QJsonArray logic_component::get_stat()
{
    QJsonArray res;
    for (qint32 i = 0; i < all_animals_levels.size(); ++i)
    {
        qint32 num = 0;
        qint32 lvl = all_animals_levels[i];
        qint32 speed = 0;
        qint32 endurance = 0;
        qint32 vitality = 0;
        qint32 max_vitality = 0;
        for (auto iter = all_animals[i].begin(); iter != all_animals[i].end(); ++iter)
        {
            num += iter.value().size();
            for (auto i: iter.value())
            {
                speed += i.speed;
                endurance += i.endurance;
                vitality += i.vitality;
                max_vitality += i.max_vitality;
            }
        }
        if (num) res.push_back(QJsonArray{lvl, num, speed/num, endurance/num, vitality/num, max_vitality/num});
        else  res.push_back(QJsonArray{lvl, 0, 0, 0, 0, 0});
    }
    return res;
}

void logic_component::remove_animal(qint32 pos)
{
    for (auto cell = all_animals[pos].begin(); cell != all_animals[pos].end(); ++cell) all_free_space.insert(cell.key());
    all_animals.remove(pos);
    all_animals_levels.remove(pos);
    _free_colors.push_back(_colors.takeAt(pos));
    update();
}

void logic_component::clear()
{
    _colors.clear();
    _free_colors.clear();
    for (qint32 i = 0; i < _max_specs; ++i) _free_colors.push(i);
    all_animals_levels.clear();
    all_animals.clear();
    all_grass.clear();
    all_free_space.clear();
    for (qint32 x = 0; x < height; ++x)
    {
        for (qint32 y = 0; y < width; ++y)
        {
            all_free_space.insert(QPair<qint32,qint32> {x,y});
        }
    }
    update();
}

void logic_component::tik()
{
    move();
    eat();
    reproduction();
    update();
}

void logic_component::update()
{
    QJsonObject res;
    res["koord"] = make_data();
    res["stats"] = get_stat();
    QJsonArray colors;
    for (auto i : _colors) colors.push_back(i);
    res["colors"] = colors;
    emit notify(res);
}

QPair<qint32, qint32> logic_component::get_free_pos()
{
    qint32 new_num = qrand() % all_free_space.size();
    QPair<qint32,qint32> pos = all_free_space.values()[new_num];
    all_free_space.remove(pos);
    return pos;
}

logic_component::Animal logic_component::new_animal(logic_component::Animal f, logic_component::Animal m)
{
    Animal res
    {
            new_stat(f.speed, m.speed),
            new_stat(f.endurance, m.endurance),
            (f.vitality + m.vitality)/2,
            new_stat(f.max_vitality, m.max_vitality)
    };
    return res;
}

qint32 logic_component::new_stat(qint32 f, qint32 m)
{
    /* кроссовер */
    qint32 max_binary_len = qMax(qLn(f)/qLn(2), qLn(m)/qLn(2));
    qint32 num = qrand() % (max_binary_len + 1);
    qint32 two = qPow(2, num);
    int result = f - (f%two) + (m%two);
    /* мутация  */
    if (qrand() % 4 == 0)
    {
        num = qrand() % (max_binary_len + 1);
        result += qPow(2, num) * ((result>>num)&1 ? -1 : 1);
    }
    return qMax(1, result);
}

void logic_component::move()
{
    for (auto &animal: all_animals) animal_move(animal);
}

void logic_component::eat()
{
    for (qint32 x = 0; x < height; ++x)
    {
        for (qint32 y = 0; y < width; ++y)
        {
            QPair<qint32,qint32> pos {x, y};
            if (all_free_space.contains(pos)) continue;
            qint32 max_lvl = -1;
            qint32 low_lvl_animals = 0;
            qint32 hight_lvl_animals = 0;
            QLinkedList<qint32> max_lvl_animals;
            bool is_0_lvl = false;
            for (qint32 i = 0; i < all_animals.size(); ++i)
            {

                if (all_animals[i].contains(pos))
                {
                    if (all_animals_levels[i] == 0) is_0_lvl = true;
                    if (all_animals_levels[i] > max_lvl) {
                        max_lvl = all_animals_levels[i];
                        low_lvl_animals += hight_lvl_animals;
                        hight_lvl_animals = all_animals[i][pos].size();
                        for (auto ind: max_lvl_animals) all_animals[ind].remove(pos);
                        max_lvl_animals.clear();
                        max_lvl_animals.push_back(i);

                    } else if (all_animals_levels[i] == max_lvl)
                    {
                        hight_lvl_animals += all_animals[i][pos].size();
                        max_lvl_animals.push_back(i);
                    } else
                    {
                        low_lvl_animals += all_animals[i][pos].size();
                        all_animals[i].remove(pos);
                    }
                }
            }
            if (hight_lvl_animals)
            {
                qint32 point = 15 * (max_lvl ? low_lvl_animals : all_grass[pos]+1) / hight_lvl_animals;
                for (auto i: max_lvl_animals) for (auto& zoo: all_animals[i][pos]) zoo.vitality = qMin(zoo.max_vitality, zoo.vitality + point);
                all_grass.remove(pos);
            }
        }
    }
}

void logic_component::reproduction()
{
    QVector<QPair<qint32,qint32>> temp;
    for (auto iter = all_grass.begin(); iter != all_grass.end(); ++iter)
    {
        switch (iter.value()) {
            case LITTLE:
                all_grass[iter.key()] = MEDIUM;
                break;
            case MEDIUM:
                all_grass[iter.key()] = BIG;
                break;
            case BIG:
                for (qint32 x = -1; x < 2; ++x)
                {
                    for (qint32 y = -1; y < 2; ++y)
                    {
                        QPair<qint32,qint32> pos {iter.key().first + x, iter.key().second + y};
                        if (pos.first < height && pos.first >= 0 && pos.second < width && pos.second >= 0 && all_free_space.contains(pos))
                        {
                            temp.push_back(pos);
                            all_free_space.remove(pos);
                        }
                    }
                }
                break;
        }
    }
    for (auto pos: temp) all_grass[pos] = LITTLE;

    for (qint32 ind = 0; ind < all_animals.size(); ++ind)
    {
        auto spec = all_animals[ind];
        for (auto cell = spec.begin(); cell != spec.end(); ++cell)
        {
            qint32 size = cell.value().size()/2;
            auto a = all_animals[ind][cell.key()].begin();
            for (qint32 i = 0; i < size; ++i)
            {
                a->vitality /= 2;
                (a+1)->vitality /= 2;
                all_animals[ind][cell.key()].append(new_animal(*a, *(a+1)));
                a += 2;
            }
        }
    }
}

void logic_component::animal_move(QHash<QPair<qint32, qint32>, QLinkedList<Animal> > &data)
{
    QHash<QPair<qint32,qint32>,QLinkedList<Animal>> temp;   /* данные для следущего шага */
    for (auto iter = data.begin(); iter != data.end(); ++iter)   /* итерируемся по словарю животных */
    {
        all_free_space.insert(iter.key());
        for (Animal zoo: iter.value())   /* итерируемся по животным в этой ячейке */
        {
            if (zoo.endurance < zoo.vitality)   /* если животному хватит энергии для движения */
            {
                QPair<qint32,qint32> pos;
                QPair<qint32,qint32> new_pos = iter.key();   /* координаты ячейки на текущей итерации */
                do {
                    pos.first = qrand() % (2 * zoo.speed + 1) - zoo.speed;
                    pos.second = qrand() % (2 * zoo.speed + 1) - zoo.speed;
                } while (pos.first == 0 && pos.second == 0); /* мы не можем стоять на месте */
                new_pos.first += pos.first;   /* прибавляем сдвиг к координатам */
                new_pos.first = qMax(0, new_pos.first);   /* смотрим, чтобы не выйти за рамки */
                new_pos.first = qMin(height - 1, new_pos.first);
                new_pos.second += pos.second;
                new_pos.second = qMax(0, new_pos.second);
                new_pos.second = qMin(width - 1, new_pos.second);
                zoo.vitality -= zoo.endurance;   /* отнимаем энергию на перемещение */
                if (!temp.contains(new_pos)) temp[new_pos] = QLinkedList<Animal> {};   /* создадим массив, если до этого в словаре его не было */
                temp[new_pos].push_back(zoo);   /* переместим результат в словарь данных для следующего шага */
                all_free_space.remove(new_pos);
            }
        }
    }
    data = temp;
}
