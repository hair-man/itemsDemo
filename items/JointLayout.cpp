#include "JointLayout.h"

JointLayout::JointLayout(QGraphicsItem* item)
    :mpItem(item)
{
}


void JointLayout::setJointsLocation(QList<JointContent*> &pJointContents)
{
    //"""将控件设置到预计位置"""
    //总高度
    qreal height1 = 0;
    //总高度
    qreal height2 = 0;

    qreal X = 0;

    for (int i = 0; i < pJointContents.count(); i++)
    {
        if (pJointContents[i]->getJointDirection() == JointItem::DIRECTION_INPUT)
        {
            pJointContents[i]->setJointContentGeometry(0.0, height1, pJointContents[i]->boundingRect().width(), pJointContents[i]->boundingRect().height());

            height1 = height1 + pJointContents[i]->boundingRect().height() + 8;
        }
        else if (pJointContents[i]->getJointDirection() == JointItem::DIRECTION_OUTPUT)
        {
            X = mpItem->boundingRect().width() - pJointContents[i]->boundingRect().width();
            pJointContents[i]->setJointContentGeometry(X, height2, pJointContents[i]->boundingRect().width(), pJointContents[i]->boundingRect().height());
            height2 = height2 + pJointContents[i]->boundingRect().height() + 8;
        }
    }
}


QSize JointLayout::getJointsSize(QList<JointContent*>& pJointContents)
{
    /* 获取控件预计尺寸 */
    qreal heights1 = 0;         //总高度
    qreal heights2 = 0;         // 总高度
    qreal width1 = 0;           // 总宽度
    qreal width2 = 0;           // 总宽度
    qreal maxWidth = 0;         // 最长宽度
    qreal maxHeight = 0;        // 最长宽度

    for (int i = 0; i < pJointContents.count(); i++)
    {
        if (pJointContents[i]->getJointDirection() == JointItem::DIRECTION_INPUT)
        {
            heights1 = heights1 + pJointContents[i]->boundingRect().height() + 8;
            if (pJointContents[i]->boundingRect().width() > width1)
                width1 = pJointContents[i]->boundingRect().width();
        }
        else if (pJointContents[i]->getJointDirection() == JointItem::DIRECTION_OUTPUT)
        {
            heights2 = heights2 + pJointContents[i]->boundingRect().height() + 8;
            if (pJointContents[i]->boundingRect().width() > width2)
                width2 = pJointContents[i]->boundingRect().width();
        }

        maxHeight = heights2;
        if (heights1 > heights2)
            maxHeight = heights1;
        maxWidth = width1 + width2;
    }

    return QSize(maxWidth, maxHeight);
}
