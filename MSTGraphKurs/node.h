#ifndef NODE_H
#define NODE_H


#include <QGraphicsItem>
#include <QKeyEvent>



class Node : public QObject, public QGraphicsItem
{
Q_OBJECT
public:
    explicit Node(int index);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void keyPressEvent ( QKeyEvent * event );
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int getIndex();
    bool Selected();
signals:
    void moved(Node *node);
    void deleted(Node *node);

public slots:
private:
    int m_nIndex;

};
#endif // NODE_H
