#ifndef GRAPH_H
#define GRAPH_H
#include"node.h"
#include<vector>
#include<QStack>
#include<qfile.h>
#include<QObject>
#include<QAxObject>
#include "Buildings.h"

using namespace std;
class d{
public:
    d(vector<int> Set,int C,int start);
    int  Cik;   //起始点
    vector<int> set;     //要经过的点的集合
    vector<vector<int>> getsubset();//所有子集
    vector<d*> parse();   //将d的set分解成更小的d
    int startIndex;     //最终要回到的点的下标
};
struct Path{
    int*parent;
    int*distance;
};

class Graph{
public:
    Graph(QString nodefile,QString buildingsfile,QString graphfile);
    Graph(vector<node> a);
    void insertnode(node b); //插入点
    vector<node> nodes;  //所有点
    int**AdjacentMatrice;  //权重矩阵
    vector<building> allbuildings;   //所有建筑物
    Path*Dj(node start);      //迪杰斯特拉算法，用Path结构存储返回值
    int FindIndex(vector<node> allnodes, QString a); //对应的地点名称在图中的所有点的下标
    int distance(node a,node b);   //两个点的距离
    int fabs(int a);    //绝对值
    void ReadGraph(QString filename);  //从txt文件中读取每个点和另外的点的连接情况
    void ReadNodes(QString filename);   //从txt文件中读取每个点的信息，名称和坐标
    void ReadBuildings(QString filename); //读取建筑物信息
    void writenodes();   //将图中的点的信息写入txt
    vector<int> FindShortestPath(QString start,QString dest);  //寻找从一个地点到另一个地点的最短路径，用int向量存储对应点的下标
    int getlength(vector<int> path);  //得到路径的长度
    int FindBuildingIndex(QString buildingsname); //找到建筑物的名称在allbuildings中的下标
    void printallnodes();   //打印所有点的信息
    void showallbuildings();   //打印所有建筑物的信息
    vector<int> PostMan(vector<QString>);    //求从一个点出发经过多个点回到原点的最短路径，返回途径点的下标
    int min(vector<int>);      //一个int向量最小值的下标
    vector<int> TSP(d*,vector<int>);   //递归求得中国邮差问题的解，得到从d的Cik点出发，经过set里面所有点，回到startIndex的最短路径
};
#endif

