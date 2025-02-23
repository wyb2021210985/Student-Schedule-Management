#include"ScheduleTable.h"
taken::taken(){
    this->type=0;
}
ScheduleTable::ScheduleTable(){
    for(int i=0;i<20;i++){
        for(int j=0;j<7;j++){
            for(int k=0;k<24;k++){
                this->t[i][j][k]=new taken();
            }
        }
    }
    for(int i=0;i<9;i++){
        this->hashTemporary.push_back(new Temporary(i));
    }
    for(int i=0;i<7;i++){
        this->hashActivity.push_back(new Activity(i));
    }
    this->courseAVL=new CourseAVL();
}

int ScheduleTable::getDay(QString a){
    if(a=="Mon"||a=="周一"){
        return 1;
    }
    else if(a=="Tue"||a=="周二"){
        return 2;
    }
    else if(a=="Wed"||a=="周三"){
        return 3;
    }
    else if(a=="Thu"||a=="周四"){
        return 4;
    }
    else if(a=="Fri"||a=="周五"){
        return 5;
    }
    else if(a=="Sat"||a=="周六"){
        return 6;
    }
    else if(a=="Sun"||a=="周日"){
        return 7;
    }
    else{
        return 0;
    }
}
//成功插入返回1,否则返回0
int ScheduleTable::addTemporary(Temporary*tem){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int day=InitialTime.daysTo(tem->getStartTime());
    int hour=tem->getStartTime().toString("HH").toInt();
    if(this->t[day/7][day%7][hour]->type==3||this->t[day/7][day%7][hour]->type==0){
        if(this->t[day/7][day%7][hour]->type==0){
            Temporary*start=new Temporary(tem->getStartTime());
            start->addTemporaryNode(tem);
            this->t[day/7][day%7][hour]->Event.temporary=start;
            this->t[day/7][day%7][hour]->type=3;
        }
        else{
            if(this->Temporaryconflict(tem)!=0){
                return this->Temporaryconflict(tem);
            }
            this->t[day/7][day%7][hour]->Event.temporary->addTemporaryNode(tem);
        }
        Temporary*added=new Temporary(tem);
        this->hashTemporary[tem->getEventType()]->addTemporaryNode(added);
        return 1;   //成功插入
    }
    else{
        return 2;  //对应的时间有其他事务
    }
}
Temporary*ScheduleTable::searchTemporarybyTag(int tag){
    hashTemporary[tag]->sortbyTime();
    return this->hashTemporary[tag];
}
Temporary* ScheduleTable::searchTemporarybyTime(QDateTime time){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    QString hourStr=time.toString("HH");
    int hour=hourStr.toInt();
    int day=InitialTime.daysTo(time);
    if(day>=140){
        return NULL;
    }
    if(this->t[day/7][day%7][hour]->type!=3){
        return NULL;
    }
    else{
        return this->t[day/7][day%7][hour]->Event.temporary;
    }
}
void ScheduleTable::destroyTemporaryList(Temporary*a){
    while(a){
        Temporary*temp=a;
        a=a->next;
        delete temp;
    }
}
int ScheduleTable::deleteTemporaryByTime(QDateTime time){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int hour=time.toString("HH").toInt();
    int day=InitialTime.daysTo(time);
    switch(this->t[day/7][day%7][hour]->type){
        case 0:return 0;break;
        case 1:return 1;break;
        case 2:return 2;break;
        case 3:{
            this->destroyTemporaryList(this->t[day/7][day%7][hour]->Event.temporary);
            this->t[day/7][day%7][hour]->type=0;
            for(int i=0;i<9;i++){
                Temporary*temp=this->hashTemporary.at(i)->next;
                while(temp){
                    if(temp->getStartTime()==time){
                        Temporary*temp2=temp;
                        if(temp->next)temp->next->prior=temp->prior;
                        temp->prior->next=temp->next;
                        temp=temp->next;
                        delete temp2;
                    }
                    else{
                        temp=temp->next;
                    }
                }
            }
            break;
        }
    }
    return 3;
}
bool ScheduleTable::CourseNotice(QDateTime a){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int hour=a.toString("HH").toInt();
    int day=InitialTime.daysTo(a);
    if(hour>=20){
        return false;
    }
    if(this->t[day/7][day%7][hour]->type==1){
        return true;
    }
    else{
        return false;
    }
}
bool ScheduleTable::TemporaryNotice(QDateTime a){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int hour=a.toString("HH").toInt();
    int day=InitialTime.daysTo(a);
    if(this->t[day/7][day%7][hour]->type==3){
        return true;
    }
    else{
        return false;
    }
}
vector<QString> ScheduleTable::TemporaryPath(Temporary*a){
    vector<QString> result;
    while(a->next){
        result.push_back(a->next->getLocation());
        a=a->next;
    }
    return result;
}
int ScheduleTable::Temporaryconflict(Temporary*a){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int hour=a->getStartTime().toString("HH").toInt();
    int day=InitialTime.daysTo(a->getStartTime());
    if(this->t[day/7][day%7][hour]->type==0){
        return 0;
    }
    if(this->t[day/7][day%7][hour]->type==3){
        Temporary*temp=this->t[day/7][day%7][hour]->Event.temporary->next;
        while(temp){
            if(temp->getLocation()==a->getLocation()){
                return 3;
            }
            temp=temp->next;
        }
    }
    return 0;
}
bool ScheduleTable::CouldaddCourse(Course*b){    //是否能增加课程
    QDateTime start=b->getStartTime();
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int day=InitialTime.daysTo(start);
    int hour=start.toString("HH").toInt();
    if(b->getCirculation()==1){    //单次
        for(int i=0;i<b->getLastTime();i++){
            if(this->t[day/7][day%7][hour+i]->type==1||this->t[day/7][day%7][hour+i]->type==4){
                return false;    //插入失败
            }
        }
    }
    else if(b->getCirculation()==2){   //每周的课
        for(int j=day/7;j<18;j++){
            for(int i=0;i<b->getLastTime();i++){
                if(this->t[j][day%7][hour+i]->type==1||this->t[j][day%7][hour+i]->type==4){
                    return false;    //插入失败
                }
            }
        }
    }
    QDateTime ExamTime=b->getExamTime();
    int day2=InitialTime.daysTo(ExamTime);
    int hour2=ExamTime.toString("HH").toInt();
    for(int k=0;k<b->getExamLastTime();k++){
        if(this->t[day2/7][day2%7][hour2+k]->type==1||this->t[day2/7][day2%7][hour2+k]->type==4){
            return false;    //插入失败
        }
    }
    return true;
}
int ScheduleTable::addCourse(Course* b){

    //之前为判断能否插入,接下来开始插入
    QDateTime start=b->getStartTime();
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int day=InitialTime.daysTo(start);
    int hour=start.toString("HH").toInt();
    QDateTime ExamTime=b->getExamTime();
    int day2=InitialTime.daysTo(ExamTime);
    int hour2=ExamTime.toString("HH").toInt();
    if(b->getCirculation()==1){
        for(int i=0;i<b->getLastTime();i++){
            if(this->t[day/7][day%7][hour+i]->type==2){
                this->deleteActivitybyTime(InitialTime.addDays(day).addSecs((hour+i)*3600));
            }
            else if(this->t[day/7][day%7][hour+i]->type==3){
                this->deleteTemporaryByTime(InitialTime.addDays(day).addSecs((hour+i)*3600));
            }
            this->t[day/7][day%7][hour+i]->type=1;
            this->t[day/7][day%7][hour+i]->Event.course=b;
        }
    }
    else if(b->getCirculation()==2){
        for(int j=day/7;j<18;j++){

            for(int i=0;i<b->getLastTime();i++){
                if(this->t[j][day%7][hour+i]->type==2){
                    this->deleteActivitybyTime(InitialTime.addDays(day%7+j*7).addSecs((hour+i)*3600));
                }
                else if(this->t[j][day%7][hour+i]->type==3){
                    this->deleteTemporaryByTime(InitialTime.addDays(day%7+j*7).addSecs((hour+i)*3600));
                }
                this->t[j][day%7][hour+i]->type=1;
                this->t[j][day%7][hour+i]->Event.course=b;
            }
        }
    }
    for(int i=0;i<b->getExamLastTime();i++){
        this->t[day2/7][day2%7][hour2+i]->type=4;
        this->t[day2/7][day2%7][hour2+i]->Event.course=b;
    }
    Course D=*b;
    return this->courseAVL->insertAVL(this->courseAVL->root,D);
}
int ScheduleTable::deleteCourse(Course b){
    QDateTime time1=b.getStartTime();
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int day=InitialTime.daysTo(time1);
    int hour=time1.toString("HH").toInt();
    if(b.getCirculation()==1){
        for(int i=0;i<b.getLastTime();i++){
            if(this->t[day/7][day%7][hour+i]->type!=1){
                return 0;
            }
            else if(this->t[day/7][day%7][hour+i]->Event.course->getname()!=b.getname()){
                return 0;
            }
        }
    }
    else{
        for(int j=day/7;j<18;j++){    //j表示课程开始时间的周数
            for(int i=0;i<b.getLastTime();i++){
                if(this->t[j][day%7][hour+i]->type!=1){
                    return 0;
                }
                else if(this->t[j][day%7][hour+i]->Event.course->getname()!=b.getname()){
                    return 0;
                }
            }
        }
    }
    QDateTime ExamTime=b.getExamTime();
    int day2=InitialTime.daysTo(ExamTime);
    int hour2=ExamTime.toString("HH").toInt();
    for(int k=0;k<b.getExamLastTime();k++){
        if(this->t[day2/7][day2%7][hour2+k]->type!=4){
            return 0;
        }
        else if(this->t[day2/7][day2%7][hour2+k]->Event.course->getname()!=b.getname()){
            return 0;
        }
    }

    if(b.getCirculation()==1){
        delete this->t[day/7][day%7][hour]->Event.course;
        for(int i=0;i<b.getLastTime();i++){
            this->t[day/7][day%7][hour+i]->type=0;
        }
    }
    else{
        delete this->t[day/7][day%7][hour]->Event.course;
        for(int j=day/7;j<18;j++){    //j表示课程开始时间的周数
            for(int i=0;i<b.getLastTime();i++){
                this->t[j][day%7][hour+i]->type=0;
            }
        }
    }
    for(int k=0;k<b.getExamLastTime();k++){
        this->t[day2/7][day2%7][hour2+k]->type=0;
    }
    return this->courseAVL->deleteAVLNode(this->courseAVL->root,b);
}

