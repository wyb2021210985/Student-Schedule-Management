#include <iostream>
#include <string>
#include <vector>
#include <QtWidgets>
#include <QObject>
#include<QStack>
#include<QPen>
#include<QPainter>
#include<QAxObject>
#include<qfile.h>
#include"Graph.h"
#include "User.h"
#include "Map.h"
#include"ScheduleTable.h"
#include"CourseWidget.h"
#include"ClassTable.h"
using namespace std;
struct HourUsage{
    int hour;
    int conflictTime;
};
//时钟类
class mainWindow : public QMainWindow{
    Q_OBJECT
public:
    mainWindow(User*current,vector<User*> UserList,QWidget* parent = nullptr):QMainWindow(parent),UserList(UserList),CurrentUser(current){
        // Set up tab widget
        this->UserID=this->CurrentUser->getID();
        this->currentLocation="学十一公寓";
        this->schedule=this->CurrentUser->scheduletable;
        QTimer*timer=new QTimer(this);
        QLabel*timelabel=new QLabel("当前时间",this);
        timelabel->setGeometry(20,70,70,30);
        timer->stop();
        timer->setInterval(10000);
        timer->start();
        this->currentTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
        this->showtime=new QTextBrowser(this);
        showtime->setText(currentTime.toString("yyyy-MM-dd HH"));
        showtime->setGeometry(20,100,120,30);
        showtime->show();
        QDateTimeEdit* timeEdit=new QDateTimeEdit(this->currentTime,this);
        timeEdit->setDisplayFormat("yyyy-MM-dd HH");
        timeEdit->setGeometry(150,100,150,30);
        QPushButton*startButton = new QPushButton("开始",this);
        QPushButton*pauseButton = new QPushButton("暂停",this);
        QPushButton*skipButton = new QPushButton("跳转",this);
        QPushButton*quickenButton = new QPushButton("加速",this);
    /*    QPushButton*setClock=new QPushButton("设置闹钟",this);
        QComboBox*alarmtype=new QComboBox(this);
        QStringList allalarmtype={"一次性","每天","每周"};
        QDateTimeEdit*alarmclock=new QDateTimeEdit(this->currentTime,this);*/

       /* alarmtype->addItems(allalarmtype);
        alarmclock->setGeometry(20,180,120,30);
        alarmtype->setGeometry(150,180,60,30);
        setClock->setGeometry(50,215,80,20);*/
         QPushButton*recoverButton = new QPushButton("恢复",this);
        recoverButton->setGeometry(230,150,40,20);
        startButton->setGeometry(20,150,40,20);
        pauseButton->setGeometry(70,150,40,20);
        quickenButton->setGeometry(130,150,40,20);
        skipButton->setGeometry(180,150,40,20);
        //搜索功能
        QPushButton*searchbyAfterClassType=new QPushButton("根据课外活动类型搜索",this);
        QPushButton*searchbyAfterClassTime=new QPushButton("根据课外活动时间搜索",this);
        QPushButton*searchbyTemporaryType=new QPushButton("根据临时事务类型搜索",this);
        QPushButton*searchbyTemporaryTime=new QPushButton("根据临时事务时间搜索",this);
        QDateTimeEdit*afterclassTime=new QDateTimeEdit(this->currentTime,this);
        QDateTimeEdit*TemporaryTime=new QDateTimeEdit(this->currentTime,this) ;
        QPushButton*searchByName=new QPushButton("搜索课程",this);
        QComboBox*TemporaryType=new QComboBox(this);
        QComboBox*AfterClassType=new QComboBox(this);
        QStringList allAfterClass={"自习","锻炼","外出","班会","小组作业","创新创业","聚餐"};
        QStringList allTemporary={"购物","洗澡","取外卖","取快递","吃饭","洗衣服","勤工俭学","做志愿","睡午觉"};
        QLineEdit*classnameinput=new QLineEdit(this);
        TemporaryType->addItems(allTemporary);
        AfterClassType->addItems(allAfterClass);
        QLabel*searchClass=new QLabel("搜索课程",this);
        QLabel*searchAfterClass=new QLabel("搜索课外活动",this);
        QLabel*searchTemporary=new QLabel("搜索临时事务",this);
        searchClass->setGeometry(20,250,120,30);
        classnameinput->setGeometry(20,280,120,30);
        searchByName->setGeometry(150,280,100,30);
        searchAfterClass->setGeometry(20,310,120,30);
        afterclassTime->setGeometry(20,340,120,30);
        afterclassTime->setDisplayFormat("yyyy-MM-dd HH");
        AfterClassType->setGeometry(150,340,80,30);
        searchbyAfterClassTime->setGeometry(00,370,140,30);
        searchbyAfterClassType->setGeometry(150,370,140,30);
        searchTemporary->setGeometry(20,410,100,20);
        TemporaryTime->setGeometry(20,430,120,30);
        TemporaryTime->setDisplayFormat("yyyy-MM-dd HH");
        TemporaryType->setGeometry(150,430,120,30);
        searchbyTemporaryTime->setGeometry(00,460,140,30);
        searchbyTemporaryType->setGeometry(150,460,140,30);
        //输出栏
        QTextBrowser*output=new QTextBrowser(this);
        output->setGeometry(20,500,800,200);
        //增加事物栏
        QLabel*add=new QLabel("新增事物",this);
        QLabel*addAfterClass=new QLabel("新增课外活动",this);
        QLabel*addTemporary=new QLabel("新增临时事务",this);
        QLabel*l1=new QLabel("地点",this);
        QLabel*l2=new QLabel("地点",this);
        QLabel*t1=new QLabel("时间",this);
        QLabel*t2=new QLabel("时间",this);
        QLabel*tp1=new QLabel("类型",this);
        QLabel*tp2=new QLabel("类型",this);
        QLabel*cir=new QLabel("周期",this);
        QLabel*online=new QLabel("线上或线下",this);
        online->setGeometry(860,270,100,30);
        cir->setGeometry(970,270,100,30);
        QComboBox*AfterClassCirculation=new QComboBox(this);
        QComboBox*AfterClassonline=new QComboBox(this);
        QStringList AfterClassonlineoroffline={"线下","线上"};
        QStringList Circulation={"单次","每天","每周"};
        AfterClassonline->addItems(AfterClassonlineoroffline);
        AfterClassCirculation->addItems(Circulation);
        AfterClassonline->setGeometry(860,300,80,30);
        AfterClassCirculation->setGeometry(970,300,80,30);
        addAfterClass->setGeometry(350,250,100,20);
        add->setGeometry(350,230,100,20);
        QPushButton*addAfterClassbtn=new QPushButton("增加课外活动",this);
        QPushButton*addTemporarybtn=new QPushButton("增加临时事务",this);
        QLineEdit*AfterClassLocationinput=new QLineEdit(this);
        QLineEdit*TemporaryLocationinput=new QLineEdit(this);
        QDateTimeEdit*AfterClassTimeadd=new QDateTimeEdit(this->currentTime,this);
        AfterClassTimeadd->setDisplayFormat("yyyy-MM-dd HH");
        QDateTimeEdit*TemporaryTimeadd=new QDateTimeEdit(this->currentTime,this);
        TemporaryTimeadd->setDisplayFormat("yyyy-MM-dd HH");
        QComboBox*TemporaryTypeadd=new QComboBox(this);
        TemporaryTypeadd->addItems(allTemporary);
        QComboBox*AfterClassTypeadd=new QComboBox(this);
        AfterClassTypeadd->addItems(allAfterClass);
        AfterClassLocationinput->setGeometry(350,300,150,30);
        AfterClassTypeadd->setGeometry(510,300,60,30);
        AfterClassTimeadd->setGeometry(580,300,150,30);
        QLabel*gop=new QLabel("个人或集体",this);
        QStringList gobstring={"个人","集体"};
        QComboBox*gobset=new QComboBox(this);
        gobset->addItems(gobstring);
        gobset->setGeometry(740,300,100,30);
        gop->setGeometry(740,270,120,30);
        l1->setGeometry(350,270,60,30);
        tp1->setGeometry(510,270,60,30);
        t1->setGeometry(580,270,60,30);
        addAfterClassbtn->setGeometry(350,350,100,30);
        addTemporary->setGeometry(350,390,100,30);
        l2->setGeometry(350,420,60,30);
        tp2->setGeometry(510,420,60,30);
        t2->setGeometry(580,420,60,30);
        TemporaryLocationinput->setGeometry(350,450,150,30);
        TemporaryTypeadd->setGeometry(510,450,60,30);
        TemporaryTimeadd->setGeometry(580,450,150,30);
        addTemporarybtn->setGeometry(740,450,100,30);
        //导航
        QString nodesfile="nodes.txt";
        QString graphfile="graph.txt";
        QString buildingsfile="buildings.txt";
        Graph*g=new Graph(nodesfile,buildingsfile,graphfile);
        QPushButton*showALLbuildings=new QPushButton("显示所有建筑物信息",this);
        QPushButton*showmap=new QPushButton("显示地图",this);
        QLabel*currentLocation=new QLabel("当前所在地点",this);
        QComboBox*allbuildings=new QComboBox(this);
        QStringList allbuildingsname;
        QPushButton*classTable=new QPushButton("显示课程表",this);
        classTable->setGeometry(150,0,120,30);
        //日程导航
        QLabel*scheduleNavigate=new QLabel("日程导航",this);
        scheduleNavigate->setGeometry(600,30,120,30);
        QLabel*ClassNavigate=new QLabel("课程导航",this);
        ClassNavigate->setGeometry(600,60,120,30);
        QLabel*ActivityNavigate=new QLabel("课外活动导航",this);
        ActivityNavigate->setGeometry(750,60,120,30);
        QLabel*TemporaryNavigate=new QLabel("临时事务导航",this);
        TemporaryNavigate->setGeometry(900,60,120,30);
        for(int i=0;i<(int)g->allbuildings.size();i++){
            allbuildingsname.push_back(g->allbuildings[i].name);
        }
        QLineEdit*ClassNavigateinput=new QLineEdit(this);
        ClassNavigateinput->setGeometry(600,90,150,30);
        QComboBox*AfterClassNavigateinput=new QComboBox(this);
        AfterClassNavigateinput->addItems(allAfterClass);
        AfterClassNavigateinput->setGeometry(760,90,120,30);
        QComboBox*TemporaryNavigateinput=new QComboBox(this);
        TemporaryNavigateinput->addItems(allTemporary);
        TemporaryNavigateinput->setGeometry(910,90,120,30);
        QPushButton*ClassNavigateBtn=new QPushButton("课程导航",this);
        ClassNavigateBtn->setGeometry(600,120,120,30);
        QPushButton*AfterClassNavigateBtn=new QPushButton("课外活动导航",this);
        AfterClassNavigateBtn->setGeometry(750,120,120,30);
        QPushButton*TemporaryNavigateBtn=new QPushButton("临时事务导航",this);
        TemporaryNavigateBtn->setGeometry(900,120,120,30);
        allbuildingsname.push_back("北门");
        allbuildingsname.push_back("东北门");
        allbuildingsname.push_back("中门");
        allbuildingsname.push_back("西门");
        allbuildingsname.push_back("东门");
        allbuildings->addItems(allbuildingsname);
        this->g=g;
        showALLbuildings->setGeometry(0,0,100,30);
        currentLocation->setGeometry(400,100,100,30);
        allbuildings->setGeometry(400,130,150,30);
        QPushButton*changeLocation=new QPushButton("改变当前位置",this);
        changeLocation->setGeometry(400,160,150,30);
        QPushButton*save=new QPushButton("保存",this);
        save->setGeometry(250,0,100,30);
        connect(save,&QPushButton::clicked,this,[=](){
            this->save();
        });
        connect(classTable,&QPushButton::clicked,this,[=](){
            ClassTable*classtable=new ClassTable(this->CurrentUser->scheduletable);
            classtable->show();
        });
        connect(timer,&QTimer::timeout,this,[=](){
            currentTime=currentTime.addSecs(3600);
            if(this->JudgetTimevalid()){
                QString log;
                this->showtime->setText(currentTime.toString("yyyy-MM-dd hh"));
                QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
                if(currentTime.toString("HH").toInt()==23){
                    QDateTime next=currentTime.addDays(1);
                    int days=InitialTime.daysTo(next);
                    log=log+"系统提醒:\n";
                    QString result="第二天的课程:\n";
                    for(int i=8;i<20;i++){
                        if(this->CurrentUser->scheduletable->t[days/7][days%7][i]->type==1){
                            int lasttime=this->CurrentUser->scheduletable->t[days/7][days%7][i]->Event.course->getLastTime();
                            result=result+"课程名称:"+this->CurrentUser->scheduletable->t[days/7][days%7][i]->Event.course->getname()
                                     +"\n"+"上课地点:"+this->CurrentUser->scheduletable->t[days/7][days%7][i]->Event.course->getLocation()
                                     +"\n"+"上课时间:"+this->CurrentUser->scheduletable->t[days/7][days%7][i]->Event.course->getStartTime().toString("HH")+"点--"
                                     +this->CurrentUser->scheduletable->t[days/7][days%7][i]->Event.course->getStartTime().addSecs(3600*lasttime).toString("HH")+"点\n";
                            i=i+lasttime-1;
                        }
                    }
                    result=result+"第二天的课外活动:\n";
                    for(int j=6;j<22;j++){
                        if(this->CurrentUser->scheduletable->t[days/7][days%7][j]->type==2){
                            result=result+"课外活动类型:"+allAfterClass[this->CurrentUser->scheduletable->t[days/7][days%7][j]->Event.activity->getTag()]
    +"\n"+"课外活动时间:"+this->CurrentUser->scheduletable->t[days/7][days%7][j]->Event.activity->getStartTime().toString("HH")+"点\n"
                            +"地点:"+this->CurrentUser->scheduletable->t[days/7][days%7][j]->Event.activity->getlocation()+"\n";
                        }
                    }
                    log=log+result;
                    output->clear();
                    output->setText(result);
                    this->writelog(log);
                }
                if(this->schedule->TemporaryNotice(currentTime.addSecs(3600))){
                    vector<QString> locationtogo=this->schedule->TemporaryPath(this->schedule->searchTemporarybyTime(currentTime.addSecs(3600)));
                    locationtogo.insert(locationtogo.begin(),this->currentLocation);
                    this->path=g->PostMan(locationtogo);
                    this->showpath=true;
                    output->clear();
                    log=log+"系统提醒:\n";
                    QString PathString="临时事务路线:\n";
                    int i;
                    for(i=0;i<this->path.size();i++){
                        if(i>0&&i%3==0){
                            PathString=PathString+"\n";
                        }
                        if(i==this->path.size()-1){
                            PathString=PathString+this->g->nodes[this->path[i]].getname()+"\n";
                        }
                        else{
                            PathString=PathString+this->g->nodes[this->path[i]].getname()+"->";
                        }

                    }
                    log=log+PathString;
                    output->setText(PathString);
                    this->writelog(log);
                }
                if(this->CurrentUser->scheduletable->CourseNotice(currentTime.addSecs(3600))){
                    QDateTime CourseTime=currentTime.addSecs(3600);
                    int days2=InitialTime.daysTo(CourseTime);
                    int hour2=CourseTime.toString("HH").toInt();
                    QString PathString="课程提醒:"+this->CurrentUser->scheduletable->t[days2/7][days2%7][hour2]->Event.course->getname()
                        +"\n"+"地点:";
                    if(this->CurrentUser->scheduletable->t[days2/7][days2%7][hour2]->Event.course->getType()==0){
                        QString dest=this->CurrentUser->scheduletable->t[days2/7][days2%7][hour2]->Event.course->getLocation();
                        PathString=PathString+dest+"\n"+"路线:";
                        this->path=this->g->FindShortestPath(this->currentLocation,dest);
                        this->showpath=true;
                        int i;
                        for(i=0;i<this->path.size();i++){
                            if(i==this->path.size()-1){
                                PathString=PathString+this->g->nodes[this->path[i]].getname();
                            }
                            else{
                                PathString=PathString+this->g->nodes[this->path[i]].getname()+"->";
                            }
                            if(i>0&&i%3==0){
                                PathString=PathString+"\n";
                            }
                        }
                    }
                    else{
                        PathString=PathString+this->CurrentUser->scheduletable->t[days2/7][days2%7][hour2]->Event.course->getLocation();

                    }
                    log=log+PathString;
                     output->setText(PathString);
                     this->writelog(log);
                }
                if(this->CurrentUser->scheduletable->ActivityNotice(currentTime.addSecs(3600))){
                    QDateTime ActivityTime=this->currentTime.addSecs(3600);
                    int days3=InitialTime.daysTo(ActivityTime);
                    int hour3=ActivityTime.toString("HH").toInt();
                    QString PathString="课外活动提醒\n活动:"+allAfterClass[this->CurrentUser->scheduletable->t[days3/7][days3%7][hour3]->Event.activity->getTag()]+"\n地点:"+this->CurrentUser->scheduletable->t[days3/7][days3%7][hour3]->Event.activity->getlocation()+"\n路线为:\n";
                    if(this->CurrentUser->scheduletable->t[days3/7][days3%7][hour3]->Event.activity->getFlag()==0){
                        QString dest=this->CurrentUser->scheduletable->t[days3/7][days3%7][hour3]->Event.activity->getlocation();
                        this->path=this->g->FindShortestPath(this->currentLocation,dest);
                        this->showpath=true;
                        int i;
                        for(i=0;i<this->path.size();i++){
                            if(i==this->path.size()-1){
                                PathString=PathString+this->g->nodes[this->path[i]].getname();
                            }
                            else{
                                PathString=PathString+this->g->nodes[this->path[i]].getname()+"->";
                            }
                            if(i>0&&i%3==0){
                                PathString=PathString+"\n";
                            }
                        }
                    }
                    log=log+PathString;
                    output->setText(PathString);
                    this->writelog(log);
                }
            }
        });
        connect(ClassNavigateBtn,&QPushButton::clicked,this,[=](){  //课程导航
            QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
            QString tempCourseName=ClassNavigateinput->text();
            QString log="用户"+CurrentUser->getID()+"在课程导航中输入"+tempCourseName+"\n";
            vector<Course> result=this->CurrentUser->scheduletable->courseAVL->searchByname(tempCourseName,this->CurrentUser->scheduletable->courseAVL->root);
            if(result.size()==0){
                output->clear();
                output->setText("查找不到课程");
                log=log+"查找不到课程\n";
            }
            else{
                int min=-1;
                QDateTime tempTime;
                QDateTime Final;
                for(int i=0;i<result.size();i++){
                    if(result[i].getCirculation()==1){
                        tempTime=result[i].getStartTime();
                        int timedifferent=this->hourto(this->currentTime,tempTime);
                        if(timedifferent>0){
                            if((min==-1)||(min!=-1&&min>timedifferent)){
                                min=timedifferent;
                            }
                        }
                    }
                    else if(result[i].getCirculation()==2){
                        tempTime=result[i].getStartTime();
                        int days=InitialTime.daysTo(tempTime);
                        for(int j=days/7;j<18;j++){
                            int timedifferent2=this->hourto(this->currentTime,tempTime);
                            if(timedifferent2>0){
                                if((min==-1)||(min!=-1&&min>timedifferent2)){
                                    min=timedifferent2;
                                }
                            }
                            tempTime=tempTime.addDays(7);
                        }
                    }
                }
                if(min!=-1){
                    Final=this->currentTime.addSecs(min*3600);
                    int days2=InitialTime.daysTo(Final);
                    int hours2=Final.toString("HH").toInt();
                    QString dest=this->CurrentUser->scheduletable->t[days2/7][days2%7][hours2]->Event.course->getLocation();
                    int CourseTypeTemp=this->CurrentUser->scheduletable->t[days2/7][days2%7][hours2]->Event.course->getType();
                    QString PathString;
                    QString result2="地点:"+dest+"\n"+"时间:"+Final.toString("yyyy-MM-dd HH")+"\n"+"线上或线下:"+AfterClassonlineoroffline[CourseTypeTemp]+"\n";
                    if(CourseTypeTemp==0){
                        this->path=this->g->FindShortestPath(this->currentLocation,dest);
                        result2=result2+"路线为:\n";
                        for(int i=0;i<this->path.size();i++){
                            if(i>0&&i%3==0){
                                PathString=PathString+"\n";
                            }
                            if(i!=this->path.size()-1){
                               PathString=PathString+this->g->nodes[this->path[i]].getname()+"->";
                            }
                            else{
                               PathString=PathString+this->g->nodes[this->path[i]].getname()+"\n";
                            }
                        }
                        result2=result2+PathString;
                        this->showpath=true;
                    }
                    output->clear();
                    log=log+result2;
                    output->setText(result2);
                }
            }
            this->writelog(log);
        });
        connect(AfterClassNavigateBtn,&QPushButton::clicked,this,[=](){  //课外活动导航
            QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
            int tag=AfterClassNavigateinput->currentIndex();
            QString log="用户"+CurrentUser->getID()+"在课外活动导航中输入"+AfterClassNavigateinput->currentText()+"\n";
            this->CurrentUser->scheduletable->hashActivity[tag]->sortbyTime();
            Activity*temp=this->CurrentUser->scheduletable->hashActivity[tag]->next;
            int min=-1;
            QString result;
            while(temp){
                QDateTime TempTime;
                if(temp->getCirculation()==1){  //单次
                    int timedifferent=this->hourto(this->currentTime,temp->getStartTime());
                    if(timedifferent>0){
                        if((min==-1)||(min!=-1&&min>timedifferent)){
                            min=timedifferent;
                        }
                    }
                }
                else if(temp->getCirculation()==2){   //每天
                    TempTime=temp->getStartTime();
                    int days2=InitialTime.daysTo(TempTime);
                    for(int i=days2;i<140;i++){
                        int timedifferent3=this->hourto(this->currentTime,TempTime);
                        if(timedifferent3>0){
                            if((min==-1)||(min!=-1&&min>timedifferent3)){
                                min=timedifferent3;
                            }
                        }
                        TempTime=TempTime.addDays(1);
                    }
                }
                else if(temp->getCirculation()==3){    //每周
                    TempTime=temp->getStartTime();
                    int days=InitialTime.daysTo(TempTime);
                    for(int j=days/7;j<20;j++){
                        int timedifferent2=this->hourto(this->currentTime,TempTime);
                        if(timedifferent2>0){
                            if((min==-1)||(min!=-1&&min>timedifferent2)){
                                min=timedifferent2;
                            }
                        }
                        TempTime=TempTime.addDays(7);
                    }
                }
                temp=temp->next;
            }
            if(min==-1){
                result="查找不到课外活动\n";

            }
            else{
                QDateTime Final=this->currentTime.addSecs(3600*min);
                int days2=InitialTime.daysTo(Final);
                int hours2=Final.toString("HH").toInt();
                int TempAcivityType=this->CurrentUser->scheduletable->t[days2/7][days2%7][hours2]->Event.activity->getFlag();
                QString dest=this->CurrentUser->scheduletable->t[days2/7][days2%7][hours2]->Event.activity->getlocation();
                if(TempAcivityType==0){
                    this->path=this->g->FindShortestPath(this->currentLocation,dest);
                    this->showpath=true;
                }
                result="地点:"+dest+"\n"+"时间:"+Final.toString("yyyy-MM-dd HH")+"\n"+"线上或线下:"+AfterClassonlineoroffline[TempAcivityType]+"\n";

            }
            output->clear();
            log=log+result;
            this->writelog(log);
            output->setText(result);
        });
        connect(TemporaryNavigateBtn,&QPushButton::clicked,this,[=](){  //临时事务导航
            QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
            int tag=TemporaryNavigateinput->currentIndex();
            this->CurrentUser->scheduletable->hashTemporary[tag]->sortbyTime();
            QString log="用户"+CurrentUser->getID()+"在课外活动导航中输入"+TemporaryNavigateinput->currentText()+"\n";
            Temporary*temp=this->CurrentUser->scheduletable->hashTemporary[tag]->next;
            while(temp&&this->hourto(this->currentTime,temp->getStartTime())<=0){
                temp=temp->next;
            }
            QString result;
            if(!temp){
                result="查找不到临时事务";
            }
            else{
                this->path=this->g->FindShortestPath(this->currentLocation,temp->getLocation());
                this->showpath=true;
                result="地点:"+temp->getLocation()+"\n"+"时间:"+temp->getStartTime().toString("yyyy-MM-dd HH")+"\n";
                result=result+"路线为:\n";
                int i;
                for(i=0;i<this->path.size();i++){
                    if(i==this->path.size()-1){
                       result=result+this->g->nodes[this->path[i]].getname();
                    }
                    else{
                        result=result+this->g->nodes[this->path[i]].getname()+"->";
                    }
                    if(i>0&&i%3==0){
                        result=result+"\n";
                    }
                }
            }
            output->clear();
            output->setText(result);
            log=log+result;
            this->writelog(log);
        });
        connect(changeLocation,&QPushButton::clicked,this,[=](){  //改变当前位置
            this->currentLocation=allbuildings->currentText();
        });
        connect(recoverButton,&QPushButton::clicked,this,[=](){  //恢复正常速度
            timer->setInterval(10000);
        });
        connect(startButton,&QPushButton::clicked,this,[=](){   //时钟开始
            timer->start();
        });
        connect(pauseButton,&QPushButton::clicked,this,[=](){    //时钟暂停
            timer->stop();
        });
        connect(skipButton,&QPushButton::clicked,this,[=](){     //时钟跳转
            this->currentTime=timeEdit->dateTime();
            this->showtime->setText(currentTime.toString("yyyy-MM-dd hh"));
            timer->stop();
        });
        connect(quickenButton,&QPushButton::clicked,this,[=](){  //加速
            timer->setInterval(1000);
        });
        connect(searchByName,&QPushButton::clicked,this,[=](){  //根据名称搜索课程
            QString a=classnameinput->text();
            QString OutPutResult;
            QString log="用户"+this->CurrentUser->getID()+"搜索了课程:"+a+"\n";
            vector<Course> result=this->CurrentUser->scheduletable->courseAVL->searchByname(a,this->CurrentUser->scheduletable->courseAVL->root);
            if(result.size()==0){
                OutPutResult="查找不到该课程";
            }
            else{
                for(int i=0;i<result.size();i++){
                    OutPutResult=OutPutResult+result[i].toString(0);
                }
            }
            log=log+OutPutResult;
            this->writelog(log);
            output->clear();
            output->setText(OutPutResult);
        });
        connect(searchbyAfterClassType,&QPushButton::clicked,this,[=](){  //根据课外活动的类型搜索
            int i=AfterClassType->currentIndex();
            Activity*result=this->schedule->searchActivitybyTag(i);
            QString log="用户"+this->CurrentUser->getID()+"按类型搜索了课外活动:"+AfterClassType->currentText()+"\n";
            QString out;
            if(!result){
                out="查找不到课外活动";
            }
            else{
                out=result->toString(1);
            }
            log=log+out;
            this->writelog(log);
            output->setText(out);
        });
        connect(searchbyAfterClassTime,&QPushButton::clicked,this,[=](){    //根据课外活动的时间搜索
            QDateTime a=afterclassTime->dateTime();
            QString log="用户"+this->CurrentUser->getID()+"按时间搜索了课外活动:"+a.toString("yyyy-MM-dd HH")+"\n";
            Activity*result=this->schedule->searchActivitybyTime(a);
            output->clear();
            if(result){
                output->setText(result->toString(1));
                log=log+result->toString(1);
            }
            else{
                output->setText("查找不到相关课外活动");
                log=log+"查找不到相关课程";
            }
            this->writelog(log);
        });
        connect(searchbyTemporaryType,&QPushButton::clicked,this,[=](){     //根据临时事务的类型搜索
            int tag=TemporaryType->currentIndex();
            Temporary*result=this->schedule->searchTemporarybyTag(tag);
            QString log="用户"+this->CurrentUser->getID()+"按类型搜索了临时事务:"+TemporaryType->currentText()+"\n";
            output->clear();
            QString outputtext;
            if(result){
               // result->sortbyTime();
                outputtext=result->toString(1);
               output->setText(outputtext);
                log=log+outputtext;
            }
            else{
                outputtext="查找不到相关临时事务";
                output->setText(outputtext);
                log=log+outputtext;
            }
            this->writelog(log);
        });
        connect(searchbyTemporaryTime,&QPushButton::clicked,this,[=](){      //根据临时事务的时间搜索
            QDateTime a=TemporaryTime->dateTime();
            Temporary*result=this->schedule->searchTemporarybyTime(a);
            QString log="用户"+this->CurrentUser->getID()+"按时间搜索了临时事务:"+a.toString("yyyy-MM-dd HH")+"\n";
            output->clear();
            QString outputtext;
            if(result){
                result->sortbyType();
                outputtext=result->toString(1);
                output->setText(outputtext);
            }
            else{
                outputtext="查找不到相关临时事务";
                output->setText(outputtext);
            }
            log=log+outputtext;
            this->writelog(log);
        });
        connect(showmap,&QPushButton::clicked,this,[=](){               //显示地图
            Map*map=new Map(g,showpath,path);
            map->show();
        });
        connect(addAfterClassbtn,&QPushButton::clicked,this,[=](){   //增加课外活动
            int AfterClassTag= AfterClassTypeadd->currentIndex();   //课外活动类型
            QDateTime ACTime=AfterClassTimeadd->dateTime();        //课外活动开始时间
            QString AFTL=AfterClassLocationinput->text();           //课外活动的地点;
            int onlineornot=AfterClassonline->currentIndex();      //线下或者线上,0为线下,1为线上
            int circulationofAfterClass=AfterClassCirculation->currentIndex()+1;  //周期
            int ATP=1-gobset->currentIndex();  //ATP表示1个人或者0集体
            QString result;
            QString log="用户"+this->CurrentUser->getID()+"添加了课外活动\n";
            if(!this->judgeTemporaryTimevalid(ACTime)){
                result="课外活动的时间不合规";
            }
            else{
                if(!this->validlocation(AFTL)){
                    result="查找不到该地点";
                }
                else{
                    Activity*tempActivity=new Activity(ATP,AfterClassTag,AFTL,circulationofAfterClass,ACTime,onlineornot);
                    log=log+tempActivity->toString(2);
                    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
                    int days=InitialTime.daysTo(ACTime);
                    if(ATP==0){
                        int insertresult=this->addActivityAll(tempActivity);
                        if(insertresult==0){
                            result="没有冲突";
                        }
                        else if(insertresult==1){
                            result="有冲突,当天可行时间如下";
                            for(int i=0;i<this->minConflict.size();i++){
                                result=result+this->minConflict[i].toString("yyyy-MM-dd HH")+"\n";
                            }
                        }
                        else if(insertresult==2){
                            result="有冲突,没有可行时间,当天冲突最少的三个时间如下:";
                            for(int i=0;i<this->minConflict.size();i++){
                                result=result+this->minConflict[i].toString("yyyy-MM-dd HH")+"\n";
                            }
                        }
                    }
                    else{    //插入个人课外活动
                        int insertresult2=this->addActivityOne(tempActivity);
                        if(insertresult2==0){
                            result="添加成功";
                        }
                        else if(insertresult2==1){
                            result="没有可行时间，添加失败";
                        }
                        else if(insertresult2==2){
                            result="有冲突，当天可行时间如下";
                            for(int i=0;i<this->minConflict.size();i++){
                                result=result+this->minConflict[i].toString("yyyy-MM-dd HH")+"\n";
                            }
                        }
                    }
                }
            }
            log=log+result;
            output->clear();
            output->setText(result);
            this->writelog(log);
        });
        connect(addTemporarybtn,&QPushButton::clicked,this,[=](){     //增加临时事物
            QString result;
            QDateTime a=TemporaryTimeadd->dateTime();
            output->clear();
            QString log="用户"+this->CurrentUser->getID()+"增加了临时事务:\n";
            log=log+TemporaryLocationinput->text()+"--"+TemporaryTypeadd->currentText()+"--"+a.toString("yyyy-MM-dd HH")+"\n";
            if(!judgeTemporaryTimevalid(a)){
                result="临时事物的时间不合规\n";
            }
            else{
                if(!validlocation(TemporaryLocationinput->text())){
                    result="无法找到对应的临时事务地点\n";
                }
                else{
                    Temporary*t=new Temporary(a,TemporaryTypeadd->currentIndex(),TemporaryLocationinput->text());
                    if(this->CurrentUser->scheduletable->addTemporary(t)==1){
                        result="插入成功\n";
                    }
                    else{
                        result="插入失败\n";
                    }
                }
            }
            output->setText(result);
            log=log+result;
            this->writelog(log);
        });
    }

