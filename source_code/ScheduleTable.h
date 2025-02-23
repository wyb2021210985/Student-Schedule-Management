
#ifndef SCHEDULETABLE_H
#define SCHEDULETABLE_H
#include<QObject>
#include<vector>
using namespace std;
#include"Course.h"
#include"AfterClass.h"
#include"Temporary.h"
#include"AVLCourseNode.h"
union event{
    Temporary*temporary;
    Course*course;
    Activity*activity;
};
class taken{
public:
    taken();
    int type;   //0为空闲，1为课程，2为课外活动，3为临时事务，4为考试
    event Event;
};

class ScheduleTable{
public:
    taken*t[20][7][24];      //表示这一学期每一小时的事件占用情况
    ScheduleTable();
    int addTemporary(Temporary*t); //成功插入返回1,否则返回0
    QString toString();      //转化为字符串，与用户信息的保存有关
    Temporary* searchTemporarybyTag(int tag); //按临时事务的类型搜索
    Temporary*searchTemporarybyTime(QDateTime time);   //按临时事务的时间搜索
    void destroyTemporaryList(Temporary*a);   //清空链表，释放链表的所占的内存空间
    int getDay(QString a);
    int deleteTemporaryByTime(QDateTime time); //根据时间time删除临时事务，包括t中的和hashTemporary中的
    bool CourseNotice(QDateTime);               //该时间是否有课程
    bool TemporaryNotice(QDateTime a);         //该事件是否有临时事务
    vector<QString> TemporaryPath(Temporary*);   //返回同一小时的临时事务的所经过地点
    int Temporaryconflict(Temporary*);          //临时事务是否有冲突
    CourseAVL*courseAVL;             //存储个人课程的平衡二叉树
    void SearchbyName(QString name);//查
    bool CouldaddCourse(Course*b); //能否增加课程
    bool CouldChangeCourse(Course*origin,Course*newCourse); //能否改变课程
    int addCourse(Course*b);  //增加课程，成功插入返回1,否则返回0
    int deleteCourse(Course b);//删除课程，成功删除返回1，否则返回0
    int change(Course*newCourse,Course*origin);//改，包括课程和考试信息
    int addActivity(Activity*a);//添加课外活动
    int Activityconflict(Activity*);//课外活动冲突检测
    Activity* searchActivitybyTag(int tag);   //按课外活动类型搜索课程
    Activity* searchActivitybyTime(QDateTime time);//按课外活动时间搜索课程
    void destroyActivityList(Activity*a);    //释放课外活动链表所占内存空间
    int deleteActivitybyTime(QDateTime time); //按时间删除课外活动
    bool ActivityNotice(QDateTime time);      //该事件是否有课程
    bool checktimeOne(int week,int weekday,int hour);  //检查一次性课外活动是否和日程有冲突
    bool checktimeDay(int week,int weekday,int hour);   //检查周期为每天的课外活动是否与日程有冲突
    bool checktimeWeek(int week,int weekday,int hour); //检查周期为每周的课外活动是否与日程有冲突
    vector<Activity*> hashActivity;
    vector<Temporary*> hashTemporary;
};

#endif // SCHEDULETABLE_H
