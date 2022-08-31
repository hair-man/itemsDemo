#pragma once

#include <QCursor>
#include <QObject>
#include <QColor>
#include <QBrush>
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>



class JointItem :public QGraphicsItem
{

public:

    enum JOINT_DIRECTION_ENUM
    {
        DIRECTION_INPUT = 0,        //需要在节点输入侧添加端口
        DIRECTION_OUTPUT            //需要在节点输出侧添加端口
    };



    JointItem(int direction, QGraphicsItem* parent = nullptr);


    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);


    void drawJoint(QPainter* painter);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);




    void setJointItemGeometry(qreal x, qreal y, qreal width, qreal height);

    QPointF getJointLocation();
    int  getDirection();

    void setJointState(bool isLink);

    QRectF boundingRect() const;

private:

    // 方向
    int mDirection;
    // 链接状态
    bool mLinkStat;

    qreal mWidth;
    qreal mHeight;

    qreal mRadius;
    qreal mRectStepWidth;


    QColor     m_color_outline;
    QColor     m_color_background;
    QColor     m_color_background2;

    QPen       m_pen;
    QBrush     m_brush;
    QBrush     m_brush2;
};