    bool validlocation(QString a){
        for(int i=0;i<(int)g->nodes.size();i++){
            if(g->nodes[i].getname()==a){
                return true;
                break;
            }
        }
        return false;
    }
    int addActivityAll(Activity*a){//添加集体活动
        HourUsage hourUsage[16];//有效课外活动时间只有16个小时
        QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
        int day=InitialTime.daysTo(a->getStartTime());
        int week=day/7;
        int weekday=day%7;
        int hour=a->getStartTime().toString("HH").toInt();
        minConflict.clear();
        if(a->getCirculation()==1){//单次
            for(int i=6;i<22;i++){
                hourUsage[i-6].hour=i;
                hourUsage[i-6].conflictTime=0;
                for(int j=0;j<this->UserList.size();j++){
                    if(this->UserList[j]->getIdentity()==1){//为学生
                        if(this->UserList[j]->scheduletable->checktimeOne(week,weekday,i)==1){//统计冲突
                            hourUsage[i-6].conflictTime++;
                        }
                    }
                }
            }
            if(hourUsage[hour-6].conflictTime==0){//该时间没有冲突
                for(int j=0;j<this->UserList.size();j++){
                    if(this->UserList[j]->getIdentity()==1){
                        int k=this->UserList[j]->scheduletable->addActivity(a);//为每一位学生添加活动
                    }
                }
                return 0;//添加成功
            }
            else{//该时间有冲突
                std::sort(hourUsage,hourUsage+16,[](HourUsage a,HourUsage b){return a.conflictTime<b.conflictTime;});//根据冲突次数升序排序
                for(int i=0;i<3;i++){
                    if(hourUsage[i].conflictTime==0){//如果有可行时间
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(hourUsage[i].hour*3600);
                        minConflict.push_back(newTime);
                    }
                }
                if(minConflict.empty()){//没有可行时间，推荐三个冲突最少的时间
                    for(int i=0;i<3;i++){
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(hourUsage[i].hour*3600);
                        minConflict.push_back(newTime);
                    }
                    return 2;
                }
                return 1;//已给出推荐时间
            }
        }
        else if(a->getCirculation()==2){//每天
            for(int i=6;i<22;i++){
                hourUsage[i-6].hour=i;
                hourUsage[i-6].conflictTime=0;
                for(int j=0;j<this->UserList.size();j++){
                    if(this->UserList[j]->getIdentity()==1){//为学生
                        if(this->UserList[j]->scheduletable->checktimeDay(week,weekday,i)==1){//统计冲突
                            hourUsage[i-6].conflictTime++;
                        }
                    }
                }
            }
            if(hourUsage[hour-6].conflictTime==0){//该时间没有冲突
                for(int j=0;j<this->UserList.size();j++){
                    if(this->UserList[j]->getIdentity()==1){
                        int k=this->UserList[j]->scheduletable->addActivity(a);//为每一位学生添加活动
                    }
                }
                return 0;//添加成功
            }
            else{//该时间有冲突
                std::sort(hourUsage,hourUsage+16,[](HourUsage a,HourUsage b){return a.conflictTime<b.conflictTime;});//根据冲突次数升序排序
                for(int i=0;i<3;i++){
                    if(hourUsage[i].conflictTime==0){//如果有可行时间
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(hourUsage[i].hour*3600);
                        minConflict.push_back(newTime);
                    }
                }
                if(minConflict.empty()){//没有可行时间，推荐三个冲突最少的时间
                    for(int i=0;i<3;i++){
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(hourUsage[i].hour*3600);
                        minConflict.push_back(newTime);
                    }
                    return 2;
                }
                return 1;//已给出推荐时间
            }
        }
        else if(a->getCirculation()==3){//每周
            for(int i=6;i<22;i++){
                hourUsage[i-6].hour=i;
                hourUsage[i-6].conflictTime=0;
                for(int j=0;j<this->UserList.size();j++){
                    if(this->UserList[j]->getIdentity()==1){//为学生
                        if(this->UserList[j]->scheduletable->checktimeWeek(week,weekday,i)==1){//统计冲突
                            hourUsage[i-6].conflictTime++;
                        }
                    }
                }
            }
            if(hourUsage[hour-6].conflictTime==0){//该时间没有冲突
                for(int j=0;j<this->UserList.size();j++){
                    if(this->UserList[j]->getIdentity()==1){
                        int k=this->UserList[j]->scheduletable->addActivity(a);//为每一位学生添加活动
                    }
                }
                return 0;//添加成功
            }
            else{//该时间有冲突
                std::sort(hourUsage,hourUsage+16,[](HourUsage a,HourUsage b){return a.conflictTime<b.conflictTime;});//根据冲突次数升序排序
                for(int i=0;i<3;i++){
                    if(hourUsage[i].conflictTime==0){//如果有可行时间
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(hourUsage[i].hour*3600);
                        minConflict.push_back(newTime);
                    }
                }
                if(minConflict.empty()){//没有可行时间，推荐三个冲突最少的时间
                    for(int i=0;i<3;i++){
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(hourUsage[i].hour*3600);
                        minConflict.push_back(newTime);
                    }
                    return 2;
                }
                return 1;//已给出推荐时间
            }
        }
    }
    int addActivityOne(Activity*a){   //这里实现
        minConflict.clear();
        QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
        int day=InitialTime.daysTo(a->getStartTime());
        int week=day/7;
        int weekday=day%7;
        int hour=a->getStartTime().toString("HH").toInt();
        if(a->getCirculation()==1){//单次
            if(CurrentUser->scheduletable->checktimeOne(week,weekday,hour)==0){//空闲
                int k=CurrentUser->scheduletable->addActivity(a);
                return 0;//添加成功
            }
            else{//不空闲
                int m=0;
                for(int i=6;i<22;i++){
                    if(CurrentUser->scheduletable->checktimeOne(week,weekday,i)==0){
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(i*3600);
                        minConflict.push_back(newTime);
                        m++;
                        if(m==3){
                            break;//有了三个可行时间
                        }
                    }
                }
                if(m==0){//没有可行时间
                    return 1;//添加失败
                }
                else{
                    return 2;//有可行时间
                }
            }
        }
        else if(a->getCirculation()==2){
            if(CurrentUser->scheduletable->checktimeDay(week,weekday,hour)==0){//这个每天都有空闲时间点
                int k=CurrentUser->scheduletable->addActivity(a);
                return 0;//添加成功
            }
            else{
                int m=0;
                for(int i=6;i<22;i++){
                    if(CurrentUser->scheduletable->checktimeDay(week,weekday,i)==0){
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(i*3600);
                        minConflict.push_back(newTime);
                        m++;
                        if(m==3){
                            break;//有了三个可行时间
                        }
                    }
                }
                if(m==0){//没有可行时间
                    return 1;//添加失败
                }
                else{
                    return 2;//有可行时间
                }
            }
        }
        else if(a->getCirculation()==3){//每周
            if(CurrentUser->scheduletable->checktimeWeek(week,weekday,hour)==0){//每周的这个时间都用空闲
                int k=CurrentUser->scheduletable->addActivity(a);
                return 0;//添加成功
            }
            else{
                int m=0;
                for(int i=6;i<22;i++){
                    if(CurrentUser->scheduletable->checktimeWeek(week,weekday,i)==0){
                        int days=week*7+weekday;
                        QDateTime newTime=InitialTime.addDays(days);
                        newTime=newTime.addSecs(i*3600);
                        minConflict.push_back(newTime);
                        m++;
                        if(m==3){
                            break;//有了三个可行时间
                        }
                    }
                }
                if(m==0){//没有可行时间
                    return 1;//添加失败
                }
                else{
                    return 2;//有可行时间
                }
            }
        }
    }
    vector<QDateTime> minConflict;
    User*CurrentUser;
    void writelog(QString a){
        QFile file("log.txt");
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
            qDebug()<<"打不开";
        }
        a=a+"timeStamp:"+this->currentTime.toString("yyyy-MM-dd HH")+"\n";
        QTextStream in(&file);
        in<<a;
        file.close();
    }
    vector<User*> UserList;
    QDateTime currentTime;   //当前时间
    QTextBrowser*showtime;
    bool judgeTemporaryTimevalid(QDateTime a){
        QDateTime InitialTime=QDateTime::fromString("2023-02-27 00","yyyy-MM-dd HH");
        QString astr=a.toString("yyyy-MM-dd HH");
        int b=astr.compare(InitialTime.toString("yyyy-MM-dd HH"));
        if(b<0){
            return false;
        }
        if(a.daysTo(InitialTime)>=140){
            return false;
        }
        if(a.toString("HH").toInt()<6||a.toString("HH").toInt()>=22){
            return false;
        }
        return true;
    }
    int hourto(QDateTime a,QDateTime b){
        int day=a.daysTo(b);
        int hour=b.toString("HH").toInt()-a.toString("HH").toInt();
        return (day*24+hour);
    }
    void save(){
        QFile UserInfo("UserInfo.txt");
        if(!UserInfo.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"打不开";
        }
        QTextStream a(&UserInfo);
        for(int i=0;i<this->UserList.size();i++){
            a<<UserList[i]->toString();
        }
        UserInfo.close();
    }
    bool JudgetTimevalid(){
       QDateTime InitialTime=QDateTime::fromString("2023-02-27 00","yyyy-MM-dd HH");
       int day=InitialTime.daysTo(this->currentTime.addSecs(3600));
       if(day<0||day>=140){
            return false;
       }
       else{
            return true;
       }
    }
    Graph*g;
    ScheduleTable*schedule;
    QString UserID;
    QString currentLocation;
