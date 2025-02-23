#include"node.h"
node::node(QString a,int X,int Y){
    this->name=a;
    this->x=X;
    this->y=Y;
}
int node::getX(){
    return this->x;
}
int node::getY(){
    return this->y;
}
QString node::getname(){
    return this->name;
}
node::node(){

}
