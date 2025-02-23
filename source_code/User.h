
#ifndef USER_H
#define USER_H

#include <QMainWindow>
#include <QObject>
#include"ScheduleTable.h"
#include <QWidget>
class User{
public:
    User(QString id,QString password,int identity);
    QString getPassword();
    QString getID();
    QString getName();
    void setID(QString);
    void setPassword(QString);
    void setName(QString);
    void setIdentity(int);
    int getIdentity();
    ScheduleTable*scheduletable;
    QString toString();
private:
    QString ID;
    QString Password;
    QString name;
    int Identity;       //1为学生，0为管理员
};
#endif // USER_H
