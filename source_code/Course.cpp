#include"Course.h"
Course::Course(QString name,QString location,QDateTime startTime,int lasttime,QDateTime examTime,QString examlocaion,int examlastTime,int type,int circulation){
    this->lasttime=lasttime;
    this->name=name;
    this->location=location;
    this->startTime=startTime;
    this->circulation=circulation;
    this->ExamTime=examTime;
    this->ExamLocation=examlocaion;
    this->ExamLastTime=examlastTime;
    this->type=type;
}
Course::Course(){

}
void Course::setExamTime(QDateTime a){
    this->ExamTime=a;
}
QString Course::getname(){
    return this->name;
}
QDateTime Course::getStartTime(){
    return this->startTime;
}
int Course::getLastTime(){
    return this->lasttime;
}
int Course::getCirculation(){
    return this->circulation;
}
QString Course::getLocation(){
    return this->location;
}
QDateTime Course::getExamTime(){
    return this->ExamTime;
}
int Course::getExamLastTime(){
    return this->ExamLastTime;
}
QString Course::toString(int i){

    QString result;
    QString circulate;
    QString offline;
    if(this->circulation==1){
        circulate="单次";
    }
    else if(this->circulation==2){
        circulate="每周";
    }
    if(this->type==0){
        offline="线下";
    }
    else{
        offline="线上";
    }
    if(i==0){
        result="课程名:"+this->name+"\n"+"上课时间:"+this->startTime.toString("yyyy-MM-dd HH")+"\n"+"上课地点:"+this->location+"\n"
                 +"持续时间:"+QString::number(this->lasttime)+"\n"+"考试地点:"+this->ExamLocation+"\n"+"考试时间:"
                 +this->ExamTime.toString("yyyy-MM-dd HH")+"\n"+"考试持续时间:"+QString::number(this->ExamLastTime)+"\n"
                +"周期:"+circulate+"\n"+"类型:"+offline+"\n";
    }
    else{
        result=this->name+"  "+this->startTime.toString("yyyy-MM-dd HH")+"  "+QString::number(this->lasttime)+"  "+
                 offline+"  "+this->location+"  "+this->ExamTime.toString("yyyy-MM-dd HH")+"  "+QString::number(this->ExamLastTime)
                 +"  "+this->ExamLocation;
    }
    return result;
}
int Course::compare(Course a){
    int result=this->name.compare(a.getname());
    if(result!=0){
        return result;
    }
    else{
        QString timea=this->startTime.toString("yyyy-MM-dd HH");
        QString timeb=a.getStartTime().toString("yyyy-MM-dd HH");
        return timea.compare(timeb);
    }
}
void Course::setExamLocation(QString a){
    this->ExamLocation=a;
}
void Course::setExamLastTime(int a){
    this->ExamLastTime=a;
}
void Course::setLastTime(int a){
    this->lasttime=a;
}
void Course::setType(int a){
    this->type=a;
}
int Course::getType(){
    return this->type;
}
void Course::setName(QString a){
    this->name=a;
}
void Course::setStartTime(QDateTime a){
    this->startTime=a;
}
void Course::setCirculation(int a){
    this->circulation=a;
}
void Course::setLocation(QString a){
    this->location=a;
}
QString Course::getExamLocation(){
    return this->ExamLocation;
}
