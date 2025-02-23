
#ifndef AVLCOURSENODE_H
#define AVLCOURSENODE_H
#define LH +1
#define EH 0
#define RH -1
#include"Course.h"
#include <vector>
using namespace std;
class AVLCourseNode{
public:
    AVLCourseNode(Course c);
    Course course;
    int bf;   //平衡因子
    AVLCourseNode*leftchild;
    AVLCourseNode*rightchild;
};
class CourseAVL{
public:
    CourseAVL(vector<Course> courseList);
    CourseAVL();
    int taller;  //变高为1，否则为0
    int shorter;  //变矮为1，否则为0
    int insertAVL(AVLCourseNode*&T,Course e); //插入节点
    AVLCourseNode*root;
    void L_Rotate(AVLCourseNode*&p);  //左旋
    void R_Rotate(AVLCourseNode*&p); //右旋
    void LeftBalance(AVLCourseNode*&p);  //左平衡
    void RightBalance(AVLCourseNode*&p);  //右平衡
    int deleteAVLNode(AVLCourseNode*&p,Course e);  //删除存储课程e的节点
    AVLCourseNode*FindMax(AVLCourseNode*);  //寻找最大值
    AVLCourseNode*FindMin(AVLCourseNode*);  //寻找最小值
    void destroyAVL(AVLCourseNode*);     //释放平衡二叉树所占的内存空间
    void Inordertraverse(AVLCourseNode*p);  //中序遍历
    vector<Course> PersonCourseList;      //中序遍历结果的存储容器
    AVLCourseNode*search(Course e,AVLCourseNode*T); //搜索课程
    vector<Course> searchByname(QString a,AVLCourseNode*T); //按名称a搜索课程
};

#endif // AVLCOURSENODE_H
