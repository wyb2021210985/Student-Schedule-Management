
#ifndef TEMPORARY_H
#define TEMPORARY_H
#include "qdatetime.h"
#include <QObject>

class Temporary{
public:
    Temporary(QDateTime start,int EventType,QString location);
    Temporary();
    Temporary(int e);
    QDateTime getStartTime();
    Temporary*next;
    Temporary*prior;
    void addTemporaryNode(Temporary*t);
    int sign;   //使用双向链表,sign=1表示哨兵节点,sign=0表示普通节点;
    void sortbyType(); //根据活动类型排序;
    void deleteTemporarybyType(int e);  //按类型删除;
    int getEventType();
    void quicksort(Temporary*low,Temporary*high);  //根据EventType快速排序
    Temporary*quickPass(Temporary*low,Temporary*high); //根据EventType快速排序寻找枢纽单元
    void swap(Temporary*a,Temporary*b);  //交换a和b临时事务的所有信息;
    void setstartTime(QDateTime a);
    void setEventType(int e);
    void setlocation(QString l);
    QString getLocation();
    void deleteByTime(QDateTime);     //根据时间删除
    Temporary(QDateTime);
    int comparetime(QDateTime,QDateTime);  //比较两个时间，如果第一个参数早于第二个，返回值小于0,相同返回0,如果第一个参数晚于第二个返回值大于零
    void sortbyTime();           //根据时间排序
    void quicksortTime(Temporary*low,Temporary*high);  //根据时间的快速排序
    Temporary*quickPassTime(Temporary*low,Temporary*high);  //根据时间快速排序寻找枢纽单元
    QString toString(int);
    Temporary(Temporary*);

private:
    QDateTime startTime;
    int EventType;
    QString location;
};
#endif // TEMPORARY_H