private:
    bool showpath;
    vector<int> path;
};
class adminwidget:public QMainWindow{
    Q_OBJECT
public:
    adminwidget(User*current,vector<User*> UserList,QWidget* parent = nullptr):QMainWindow(parent),UserList(UserList),CurrentUser(current){   //管理员窗口
        QTimer*timer=new QTimer(this);
        QLabel*timelabel=new QLabel("当前时间",this);
        this->ReadCourses("allCourse.txt");
        timelabel->setGeometry(20,70,70,30);
        timer->stop();
        timer->setInterval(10000);
        timer->start();
        this->searched=false;
        /*if(this->CurrentUser.getIdentity()==0){
            ScheduleTable*scheduleTable=new ScheduleTable();
        }
        else{
            classTable classtable=new classtable();
        }*/
        this->currentTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
        this->showtime=new QTextBrowser(this);
        showtime->setText(currentTime.toString("yyyy-MM-dd HH"));
        showtime->setGeometry(20,100,120,30);
        showtime->show();
        this->ReadBuildings("buildings.txt");
        QDateTimeEdit* timeEdit=new QDateTimeEdit(this->currentTime,this);
        timeEdit->setDisplayFormat("yyyy-MM-dd HH");
        timeEdit->setGeometry(150,100,150,30);
        QPushButton*startButton = new QPushButton("开始",this);
        QPushButton*pauseButton = new QPushButton("暂停",this);
        QPushButton*skipButton = new QPushButton("跳转",this);
        QPushButton*quickenButton = new QPushButton("加速",this);
        QPushButton*recoverButton = new QPushButton("恢复",this);
        startButton->setGeometry(20,150,40,20);
        pauseButton->setGeometry(70,150,40,20);
        quickenButton->setGeometry(130,150,40,20);
        skipButton->setGeometry(180,150,40,20);
        recoverButton->setGeometry(230,150,40,20);
        //增加课程
        QLabel*addCourseLabel=new QLabel("增加课程",this);
        QLabel*CourseName=new QLabel("课程名称",this);
        QLabel*CourseStartTime=new QLabel("上课时间",this);
        QLabel*CourseType=new QLabel("课程类型",this);
        QLabel*CourseLocation=new QLabel("上课地点(如果为线上则输入链接)",this);
        QLabel*ExamTime=new QLabel("考试时间",this);
        QLabel*ExamLocation=new QLabel("考试地点",this);
        QLineEdit*CourseNameInput=new QLineEdit(this);
        QDateTimeEdit*CourseStartTimeInput=new QDateTimeEdit(this->currentTime,this);
        CourseStartTimeInput->setDisplayFormat("yyyy-MM-dd HH");
        QLineEdit*ExamLocationInput=new QLineEdit(this);
        QDateTimeEdit*ExamTimeInput=new QDateTimeEdit(this->currentTime,this);
        ExamTimeInput->setDisplayFormat("yyyy-MM-dd HH");
        QStringList courseType={"线下","线上"};
        QComboBox*CourseTypeInput=new QComboBox(this);
        CourseTypeInput->addItems(courseType);
        QStringList Circulation={"单次","每周"};
        QComboBox*circulationInput=new QComboBox(this);
        circulationInput->addItems(Circulation);
        QLineEdit*CourseLocationInput=new QLineEdit(this);
        QPushButton*ConfirmAdd=new QPushButton("加入课程",this);
        QStringList allLastTime={"0","1","2","3"};
        QComboBox*classLastTime=new  QComboBox(this);
        QComboBox*examLastTime=new QComboBox(this);
        circulationInput->setGeometry(920,240,70,30);
        classLastTime->addItems(allLastTime);
        classLastTime->setGeometry(1000,240,100,30);
        examLastTime->addItems(allLastTime);
        examLastTime->setGeometry(1110,240,100,30);
        addCourseLabel->setGeometry(20,180,100,30);
        CourseName->setGeometry(20,210,100,20);
        CourseStartTime->setGeometry(180,210,100,20);
        CourseType->setGeometry(310,210,100,20);
        CourseLocation->setGeometry(400,210,200,20);
        ExamTime->setGeometry(610,210,100,20);
        ExamLocation->setGeometry(740,210,100,20);
        CourseNameInput->setGeometry(20,240,150,30);
        CourseStartTimeInput->setGeometry(180,240,120,30);
        CourseTypeInput->setGeometry(310,240,60,30);
        CourseLocationInput->setGeometry(400,240,200,30);
        ExamTimeInput->setGeometry(610,240,120,30);
        ExamLocationInput->setGeometry(740,240,200,30);
        QLabel*ExamLastTime=new QLabel("考试持续时间",this);
        QLabel*CourseLastTime=new QLabel("课程持续时间",this);
        ExamLastTime->setGeometry(1110,210,100,30);
        CourseLastTime->setGeometry(1000,210,100,30);
        ConfirmAdd->setGeometry(20,270,80,30);
        QScrollArea*showallCourse=new QScrollArea(this);
        showallCourse->setGeometry(20,300,1400,1400);
        QLabel*CourseNameTitle=new QLabel("课程名称",showallCourse);
        CourseNameTitle->setGeometry(10,5,100,30);
        QLabel*CourseStartTimeTitle=new QLabel("上课时间",showallCourse);
        CourseStartTimeTitle->setGeometry(120,5,120,30);
        QLabel*CourseLastTimeTitle=new QLabel("课程持续时间",showallCourse);
        CourseLastTimeTitle->setGeometry(250,5,100,30);
        QLabel*CourseTypeTitle=new QLabel("课程类型",showallCourse);
        CourseTypeTitle->setGeometry(360,5,100,30);
        QLabel*CourseLocationTitle=new QLabel("上课地点或网址",showallCourse);
        CourseLocationTitle->setGeometry(470,5,100,30);
        QLabel*ExamStartTimeTitle=new QLabel("考试开始时间",showallCourse);
        ExamStartTimeTitle->setGeometry(650,5,120,30);
        QLabel*ExamLastTimeTitle=new QLabel("考试持续时间",showallCourse);
        ExamLastTimeTitle->setGeometry(780,5,120,30);
        QLabel*ExamLocationTitle=new QLabel("考试地点",showallCourse);
        ExamLocationTitle->setGeometry(900,5,150,30);
        this->CourseList=new QListWidget(showallCourse);
        CourseList->setGeometry(5,30,1000,1000);
        for(int i=0;i<this->allCourse.size();i++){
            CourseList->addItem(this->allCourse[i].toString(1));
        }
        //查找课程
        QPushButton*searchByName=new QPushButton("搜索课程",this);
        QLineEdit*CourseNameInput3=new QLineEdit(this);
        CourseNameInput3->setGeometry(120,270,170,30);
        searchByName->setGeometry(300,270,100,30);
        QPushButton*showallCoursebtn=new QPushButton("显示所有课程",this);
        QPushButton*save=new QPushButton("保存",this);
        save->setGeometry(250,0,100,30);
        connect(save,&QPushButton::clicked,this,[=](){
            this->save();
        });
        showallCoursebtn->setGeometry(440,270,100,30);
        connect(CourseList,SIGNAL(listItemClicked(int)),this,SLOT(showCourseInfo(int)));
        connect(timer,&QTimer::timeout,this,&adminwidget::updateTime); //时钟推进;
        connect(CourseList,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(editCourse(QListWidgetItem*)));
        connect(startButton,&QPushButton::clicked,this,[=](){   //时钟开始
            timer->start();
        });
        connect(pauseButton,&QPushButton::clicked,this,[=](){    //时钟暂停
            timer->stop();
        });
        connect(skipButton,&QPushButton::clicked,this,[=](){     //时钟跳转
             this->currentTime=timeEdit->dateTime();
             this->showtime->setText(currentTime.toString("yyyy-MM-dd hh"));
             timer->stop();
        });
        connect(quickenButton,&QPushButton::clicked,this,[=](){  //加速
            timer->setInterval(1000);
        });
        connect(recoverButton,&QPushButton::clicked,this,[=](){  //恢复正常速度
            timer->setInterval(10000);
        });
        connect(showallCoursebtn,&QPushButton::clicked,this,[=](){    //显示所有课程
            this->CourseList->clear();
            this->searched=false;
            for(int i=0;i<this->allCourse.size();i++){
                CourseList->addItem(this->allCourse[i].toString(1));
            }
        });
        connect(ConfirmAdd,&QPushButton::clicked,this,[=](){    //在所有课程中加入课程
            QString tempCourseName=CourseNameInput->text();
            QString tempCourseLocation=CourseLocationInput->text();
            QDateTime tempCourseTime=CourseStartTimeInput->dateTime();
            int templastTime=circulationInput->currentText().toInt();
            QDateTime tempExamTime=ExamTimeInput->dateTime();
            QString tempExamLocation=ExamLocationInput->text();
            int tempExamLastTime=examLastTime->currentText().toInt();
            int temptype=CourseTypeInput->currentIndex();
            int tempcirculation=circulationInput->currentIndex()+1;
            bool insertSuccess=true;
            QString reason;
            if(temptype==0&&!this->judgeLocationValid(tempCourseLocation)){
                reason="上课地点不存在\n";
                insertSuccess=false;
            }
            if(!this->judgeLocationValid(tempExamLocation)&&temptype==0){
                reason=reason+"考试地点不存在\n";
                insertSuccess=false;
            }
            if(!this->judgeValidCourseTime(tempCourseTime,templastTime)){
                reason=reason+"上课时间不合规\n";
                insertSuccess=false;
            }
            if(!this->judgeValidCourseTime(tempExamTime,tempExamLastTime)){
                reason=reason+"考试时间不合规\n";
                insertSuccess=false;
            }
            for(int i=0;i<this->allCourse.size();i++){
                if(this->allCourse[i].getname()==tempCourseName){
                    insertSuccess=false;
                    reason=reason+"课程已存在";
                }
            }
            QString log;
            log="管理员"+this->CurrentUser->getID()+"在所有课程中加入课程:\n";
            Course newCourse(tempCourseName,tempCourseLocation,tempCourseTime,templastTime,tempExamTime,tempExamLocation,tempExamLastTime,temptype,tempcirculation);
            log=log+newCourse.toString(1);
            for(int i=0;i<this->allCourse.size();i++){
                if(this->allCourse[i].getname()==newCourse.getname()&&this->allCourse[i].getStartTime()==newCourse.getStartTime()){
                    insertSuccess=false;
                    break;
                }
            }
            if(insertSuccess){
                log=log+"插入成功\n";
                this->CourseList->clear();
                this->allCourse.push_back(newCourse);
                for(int i=0;i<this->allCourse.size();i++){
                    CourseList->addItem(this->allCourse[i].toString(1));
                }
            }
            else{
                log=log+"插入失败\n"+reason;
                QMessageBox::warning(this, "插入课程失败",reason);
            }
            this->writelog(log);
        });
        connect(searchByName,&QPushButton::clicked,this,[=](){   //按名称搜索
            QString Coursename=CourseNameInput3->text();
            this->searched=true;
            this->index.clear();
            for(int i=0;i<this->allCourse.size();i++){
                if(Coursename==this->allCourse[i].getname()){
                    this->index.push_back(i);
                }
            }
            this->CourseList->clear();
            for(int i=0;i<index.size();i++){
                this->CourseList->addItem(this->allCourse[index[i]].toString(1));
            }
        });
    }
    vector<User*> UserList;
    User*CurrentUser;
    QDateTime currentTime;
    QTextBrowser*showtime;
    vector<Course> allCourse;
    QListWidget*CourseList;
    vector<QString> allbuildings;
    void ReadBuildings(QString filename){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!";
        }
        QTextStream out(&file);
        QString oneline=out.readLine();
        while(!out.atEnd()){
            int j=0;
            int temp1;
            QString start,temp;
            for(int i=0;i<(int)oneline.length();i++){
                j=0;
                while(oneline[i]!=L'['&&i<(int)oneline.length()){
                    j++;
                    i++;
                }
                start=oneline.left(j);
                this->allbuildings.push_back(start);
                break;
            }
            oneline=out.readLine();
        }
        file.close();
    }
    bool judgeLocationValid(QString a){
        for(int i=0;i<this->allbuildings.size();i++){
            if(a==this->allbuildings[i]){
                return true;
            }
        }
        return false;
    }
    void ReadCourses(QString filename){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!";
        }
        QTextStream out(&file);
        QString oneline=out.readLine();
        Course temp;
        int state=0;
        while(!out.atEnd()){
            if(oneline=="{"&&state==0){
                state=1;
            }
            else if(oneline=="}"){
                state=0;
            }
            else if(state==1){
                QString field;
                QString temp2;
                int i;
                for(i=0;oneline[i]!=L':';i++);
                field=oneline.left(i);
                temp2=oneline.mid(i+1,oneline.length()-i-1);
                if(field=="课程名"){
                    temp.setName(temp2);
                }
                else if(field=="上课时间"){
                    QDateTime tempTime=QDateTime::fromString(temp2,"yyyy-MM-dd HH");
                    temp.setStartTime(tempTime);
                }
                else if(field=="上课地点"){
                    temp.setLocation(temp2);
                }
                else if(field=="持续时间"){
                    temp.setLastTime(temp2.toInt());
                }
                else if(field=="考试地点"){
                    temp.setExamLocation(temp2);
                }
                else if(field=="考试时间"){
                    temp.setExamTime(QDateTime::fromString(temp2,"yyyy-MM-dd HH"));
                }
                else if(field=="考试持续时间"){
                    temp.setExamLastTime(temp2.toInt());
                }
                else if(field=="周期"){
                    if(temp2=="单次"){
                        temp.setCirculation(1);
                    }
                    else if(temp2=="每周"){
                        temp.setCirculation(2);
                    }
                }
                else if(field=="类型"){
                    if(temp2=="线下"){
                        temp.setType(0);
                    }
                    else{
                        temp.setType(1);
                    }
                    this->allCourse.push_back(temp);
                }
            }
            oneline=out.readLine();
        }
        file.close();
    }
    void writelog(QString a){
        QFile file("log.txt");
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
            qDebug()<<"打不开";
        }
        a=a+"timeStamp:"+this->currentTime.toString("yyyy-MM-dd HH")+"\n";
        QTextStream in(&file);
        in<<a;
        file.close();
    }
    bool judgeValidCourseTime(QDateTime a,int lastTime){
        QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
        int days=InitialTime.daysTo(a);
        int hour=a.toString("HH").toInt();
        if(a.toString("yyyy-MM-dd HH").compare(InitialTime.toString("yyyy-MM-dd HH"))<0){
            return false;
        }
        else{
            if(days>=140){
                return false;
            }
            if(hour<8||hour+lastTime>20){
                return false;
            }
        }
        return true;
    }
    void save(){
        QFile UserInfo("UserInfo.txt");
        if(!UserInfo.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"打不开";
        }
        QTextStream a(&UserInfo);
        for(int i=0;i<this->UserList.size();i++){
            a<<UserList[i]->toString();
        }
        UserInfo.close();
        QFile CourseFile("allCourse.txt");
        if(!CourseFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"打不开";
        }
        QTextStream b(&CourseFile);
        for(int i=0;i<this->allCourse.size();i++){
            b<<"{\n"+this->allCourse[i].toString(0)+"}\n";
        }
        CourseFile.close();
    }
    bool JudgetTimevalid(){
        QDateTime InitialTime=QDateTime::fromString("2023-02-27 00","yyyy-MM-dd HH");
        int day=InitialTime.daysTo(this->currentTime);
        if(day<0||day>=140){
            return false;
        }
        else{
            return true;
        }
    }
    vector<int> index;
    bool searched;
