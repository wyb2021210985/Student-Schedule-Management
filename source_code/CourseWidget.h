
#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H
#include<QtWidgets>
#include<QObject>
#include<QStack>
#include<QPen>
#include<QPainter>
#include<QAxObject>
#include<QFile>
#include"User.h"
using namespace std;
class CourseWidget:public QWidget{
    Q_OBJECT
public:
    CourseWidget(vector<Course>*a,int index,vector<User*> UserList,QDateTime currentTime,QString ID,vector<QString> allbuildingsname,QWidget* parent=nullptr);
    int index;
    void deleteAllStudentsCourse(Course a);   //删除所有学生的一门课程
    bool CouldaddCourseToAll(Course*a);      //可以把课程增加给所有学生
    void deleteOneStudentsCourse(Course a,User*u);   //删除一个学生的一门课程
    bool CouldChangeAllCourse(Course*a,Course*b);    //可以更改课程
    vector<Course>*CourseList;
    vector<User*> UserList;
    QDateTime currentTime;
    QString adminID;
    vector<QString> allbuildingsname;
    bool judgeValidCourseTime(QDateTime a,int lastTime); //上课时间是否合规
    void writelog(QString a);   //写日志
    bool judgeValidLocation(QString a);    //判断线下课程的地点是否合规
};
#endif // COURSEWIDGET_H
