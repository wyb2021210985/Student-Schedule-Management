#include"CourseWidget.h"
CourseWidget::CourseWidget(vector<Course>*a,int index,vector<User*> UserList,QDateTime currentTime,QString ID,vector<QString> allbuildings,QWidget* parent):QWidget(parent),currentTime(currentTime),UserList(UserList),index(index),adminID(ID),allbuildingsname(allbuildings),CourseList(a){
    resize(600,600);
    QPushButton*deletebtn=new QPushButton("删除课程",this);
    QDateTimeEdit*CourseStartTimeInput=new QDateTimeEdit(this->CourseList->at(index).getStartTime(),this);
    QDateTimeEdit*ExamStartTimeInput=new QDateTimeEdit(this->CourseList->at(index).getExamTime(),this);
    CourseStartTimeInput->setDisplayFormat("yyyy-MM-dd HH");
    ExamStartTimeInput->setDisplayFormat("yyyy-MM-dd HH");
    QLabel*CourseLastTime=new QLabel("课程持续时间",this);
    QLabel*CourseName=new QLabel("课程名称",this);
    QLabel*CourseStartTime=new QLabel("上课时间",this);
    QLabel*CourseType=new QLabel("课程类型",this);
    QLabel*CourseLocation=new QLabel("上课地点(如果为线上则输入链接)",this);
    QLabel*ExamTime=new QLabel("考试时间",this);
    QLabel*ExamLocation=new QLabel("考试地点",this);
    QLabel*ExamLastTime=new QLabel("考试持续时间",this);
    QLabel*Circulation=new QLabel("周期",this);
    QLineEdit*CourseNameInput=new QLineEdit(a->at(index).getname(),this);
    CourseNameInput->setReadOnly(true);
    QLineEdit*ExamLocationInput=new QLineEdit(a->at(index).getLocation(),this);
    QLineEdit*CourseLocationInput=new QLineEdit(a->at(index).getLocation(),this);
    QComboBox*circulationInput=new QComboBox(this);
    QComboBox*CourseTypeInput=new QComboBox(this);
    QComboBox*CourseLastTimeInput=new QComboBox(this);
    QComboBox*ExamLastTimeInput=new QComboBox(this);
    QStringList allLastTime={"0","1","2","3"};
    QStringList courseType={"线下","线上"};
    QStringList cir={"单次","每周"};
    circulationInput->addItems(cir);
    CourseTypeInput->addItems(courseType);
    CourseLastTimeInput->addItems(allLastTime);
    ExamLastTimeInput->addItems(allLastTime);
    circulationInput->setCurrentIndex(a->at(index).getCirculation()-1);
    CourseTypeInput->setCurrentIndex(a->at(index).getType());
    CourseLastTimeInput->setCurrentIndex(a->at(index).getLastTime());
    ExamLastTimeInput->setCurrentIndex(a->at(index).getExamLastTime());
    CourseName->setGeometry(5,5,100,30);
    CourseNameInput->setGeometry(200,5,150,30);
    CourseLocation->setGeometry(5,40,190,30);
    CourseLocationInput->setGeometry(200,40,150,30);
    CourseStartTime->setGeometry(5,70,150,30);
    CourseStartTimeInput->setGeometry(200,70,150,30);
    CourseLastTime->setGeometry(5,100,150,30);
    CourseLastTimeInput->setGeometry(200,100,70,30);
    CourseType->setGeometry(5,130,100,30);
    CourseTypeInput->setGeometry(200,130,100,30);
    Circulation->setGeometry(5,160,100,30);
    circulationInput->setGeometry(200,160,70,30);
    ExamTime->setGeometry(5,190,120,30);
    ExamStartTimeInput->setGeometry(200,190,150,30);
    ExamLocation->setGeometry(5,220,120,30);
    ExamLocationInput->setGeometry(200,220,150,30);
    ExamLastTime->setGeometry(5,250,150,30);
    ExamLastTimeInput->setGeometry(200,250,70,30);
    deletebtn->setGeometry(320,380,100,30);
    QPushButton*addCourse=new QPushButton("给学生增加课程",this);
    QString allUser="全体";
    QComboBox*chooseUser=new QComboBox(this);
    chooseUser->addItem(allUser);
    for(int i=0;i<this->UserList.size();i++){
        if(this->UserList[i]->getIdentity()==1)chooseUser->addItem(this->UserList[i]->getID());
    }
    chooseUser->setGeometry(5,380,150,30);
    addCourse->setGeometry(160,380,150,30);
    QPushButton*confirmChange=new QPushButton("确认修改",this);
    confirmChange->setGeometry(5,300,100,30);
    connect(deletebtn,&QPushButton::clicked,this,[=](){
        QString range=chooseUser->currentText();
        if(range=="全体"){
            this->deleteAllStudentsCourse(this->CourseList->at(index));
        }
        else{
            for(int i=0;i<this->UserList.size();i++){
                if(this->UserList[i]->getID()==range){
                    this->deleteOneStudentsCourse(this->CourseList->at(index),this->UserList[i]);
                }
            }
        }
    });
    connect(addCourse,&QPushButton::clicked,this,[=](){ //增加课程
        QString range=chooseUser->currentText();
        QString tempCourseName=CourseNameInput->text();
        QString tempCourseLocation=CourseLocationInput->text();
        QDateTime tempCourseTime=CourseStartTimeInput->dateTime();
        int templastTime=circulationInput->currentText().toInt();
        QDateTime tempExamTime= ExamStartTimeInput->dateTime();
        QString tempExamLocation=ExamLocationInput->text();
        int tempExamLastTime=ExamLastTimeInput->currentText().toInt();
        int temptype=CourseTypeInput->currentIndex();
        int tempcirculation=circulationInput->currentIndex()+1;
        QString log="管理员"+this->adminID;
        QString result;
        Course*newCourse=new Course(tempCourseName,tempCourseLocation,tempCourseTime,templastTime,tempExamTime,tempExamLocation,tempExamLastTime,temptype,tempcirculation);
        if(range=="全体"){
            if(this->CouldaddCourseToAll(newCourse)){
                for(int i=0;i<this->UserList.size();i++){
                    if(this->UserList[i]->getIdentity()==1){
                        this->UserList[i]->scheduletable->addCourse(newCourse);
                    }
                }
                result="添加成功\n";
            }
            else{
                result="添加失败\n";
            }
            log=log+"给全体成员添加课程:\n"+newCourse->toString(0);
        }
        else{
            result="添加失败";
            for(int i=0;i<this->UserList.size();i++){
                if(this->UserList[i]->getID()==range&&this->UserList[i]->scheduletable->CouldaddCourse(newCourse)){
                    this->UserList[i]->scheduletable->addCourse(newCourse);
                    log=log+"给用户"+range+"添加了课程:\n"+newCourse->toString(0);
                     result="添加成功\n";
                }
            }
        }
        QMessageBox::warning(this, "添加课程",result);
        log=log+result;
        this->writelog(log);
    });
    connect(confirmChange,&QPushButton::clicked,this,[=](){ //修改课程
        QString tempCourseName=CourseNameInput->text();
        QString tempCourseLocation=CourseLocationInput->text();
        QDateTime tempCourseTime=CourseStartTimeInput->dateTime();
        int templastTime=CourseLastTimeInput->currentText().toInt();
        QDateTime tempExamTime= ExamStartTimeInput->dateTime();
        QString tempExamLocation=ExamLocationInput->text();
        int tempExamLastTime=ExamLastTimeInput->currentText().toInt();
        int temptype=CourseTypeInput->currentIndex();
        int tempcirculation=circulationInput->currentIndex()+1;
        QString reason,log;
        log="管理员"+this->adminID+"修改了课程"+this->CourseList->at(index).getname()+"\n";
        bool changesuccess=true;
        if(this->judgeValidCourseTime(tempCourseTime,templastTime)==false){
            reason="上课时间不合规\n";
            changesuccess=false;
        }
        if(!this->judgeValidLocation(tempCourseLocation)&&temptype==0){
            reason=reason+"上课地点不合规\n";
            changesuccess=false;
        }
        if(this->judgeValidCourseTime(tempExamTime,tempExamLastTime)==0){
            reason=reason+"考试时间不合规\n";
            changesuccess=false;
        }
        if(!this->judgeValidLocation(tempExamLocation)&&temptype==0){
            reason=reason+"考试地点不合规\n";
            changesuccess=false;
        }
        if(changesuccess){
            Course*newCourse=new Course(tempCourseName,tempCourseLocation,tempCourseTime,templastTime,tempExamTime,tempExamLocation,tempExamLastTime,temptype,tempcirculation);
            if(this->CouldChangeAllCourse(&(this->CourseList->at(this->index)),newCourse)){
                for(int k=0;k<this->UserList.size();k++){
                    if(this->UserList[k]->getIdentity()==1){
                        this->UserList[k]->scheduletable->change(newCourse,&(this->CourseList->at(this->index)));
                    }
                }
                QMessageBox::warning(this, "修改课程成功","修改课程成功");
                log=log+"修改课程成功\n修改后的课程信息:";
                log=log+newCourse->toString(0);
                this->CourseList->at(index)=*newCourse;
            }
            else{
                delete newCourse;
                QMessageBox::warning(this, "修改课程失败","修改课程失败");
            }
        }
        else{
            QMessageBox::warning(this, "修改课程失败",reason);
            log=log+"修改课程失败\n";
        }
        this->writelog(log);
    });
}
void CourseWidget::deleteAllStudentsCourse(Course a){
    QString log,result;
    log="管理员"+this->adminID+"删除了全体同学的课程\n"+a.toString(0);
    vector<QString> deletesuccessUserList;
    for(int i=0;i<this->UserList.size();i++){
        if(this->UserList[i]->getIdentity()==1){
            int q=this->UserList[i]->scheduletable->deleteCourse(a);
            qDebug()<<q;
            if(q){
                deletesuccessUserList.push_back(this->UserList[i]->getID());
            }
        }
    }
    if(deletesuccessUserList.size()>0){
        result="删除了以下学生的该门课程:\n";
        for(int i=0;i<deletesuccessUserList.size();i++){
            result=result+deletesuccessUserList[i]+"\n";
        }
    }
    else{
        result="没有学生修读该门课程:\n";
    }
    log=log+result;
    QMessageBox::warning(this, "删除课程结果",result);
    this->writelog(log);
}
void CourseWidget::deleteOneStudentsCourse(Course a,User*u){
    QString log,result;
    log="管理员"+this->adminID+"删除用户"+u->getID()+"的课程\n"+a.toString(0);
    int i=u->scheduletable->deleteCourse(a);
    if(i==0){
        result="删除失败,用户没有该课程";
        QMessageBox::warning(this, "删除课程失败",result);
    }
    else{
        result="删除成功";
        QMessageBox::warning(this, "删除课程成功",result);
    }
    log=log+result;
    this->writelog(log);
}
bool CourseWidget::CouldaddCourseToAll(Course*a){
    bool result=true;
    for(int i=0;i<this->UserList.size();i++){
        if(this->UserList[i]->getIdentity()==1){
            result=result&&this->UserList[i]->scheduletable->CouldaddCourse(a);
        }
    }
    return result;
}
bool CourseWidget::CouldChangeAllCourse(Course*a,Course*b){
    bool result=true;
    for(int i=0;i<this->UserList.size();i++){
        if(this->UserList[i]->getIdentity()==1){
            result=result&&this->UserList[i]->scheduletable->CouldChangeCourse(a,b);
        }
    }
    return result;
}
bool CourseWidget::judgeValidCourseTime(QDateTime a,int lastTime){
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
void CourseWidget::writelog(QString a){
     QFile file("log.txt");
     if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        qDebug()<<"打不开";
     }
     QTextStream in(&file);
     a=a+"timeStamp:"+this->currentTime.toString("yyyy-MM-dd HH")+"\n";
     in<<a;
     file.close();
}
bool CourseWidget::judgeValidLocation(QString a){
    for(int i=0;i<this->allbuildingsname.size();i++){
        if(a==this->allbuildingsname[i]){
            return true;
        }
    }
    return false;
}
