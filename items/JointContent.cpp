#include <QFontMetrics>
#include <QLinearGradient>

#include "JointContent.h"



void JointContent::drawMouseEnterLabel(QPainter* painter)
{
    //"""绘制鼠标悬浮时高亮效果"""
    if (mMouseStay)
    {
        QLinearGradient lg(0, 0, mWidth, 0);

        lg.setColorAt(0, m_color_mouse_enter_label_0);
        lg.setColorAt(0.1, m_color_mouse_enter_label_1);
        lg.setColorAt(0.9, m_color_mouse_enter_label_1);
        lg.setColorAt(1, m_color_mouse_enter_label_0);
        painter->setBrush(lg);
        painter->setPen(Qt::transparent);
        painter->drawRect(0, 0, mWidth, mHeight);
    }
}



void JointContent::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //"""重载-绘制"""
    drawMouseEnterLabel(painter);

    // 绘制文字
    painter->setFont(mTextFont);
    painter->setPen(mTextPen);
    painter->drawText(mTextPosX, 15, mText);
}



int JointContent::getJointTextLen()
{
    //"""获取端口文字长度"""
    QFontMetrics font_metrics(mTextFont);
    return font_metrics.width(mText, mText.length()) + 7;
}



void JointContent::setJointContentText(QString text)
{
    //"""设置端口文字"""
    mText = text;
    mWidth = 26 + getJointTextLen();
}


void JointContent::setJointState(bool isLink)
{
    //"""设置端口状态是否已连接"""
    mpJoint->setJointState(isLink);
}



int JointContent::getJointDirection()
{
    //"""获取插槽是左边还是右边"""
    return mpJoint->getDirection();
}




QPointF JointContent::getJointLocation()
{
    //"""获取插槽的绝对位置"""
    return pos() + mpJoint->getJointLocation();
}

QSize JointContent::getRequiredSize()
{
    //"""获取所需尺寸用来让父控件延展"""
    QFontMetrics font_metrics(mTextFont);
    int font_width = font_metrics.width(mText, mText.length());
    int len = font_width + 7;

    // 加上文字的长度
    return QSize(mWidth + len, mHeight);
}


QRectF JointContent::boundingRect() const
{
    //"""定义Qt的边框"""
    return QRectF(0, 0, mWidth, mHeight).normalized();

}



void JointContent::setJointContentGeometry(qreal x, qreal y, qreal width, qreal height)
{
    //"""设置位置尺寸"""
    setPos(x, y);
    mWidth = width;
    mHeight = height;
}

JointContent::JointContent(int direction, QGraphicsItem* parent)
    :QGraphicsItem(parent)
{

    //接受悬停事件
    setAcceptHoverEvents(true);


    mWidth = 26;
    mHeight = 20;

    //标停留状态
    mMouseStay = false;
    // 鼠标悬浮时背景亮片颜色
    m_color_mouse_enter_label_1 = QColor("#7fffffff");
    // 鼠标悬浮时背景亮片颜色--渐变
    m_color_mouse_enter_label_0 = QColor("#00ffffff");


    mpJoint = new JointItem(direction, this);

    //文字颜色
    mTextPen = QPen(QColor("#dee1e2"));
    mTextFont = QFont("Arial", 11);

    setJointContentText("test");

    //createInputWidget();

    if (direction == JointItem::DIRECTION_INPUT)
        mTextPosX = 24;
    else
        mTextPosX = 9;

    mpJoint->setJointItemGeometry(mWidth - 26, 0, 26, 20);
}
