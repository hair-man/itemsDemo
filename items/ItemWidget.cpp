#include "ItemWidget.h"

#include <QCursor>
#include <QDebug>

int ItemWidget::getMousePos(QPoint pos)
{
    for (int i = 0; i< 8; i++ )
    {
#if 1
        if (pos.x() + 3 >= mResizePos[i].x() && pos.x() - 3 <= mResizePos[i].x() &&
            pos.y() + 3 >= mResizePos[i].y() && pos.y() - 3 <= mResizePos[i].y())
#else
        if(pos == mResizePos[i])
#endif
            return i;
    }

    return -1;
}

void ItemWidget::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsItem::hoverEnterEvent(event);

    int index = 0;
    if (this->isSelected())
    {
        index = getMousePos(event->pos().toPoint());
        
        qDebug() << event->pos();

        switch (index) {
        case 0:     // 左上
        case 7:     // 右下
            this->setCursor(Qt::SizeFDiagCursor);
            break;
        case 5:      // 左下
        case 2:      // 右上
            this->setCursor(Qt::SizeBDiagCursor);
            break;
        case 1:       // 上
        case 6:       // 下
            this->setCursor(Qt::SizeVerCursor);
            break;
        case 3:      // 左
        case 4:      // 右
            this->setCursor(Qt::SizeHorCursor);
            break;
        default:
            this->setCursor(Qt::SizeAllCursor);
            break;
        }
    }
}

void ItemWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();

    qDebug() << "Press Press" << endl;
    QGraphicsItem::mousePressEvent(event);

    if ((_resizeHandle = getMousePos(event->pos().toPoint())) != -1)
    {
        _lastMousePosWithGridMove = event->scenePos();
    }
    else
        this->setCursor(Qt::SizeAllCursor);

}

void ItemWidget::setSize(const QSizeF& size)
{
    // short circuit when no effective change at all times as a manner of policy
    if (size == _size) {
        return;
    }

    // Boundary checks
    if (size.width() < 1 || size.height() < 1) {
        return;
    }

    QSizeF oldSize = _size;

    prepareGeometryChange();

    _size = size;

    mRect = QRect(0,0, _size.width(), _size.height());

    mpTittle->setTittleSize(_size.width(), 38);

    setTransformOriginPoint(mRect.center());
}


void ItemWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();
    qDebug() << "Move Move" << endl;


    QPointF newMousePos(event->scenePos());

   
    if (event->buttons() & Qt::LeftButton && _resizeHandle != -1)
    {
        QPointF d(newMousePos - _lastMousePosWithGridMove);
        qreal dx = d.x();
        qreal dy = d.y();

        // Don't do anything if there's nothing to do
        if (qFuzzyIsNull(dx) && qFuzzyIsNull(dy))
            return ;

        _lastMousePosWithGridMove = newMousePos;

        // Perform resizing
        qreal newX = pos().x();
        qreal newY = pos().y();
        qreal newWidth = mRect.width();
        qreal newHeight = mRect.height();
        switch (_resizeHandle) {
        case LT_POS:
            newX += dx;
            newY += dy;
            newWidth -= dx;
            newHeight -= dy;
            break;

        case CT_POS:
            newY += dy;
            newHeight -= dy;
            break;

        case RT_POS:
            newY += dy;
            newWidth += dx;
            newHeight -= dy;
            break;

        case CR_POS:
            newWidth += dx;
            break;

        case RB_POS:
            newWidth += dx;
            newHeight += dy;
            break;

        case CB_POS:
            newHeight += dy;
            break;

        case LB_POS:
            newX += dx;
            newWidth -= dx;
            newHeight += dy;
            break;

        case CL_POS:
            newX += dx;
            newWidth -= dx;
            break;
        }

        // Snap to grid (if supposed to)
        QPointF newPos(newX, newY);
        QSizeF newSize(newWidth, newHeight);

        // Minimum size
        if (newSize.height() < 1) {
            newSize.setHeight(1);
            if (!qFuzzyCompare(newPos.ry(), pos().ry())) {
                newPos.setY(pos().y() + mRect.height() - 1);
            }
        }
        if (newSize.width() < 1) {
            newSize.setWidth(1);
            if (!qFuzzyCompare(newPos.rx(), pos().rx())) {
                newPos.setX(pos().x() + mRect.width() - 1);
            }
        }

        setPos(newPos);
        setSize(newSize);
    }
    else
        QGraphicsItem::mouseMoveEvent(event);


}


void ItemWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();
    _resizeHandle = -1;
    qDebug() << "Release Release" << endl;
    QGraphicsItem::mouseReleaseEvent(event);

}


JointContent* ItemWidget::addJoint(int direction)
{
    /* """给节点内容增加端口
        : param data_type : 节点表示的变量的数据类型（整型 / 字符串）
        : param direction : 需要在节点输(入 / 出)侧添加端口
        : param logic_type : 节点表示的变量的逻辑类型（数据 / 逻辑）
        """
        */

    JointContent* pJoint = new JointContent(direction, this);

    mJointContentList.append(pJoint);

    mpJointLayout->setJointsLocation(mJointContentList);

    return pJoint;
}

ItemWidget::ItemWidget(int itemType, QGraphicsItem* parent)
    :QGraphicsObject(parent)
    ,mItemType(itemType)
{
    // 接收鼠标悬浮事件
    this->setAcceptHoverEvents(true);
    _resizeHandle = -1;

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    mRect = QRect(0, 0, 200, 100);

    mpTittle = new ItemTittle(mRect.width(), 38, this);

    mpJointLayout = new JointLayout(this);

    addJoint(0);
    addJoint(0);
    addJoint(0);
    addJoint(1);
    addJoint(1);
    addJoint(1);
}

ItemWidget::~ItemWidget()
{

}

void ItemWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPen pen(Qt::blue, 1);
    QBrush brush(Qt::green);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(mRect);

    painter->setPen(QPen(Qt::black));
    switch (mItemType)
    {
    case ItemWidget::YTHCLIENT:
        painter->drawText(0, 20, QString::fromWCharArray(L"客户端"));
        break;
    case ItemWidget::IPDEV:
        painter->drawText(0, 20, QString::fromWCharArray(L"IP程序"));
        break;
    case ItemWidget::VOIP:
        painter->drawText(0, 20, QString::fromWCharArray(L"视频"));
        break;
    default:
        painter->drawText(0, 20, QString::fromWCharArray(L"自定义"));
        break;
    }

    if (isSelected())
    {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::white);

        
        int _cSize = 4;

        painter->drawEllipse(mResizePos[0] = mRect.topLeft(), _cSize, _cSize);
        painter->drawEllipse(mResizePos[1] = QPoint(mRect.center().x() + _cSize/2, mRect.top()), _cSize, _cSize);
        painter->drawEllipse(mResizePos[2] = mRect.topRight(), _cSize, _cSize);
        
        painter->drawEllipse(mResizePos[3] = QPoint(mRect.left(), mRect.center().y() + 2), _cSize, _cSize);
        painter->drawEllipse(mResizePos[4] = QPoint(mRect.right(), mRect.center().y() + 2), _cSize, _cSize);

        painter->drawEllipse(mResizePos[5] = mRect.bottomLeft(), _cSize, _cSize);
        painter->drawEllipse(mResizePos[6] = QPoint(mRect.center().x() + _cSize/2, mRect.bottom()), _cSize, _cSize);
        painter->drawEllipse(mResizePos[7] = mRect.bottomRight(), _cSize, _cSize);

        //painter->drawEllipse(mResizePos[8] = QPoint(mRect.center().x() + _cSize/2, - mRect.center().y()), _cSize, _cSize);
    }
}

QRectF ItemWidget::boundingRect() const
{
    return mRect;
}

int ItemWidget::type() const
{
    return mItemType;
}
