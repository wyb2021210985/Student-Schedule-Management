#include"Graph.h"
#include "qdebug.h"
Graph::Graph(QString nodefile,QString buildingsfile,QString graphfile){
    this->ReadNodes(nodefile);
    this->ReadBuildings(buildingsfile);
   // this->writeBuildings();
    this->ReadGraph(graphfile);
}
Graph::Graph(vector<node> a){
    this->nodes=a;
    int nodesize=this->nodes.size();
    this->AdjacentMatrice=new int*[nodesize];
    for(int i=0;i<nodesize;i++){
        this->AdjacentMatrice[i]=new int[nodesize];
    }
    for(int i=0;i<nodesize;i++){
        for(int j=0;j<nodesize;j++){
            this->AdjacentMatrice[i][j]=0;
        }
    }
}
Path*Graph:: Dj(node start){
    int StartIndex=FindIndex(this->nodes,start.getname());
    vector<int> path;
    int *dist=new int[(int)this->nodes.size()];
    int *visited=new int[(int)this->nodes.size()];
    int *parent=new int[(int)this->nodes.size()];  //按照最短路径到达的终点的前驱结点的下标数组
    for(int i=0;i<(int)this->nodes.size();i++){
        if(i==StartIndex){
            visited[i]=1;
            dist[i]=0; //-1指无穷大
        }
        else{
            visited[i]=0;
            if(this->AdjacentMatrice[StartIndex][i]==0){
                dist[i]=-1;
            }
            else{
                dist[i]=this->AdjacentMatrice[StartIndex][i];
                parent[i]=StartIndex;
            }
        }
        parent[StartIndex]=-1;
    }

    for(int j=0;j<(int)this->nodes.size()-1;j++){
        int TempMinDist=-1,nearest=-1;
        for(int k=0;k<(int)this->nodes.size();k++){
            if((TempMinDist==-1||TempMinDist>dist[k])&&dist[k]!=-1&&!visited[k]){
                TempMinDist=dist[k];
                nearest=k;
            }
        }
        visited[nearest]=1;
        for(int q=0;q<(int)this->nodes.size();q++){
            if(!visited[q]&&this->AdjacentMatrice[nearest][q]!=0){ //如果这个点没有被访问过，且结点能到达
                if((dist[q]==-1&&dist[nearest]!=-1&&this->AdjacentMatrice[nearest][q]!=0)||
                    (dist[q]!=-1&&this->AdjacentMatrice[nearest][q]+dist[nearest]<dist[q]&&this->AdjacentMatrice[nearest][q]!=-1)){
                    dist[q]=this->AdjacentMatrice[nearest][q]+dist[nearest];
                    parent[q]=nearest;
                }
            }
        }
    }
    Path*result=new Path;
    result->distance=dist;
    result->parent=parent;
    delete[] visited;
    return result;
}
int Graph::FindIndex(vector<node> allnodes, QString a){
    for(int i=0;i<(int)allnodes.size();i++){
        if(a==allnodes[i].getname()){
            return i;
        }
    }
    return -1;
}
int Graph::distance(node a,node b){
    if(a.getX()==b.getX()){
        return this->fabs(a.getY()-b.getY());
    }
    else if(a.getY()==b.getY()){
        return this->fabs(a.getX()-b.getX());
    }
    else{
        return (this->fabs(a.getX()-b.getX())+this->fabs(a.getY()-b.getY()));
    }
}
int Graph::fabs(int a){
    if(a>=0){
        return a;
    }
    else{
        return (0-a);
    }
}
void Graph::ReadGraph(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!";
    }
    QTextStream out(&file);
    QString oneline=out.readLine();
    while(!out.atEnd()) {
        int state=3;
        int a;
        int b;
        QString start,temp;
        for(int i=0;i<(int)oneline.length();i++){
            if(state==3){
                while(oneline[i]!=L'-'&&oneline[i]!=L';'){
                    i++;
                }
                start=oneline.left(i);
                state=2;
                a=this->FindIndex(this->nodes,start);
            }
            else if(state==2){
                while(oneline[i]==L'-'){
                    i++;
                }
                int temp1=i,j=0;
                while(oneline[i]!=L';'&&oneline[i]!=L'-'&&oneline[i]!=L'['){
                    i++;
                    j++;
                }
                temp=oneline.mid(temp1,j);

                b=FindIndex(this->nodes,temp);

                this->AdjacentMatrice[a][b]=distance(this->nodes[a],this->nodes[b]);
                this->AdjacentMatrice[b][a]=distance(this->nodes[a],this->nodes[b]);
            }
        }
        oneline=out.readLine();
    }
    file.close();
}
/*
void Graph::ReadNodes(QString filename){
    QAxObject excel("Excel.application");
    excel.dynamicCall("SetVisible(bool Visible)","false");
    excel.setProperty("DisplayAlerts",false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open(const QString&)", filename);
    QAxObject *work_book=excel.querySubObject("ActiveWorkBook");
    QAxObject *work_sheet = work_book->querySubObject("WorkSheets(int)",1);
    QAxObject *used_range = work_sheet->querySubObject("UsedRange");
    QAxObject *rows = used_range->querySubObject("Rows");
    QAxObject *columns = used_range->querySubObject("Columns");
    int row_start = used_range->property("Row").toInt();  //获取起始行
    int column_start = used_range->property("Column").toInt();  //获取起始列
    int row_count = rows->property("Count").toInt();  //获取行数
    int column_count = columns->property("Count").toInt();  //获取列数
    for(int i=row_start+1;i<=row_count;i++){
        QString name;
        int xtemp,ytemp;
        for(int j=column_start;j<=column_count;j++){
            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
            QVariant cell_value = cell->property("Value");  //获取单元格内容
            switch(j){
                case 1:name=cell_value.toString();break;
                case 2:xtemp=cell_value.toInt();break;
                case 3:ytemp=cell_value.toInt();break;
            }
        }
        this->nodes.push_back(node(name,xtemp,ytemp));
    }
    int nodesize=this->nodes.size();
    this->AdjacentMatrice=new int*[nodesize];
    for(int i=0;i<nodesize;i++){
        this->AdjacentMatrice[i]=new int[nodesize];
    }
    for(int i=0;i<nodesize;i++){
        for(int j=0;j<nodesize;j++){
            this->AdjacentMatrice[i][j]=0;
        }
    }
    work_books->dynamicCall("Close()");
    excel.dynamicCall("Quit()");
}*/
void Graph::ReadNodes(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!";
    }
    QTextStream out(&file);
    QString oneline=out.readLine();
    while(!out.atEnd()){
        QString name=oneline;
        oneline=out.readLine();
        int x=oneline.toInt();
       oneline=out.readLine();
        int y=oneline.toInt();
        node temp(name,x,y);
        this->nodes.push_back(temp);
        oneline=out.readLine();
    }
    file.close();
    int nodesize=this->nodes.size();
    this->AdjacentMatrice=new int*[nodesize];
    for(int i=0;i<nodesize;i++){
        this->AdjacentMatrice[i]=new int[nodesize];
    }
    for(int i=0;i<nodesize;i++){
        for(int j=0;j<nodesize;j++){
            this->AdjacentMatrice[i][j]=0;
        }
    }
}
void Graph::ReadBuildings(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!";
    }
    QTextStream out(&file);
    QString oneline=out.readLine();
    while(!out.atEnd()){
        int j=0;
        int temp1;
        QString start,temp;
        for(int i=0;i<(int)oneline.length();i++){
                j=0;
            while(oneline[i]!=L'['){
                    j++;
                    i++;
                }
                start=oneline.left(j);
                i++;
                j=0;
                QString xstr,ystr,widthstr,lengthstr;
                temp1=i;
                while(oneline[i]!=L','){
                    j++;
                    i++;
                }
                xstr=oneline.mid(temp1,j);
                i++;
                temp1=i;
                j=0;
                while(oneline[i]!=L','){
                    j++;
                    i++;
                }
                ystr=oneline.mid(temp1,j);
                i++;
                temp1=i;
                j=0;
                while(oneline[i]!=L','){
                    j++;
                    i++;
                }
                widthstr=oneline.mid(temp1,j);
                i++;
                temp1=i;
                j=0;
                while(oneline[i]!=L']'){
                    j++;
                    i++;
                }
                lengthstr=oneline.mid(temp1,j);
                i++;
                building newbuilding(xstr.toInt(),ystr.toInt(),widthstr.toInt(),lengthstr.toInt(),start);
                this->allbuildings.push_back(newbuilding);
        }
        oneline=out.readLine();
    }
    file.close();
}
void Graph::writenodes(){
    QFile file("nodes.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        qDebug()<<"打不开";
    }
    QTextStream a(&file);
    for(int i=0;i<(int)this->nodes.size();i++){
        a<<this->nodes[i].getname()+"\n";
        a<<QString::number(this->nodes[i].getX())+"\n";
        a<<QString::number(this->nodes[i].getY())+"\n";
    }
    file.close();
}
vector<int> Graph::FindShortestPath(QString start,QString dest){
    int StartIndex=this->FindIndex(this->nodes,start);
    int EndIndex=this->FindIndex(this->nodes,dest);
    Path*shortestpath;
    shortestpath=this->Dj(this->nodes[StartIndex]);
    vector<int> result;
    QStack<int> stack;
    int back=EndIndex;
    while(back!=StartIndex){
        stack.push(back);
        back=shortestpath->parent[back];
    }
    stack.push(StartIndex);
    while(!stack.isEmpty()){
        result.push_back(stack.pop());
    }
    return result;
}
int Graph:: getlength(vector<int> path){
    int length=0;
    for(int i=0;i<(int)path.size()-1;i++){
        length=this->AdjacentMatrice[path[i]][path[i+1]]+length;
    }
    return length;
}
int Graph::FindBuildingIndex(QString buildingsname){
    for(int i=0;i<(int)this->allbuildings.size();i++){
        if(this->allbuildings[i].name==buildingsname){
            return i;
        }
    }
    return -1;
}
void Graph::printallnodes(){
    for(int i=0;i<this->nodes.size();i++){
        qDebug()<<this->nodes[i].getname();
        qDebug()<<this->nodes[i].getX();
        qDebug()<<this->nodes[i].getY();
    }
}
void Graph::showallbuildings(){
    for(int i=0;i<this->allbuildings.size();i++){
        qDebug()<<this->allbuildings[i].build.getname();
        qDebug()<<this->allbuildings[i].build.getX();
        qDebug()<<this->allbuildings[i].build.getY();
    }
}
vector<int> Graph::PostMan(vector<QString> a){                //从一个点出发，经过多个点返回原点的最短路径
    vector<int> Indexcollocation;
    vector<node> subgraphnodes;
    for(int i=0;i<(int)a.size();i++){
        Indexcollocation.push_back(this->FindIndex(this->nodes,a[i]));
        subgraphnodes.push_back(this->nodes[this->FindIndex(this->nodes,a[i])]);
    }
    vector<int> temp1;
    for(int i=1;i<(int)a.size();i++){
        temp1.push_back(Indexcollocation[i]);
    }
    Graph*subgraph=new Graph(subgraphnodes);
    int subgraphnodesize=subgraphnodes.size();
    for(int i=0;i<subgraphnodesize;i++){    //通过迪杰斯特拉算法求子图每个点之间的最短距离
        Path*temp=this->Dj(this->nodes[Indexcollocation[i]]);
        for(int j=i+1;j<subgraphnodesize;j++){
            vector<int> TempPath;
            QStack<int> stack;
            int back=Indexcollocation[j];
            while(back!=Indexcollocation[i]){
                stack.push(back);
                back=temp->parent[back];
            }
            stack.push(Indexcollocation[i]);
            while(!stack.isEmpty()){
                TempPath.push_back(stack.pop());
            }
            subgraph->AdjacentMatrice[i][j]=this->getlength(TempPath);
            subgraph->AdjacentMatrice[j][i]=this->getlength(TempPath);
        }
        delete temp;
    }
    d*Indexset=new d(temp1,Indexcollocation[0],Indexcollocation[0]);
    vector<d*> sub;
    vector<int> result=subgraph->TSP(Indexset,Indexcollocation);
    vector<int> result2;
    for(int i=0;i<(int)result.size()-1;i++){
        Path*expansionPath=this->Dj(this->nodes[result[i]]);
        vector<int> TempPath2;
        QStack<int> stack2;
        int back=result[i+1];
        while(back!=result[i]){
            stack2.push(back);
            back=expansionPath->parent[back];
        }
        if(i==0)stack2.push(result[i]);
        while(!stack2.isEmpty()){
            TempPath2.push_back(stack2.pop());
        }
        for(int i=0;i<(int)TempPath2.size();i++){
            result2.push_back(TempPath2[i]);
        }
        delete expansionPath;
    }
    delete Indexset;
    delete subgraph;
    return result2;
}
int Graph::min(vector<int> a){
    int min=-1;
    int index=-1;
    for(int i=0;i<(int)a.size();i++){
        if(i==0||min>a[i]){
            min=a[i];
            index=i;
        }
    }
    return index;
}
d::d(vector<int> sub,int a,int start){
    this->startIndex=start;
    this->Cik=a;
    this->set=sub;
}
vector<vector<int>> d::getsubset(){
    vector< vector<int> > result;
    int n=this->set.size();
    for(int i=0;i<(1<<n);i++){
        vector<int> temp;
        for(int j=0;j<n;j++){
            if((1<<j)&i){
                temp.push_back(this->set[j]);
            }
        }
        result.push_back(temp);
    }
    return result;
}
vector<d*> d::parse(){
    vector<d*> result;
    for(int i=0;i<(int)this->set.size();i++){
        vector<int> sub;
        for(int j=0;j<(int)this->set.size();j++){
            if(j!=i){
                sub.push_back(this->set[j]);
            }
        }
        d*temp=new d(sub,this->set[i],this->startIndex);
        result.push_back(temp);
    }
    return result;
}
vector<int> Graph::TSP(d*a, vector<int> indexset){
    if(a->set.size()==1){
        vector<int> TempPath;
        TempPath.push_back(a->Cik);
        TempPath.push_back(a->set[0]);
        TempPath.push_back(a->startIndex);
        return TempPath;
    }
    else{
        vector<int> allLength;
        vector<vector<int>> allsubPath;
        vector<d*> SubSet=a->parse();
        for(int i=0;i<(int)SubSet.size();i++){
            allsubPath.push_back(this->TSP(SubSet[i],indexset));
            allsubPath[i].insert(allsubPath[i].begin(),a->Cik);
            vector<int> Indexofsubpath;
            for(int j=0;j<(int)allsubPath[i].size();j++){

                for(int k=0;k<(int)indexset.size();k++){
                    if(allsubPath[i][j]==indexset[k]){
                        Indexofsubpath.push_back(k);
                    }
                }
            }
            allLength.push_back(this->getlength(Indexofsubpath));
        }
        return allsubPath[min(allLength)];
    }
}
