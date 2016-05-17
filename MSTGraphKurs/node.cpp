#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "node.h"
#include "mainwindow.h"

Node::Node(int index):QGraphicsItem()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(ItemSendsGeometryChanges);
    m_nIndex = index;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);
    painter->setPen(Qt::NoPen);
    QRadialGradient gradient(-3, -3, 10);

    if (option->state & QStyle::State_Selected)
    {
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(1, Qt::red);
    }
    else
    {
        gradient.setColorAt(0, Qt::lightGray);
        gradient.setColorAt(1, Qt::lightGray);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawText(QPoint(-3,3),objectName());

}

QRectF Node::boundingRect() const
{
     qreal adjust = 2;
     return QRectF(-10 - adjust, -10 - adjust,
                        23 + adjust, 23 + adjust);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
     switch (change) {
     case ItemPositionHasChanged:

         emit moved(this);
          break;
     default:
          break;
     };

     return QGraphicsItem::itemChange(change, value);
}

void  Node::keyPressEvent ( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Delete)
        emit deleted(this);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if(event->button()==Qt::RightButton)
      emit deleted(this);
}


int  Node::getIndex()
{
    return m_nIndex;
}

bool Node::Selected()
{
    if(QStyle::State_Selected)
        return true;
    else return false;
}


