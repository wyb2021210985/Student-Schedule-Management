
#ifndef CLASSTABLE_H
#define CLASSTABLE_H
#include<QtWidgets>
#include"ScheduleTable.h"
class ClassTable:public QWidget{
    Q_OBJECT;
public:
    ClassTable(ScheduleTable*schedule,QWidget*parent=nullptr);
    ScheduleTable*scheduleTable;  //用户的日程
    int week;    //表示第几周的课程
};
#endif // CLASSTABLE_H

