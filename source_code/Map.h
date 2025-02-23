#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include<QtWidgets>
#include <QObject>
#include<QStack>
#include<QPen>
#include<QPainter>
#include<QAxObject>
#include<QFile>
#include "Graph.h"
class Map:public QWidget{
    Q_OBJECT
public:
    Map(Graph*g,bool showpath,vector<int> path,QWidget* parent=nullptr);
    Graph*g;  //图
    void writelog(QString content);
    void paintEvent(QPaintEvent*event);  //绘制地图
private:
    QString START;
    QString DEST;
    bool showpath; //是否显示路径
    bool showallnodes;  //是否显示图的点和边
    vector<int> path;   //路径
};

#endif // MAP_H
