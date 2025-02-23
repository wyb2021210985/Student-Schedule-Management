#include"Temporary.h"
Temporary::Temporary(QDateTime start,int e,QString Location){
    this->EventType=e;
    this->startTime=start;
    this->next=NULL;
    this->prior=NULL;
    this->sign=0;
    this->location=Location;
}
Temporary::Temporary(){
    this->sign=1;
    this->next=NULL;
    this->prior=NULL;
}
Temporary::Temporary(int e){
    this->EventType=e;
    this->sign=1;
    this->next=NULL;
    this->prior=NULL;
}
void Temporary::addTemporaryNode(Temporary*t){
    Temporary*temp=this;
    this->prior=NULL;
    while(temp->next){
        temp=temp->next;
    }
    t->next=NULL;
    t->prior=temp;
    temp->next=t;
}
Temporary::Temporary(QDateTime a){
    this->sign=1;
    this->next=NULL;
    this->prior=NULL;
    this->startTime=a;
}
void Temporary::deleteTemporarybyType(int e){
    Temporary*temp=this->next;
    while(temp){
        if(temp->getEventType()==e){
            temp->prior->next=temp->next;
            if(temp->next){
                temp->next->prior=temp->prior;
            }
            break;
            Temporary*temp2=temp;
            temp=temp->prior;
            delete temp2;
        }
        temp=temp->next;
    }
}
void Temporary::sortbyTime(){
    Temporary*high=this;
    while(high->next){
        high=high->next;
    }
    if(high!=this->next&&high!=this){
         this->quicksortTime(this->next,high);
    }
}
void Temporary::quicksortTime(Temporary*low,Temporary*high){
    if(low!=high){
        Temporary*pivot=quickPassTime(low,high);
        if(low!=pivot){
            quicksortTime(low,pivot->prior);
        }
        if(high!=pivot){
            quicksortTime(pivot->next,high);
        }
    }
}
Temporary*Temporary::quickPassTime(Temporary*low,Temporary*high){
    QDateTime pivot=low->getStartTime();
    while(low!=high){
        while(low!=high && this->comparetime(high->getStartTime(),pivot)>=0){
            high=high->prior;
        }
        this->swap(low,high);
        while(low!=high && this->comparetime(low->getStartTime(),pivot)<=0){
            low=low->next;
        }
        this->swap(low,high);
    }
    return low;
}
void Temporary::sortbyType(){     //根据类型排序
    Temporary*high=this;
    while(high->next){
        high=high->next;
    }
    if(high!=this->next&&high!=this){
        this->quicksort(this->next,high);

    }
}
void Temporary::quicksort(Temporary*low,Temporary*high){
    //快速排序
    if(low!=high){
        Temporary*pivot=quickPass(low,high);
        if(low!=pivot){
            quicksort(low,pivot->prior);
        }
        if(high!=pivot){
            quicksort(pivot->next,high);
        }
    }
}
Temporary*Temporary::quickPass(Temporary*low,Temporary*high){
    int pivot=low->getEventType();
    while(low!=high){
        while(low!=high && high->getEventType()>=pivot){
            high=high->prior;
        }
        this->swap(low,high);
        while(low!=high && low->getEventType()<=pivot){
            low=low->next;
        }
        this->swap(low,high);
    }
    return low;
}
void Temporary::swap(Temporary*a,Temporary*b){
    QDateTime tempT=a->getStartTime();
    int tempe=a->getEventType();
    QString templocation=a->getLocation();
    a->setEventType(b->getEventType());
    a->setstartTime(b->getStartTime());
    a->setlocation(b->getLocation());
    b->setlocation(templocation);
    b->setstartTime(tempT);
    b->setEventType(tempe);
}
QDateTime Temporary::getStartTime(){
    return this->startTime;
}
int Temporary::getEventType(){
    return this->EventType;
}
QString Temporary::getLocation(){
    return this->location;
}
void Temporary::setstartTime(QDateTime a){
    this->startTime=a;
}
void Temporary::setEventType(int e){
    this->EventType=e;
}
void Temporary::setlocation(QString l){
    this->location=l;
}
int Temporary::comparetime(QDateTime a,QDateTime b){
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
QString Temporary::toString(int i){     //0为写入文件，不为0为正常输出
    QStringList alltag={"购物","洗澡","取外卖","取快递","吃饭","洗衣服","勤工俭学","做志愿","睡午觉"};
    Temporary*temp=this;
    QString result;
    result.clear();
    if(this->sign==1)temp=this->next;
    if(i==0){   //写入文件的字符串
        while(temp){
            result=result+QString::number(temp->EventType)+"\n"+temp->startTime.toString("yyyy-MM-dd HH")+"\n"+temp->location+"\n";
            temp=temp->next;
        }
    }
    else if(i==1){    //在系统中输出的字符串
        while(temp){
            result=result+temp->location+"--"+alltag[temp->EventType]+"--"+temp->startTime.toString("yyyy-MM-dd HH")+"\n";
            temp=temp->next;
        }
    }
    else if(i==2){
        result=this->getLocation()+"--"+alltag[this->EventType]+"--"+this->startTime.toString("yyyy-MM-dd HH")+"\n";  //只把当前节点转为字符串
    }
    return result;
}
Temporary::Temporary(Temporary*a){
    this->setEventType(a->getEventType());
    this->setlocation(a->getLocation());
    this->setstartTime(a->getStartTime());
    this->prior=NULL;
    this->next=NULL;
}
