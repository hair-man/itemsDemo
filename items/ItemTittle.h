#pragma once

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>
#include <QLinearGradient>


class ItemTittle : public QGraphicsItem
{
public:
    ItemTittle(int width, int height, QGraphicsItem* parent = nullptr);

    void ItemTittleInit();
    void setTitleName(QString name);
    void setTittleSize(qreal w, qreal h);
    void setTextColor(QColor left, QColor right);

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) ;


private:
    qreal mWidth;
    qreal mHeight;

    /* 标题颜色渐变 */
    QColor mLeftColor;
    QColor mRightColor;
    QPen mGaoGuangPen;

    /* 标题圆角 */
    qreal mRoundnes;
    
    QString mTittleText;

    QPixmap mPixIco;
    QPixmap mPixBackground;

    QPen    mTextPen;
    QFont   mTextFont;
};

