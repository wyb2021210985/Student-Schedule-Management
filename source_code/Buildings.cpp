
#include"Buildings.h"
building::building(int l,int d ,int m,int n,QString Name){
    this->x=l;
    this->y=d;
    this->width=m;
    this->length=n;
    this->name=Name;
    this->build=node(Name,l+m/2,d+n/2);
}
QString building::ToString(){
    QString result;
    result=this->name+"["+QString::number(this->x)+","+QString::number(this->y)+","+QString::number(this->width)+","+QString::number(this->length)+"]";
    return result;
}
