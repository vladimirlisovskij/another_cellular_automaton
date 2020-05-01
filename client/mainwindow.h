#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <client_component.h>
#include <graph_component.h>
#include <panel_component.h>
#include <screen_component.h>
#include <table_component.h>
#include <buts_component.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    graph_component* graph_;
    panel_component* panel1_;
    panel_component* panel2_;
    screen_component* screen_;
    table_component* table_;
    client_component* client_;
    start_component* start_;
    restart_component* restart_;
    const QVector<QColor> free_colors_;
    const QVector<QColor> grass_colors_;

private slots:
    void change_focus (QJsonObject data);
    void clear (QJsonObject data);
    void add_animal (QJsonObject data);
    void add_grass (QJsonObject data);
    void next (QJsonObject data);
    void change_stats (QJsonObject data);
};
#endif // MAINWINDOW_H
