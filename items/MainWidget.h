#pragma once

#include <QtWidgets/QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>


class MainWidget : public QDialog
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    
    QGraphicsView* mpView;
    QGraphicsScene* mpScene;
};
