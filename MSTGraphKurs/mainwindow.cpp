#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include "node.h"
#include <time.h>
#include "math.h"
#include <QMessageBox>

#define min  qMin
template<class T> void showTable(int n, T *table)
{
    QString str;
    for( int i=0; i< n; i++){
    for(int j=0; j<n; j++)
        {
    str+=QString::number(table[i*n+j])+", ";
}
    str+="\r\n";
}
    QMessageBox::information(0,"",str);
}
#define _INFINITY (INT_MAX/3)
int findMinEdge(int n,double  * table, int& str)
{
    int minWeight=_INFINITY;
    int minIndex=-1;

    for(int k=0; k<n; k++)
    {
        if(!table[n*n+k] || table[n*n+k] == _INFINITY) continue;
        for(int j=0; j<n; j++)
        {
            double curWeight = table[k * n + j];
            if(curWeight == -1 || curWeight == 0) continue;
            if(curWeight < minWeight)
            {
                minWeight= curWeight;
                minIndex = j;
                str = k;
            }
        }
    }
    return minIndex;
}

struct EdgeStruct
{
    int v1; int v2;
    double weight;
};


//Minimum spanning tree
void genEdges(int n, QVector<EdgeStruct> &edges, QVector<EdgeStruct> &usedEdges)
{
    double  * table = new double[(n+1)*n];

    for(int i=0; i<n*n; i++)
    {
        table[ i]=_INFINITY;
    }

    // i - строка,  j - столбец
    for(int i =0; i<edges.count();i++)
    {
        int x = edges[i].v1;
        int y = edges[i].v2;
        table[x * n + y]= edges[i].weight;
        table[y * n + x]= edges[i].weight;
    }
    for(int i=0; i<n; i++)
    {
        table[ i * n +i]=0;
        table[n*n+i] =0; // Обнуляем звездочки
    }

    int str = 0;
    table[n*n + str] = 1;
    int minElem=0;
    int c=0;
    do
    {
        for(int i=0; i<n; i++)
        {
            table[i*n + minElem] = -1; // Удаляем столбец
        }

        minElem = findMinEdge(n, table, str);
        if(minElem == -1) break;

        EdgeStruct edge = {str,minElem,table[str * n + minElem]};

        usedEdges.push_back(edge);

        table[n*n + minElem] = 1;
        c++;
    }
    while(c<10000);
    delete table;
}



int my_min(int left, int right1, int right2, bool& LeftOperandSelected)
{
    LeftOperandSelected = true;
    if(right1== _INFINITY || right2== _INFINITY) return left;

    int right = right1 + right2;
    if(left <= right)
        return left;

    LeftOperandSelected = false;
    return right;
}






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qsrand(time(0));
    ui->graphicsView->setScene(&scene);
    nStartVertex = -1;
    nEndVertex = -1;
    ui->graphicsView->setScene(&scene);
    ui->treeWidget->setColumnCount(2);
    QStringList labls;
    labls<<"Vertex";
    labls<<"Weight";
    ui->treeWidget->setHeaderLabels(labls);
    vertices.push_back(new CVertex(50,50));
    vertices.push_back(new CVertex(150,150));
    vertices.push_back(new CVertex(250,350));
    vertices.push_back(new CVertex(50,350));
    updateNodes();
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->label_2->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->checkBox_3->setVisible(false);
    ui->pushButton_3->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddRoot(QString Vertex, QString NumberOfChild)
{
    QTreeWidgetItem *itm=new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,Vertex);
    itm->setText(1,NumberOfChild);
    ui->treeWidget->addTopLevelItem(itm);
    itmNodes.push_back(itm);
}

void MainWindow::AddChild(QTreeWidgetItem *parent, QString Vertex, QString Weight)
{
    QTreeWidgetItem *itm=new QTreeWidgetItem();
    itm->setText(0,Vertex);
    itm->setText(1,Weight);
    parent->addChild(itm);
}

