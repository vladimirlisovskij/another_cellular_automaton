#include "logic_component.h"

logic_component::logic_component(qint32 width, qint32 height, QWidget *parent)
    : BaseLogicComponent(parent)
    , width(width)
    , height(height)
    , square(height*width)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    clear();
}

void logic_component::add_animal(logic_component::Animal animal, qint32 num, qint32 level)
{
    if (all_free_space.size() >= num)
    {
        QHash<QPair<qint32,qint32>,QVector<Animal>> temp;
        for (qint32 i = 0; i < num; ++i)
        {
            temp[get_free_pos()] = QVector<Animal>{animal};
        }
        all_animals.push_back(temp);
        all_animals_levels.push_back(level);
    }
    update();
}

void logic_component::add_grass(qint32 num)
{
    if (all_free_space.size() >= num) for (qint32 i = 0; i < num; ++i) all_grass[get_free_pos()] = LITTLE;
    update();
}


QVector<QHash<QPair<qint32,qint32>,qint32>> logic_component::make_data()
{
    QVector<QHash<QPair<qint32,qint32>,qint32>> res;
    QHash<QPair<qint32,qint32>,qint32> temp;
    for (auto cell = all_grass.begin(); cell != all_grass.end(); ++ cell) temp[cell.key()] = cell.value();
    res.push_back(temp);
    for (auto spec: all_animals)
    {
        temp.clear();
        for (auto cell = spec.begin(); cell != spec.end(); ++cell) temp[cell.key()] = cell.value().size();
        res.push_back(temp);
    }
    return res;
}

QVector<QVector<qint32>> logic_component::get_stat()
{
    QVector<QVector<qint32>> res;
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
        if (num) res.push_back(QVector<qint32>{lvl, num, speed/num, endurance/num, vitality/num, max_vitality/num});
        else  res.push_back(QVector<qint32>{lvl, 0, 0, 0, 0, 0});
    }
    return res;
}

void logic_component::remove_animal(qint32 pos)
{
    for (auto cell = all_animals[pos].begin(); cell != all_animals[pos].end(); ++cell) all_free_space.insert(cell.key());
    all_animals.remove(pos);
    all_animals_levels.remove(pos);
    update();
}

void logic_component::clear()
{
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
    emit notify(new Response(new QPair<QVector<QHash<QPair<qint32,qint32>,qint32>>,QVector<QVector<qint32>>> {make_data(), get_stat()}));
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
            QVector<qint32> max_lvl_animals;
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
                if (is_0_lvl) all_grass.remove(pos);
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
            for (qint32 i = 0; i < size; ++i)
            {
                all_animals[ind][cell.key()][i].vitality /= 2;
                all_animals[ind][cell.key()][i+size].vitality /= 2;
                Animal temp = new_animal(all_animals[ind][cell.key()][i], all_animals[ind][cell.key()][i+size]);
                all_animals[ind][cell.key()].push_back(temp);
            }
        }
    }
}

void logic_component::animal_move(QHash<QPair<qint32,qint32>,QVector<Animal>>& animal)
{
    QHash<QPair<qint32,qint32>,QVector<Animal>> temp;   /* данные для следущего шага */
    for (auto iter = animal.begin(); iter != animal.end(); ++iter)   /* итерируемся по словарю животных */
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
                if (!temp.contains(new_pos)) temp[new_pos] = QVector<Animal> {};   /* создадим массив, если до этого в словаре его не было */
                temp[new_pos].push_back(zoo);   /* переместим результат в словарь данных для следующего шага */
                all_free_space.remove(new_pos);
            }
        }
    }
    animal = temp;
}
