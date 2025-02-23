#include"ClassTable.h"
ClassTable::ClassTable(ScheduleTable*schedule,QWidget*parent):QWidget(parent),scheduleTable(schedule){
    QTableWidget*tableWidget=new QTableWidget(13,8,this);
    QComboBox*chooseweek=new QComboBox(this);
    for(int j=0;j<20;j++){
        QString temp="第"+QString::number(j+1)+"周";
        chooseweek->addItem(temp);
    }
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    QPushButton*showCourse=new QPushButton("显示课程",this);
    showCourse->setGeometry(0,0,100,30);
    chooseweek->setGeometry(150,0,100,30);
    tableWidget->setGeometry(5,50,1000,800);
    tableWidget->setItem(0,1,new QTableWidgetItem("星期一"));
    tableWidget->setItem(0,2,new QTableWidgetItem("星期二"));
    tableWidget->setItem(0,3,new QTableWidgetItem("星期三"));
    tableWidget->setItem(0,4,new QTableWidgetItem("星期四"));
    tableWidget->setItem(0,5,new QTableWidgetItem("星期五"));
    tableWidget->setItem(0,6,new QTableWidgetItem("星期六"));
    tableWidget->setItem(0,7,new QTableWidgetItem("星期日"));
    QDateTime temp=InitialTime.addSecs(8*3600);
    for(int i=8;i<20;i++){
        tableWidget->setItem(i-7,0,new QTableWidgetItem(temp.toString("HH")+":00--"+temp.addSecs(3600).toString("HH")+"00"));
        temp=temp.addSecs(3600);
    }
    connect(showCourse,&QPushButton::clicked,this,[=](){
        int week=chooseweek->currentIndex();
        tableWidget->clear();
        tableWidget->setItem(0,1,new QTableWidgetItem("星期一"));
        tableWidget->setItem(0,2,new QTableWidgetItem("星期二"));
        tableWidget->setItem(0,3,new QTableWidgetItem("星期三"));
        tableWidget->setItem(0,4,new QTableWidgetItem("星期四"));
        tableWidget->setItem(0,5,new QTableWidgetItem("星期五"));
        tableWidget->setItem(0,6,new QTableWidgetItem("星期六"));
        tableWidget->setItem(0,7,new QTableWidgetItem("星期日"));
        QDateTime temp2=InitialTime.addSecs(8*3600);
        for(int i=8;i<20;i++){
            tableWidget->setItem(i-7,0,new QTableWidgetItem(temp2.toString("HH")+":00--"+temp2.addSecs(3600).toString("HH")+"00"));
            temp2=temp2.addSecs(3600);
        }
        for(int i=0;i<7;i++){
            for(int j=8;j<20;j++){
                if(this->scheduleTable->t[week][i][j]->type==1){
                    tableWidget->setItem(j-7,i+1,new QTableWidgetItem(this->scheduleTable->t[week][i][j]->Event.course->getname()+this->scheduleTable->t[week][i][j]->Event.course->getLocation()));
                }
                else if(this->scheduleTable->t[week][i][j]->type==4){
                    tableWidget->setItem(j-7,i+1,new QTableWidgetItem(this->scheduleTable->t[week][i][j]->Event.course->getname()+"考试\n"+this->scheduleTable->t[week][i][j]->Event.course->getExamLocation()));
                }
            }
        }
    });
};

