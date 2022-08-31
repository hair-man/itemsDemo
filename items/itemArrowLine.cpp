#include <cmath>
#include <QDebug>
#include "itemArrowLine.h"



ArrowItem::ArrowItem(ItemWidget* startI, ItemWidget* endI, QGraphicsItem* parent) :
    QGraphicsLineItem(parent)
{
    m_pendItem = endI; //���item
    m_pStartItem = startI; //�յ�item
    this->setZValue(m_pStartItem->zValue() - 1); //Ŀ�ģ��ü�ͷ����
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF ArrowItem::boundingRect() const
{
    //item��������Ĺ���ֵ
    qreal extra = (this->pen().width() + 20) / 2;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y()))
        .normalized().adjusted(-extra, -extra, extra, extra);
}

void ArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    if (m_pStartItem->collidesWithItem(m_pendItem))//�ж�ͼ�����Ƿ�����ཻ
        return;
    QPen pen(Qt::black);
    painter->setPen(pen);

    painter->setBrush(Qt::black);
    qreal arrowsize = 10;
    
    /* pos ���൱��scene������ */
    //QLineF centerLine(m_pStartItem->pos(), m_pendItem->pos());
    //qDebug() << m_pStartItem->pos() << m_pendItem->pos();    //�˴���ӡ�ľ����� pItem->setPos(300, 300); ���ñ��ֵ�һ��
    //                                                         //������Ҫ�����������ƶ���item������������Ҫ��pos���е���
    QLineF centerLine(m_pStartItem->pos() + QPointF(m_pStartItem->boundingRect().width() / 2, m_pStartItem->boundingRect().height() / 2)
        , m_pendItem->pos() + QPointF(m_pendItem->boundingRect().width() / 2, m_pendItem->boundingRect().height() / 2));



    QPolygonF endPolygon = m_pendItem->shape().toFillPolygon();//��ȡitem�ĵ���ϣ��ջ�·��
    QPointF p1 = endPolygon.first() + m_pendItem->pos();//item�����Ϸ���  + item�ڳ�����λ�õ㣨ƫ�Ƶõ����ϵ��ڳ����е�λ�ã�
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i)
    {
        p2 = endPolygon.at(i) + m_pendItem->pos();//ƫ�Ƶõ������е�λ�õ�
        polyLine = QLineF(p1, p2);//���㹹��ֱ��

        QLineF::IntersectType intersectType =
            polyLine.intersect(centerLine, &intersectPoint);//�����߱Ƚ��Ƿ��н���   ����
        if (intersectType == QLineF::BoundedIntersection)
        {
            //painter->drawLine(polyLine);
            break;
        }
        p1 = p2;
    }

    painter->setPen(Qt::black);
    /* �˴������������ߵ���� �� �յ�*/
    setLine(QLineF(intersectPoint, m_pStartItem->pos() + QPointF(m_pStartItem->boundingRect().width() / 2, m_pStartItem->boundingRect().height() / 2)));
    //setLine(QLineF(m_pStartItem->pos() + QPointF(m_pStartItem->boundingRect().width() / 2, m_pStartItem->boundingRect().height() / 2), intersectPoint));

    double angle = std::atan2(-line().dy(), line().dx()); //������ [-PI,PI]
    QPointF arrowP1 = line().p1() +
        QPointF(sin(angle + M_PI / 3) * arrowsize, //����Ա�
            cos(angle + M_PI / 3) * arrowsize); //�����ٱ�
    QPointF arrowP2 = line().p1() +
        QPointF(sin(angle + M_PI - M_PI / 3) * arrowsize,
            cos(angle + M_PI - M_PI / 3) * arrowsize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(arrowHead);

}

QPainterPath ArrowItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}