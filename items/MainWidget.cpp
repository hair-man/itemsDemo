#include <QHboxLayout>

#include "itemArrowLine.h"

#include "ItemWidget.h"
#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QDialog(parent)
{
    resize(1200, 800);

    mpScene = new QGraphicsScene(this);
    mpView = new QGraphicsView(mpScene, this);
    mpView->setSceneRect(-300, -200, 600, 400);
    mpView->setRenderHint(QPainter::Antialiasing, true);
    mpView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QHBoxLayout* pHbox = new QHBoxLayout(this);
    QWidget* pWidget = new QWidget(this);


    pHbox->addWidget(pWidget, 2);
    pHbox->addWidget(mpView, 8);


    ItemWidget* pItem = new ItemWidget(ItemWidget::TYPE::IPDEV);
    pItem->setPos(300, 300);
    mpScene->addItem(pItem);

    pItem = new ItemWidget(ItemWidget::TYPE::YTHCLIENT);
    pItem->setPos(-300, -300);
    mpScene->addItem(pItem);

    pItem = new ItemWidget(ItemWidget::TYPE::VOIP);
    pItem->setPos(-300, 300);
    mpScene->addItem(pItem);

    ItemWidget*  pItem1 = new ItemWidget(100);
    pItem1->setPos(300, -300);
    mpScene->addItem(pItem1);


    ArrowItem* pLine = new ArrowItem(pItem, pItem1);
    mpScene->addItem(pLine);

}

MainWidget::~MainWidget()
{
}
