#include"AfterClass.h"
Activity::Activity(){
    this->sign=1;
    this->next=NULL;
    this->prior=NULL;
}
Activity::Activity(int type,int tag, QString location, int circulation, QDateTime StartTime,int flag){
    this->type=type;
    this->tag=tag;
    this->location=location;
    this->circulation=circulation;
    this->StartTime=StartTime;
    this->flag=flag;
    this->next=NULL;
    this->prior=NULL;
    this->sign=0;
}
int Activity::getType(){
    return this->type;
}
int Activity::getTag(){
    return this->tag;
}
QString Activity::getlocation(){
    return this->location;
}
int Activity::getCirculation(){
    return this->circulation;
}
QDateTime Activity::getStartTime(){
    return this->StartTime;
}
int Activity::getFlag(){
    return this->flag;
}
void Activity::setType(int type){
    this->type=type;
}
void Activity::setTag(int tag){
    this->tag=tag;
}
void Activity::setLocation(QString location){
    this->location=location;
}
void Activity::setCirculation(int circulation){
    this->circulation=circulation;
}
void Activity::setStarttime(QDateTime StartTime){
    this->StartTime=StartTime;
}
void Activity::setFlag(int flag){
    this->flag=flag;
}
QString Activity::toString(int i){
    QStringList alltag={"自习","锻炼","外出","班会","小组作业","创新创业","聚餐"};
    QStringList onlineoroffline={"线下","线上"};
    QStringList allCirculation={"单次","每天","每周"};
    Activity*temp=this;
    QString result;
    if(this->sign==1)temp=this->next;
    if(i==0){   //写入文件的字符串
        while(temp){
            result=result+QString::number(temp->getType())+"\n"+QString::number(temp->getTag())+"\n"
                     +temp->getStartTime().toString("yyyy-MM-dd HH")+"\n"+temp->getlocation()+"\n"+QString::number(temp->getCirculation())+"\n"+QString::number(temp->getFlag())+"\n";
            temp=temp->next;
        }
    }
    else if(i==1){//在系统中输出的字符
        while(temp){
            result=result+"地点:"+temp->location+"\n"+"类型:"+alltag[temp->tag]+"\n"+"线上或线下:"
                     +onlineoroffline[temp->type]+"\n"+"开始时间:"
                     +temp->StartTime.toString("yyyy-MM-dd HH")+"\n"+"周期:"+allCirculation[temp->circulation-1]+"\n";
            temp=temp->next;
        }
    }
    else if(i==2){
        result=result+"地点:"+temp->location+"\n"+"类型:"+alltag[temp->tag]+"\n"+"线上或线下:"
                   +onlineoroffline[temp->type]+"\n"+"开始时间:"
                 +temp->StartTime.toString("yyyy-MM-dd HH")+"\n"+"周期:"+allCirculation[temp->circulation-1]+"\n" ; //只把当前节点转为字符串
    }
    return result;
}
Activity::Activity(Activity*a){
    this->setType(a->getType());
    this->setTag(a->getTag());
    this->setLocation(a->getlocation());
    this->setCirculation(a->getCirculation());
    this->setStarttime(a->getStartTime());
    this->setFlag(a->getFlag());
    this->prior=NULL;
    this->next=NULL;
}
Activity::Activity(QDateTime a){
    this->sign=1;
    this->next=NULL;
    this->prior=NULL;
    this->StartTime=a;
}
Activity::Activity(int tag){
    this->tag=tag;
    this->sign=1;
    this->next=NULL;
    this->prior=NULL;
}
void Activity::addActivityNode(Activity*a){
    Activity*temp=this;
    while(temp->next){
        temp=temp->next;
    }
    a->next=NULL;
    a->prior=temp;
    temp->next=a;
}
int Activity::comparetime(QDateTime a,QDateTime b){
    int ayear=a.toString("yyyy").toInt();
    int byear=b.toString("yyyy").toInt();
    int amonth=a.toString("MM").toInt();
    int bmonth=b.toString("MM").toInt();
    int aday=a.toString("dd").toInt();
    int bday=b.toString("dd").toInt();
    int ahour=a.toString("HH").toInt();
    int bhour=b.toString("HH").toInt();
    if(ayear>byear){
        return 1;
    }
    else if(ayear<byear){
        return -1;
    }
    else if(amonth>bmonth){
        return 1;
    }
    else if(bmonth>amonth){
        return -1;
    }
    else if(aday>bday){
        return 1;
    }
    else if(aday<bday){
        return -1;
    }
    else if(ahour>bhour){
        return 1;
    }
    else if(ahour<bhour){
        return -1;
    }
    return 0;
}
void Activity::sortbyTime(){
    Activity*high=this;
    while(high->next){
        high=high->next;
    }
    if(high!=this&&high!=this->next)this->quicksortTime(this->next,high);
}
void Activity::quicksortTime(Activity*low,Activity*high){
    if(low!=high){
        Activity*pivot=quickPassTime(low,high);
        if(low!=pivot){
            quicksortTime(low,pivot->prior);
        }
        if(high!=pivot){
            quicksortTime(pivot->next,high);
        }
    }
}
Activity* Activity::quickPassTime(Activity*low,Activity*high){
    QDateTime pivot=low->getStartTime();
    while(low!=high){
        while(low!=high&&this->comparetime(high->getStartTime(),pivot)>=0){
            high=high->prior;
        }
        this->swap(low,high);
        while(low!=high&&low->comparetime(low->getStartTime(),pivot)){
            low=low->next;
        }
        this->swap(low,high);
    }
    return low;
}
void Activity::swap(Activity*a,Activity*b){
    QDateTime temptime=a->getStartTime();
    int temptype=a->getType();
    int temptag=a->getTag();
    QString temploc=a->location;
    int tempcir=a->getCirculation();
    a->setLocation(b->getlocation());
    a->setType(b->getType());
    a->setTag(b->getTag());
    a->setCirculation(b->getCirculation());
    a->setStarttime(b->getStartTime());
    b->setLocation(temploc);
    b->setType(temptype);
    b->setTag(temptag);
    b->setCirculation(tempcir);
    b->setStarttime(temptime);
}
void Activity::deleteActivitybyTag(int tag){
    Activity*temp=this->next;
    while(temp){
        if(temp->getTag()==tag){
            temp->prior->next=temp->next;
            if(temp->next){
                temp->next->prior=temp->prior;
            }
            break;
            Activity*temp2=temp;
            temp=temp->prior;
            delete temp2;
        }
        temp=temp->next;
    }
}