private slots:
    void updateTime(){
         currentTime=currentTime.addSecs(3600);
        if(this->JudgetTimevalid()){
            this->showtime->setText(currentTime.toString("yyyy-MM-dd hh"));
        }
    }

    void editCourse(QListWidgetItem*b){
        int c=CourseList->indexFromItem(b).row();
        if(searched){
            c=this->index[c];
        }
        CourseWidget*coursewindow=new CourseWidget(&(this->allCourse),c,this->UserList,this->currentTime,this->CurrentUser->getID(),this->allbuildings);
        coursewindow->show();
    }
};

class signwidget:public QWidget{
    Q_OBJECT
public:
    signwidget(vector<User*>*userlist,QWidget *parent = nullptr) : QWidget(parent),userList(userlist){
        // UI布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *titleLabel = new QLabel("学生日程管理系统注册");
        QLabel *userLabel = new QLabel("学号：");
        QLabel *passwordLabel = new QLabel("密码：");
        QLabel *identityLabel= new QLabel("身份:");
        QLabel *passwordConfirm=new QLabel("确认密码");
        QLineEdit *userEdit = new QLineEdit();
        QLineEdit *passwordEdit = new QLineEdit();
        QLineEdit *passwordCon = new QLineEdit();
        QStringList allidentity={"学生","管理员"};
        QComboBox *identity=new QComboBox();
        identity->addItems(allidentity);
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordCon->setEchoMode(QLineEdit::Password);
        QPushButton *sign=new QPushButton("注册");
        layout->addWidget(titleLabel);
        layout->addWidget(userLabel);
        layout->addWidget(userEdit);
        layout->addWidget(passwordLabel);
        layout->addWidget(passwordEdit);
        layout->addWidget(identityLabel);
        layout->addWidget(identity);
        layout->addWidget(passwordConfirm);
        layout->addWidget(passwordCon);
        layout->addWidget(sign);
        connect(sign, &QPushButton::clicked, this, [=]() {
            // 注册
            QString ID = userEdit->text();
            QString password = passwordEdit->text();
            QString ide=identity->currentText();
            QString con=passwordCon->text();
            int i;
            if(ide=="学生"){
                i=1;
            }
            else{
                i=0;
            }
            User*currentUser=new User(ID,password,i);
            // 验证用户信息
            bool success = true;
            QString reason;
            if(con!=password){
                reason="密码和确认密码不一致";
                success=false;
            }
            if(success){
                for(int i=0;i<(int)this->userList->size();i++){
                    if (this->userList->at(i)->getID()==ID) {
                        success = false;
                        reason="ID已存在";
                    }
                }
            }
            if (success) {
                this->userList->push_back(currentUser);
                 QMessageBox::warning(this, "注册成功","注册成功");
            } else {
                QMessageBox::warning(this, "注册失败", reason);
                delete currentUser;
            }

            // 清空输入框
            userEdit->clear();
            passwordEdit->clear();
        });
    }
    vector<User*>*userList;
};