void MainWindow::on_pushButton_clicked()
{
    int x = qrand() % 300;
    int y = qrand() % 300;
    vertices.push_back(new CVertex(x,y));
    updateNodes();
    ui->statusBar->showMessage("Vertex Added");
}
void MainWindow::updateNodes()
{
    qDeleteAll(graphicsNodes);
    qDeleteAll(itmNodes);
    itmNodes.clear();
    graphicsNodes.clear();
    ui->treeWidget->clear();
    int i=0;
    for(i=0; i< vertices.count(); i++)
    {
        Node* nn = new Node(i);
        scene.addItem(nn);
        nn->setPos(vertices[i]->x(),vertices[i]->y());
        nn->setZValue(2);
        QString name=QString::number(i);
        vertices[i]->setName(name);
        nn->setObjectName(vertices[i]->name());
        AddRoot(vertices[i]->name(),"0");
        connect(nn,SIGNAL(moved(Node*)),SLOT(sceneChanged(Node*)));
        connect(nn,SIGNAL(deleted(Node*)),SLOT(nodeDeleted(Node*)));
        graphicsNodes.push_back(nn);
    }
    updateEdges();
}
void MainWindow::nodeDeleted(Node *node)
{
    vertices.remove(node->getIndex());
    for(int i=0; i<graphicsNodes.count(); i++)
    {
        graphicsNodes[i]->deleteLater();
    }
    graphicsNodes.clear();
    updateNodes();
    ui->statusBar->showMessage("Vertex Deleted",10000);
}
void MainWindow::sceneChanged(Node *data)
{
    int index = data->getIndex();
    CVertex* node = vertices[index];
    node->setX (data->x());
    node->setY(data->y());
    updateEdges();
}

void MainWindow::updateEdges()
{
    for(int i =0; i< graphicsEdges.count(); i++)
    {
        delete graphicsEdges[i];
    }
    graphicsEdges.clear();

    if(userEdges.empty())
    rebuildGraph();


    for(int i=0; i< edges.count(); i++)
    {
        QList<QGraphicsItem *> items;
        CEdge* it2 = edges[i];

        int x1,y1, x2, y2;
        x1 = it2->v1()->x();
        y1 = it2->v1()->y();
        x2 = it2->v2()->x();
        y2 = it2->v2()->y();
        QGraphicsLineItem * line = scene.addLine(x1,y1,x2, y2);
        if(!it2->isEnabled())
        {
            QPen pen(Qt::lightGray);
            pen.setStyle(Qt::DashLine);

            line->setPen(pen);
        }
        items.push_back(line);

        double distance = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
        if(distance>30)
        {

            double angle = atan((double)(y1-y2)/((x1-x2)));
            angle = 180/M_PI*angle;

            int offsetX, offsetY;

            QGraphicsSimpleTextItem* text = scene.addSimpleText(QString::number(it2->weight()));

            offsetX = text->sceneBoundingRect().width()/2;
            offsetY = text->sceneBoundingRect().height()/2;
            text->setPos((x1+x2)/2 - text->boundingRect().width()/2, (y1+y2)/2-text->boundingRect().height()/2);


            QGraphicsRectItem* bgRect =  scene.addRect(0,0,text->sceneBoundingRect ().width(),text->sceneBoundingRect ().height() ,QPen(Qt::green),QBrush(Qt::yellow));
            if(!it2->isEnabled())
            {
                QPen pen(Qt::lightGray);
                pen.setStyle(Qt::DashLine);
                bgRect->setPen(pen);
                bgRect->setBrush(QBrush(Qt::white));
                text->setBrush(QBrush(Qt::lightGray));

            }
            bgRect->setPos(text->sceneBoundingRect().x(),text->sceneBoundingRect().y());

            text->setTransform(QTransform().translate(offsetX, offsetY).rotate(angle).translate(-offsetX, -offsetY));
            text->setZValue(2);
            bgRect->setTransform(QTransform().translate(offsetX, offsetY).rotate(angle).translate(-offsetX, -offsetY));
            items.push_back(text);
            items.push_back(bgRect);
        }


        QGraphicsItem* group = scene.createItemGroup(items);
        graphicsEdges.push_back(group);
        }
}

