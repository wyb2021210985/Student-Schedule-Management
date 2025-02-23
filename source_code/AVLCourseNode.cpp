#include"AVLCourseNode.h"
AVLCourseNode::AVLCourseNode(Course e){
    this->leftchild=NULL;
    this->rightchild=NULL;
    this->bf=EH;
    this->course=e;
}
void CourseAVL::L_Rotate(AVLCourseNode*&p){
    AVLCourseNode*rchild=p->rightchild;
    p->rightchild=rchild->leftchild;
    rchild->leftchild=p;
    p=rchild;
}
void CourseAVL::R_Rotate(AVLCourseNode*&p){
    AVLCourseNode*lchild=p->leftchild;
    p->leftchild=lchild->rightchild;
    lchild->rightchild=p;
    p=lchild;
}
void CourseAVL::LeftBalance(AVLCourseNode*&p){
    AVLCourseNode*lchild;
    lchild=p->leftchild;
    switch(lchild->bf){
    case LH:
        lchild->bf=EH;
        p->bf=EH;
        R_Rotate(p);
        break;
    case RH:
        AVLCourseNode* rd=lchild->rightchild;
        switch(rd->bf){
            case LH:
                p->bf=RH;
                lchild->bf=EH;
                break;
            case EH:
                p->bf=EH;
                lchild->bf=EH;
                break;
            case RH:
                p->bf=EH;
                lchild->bf=LH;
                break;
        }
        rd->bf=EH;
        L_Rotate(p->leftchild);
        R_Rotate(p);
        break;
    }
}
void CourseAVL::RightBalance(AVLCourseNode*&p){
    AVLCourseNode*rchild;
    rchild=p->rightchild;
    switch(rchild->bf){
    case RH:
        rchild->bf=EH;
        p->bf=rchild->bf;
        L_Rotate(p);
        break;
    case LH:
        AVLCourseNode*ld=rchild->leftchild;
        switch(ld->bf){
            case LH:
                p->bf=EH;
                rchild->bf=RH;
                break;
            case EH:
                p->bf=EH;
                rchild->bf=EH;
                break;
            case RH:
                p->bf=EH;
                rchild->bf=LH;
                break;
        }
        ld->bf=EH;
        R_Rotate(p->rightchild);
        L_Rotate(p);
        break;
    }
}
int CourseAVL::insertAVL(AVLCourseNode*&T,Course e){
    if(!T){
        T=new AVLCourseNode(e);
        this->taller=1;
    }
    else{
        if(e.compare(this->root->course)==0){
            this->taller=0;
            return 0;
        }
        else if(e.compare(T->course)<0){
            if(!this->insertAVL(T->leftchild,e)){
                return 0;
            }
            if(this->taller){
                switch(T->bf){
                case LH:
                    LeftBalance(T);
                    this->taller=0;
                    break;
                case EH:
                    T->bf=LH;
                    taller=1;
                    break;
                case RH:
                    T->bf=EH;
                    taller=0;
                    break;
                }
            }
        }
        else{
            if(!insertAVL(T->rightchild,e)){
                return 0;
            }
            if(taller){
                switch(T->bf){
                case LH:
                    this->taller=0;
                    T->bf=EH;
                    break;
                case EH:
                    T->bf=RH;
                    taller=1;
                    break;
                case RH:
                    RightBalance(T);
                    taller=0;
                    break;
                }
            }
        }
    }
    return 1;
}
AVLCourseNode* CourseAVL::FindMax(AVLCourseNode*T){
    if(!T){
        return NULL;
    }
    else if(T->rightchild==NULL){
        return T;
    }
    return this->FindMax(T->rightchild);
}
AVLCourseNode* CourseAVL::FindMin(AVLCourseNode*T){
    if(!T){
        return NULL;
    }
    else if(T->leftchild==NULL){
        return T;
    }
    return this->FindMin(T->leftchild);
}
int CourseAVL::deleteAVLNode(AVLCourseNode*&p,Course e){
    if(p==NULL){
        this->shorter=0;
        return 0;
    }
    else{
        if(p->course.compare(e)==0){
            AVLCourseNode*T;
            if(p->leftchild==NULL) {
                T=p;
                p=p->rightchild;
                delete T;
                this->shorter=1;
                return 1;
            }
            else if(p->rightchild==NULL){
                T=p;
                p=p->leftchild;
                delete T;
                this->shorter=1;
                return 1;
            }
            else{
                AVLCourseNode*temp=p->leftchild;
                while(temp->rightchild){
                    temp=temp->rightchild;
                }
                p->course=temp->course;
                deleteAVLNode(p->leftchild,temp->course);
            }
        }
        else if(p->course.compare(e)<0){
            if(!this->deleteAVLNode(p->rightchild,e)){
                return 0;
            }
            if(this->shorter){
                switch(p->bf){
                case LH:
                    this->LeftBalance(p);
                    if(p->leftchild->bf==EH){
                        this->shorter=0;
                    }
                    else{
                        this->shorter=1;
                    }
                    break;
                case EH:
                    p->bf=LH;
                    this->shorter=0;
                    break;
                case RH:
                    p->bf=EH;
                    this->shorter=1;
                    break;
                 }
            }
        }
        else{
            if(!this->deleteAVLNode(p->leftchild,e)){
                 return 0;
            }
            if(this->shorter){
                 switch(p->bf){
                 case LH:
                    p->bf=EH;
                    this->shorter=1;
                    break;
                 case EH:
                    p->bf=RH;
                    this->shorter=0;
                    break;
                 case RH:
                    this->RightBalance(p);
                    if(p->rightchild->bf==EH){
                        this->shorter=0;
                    }
                    else{
                        this->shorter=1;
                    }
                 }
            }
        }
    }
    return 1;
}
void CourseAVL::destroyAVL(AVLCourseNode*T){
    if(T){
        if(T->rightchild==NULL&&T->leftchild==NULL){
            delete T;
        }
        else if(T->rightchild==NULL){
            destroyAVL(T->leftchild);
            delete T;
        }
        else if(T->leftchild==NULL){
            destroyAVL(T->rightchild);
            delete T;
        }
        else{
            destroyAVL(T->leftchild);
            destroyAVL(T->rightchild);
            delete T;
        }
    }
}
void CourseAVL::Inordertraverse(AVLCourseNode*p){
    if(p){
        Inordertraverse(p->leftchild);
        this->PersonCourseList.push_back(p->course);
        Inordertraverse(p->rightchild);
    }
}
AVLCourseNode* CourseAVL::search(Course e,AVLCourseNode*T){
    if(T){
        if(T->course.compare(e)==0){
            return T;
        }
        else if(T->course.compare(e)<0){
            return search(e,T->rightchild);
        }
        else{
            return search(e,T->leftchild);
        }
    }
    else{
        return NULL;
    }
}
vector<Course> CourseAVL::searchByname(QString a,AVLCourseNode*T){
    vector<Course> result;
    if(T){
        if(a.compare(T->course.getname())<0){
           return this->searchByname(a,T->leftchild);
        }
        else if(a.compare(T->course.getname())>0){
           return this->searchByname(a,T->rightchild);
        }
        else{
           vector<Course> left=searchByname(a,T->leftchild);
           for(int i=0;i<left.size();i++){
                 result.push_back(left[i]);
           }
           result.push_back(T->course);
           vector<Course> right=searchByname(a,T->rightchild);
           for(int j=0;j<right.size();j++){
                 result.push_back(right[j]);
           }
           return result;
        }
    }
    else{
        return result;
    }
}
CourseAVL::CourseAVL(){
    this->root=NULL;
    this->shorter=0;
    this->taller=0;
}