int ScheduleTable::Activityconflict(Activity*a){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int day=InitialTime.daysTo(a->getStartTime());
    int week=day/7;
    int weekday=day%7;
    int hour=a->getStartTime().toString("HH").toInt();
    if(this->t[week][weekday][hour]->type==0){
        return 0;
    }
    if(this->t[week][weekday][hour]->type==2){
        Activity*temp=this->t[week][weekday][hour]->Event.activity->next;
        while(temp){
            if(temp->getlocation()==a->getlocation()){
                return 2;
            }
            temp=temp->next;
        }
    }
    return 0;
}
Activity*ScheduleTable::searchActivitybyTag(int tag){
    hashActivity[tag]->sortbyTime();
    return this->hashActivity[tag]->next;
}
Activity*ScheduleTable::searchActivitybyTime(QDateTime time){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    QString hourStr=time.toString("HH");
    int hour=hourStr.toInt();
    int day=InitialTime.daysTo(time);
    int week=day/7;
    int weekday=day%7;
    if(day>=140){
        return NULL;
    }
    if(this->t[week][weekday][hour]->type!=2){
        return NULL;
    }
    else{
        return this->t[week][weekday][hour]->Event.activity;
    }
}
void ScheduleTable::destroyActivityList(Activity*a){
    while(a){
        Activity*temp=a;
        a=a->next;
        delete temp;
    }
}
int ScheduleTable::deleteActivitybyTime(QDateTime time){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    QString hourStr=time.toString("HH");
    int hour=hourStr.toInt();
    int day=InitialTime.daysTo(time);
    int week=day/7;
    int weekday=day%7;
    int tag;
    switch(this->t[week][weekday][hour]->type){
        case 0:return 0;break;
        case 1:return 1;break;
        case 2:{
            tag=this->t[week][weekday][hour]->Event.activity->getTag();
            Activity*temp=this->hashActivity[tag]->next;
            QDateTime starttime=this->t[week][weekday][hour]->Event.activity->getStartTime();
            int day2=InitialTime.daysTo(starttime);
            int hour2=starttime.toString("HH").toInt();
            while(temp){
                if(temp->getStartTime()==starttime){
                    Activity*temp2=temp;
                    if(temp->next)temp->next->prior=temp->prior;
                    temp->prior->next=temp->next;
                    temp=temp->next;
                    delete temp2;
                }
                else{
                    temp=temp->next;
                }
            }
            if(this->t[day2/7][day2%7][hour2]->Event.activity->getCirculation()==1){
                delete this->t[day2/7][day2%7][hour2]->Event.activity;
                this->t[day2/7][day2%7][hour2]->type=0;
            }
            else if(this->t[day2/7][day2%7][hour2]->Event.activity->getCirculation()==2){
                delete this->t[day2/7][day2%7][hour2]->Event.activity;
                for(int j=day2;j<140;j++){
                    this->t[j/7][j%7][hour2]->type=0;
                }
            }
            else if(this->t[day2/7][day2%7][hour2]->Event.activity->getCirculation()==3){
                delete this->t[day2/7][day2%7][hour2]->Event.activity;
                for(int k=day2/7;k<20;k++){
                    this->t[k][day2%7][hour2]->type=0;
                }
            }
            return 2;
            break;
        }
        case 3:return 3;break;
    }
    return 2;
}
bool ScheduleTable::ActivityNotice(QDateTime time){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    QString hourStr=time.toString("HH");
    int hour=hourStr.toInt();
    int day=InitialTime.daysTo(time);
    int week=day/7;
    int weekday=day%7;
    if(this->t[week][weekday][hour]->type==2){
        return true;
    }
    else{
        return false;
    }
}
QString ScheduleTable::toString(){
    QString result;
    this->courseAVL->PersonCourseList.clear();
    this->courseAVL->Inordertraverse(this->courseAVL->root);
    result="课程:\n{\n";
    for(int i=0;i<this->courseAVL->PersonCourseList.size();i++){
        result=result+this->courseAVL->PersonCourseList[i].getname()+"\n"+this->courseAVL->PersonCourseList[i].getStartTime().toString("yyyy-MM-dd HH")+"\n";
    }
    result=result+"}\n";
    result=result+"课外活动:\n{\n";
    for(int i=0;i<7;i++){
        Activity*tempActivity=this->hashActivity[i]->next;
        result=result+tempActivity->toString(0);
    }
    result=result+"}\n";
    result=result+"临时事务:\n{\n";
    for(int i=0;i<9;i++){
        Temporary*temp=this->hashTemporary[i];
        result=result+temp->toString(0);
    }
    result=result+"}\n";

    return result;
}
bool ScheduleTable::CouldChangeCourse(Course*origin,Course*newCourse){
    AVLCourseNode*result=this->courseAVL->search(*origin,this->courseAVL->root);
    if(result==NULL){
        return true;                     //该用户没有相关课程,可以修改
    }
    else{
        QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
        QDateTime originstartTime=origin->getStartTime();
        QDateTime originExamTime=origin->getExamTime();
        int days=InitialTime.daysTo(originstartTime);
        int hour=originstartTime.toString("HH").toInt();
        int days2=InitialTime.daysTo(originExamTime);
        int hour2=originExamTime.toString("HH").toInt();
        if(result->course.getCirculation()==1){
            for(int i=0;i<origin->getLastTime();i++){
                this->t[days/7][days%7][hour+i]->type=0;
            }
        }
        else{
            for(int j=days/7;j<18;j++){
                for(int i=0;i<origin->getLastTime();i++){
                    this->t[j][days%7][hour+i]->type=0;
                }
            }
        }
        for(int i=0;i<origin->getExamLastTime();i++){
            this->t[days2/7][days2%7][hour2+i]->type=0;
        }
        if(this->CouldaddCourse(newCourse)){
            if(result->course.getCirculation()==1){
                for(int i=0;i<origin->getLastTime();i++){
                    this->t[days/7][days%7][hour+i]->type=3;
                }
            }
            else if(result->course.getCirculation()==2){
                for(int j=days/7;j<18;j++){
                    for(int i=0;i<origin->getLastTime();i++){
                        this->t[j][days%7][hour+i]->type=3;
                    }
                }
            }
            for(int i=0;i<origin->getExamLastTime();i++){
                this->t[days2/7][days2%7][hour2+i]->type=4;
            }
            return true;
        }
        else{
            return false;
        }
    }
}
int ScheduleTable::change(Course*newCourse,Course*origin){
    if(this->deleteCourse(*origin)){
        this->addCourse(newCourse);
        return 1;
    }
    else{
        return 0;
    }
}

