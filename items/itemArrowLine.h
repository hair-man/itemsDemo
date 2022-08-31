#pragma once


#include <QGraphicsLineItem>
#include "ItemWidget.h"


#ifndef M_PI
#define M_PI       3.14159265358979323846   // pi
#endif

class ArrowItem : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    //���캯��(����item����)
    ArrowItem(ItemWidget* startI, ItemWidget* endI, QGraphicsItem* parent = nullptr);

    //item��������Ĺ���ֵ
    QRectF boundingRect() const override;
    //ʵ�ʻ���
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr)override;

    int type() const override { return Type; }

    QPainterPath shape() const override;

private:
    ItemWidget* m_pStartItem;
    ItemWidget* m_pendItem;
    QPolygonF arrowHead;

};