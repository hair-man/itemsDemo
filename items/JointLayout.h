#pragma once

#include <QSize>
#include <QList>
#include <QGraphicsItem>

#include "JointItem.h"
#include "JointContent.h"

class JointLayout
{

public:

    JointLayout(QGraphicsItem* item);


    QSize getJointsSize(QList<JointContent*>& pJointContents);

    void setJointsLocation(QList<JointContent*>& pJointContents);



    QGraphicsItem* mpItem;
};