int ScheduleTable::addActivity(Activity*a){
    QDateTime InitialTime=QDateTime::fromString("2023-02-27","yyyy-MM-dd");
    int day=InitialTime.daysTo(a->getStartTime());
    int week=day/7;
    int weekday=day%7;
    int hour=a->getStartTime().toString("HH").toInt();
    Activity*another=new Activity(a);
    this->hashActivity[a->getTag()]->addActivityNode(another);
    if(a->getCirculation()==1){//单次
        if(this->t[week][weekday][hour]->type==3){
            int days=week*7+weekday;
            QDateTime newTime=InitialTime.addDays(days);
            newTime=newTime.addSecs(hour*3600);
            int k=deleteTemporaryByTime(newTime);
        }
        this->t[week][weekday][hour]->type=2;
        this->t[week][weekday][hour]->Event.activity=a;
    }
    else if(a->getCirculation()==2){//每天一次
        for(int i=day;i<140;i++){
            if(this->t[i/7][i%7][hour]->type==0||this->t[i/7][i%7][hour]->type==3){
                if(this->t[i/7][i%7][hour]->type==3){
                    QDateTime newTime=InitialTime.addDays(i);
                    newTime=newTime.addSecs(hour*3600);
                    int k=deleteTemporaryByTime(newTime);
                }
                this->t[i/7][i%7][hour]->type=2;
                this->t[i/7][i%7][hour]->Event.activity=a;
            }
        }
    }else if(a->getCirculation()==3){//每周一次
        while(week<18){
            if(this->t[week][weekday][hour]->type==0||this->t[week][weekday][hour]->type==3){
                if(this->t[week][weekday][hour]->type==3){
                    int days=week*7+weekday;
                    QDateTime newTime=InitialTime.addDays(days);
                    newTime=newTime.addSecs(hour*3600);
                    int k=deleteTemporaryByTime(newTime);
                }
                this->t[week][weekday][hour]->type=2;
                this->t[week][weekday][hour]->Event.activity=a;

            }
            week++;
        }
    }
    return 0;//添加成功
}
bool ScheduleTable::checktimeOne(int week,int weekday,int hour){
    if(this->t[week][weekday][hour]->type==0||this->t[week][weekday][hour]->type==3){
        return 0;//空闲
    }
    return 1;//冲突
}
bool ScheduleTable::checktimeDay(int week,int weekday,int hour){
    int day=week*7+weekday;
    for(int i=day;i<140;i++){
        if(this->t[day/7][day%7][hour]->type==1||this->t[day/7][day%7][hour]->type==2||this->t[day/7][day%7][hour]->type==4){
            return 1;//冲突
        }
    }
    return 0;//空闲
}
bool ScheduleTable::checktimeWeek(int week,int weekday,int hour){
    while(week<20){
        if(this->t[week][weekday][hour]->type==1||this->t[week][weekday][hour]->type==2||this->t[week][weekday][hour]->type==4){
            return 1;//冲突
        }
        week++;
    }
    return 0;//空闲
}