void MainWindow::rebuildGraph()
{
    QString Report;

    QVector<EdgeStruct> allEdges;
    QVector<EdgeStruct> usedEdges;
    int n =vertices.count();

    if(userEdges.empty())
    {
        for(int i=0; i<n-1; i++)
        {
           for (int j=i+1; j<n; j++)
            {
               CVertex * v1 = vertices[i];
               CVertex * v2 = vertices[j];
               EdgeStruct s;
               s.v1 = i;
               s.v2= j;
               s.weight = sqrt(pow(v1->x()-v2->x(),2) + pow(v1->y()-v2->y(),2));
               QString Vertex=QString::number(j);
               QString Weight=QString::number(s.weight);
               AddChild(itmNodes[i],Vertex,Weight);
               allEdges.push_back(s);
           }
        }
    }
    else
    {
        CEdge *edge;
        foreach (edge, userEdges)
        {
               //	qDebug() << str;
            EdgeStruct s;
            s.v1 = vertices.indexOf(edge->v1());
            s.v2 = vertices.indexOf(edge->v2());
            s.weight = edge->weight();
            allEdges.push_back(s);
        }
    }

    qDeleteAll(edges);
    edges.clear();
    genEdges(n, allEdges, usedEdges);

    double sumWeight=0;

   for(int i=0; i<usedEdges.count(); i++)
{
       if(Report.isEmpty())
       Report+=vertices[usedEdges[i].v1]->name();

       //if(!ui->interconnectRadioBtn->isChecked())
       {
           Report+="->"+vertices[usedEdges[i].v2]->name();
       }

   }
        for(int i=0; i< allEdges.count(); i++)
        {
            bool found = false;
            int jFound=0;
            for (int j=0; j< usedEdges.count(); j++)
            {
                if((usedEdges[j].v1 == allEdges[i].v1 && usedEdges[j].v2 == allEdges[i].v2) || (usedEdges[j].v1 == allEdges[i].v2 && usedEdges[j].v2 == allEdges[i].v1))
                {
                   found = true;
                   jFound = j;
               }

            }
           if(found)
            {

               sumWeight+=allEdges[i].weight;
               edges.push_back(new CEdge(vertices[allEdges[i].v1],vertices[allEdges[i].v2], allEdges[i].weight));

        }
           else if(ui->showHiddenEdges->isChecked())
                edges.push_back(new CEdge(vertices[allEdges[i].v1],vertices[allEdges[i].v2], allEdges[i].weight,false));

        }
        if(Report.isEmpty())
            Report = QString::fromLocal8Bit("Route does not exist.");
            else
        Report+=QString::fromLocal8Bit(" Route Weight=")+ QString::number(sumWeight);
        ui->statusBar->showMessage(Report,1000);
    }
void MainWindow::RefreshTable()
{
//    qDeleteAll(itmNodes);
//    itmNodes.clear();
//    int n =vertices.count();
//    for(int i=0; i<n;i++)
//                AddRoot(vertices[i]->name(),"0");
//    for(int i=0; i<n-1; i++)
//    {
//       for (int j=i+1; j<n; j++)
//        {
//           CVertex * v1 = vertices[i];
//           CVertex * v2 = vertices[j];
//           EdgeStruct s;
//           s.v1 = i;
//           s.v2 = j;
//           s.weight = sqrt(pow(v1->x()-v2->x(),2) + pow(v1->y()-v2->y(),2));
//           QString Vertex=QString::number(j);
//           QString Weight=QString::number(s.weight);
//           AddChild(itmNodes[i],Vertex,Weight);
//       }
//    }
}
void MainWindow::on_showHiddenEdges_stateChanged(int arg1)
{
        updateEdges();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString NewWeight=ui->lineEdit->text();
    if(ui->checkBox_3->isChecked())
    {
        updateEdges();
    }
    ui->label_2->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->checkBox_3->setVisible(false);
    ui->pushButton_3->setVisible(false);
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(item->childCount()==0)
    {
        QString Vexel=item->text(0);
        QString W=item->text(1);
        ui->label_2->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->checkBox_3->setVisible(true);
        ui->pushButton_3->setVisible(true);
    }
}

void MainWindow::on_AddingEdge_stateChanged(int arg1)
{
    updateEdges();
}
