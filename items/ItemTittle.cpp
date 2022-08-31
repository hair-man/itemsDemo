#include <QICon>
#include <QPixmap>
#include <QRegion>
#include <QColor>
#include <QPen>
#include <QFont>

#include "ItemTittle.h"

ItemTittle::ItemTittle(int width, int height, QGraphicsItem* parent)
    :QGraphicsItem(parent)
    ,mWidth(width)
    ,mHeight(height)
{
    ItemTittleInit();
}


void ItemTittle::ItemTittleInit()
{
    /* 发亮边缘圆角度数 */
    mRoundnes = 10.0;

    /* 标题栏左边颜色#4c748d */
    mLeftColor = QColor("#4c748d");
    /* 标题栏右边颜色#FF424342 */
    mRightColor = QColor("#4D4c748d");

    /* 白色高光 */
    mGaoGuangPen = QPen(QColor("#C8FFFFFF"));
    mGaoGuangPen.setWidthF(1.0);

    /* 文字颜色 */
    mTextPen = QPen(QColor("#eeeeee"));
    mTextFont = QFont("SimHei", 13, QFont::Bold);

    mPixIco = QPixmap("./images/tittle.png").scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    mPixBackground = QPixmap("./images/bk.png").scaled(150, 39, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    setTitleName("HelloWorld");
}

void ItemTittle::setTitleName(QString name)
{
    mTittleText = name;
}

void ItemTittle::setTittleSize(qreal w, qreal h)
{
    mWidth = w;
    mHeight = h;
    update();
}

void ItemTittle::setTextColor(QColor left, QColor right)
{
    mLeftColor = left;
    mRightColor = right;
}

QRectF ItemTittle::boundingRect() const
{
    return QRectF(0, 0, mWidth, mHeight).normalized();
}

void ItemTittle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QLinearGradient lg = QLinearGradient(0, -70, mWidth, 70);
    lg.setColorAt(0, mLeftColor);
    lg.setColorAt(0.6, mLeftColor);
    lg.setColorAt(0.9, mRightColor);
    lg.setColorAt(1, mRightColor);

    QPainterPath path_content1 = QPainterPath();
    path_content1.setFillRule(Qt::WindingFill);
    path_content1.addRoundedRect(3, 2, mWidth - 6, mHeight - 1, mRoundnes, mRoundnes);
    path_content1.addRect(3, mRoundnes + 2, mWidth - 6, mHeight - mRoundnes);

    painter->setPen(Qt::NoPen);
    painter->setBrush(lg);
    painter->drawPath(path_content1.simplified());

    /* 绘制高光 */
    painter->setClipRegion(QRegion(0, 2, mWidth, mRoundnes - 5));
    QPainterPath path_content = QPainterPath();
    path_content.addRoundedRect(3, 2, mWidth - 6, mHeight - 1, mRoundnes + 2, mRoundnes + 2);
    painter->setPen(mGaoGuangPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path_content.simplified());
    painter->setClipRegion(QRegion(0, 0, mWidth, mHeight));
        
    /* 绘制图片 */
    painter->drawPixmap(12, 8, 18, 18, mPixIco);
    painter->drawPixmap(12, 0, 150, 39, mPixBackground);

    /* 绘制文字 */
    painter->setFont(mTextFont);
    painter->setPen(mTextPen);
    painter->drawText(35, 23, mTittleText);
}


