#include "panel_component.h"

panel_component_leaf::panel_component_leaf(const QString& name, qint32 min_val, qint32 max_val, QWidget *parent)
    : QWidget (parent)
    , val_(new QSpinBox)
    , name_(name)
{
    QHBoxLayout* main_lay = new QHBoxLayout;
    QLabel* lab = new QLabel(name);
    main_lay->addWidget(lab);
    main_lay->addWidget(val_);
    main_lay->setContentsMargins(0,0,0,0);
    main_lay->setSpacing(0);
    this->setLayout(main_lay);
    val_->setMinimum(min_val);
    val_->setMaximum(max_val);
    this->setFixedSize(256, 45);
}

QPair<QString, qint32> panel_component_leaf::get_data()
{
    return {name_, val_->value()};
}

panel_component::panel_component(const QVector<panel_component_leaf *> &comps, const QString &but_name, QWidget *parent)
    : BaseComponent(parent)
    , comps_ (comps)
{
    QVBoxLayout* main_lay = new QVBoxLayout;
    for (auto& i : comps_) main_lay->addWidget(i);
    QPushButton* but = new QPushButton(but_name);
    but->setFixedSize(256,30);
    main_lay->addWidget(but);
    main_lay->setContentsMargins(0,0,0,0);
    main_lay->setSpacing(0);
    main_lay->setAlignment(Qt::AlignTop);
    this->setFixedSize(256, 45*(comps_.size()+1));
    this->setLayout(main_lay);
    connect(but, &QPushButton::clicked, this, &panel_component::get_data);
}

void panel_component::get_data()
{
    QJsonObject res;
    for (auto& i : comps_) res[i->get_data().first] = i->get_data().second;
    emit notify(res);
}
