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
        LT_POS= 0,   // ����
        CT_POS,      // ��
        RT_POS,      // ����
        CL_POS,      // ��
        CR_POS,      // ��
        LB_POS,      // ����
        CB_POS,      // ��
        RB_POS       // ����
    };

    ItemWidget(int itemType, QGraphicsItem* parent = NULL);
    ~ItemWidget();

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
    
    // ͼ�εı߿�
    QRect        mRect;
    QPoint mResizePos[8];


    QSizeF _size;
    QPointF _lastMousePosWithGridMove;
    int _resizeHandle;



    ItemTittle* mpTittle;
};

