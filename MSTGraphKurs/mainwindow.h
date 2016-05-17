#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "node.h"
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <math.h>
#include <QTreeWidgetItem>

class CVertex
{
    public:
    CVertex ()
    {
    }

    CVertex (int x, int y)
    {
        m_x = x;
        m_y= y;
    }
    virtual int x() const{ return m_x; }
    virtual int y() const { return m_y; }

    void setX(int x) {m_x = x; }
    void setY(int y) {m_y = y; }
    void setName(const QString& name) { m_name = name; }
    QString name() const { return m_name; }
private:
    int m_x, m_y;
    QString m_name;
};

class CEdge
{
    public:
    CEdge(CVertex* v1, CVertex* v2, double weight = -1, bool enabled = true)
    {
            m_v1 = v1;
            m_v2 = v2;
            m_weight = weight;
            m_enabled = enabled;
    }

    double weight() const
    {
        if(m_weight>0) return m_weight;
        return sqrt(pow(m_v1->x()-m_v2->x(),2) + pow(m_v1->y()-m_v2->y(),2));
    }

        CVertex* v1() const{ return m_v1;}
        CVertex* v2() const { return m_v2; }
        bool isEnabled() const { return m_enabled; }
    private:
        CVertex* m_v1;
        CVertex* m_v2;
        bool m_enabled;
        double m_weight;
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddRoot(QString Vertex, QString NumberOfChild);
    void AddChild(QTreeWidgetItem *parent,QString Vertex, QString Weight);
    void RefreshTable();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QVector<CVertex*> vertices;
    QVector<Node*> graphicsNodes;
    QVector<QGraphicsItem*> graphicsEdges;
    QGraphicsItemGroup *group;
    QList<CEdge*> userEdges;
    QList<CEdge*> edges;
    QVector<QTreeWidgetItem*> itmNodes;
    int nStartVertex, nEndVertex;
    void updateNodes();
    void updateEdges();
    void rebuildGraph();
private slots:
    void sceneChanged(Node *data);
    void on_pushButton_clicked();
    void nodeDeleted(Node *node);
    void on_showHiddenEdges_stateChanged(int arg1);
    void on_pushButton_3_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_AddingEdge_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
