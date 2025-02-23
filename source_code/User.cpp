
#include"User.h"
User::User(QString id,QString password, int identity){
    this->ID=id;
    this->Password=password;
    this->Identity=identity;
    if(identity==1){
        this->scheduletable=new ScheduleTable();
    }
    else{
        this->scheduletable=NULL;
    }
}
QString User::getPassword(){
    return this->Password;
}
QString User::getID(){
    return this->ID;
}
int User::getIdentity(){
    return this->Identity;
}
QString User::getName(){
    return this->name;
}
void User::setName(QString a){
    this->name=a;
}
void User::setID(QString id){
    this->ID=id;
}
void User::setPassword(QString pw){
    this->Password=pw;
}
void User::setIdentity(int i){
    this->Identity=i;
}
QString User::toString(){
    QString result;
    result=this->ID+"\n"+this->Password+"\n"+QString::number(this->Identity)+"\n";
    if(this->Identity==1){
        result=result+this->scheduletable->toString();
    }
    return "[\n"+result+"]\n";
}

