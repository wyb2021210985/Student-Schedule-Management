
#ifndef COURSE_H
#define COURSE_H
#include<QObject>
#include<QDateTime>
class Course{
public:
    Course(QString name,QString location,QDateTime startTime,int lasttime,QDateTime examTime,QString examlocaion,int examlastTime,int type,int circulation);
    Course();
    QString getname();
    QDateTime getStartTime();
    int getLastTime();
    int getCirculation();
    QString getLocation();
    QString toString(int i);
    int getExamLastTime();
    QDateTime getExamTime();
    QString getExamLocation();
    int compare(Course a);      //比较两门课程，先根据名称字符串比较，如果相同，再根据开始时间比较
    void setExamTime(QDateTime a);
    void setExamLocation(QString a);
    void setExamLastTime(int a);
    void setName(QString a);
    void setLocation(QString l);
    void setStartTime(QDateTime t);
    void setCirculation(int);
    void setLastTime(int a);
    void setType(int a);
    int getType();
private:
    QString name;
    QString location;
    QDateTime startTime;
    int circulation; //1为一次性的，2为周期性的
    QDateTime ExamTime;
    QString ExamLocation;
    int lasttime;
    int ExamLastTime;//考试持续时间
    int type; //type=0为线下,type=1为线上
};

#endif // COURSE_H
