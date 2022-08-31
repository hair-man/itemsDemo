#include <cmath>
#include <QDebug>
#include "itemArrowLine.h"



ArrowItem::ArrowItem(ItemWidget* startI, ItemWidget* endI, QGraphicsItem* parent) :
    QGraphicsLineItem(parent)
{
    m_pendItem = endI; //起点item
    m_pStartItem = startI; //终点item
    this->setZValue(m_pStartItem->zValue() - 1); //目的：让箭头后置
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF ArrowItem::boundingRect() const
{
    //item绘制区域的估计值
    qreal extra = (this->pen().width() + 20) / 2;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y()))
        .normalized().adjusted(-extra, -extra, extra, extra);
}

void ArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    if (m_pStartItem->collidesWithItem(m_pendItem))//判断图形项是否存在相交
        return;
    QPen pen(Qt::black);
    painter->setPen(pen);

    painter->setBrush(Qt::black);
    qreal arrowsize = 10;
    
    /* pos 是相当于scene的坐标 */
    //QLineF centerLine(m_pStartItem->pos(), m_pendItem->pos());
    //qDebug() << m_pStartItem->pos() << m_pendItem->pos();    //此处打印的就是与 pItem->setPos(300, 300); 设置保持的一致
    //                                                         //但是需要将这个坐标点移动到item的中心所以需要对pos进行调整
    QLineF centerLine(m_pStartItem->pos() + QPointF(m_pStartItem->boundingRect().width() / 2, m_pStartItem->boundingRect().height() / 2)
        , m_pendItem->pos() + QPointF(m_pendItem->boundingRect().width() / 2, m_pendItem->boundingRect().height() / 2));



    QPolygonF endPolygon = m_pendItem->shape().toFillPolygon();//获取item的点组合（闭环路）
    QPointF p1 = endPolygon.first() + m_pendItem->pos();//item的左上方点  + item在场景的位置点（偏移得到左上点在场景中的位置）
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i)
    {
        p2 = endPolygon.at(i) + m_pendItem->pos();//偏移得到场景中的位置点
        polyLine = QLineF(p1, p2);//两点构成直线

        QLineF::IntersectType intersectType =
            polyLine.intersect(centerLine, &intersectPoint);//两条线比较是否有交集   存在
        if (intersectType == QLineF::BoundedIntersection)
        {
            //painter->drawLine(polyLine);
            break;
        }
        p1 = p2;
    }

    painter->setPen(Qt::black);
    /* 此处重新设置了线的起点 和 终点*/
    setLine(QLineF(intersectPoint, m_pStartItem->pos() + QPointF(m_pStartItem->boundingRect().width() / 2, m_pStartItem->boundingRect().height() / 2)));
    //setLine(QLineF(m_pStartItem->pos() + QPointF(m_pStartItem->boundingRect().width() / 2, m_pStartItem->boundingRect().height() / 2), intersectPoint));

    double angle = std::atan2(-line().dy(), line().dx()); //反正切 [-PI,PI]
    QPointF arrowP1 = line().p1() +
        QPointF(sin(angle + M_PI / 3) * arrowsize, //计算对边
            cos(angle + M_PI / 3) * arrowsize); //计算临边
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