// 系统类
class System : public QWidget {
    Q_OBJECT

public:
    System(QWidget *parent = nullptr) : QWidget(parent) {
        // 初始化用户列表

        // UI布局
        this->ReadCourses("allCourse.txt");
        this->ReadUserInfo("UserInfo.txt");
        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *titleLabel = new QLabel("学生日程管理系统");
        QLabel *userLabel = new QLabel("学号：");
        QLabel *passwordLabel = new QLabel("密码：");
        QLabel *identityLabel= new QLabel("身份:");
        QLineEdit *userEdit = new QLineEdit();
        QLineEdit *passwordEdit = new QLineEdit();
        QStringList allidentity={"学生","管理员"};
        QComboBox *identity=new QComboBox();
        identity->addItems(allidentity);
        passwordEdit->setEchoMode(QLineEdit::Password);
        QPushButton *loginButton = new QPushButton("登录");
        QPushButton *sign=new QPushButton("注册");
        layout->addWidget(titleLabel);
        layout->addWidget(userLabel);
        layout->addWidget(userEdit);
        layout->addWidget(passwordLabel);
        layout->addWidget(passwordEdit);
        layout->addWidget(identityLabel);
        layout->addWidget(identity);
        layout->addWidget(loginButton);
        layout->addWidget(sign);
        // 连接信号和槽
        connect(loginButton, &QPushButton::clicked, this, [=]() {
            // 获取输入的用户名和密码
            QString ID = userEdit->text();
            QString password = passwordEdit->text();
            QString ide=identity->currentText();
            int i;
            if(ide=="学生"){
                i=1;
            }
            else{
                i=0;
            }
            User currentUser(ID,password,i);
            User*loginsuccessUser;
            // 验证用户信息
            bool success = false;
            for (auto user : userList) {
                if (user->getID()==ID && user->getPassword() == password&&user->getIdentity()==i) {
                    success = true;
                    loginsuccessUser=user;
                    break;
                }
            }

            if (success) {
                openAlarmClockWidget(loginsuccessUser);
            } else {
                QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
            }

            // 清空输入框
            userEdit->clear();
            passwordEdit->clear();
        });
        connect(sign, &QPushButton::clicked, this, [=](){
            opensignWidget();
        });
    }
    void ReadCourses(QString filename){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!";
        }
        QTextStream out(&file);
        QString oneline=out.readLine();
        Course temp;
        int state=0;
        while(!out.atEnd()){
            if(oneline=="{"&&state==0){
                state=1;
            }
            else if(oneline=="}"){
                state=0;
            }
            else if(state==1){
                QString field;
                QString temp2;
                int i;
                for(i=0;oneline[i]!=L':';i++);
                field=oneline.left(i);
                temp2=oneline.mid(i+1,oneline.length()-i-1);
                if(field=="课程名"){
                    temp.setName(temp2);
                }
                else if(field=="上课时间"){
                    QDateTime tempTime=QDateTime::fromString(temp2,"yyyy-MM-dd HH");
                    temp.setStartTime(tempTime);
                }
                else if(field=="上课地点"){
                    temp.setLocation(temp2);
                }
                else if(field=="持续时间"){
                    temp.setLastTime(temp2.toInt());
                }
                else if(field=="考试地点"){
                    temp.setExamLocation(temp2);
                }
                else if(field=="考试时间"){
                    temp.setExamTime(QDateTime::fromString(temp2,"yyyy-MM-dd HH"));
                }
                else if(field=="考试持续时间"){
                    temp.setExamLastTime(temp2.toInt());
                }
                else if(field=="周期"){
                    if(temp2=="单次"){
                        temp.setCirculation(1);
                    }
                    else if(temp2=="每周"){
                        temp.setCirculation(2);
                    }
                }
                else if(field=="类型"){
                    if(temp2=="线下"){
                        temp.setType(0);
                    }
                    else{
                        temp.setType(1);
                    }
                    this->allCourse.push_back(temp);
                }
            }
            oneline=out.readLine();
        }
        file.close();
    }
    void ReadUserInfo(QString filename){
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!";
        }
        QTextStream out(&file);
        QString oneline=out.readLine();
        while(!out.atEnd()){
            if(oneline=="["){
                oneline=out.readLine();
                QString tempUsername=oneline;
                oneline=out.readLine();
                QString tempPassword=oneline;
                oneline=out.readLine();
                int tempidentity=oneline.toInt();
                oneline=out.readLine();
                User*tempUser=new User(tempUsername,tempPassword,tempidentity);

                if(tempidentity==1){
                    if(oneline=="课程:"){
                        oneline=out.readLine();
                        oneline=out.readLine();
                        while(oneline!="}"){
                            QString TempcourseName=oneline;
                            oneline=out.readLine();
                            QString TempStartTime=oneline;
                            for(int i=0;i<this->allCourse.size();i++){
                                 if(TempcourseName==this->allCourse[i].getname()&&TempStartTime==this->allCourse[i].getStartTime().toString("yyyy-MM-dd HH")){
                                        Course*tempcourse=new Course(this->allCourse[i].getname(),this->allCourse[i].getLocation(),this->allCourse[i].getStartTime()
                                                                       ,this->allCourse[i].getLastTime(),this->allCourse[i].getExamTime(),this->allCourse[i].getExamLocation(),this->allCourse[i].getExamLastTime()
                                                                      ,this->allCourse[i].getType(),this->allCourse[i].getCirculation());
                                    tempUser->scheduletable->addCourse(tempcourse);
                                    break;
                                }
                            }
                            oneline=out.readLine();
                        }
                        oneline=out.readLine();
                    }
                    if(oneline=="课外活动:"){
                        oneline=out.readLine();
                        oneline=out.readLine();
                        while(oneline!="}"){
                            int afterClassType=oneline.toInt();
                            oneline=out.readLine();
                            int AfterClassTag=oneline.toInt();
                            oneline=out.readLine();
                            QDateTime afterClassTime=QDateTime::fromString(oneline,"yyyy-MM-dd HH");
                            oneline=out.readLine();
                            QString AfterClassLocation=oneline;
                            oneline=out.readLine();
                            int circulation=oneline.toInt();
                            oneline=out.readLine();
                            int onelineornot=oneline.toInt();
                            oneline=out.readLine();
                            Activity*tempActivity=new Activity(afterClassType,AfterClassTag,AfterClassLocation,circulation,afterClassTime,onelineornot);
                            tempUser->scheduletable->addActivity(tempActivity);
                        }
                        oneline=out.readLine();
                    }
                    if(oneline=="临时事务:"){
                        oneline=out.readLine();
                        oneline=out.readLine();
                        while(oneline!="}"){
                            int TemporaryType=oneline.toInt();
                            oneline=out.readLine();
                            QDateTime TemporaryTime=QDateTime::fromString(oneline,"yyyy-MM-dd HH");
                            oneline=out.readLine();
                            QString TemporaryLocation=oneline;
                            Temporary*tempTemp=new Temporary(TemporaryTime,TemporaryType,TemporaryLocation);
                            tempUser->scheduletable->addTemporary(tempTemp);
                            oneline=out.readLine();
                        }
                        oneline=out.readLine();
                    }
                }
                if(oneline=="]"){
                    this->userList.push_back(tempUser);
                }
            }
            oneline=out.readLine();
        }
    }
    vector<Course> allCourse;
private slots:
    void openAlarmClockWidget(User*currentUser) {
        QMessageBox::information(this, "登录成功", "欢迎使用本系统！");
        if(currentUser->getIdentity()==1){
            mainWindow* mainwindow = new mainWindow(currentUser,this->userList);
            mainwindow->show();
        }
        else{
            adminwidget*adminwindow=new adminwidget(currentUser,this->userList);
            adminwindow->show();
        }
        close();
    }
    void opensignWidget(){
        signwidget*account=new signwidget(&(this->userList));
        account->show();
    }

protected:
    vector<User*> userList;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    System system;
    system.show();
    return app.exec();
}
#include "main.moc"
