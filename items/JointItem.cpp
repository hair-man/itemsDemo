#include "JointItem.h"




void JointItem::drawJoint(QPainter* painter)
{
    //"""绘制插槽变量圆圈"""
    // 分左右进行绘制两侧位置不同
    if (mDirection == DIRECTION_INPUT)
        painter->translate(9.5, 10);
    else
        painter->translate(14.5, 10);

    painter->setBrush(m_brush);

    // 绘制底层三角和圆形
    painter->setPen(QPen(Qt::blue, 1));
    QPolygonF polygon;
    polygon << QPointF(mRadius * 0.2, mRadius * 0.9) << QPointF(mRadius * 1.5, mRadius * 0.1) 
        << QPointF(mRadius * 0.2, -mRadius * 0.9) << QPointF(mRadius * 1.2, mRadius*0.1)
        << QPointF(mRadius * 0.2, mRadius * 0.9);
    painter->drawPolygon(polygon);

    painter->setPen(m_pen);
    painter->drawEllipse(-mRadius, -mRadius, 2 * mRadius, 2 * mRadius);;

    //如果此端口已经被连接的话绘制中部小圆形
    if (mLinkStat)
    {
        painter->setBrush(m_brush2);
        painter->drawEllipse(-mRadius * 1.2 / 2, -mRadius * 1.2 / 2, 1.2 * mRadius, 1.2 * mRadius);
    }

#if 0
    painter->setPen(QPen(Qt::blue, 4));
    painter->drawPoint(mRadius / 4, mRadius);
    painter->drawPoint(mRadius / 4, -mRadius);
    painter->drawPoint(mRadius + 2, mRadius / 4);
    painter->drawPoint(mRadius + 4, mRadius / 4);
#endif
}


void JointItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    drawJoint(painter);
}

void JointItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    //"""重载-鼠标离开"""
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::hoverLeaveEvent(event);
}
void JointItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    //"""重载-鼠标进入"""
    setCursor(Qt::CrossCursor);
    QGraphicsItem::hoverEnterEvent(event);
}

void JointItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
#if 0
    //"""重载-鼠标点击"""
    socket_content = parentItem();
    node_content = socket_content.parentItem();
    w_node = node_content.parentItem();
    self.input_offect = QPointF(0, 0);

    if (mDirection == DIRECTION_INPUT)
        self.input_offect = QPointF(6, 0);

    
    w_node.bp_node.socket_base_offect = event->pos() - QPointF(25, 10) + self.input_offect; //鼠标拖拽时位置偏移
#endif
    
    
    QGraphicsItem::mousePressEvent(event);
}

int  JointItem::getDirection()
{
    return mDirection;
}


void JointItem::setJointState(bool isLink)
{
    //"""设置端口状态是否已连接"""
    mLinkStat = isLink;
}

QPointF JointItem::getJointLocation()
{
    //"""获取插槽的绝对位置"""
    qreal w = mRectStepWidth;
    qreal point = 4;
    if (mDirection == DIRECTION_INPUT)
        point = 4;
    else
        point = mWidth - 3.3 * w - 4;

    return pos() + QPointF(13, 10) + QPointF(point, 0);
}

QRectF JointItem::boundingRect() const
{
    //   """定义Qt的边框"""
    return QRectF(0, 0, mWidth, mHeight).normalized();
}

void JointItem::setJointItemGeometry(qreal x, qreal y, qreal width, qreal height)
{
    /* 设置位置尺寸 */
    setPos(x, y);

    mWidth = width;
    mHeight = height;
}


JointItem::JointItem(int direction, QGraphicsItem* parent)
    :QGraphicsItem(parent)
    , mDirection(direction)
{
    setAcceptHoverEvents(true);    // 接受悬停事件

    mWidth = 26;
    mHeight = 20;


    mRadius = 6.5;               // 插槽圆圈半径
    mRectStepWidth = 3.0;        //插槽白色多边形绘制步长

    mLinkStat = false;


    m_color_outline = QColor("#0A0C0A");              // 插槽端口周围轮廓颜色
    m_color_background = QColor("#ff0000");           // 插槽端口颜色 - 可变
    m_color_background2 = QColor("#0A0C0A");          // 插槽端口小圈黑色


    m_pen = QPen(m_color_outline);
    m_pen.setWidthF(0.5);                           //插槽轮廓线宽度
    m_brush = QBrush(m_color_background);           // 插槽端口颜色 - 可变
    m_brush2 = QBrush(m_color_background2);         // 插槽端口小圈黑色
}


