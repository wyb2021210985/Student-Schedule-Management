
#ifndef AFTERCLASS_H
#define AFTERCLASS_H
#include<QObject>
#include<vector>
#include"qdatetime.h"
using namespace std;

class Activity{
public:
    int sign;//使用双向链表,sign=1表示哨兵节点,sign=0表示普通节点;
    Activity*next;    //后继
    Activity*prior;   //前驱
    Activity();
    Activity(int type,int tag, QString location, int circulation, QDateTime StartTime,int flag);
    Activity(QDateTime);
    Activity(Activity*);
    Activity(int tag);
    int getType();
    int getTag();
    QString getlocation();
    int getCirculation();
    QDateTime getStartTime();
    int getFlag();
    void setType(int type);
    void setTag(int tag);
    void setLocation(QString location);
    void setCirculation(int circulation);
    void setStarttime(QDateTime StartTime);
    void setFlag(int flag);
    QString toString(int i);
    void addActivityNode(Activity*a); //在链表的最后增加新的节点
    int comparetime(QDateTime,QDateTime); //比较时间，第一个参数早于第二个返回值小于0，相等返回0，否则返回值大于0
    void sortbyTime();     //按时间升序排序
    void quicksortTime(Activity*low,Activity*high);   //按时间快速排序
    Activity* quickPassTime(Activity*low,Activity*high);   //按时间排序寻找枢纽
    void swap(Activity*a,Activity*b);  //交换链表a和b中的数据
    void deleteActivitybyTag(int tag); //按时间删除课外活动
private:
    //课外活动持续时间仅为1小时
    int type; //1为个人活动，0为集体活动
    int tag;//活动名，比如自习、锻炼
    QString location;
    int circulation; //1为一次性的，2为每天一次，3为每周一次
    QDateTime StartTime;
    int flag;//线下为0，线上为1
};

#endif // AFTERCLASS_H

