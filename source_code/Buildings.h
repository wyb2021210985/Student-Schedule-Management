
#ifndef BUILDINGS_H
#define BUILDINGS_H
#include<vector>
#include<QString>
using namespace std;
#include"node.h"
class building{
public:
    building(int l,int d ,int m,int n,QString Name);
    node build;
    int x;
    int y;
    int width;
    int length;
    QString name;
    QString ToString();
};

#endif // BUILDINGS_H
