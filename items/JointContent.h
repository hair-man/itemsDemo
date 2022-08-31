#pragma once


#include <QPen>
#include <QColor>
#include <QBrush>
#include <QObject>
#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPointF>
#include <QColor>

#include "JointItem.h"



class JointContent : public QGraphicsItem
{

public:
    JointContent(int direction, QGraphicsItem* parent = nullptr);


    void drawMouseEnterLabel(QPainter* painter);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    QRectF boundingRect() const;



    void setJointState(bool isLink);

    void setJointContentGeometry(qreal x, qreal y, qreal width, qreal height);


    QPointF getJointLocation();
    int getJointDirection();

    QSize getRequiredSize();
    void setJointContentText(QString text);
    int getJointTextLen();

    //void createInputWidget();


private:
    qreal mWidth;
    qreal mHeight;

    /* 鼠标停留状态 */
    int mMouseStay;

    QColor m_color_mouse_enter_label_1;
    QColor m_color_mouse_enter_label_0;

    QFont  mTextFont;
    QPen   mTextPen;
    qreal  mTextPosX;
    QString mText;

    JointItem* mpJoint;

};




