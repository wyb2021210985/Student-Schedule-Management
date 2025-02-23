#include"Map.h"
Map::Map(Graph*g,bool showpath,vector<int> path,QWidget* parent):QWidget(parent),g(g),showpath(showpath),path(path){
    this->showallnodes=false;
    this->setWindowTitle("地图");
    this->resize(1200,1200);
    update();
    QPushButton*showallnodes=new QPushButton("显示所有点",this);
    showallnodes->setGeometry(800,100,150,30);
    connect(showallnodes,&QPushButton::clicked,this,[=](){
        this->showallnodes=true;
        update();
    });
}
void Map::writelog(QString content){
    QString logpath="log.txt";
    QFile log(logpath);
    log.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream in(&log);
    in<<content+"\r\n";
    log.close();
}
void Map::paintEvent(QPaintEvent*event){
    QPainter painter(this);
    painter.begin(this);
    painter.setPen(Qt::black);
    this->resize(1600,1200);
    for(int i=0;i<(int)this->g->allbuildings.size();i++){
        painter.drawRect(this->g->allbuildings[i].x,this->g->allbuildings[i].y-120,this->g->allbuildings[i].width,this->g->allbuildings[i].length);
        int flags=Qt::TextWordWrap|Qt::AlignLeft;
        QRect Rect(this->g->allbuildings[i].x,this->g->allbuildings[i].y-120,this->g->allbuildings[i].width,this->g->allbuildings[i].length);
        painter.drawText(Rect,flags,this->g->allbuildings[i].name);
    }
    if(this->showallnodes){
        painter.setPen(QPen(Qt::red,5));
        for(int i=0;i<(int)this->g->nodes.size();i++){
            painter.drawPoint(this->g->nodes[i].getX(),this->g->nodes[i].getY()-120);
        }
        painter.setPen(QPen(Qt::blue,2));
        int linecount=0;
        for(int i=0;i<(int)this->g->nodes.size();i++){
            for(int j=i+1;j<(int)this->g->nodes.size();j++){
                if(this->g->AdjacentMatrice[i][j]>0||this->g->AdjacentMatrice[j][i]>0){
                    painter.drawLine(this->g->nodes[i].getX(),this->g->nodes[i].getY()-120,this->g->nodes[j].getX(),this->g->nodes[j].getY()-120);
                    linecount++;
                }
            }
        }
    }
    if(this->showpath){
        painter.setPen(QPen(Qt::yellow,2));
        for(int i=0;i<(int)(this->path.size()-1);i++){
            painter.drawLine(this->g->nodes[this->path[i]].getX(),this->g->nodes[this->path[i]].getY()-120,this->g->nodes[this->path[i+1]].getX(),this->g->nodes[this->path[i+1]].getY()-120);
        }
    }
    painter.end();
}

