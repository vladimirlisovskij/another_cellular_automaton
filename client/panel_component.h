#ifndef PANEL_COMPONENT_H
#define PANEL_COMPONENT_H

#include"base_component.h"

#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class panel_component_leaf : public QWidget
{
/*
    * Реализует вспомогательный виджет из надписи и поля ввода
*/
    Q_OBJECT
    friend class tormentor;
private:
    QSpinBox* val_;
    QString name_;

public:
    panel_component_leaf (const QString& name, qint32 min_val, qint32 max_val, QWidget* parent = nullptr);

public slots:
    QPair<QString,qint32> get_data ();
};

class panel_component : public BaseComponent
{
/*
    * Реализует компонент отвечающий за сбор данных из переданных ему [panel_component_leaf]
*/
    Q_OBJECT
    friend class tormentor;
private:
    QVector<panel_component_leaf*> comps_;

public:
    panel_component(const QVector<panel_component_leaf*>& comps, const QString& but_name, QWidget* parent = nullptr);

public slots:
    void get_data ();
};

#endif // PANEL_COMPONENT_H
