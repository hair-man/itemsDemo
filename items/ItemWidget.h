#pragma once

#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QRect>
#include <QObject>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "ItemTittle.h"
#include "JointLayout.h"

class ItemWidget : public QGraphicsObject
{
    Q_OBJECT

public:

    enum TYPE {
        YTHCLIENT = UserType + 1,
        IPDEV,
        VOIP
    };

    enum MPOS {
        LT_POS= 0,   // 左上
        CT_POS,      // 上
        RT_POS,      // 右上
        CL_POS,      // 左
        CR_POS,      // 右
        LB_POS,      // 左下
        CB_POS,      // 下
        RB_POS       // 右下
    };

    ItemWidget(int itemType, QGraphicsItem* parent = NULL);
    ~ItemWidget();



    JointContent* addJoint(int direction);


public:
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
    virtual QRectF boundingRect() const;
    virtual int type() const;


    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);


    int getMousePos(QPoint pos);
    void setSize(const QSizeF& size);

private:

    int mItemType;
    
    // 图形的边框
    QRect        mRect;
    QPoint mResizePos[8];


    QSizeF _size;
    QPointF _lastMousePosWithGridMove;
    int _resizeHandle;



    ItemTittle* mpTittle;

    JointLayout* mpJointLayout;
    QList<JointContent*> mJointContentList;

};

