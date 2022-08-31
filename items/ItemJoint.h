#pragma once

#include <qobject.h>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsScene>

class ItemJoint :public QGraphicsObject
{
    Q_OBJECT

public:
    ItemJoint(QGraphicsItem* parent = nullptr);

};

