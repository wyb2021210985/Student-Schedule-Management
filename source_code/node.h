
#ifndef NODE_H
#define NODE_H
#include<QString>
class node{
public:
    node(QString a,int X,int Y);
    node();
    int getX();
    int getY();
    QString getname();
private:
    QString name;
    int x;
    int y;
};
#endif // NODE_H
