#include "prm.h"

PRM::PRM(double **map, int mapSize): mGraph(NULL), celRange(100)
{
    mMap = map;
    mMapSize = mapSize;
    mGoalNode = mInitNode = NULL;
    mGraph = NULL;
    createGraph(1000,4);
}

Graph* PRM::createGraph(int numberOfNodes, int numberClosestNeighbors)
{
    struct timeval begin,end;
    gettimeofday(&begin,NULL);
    qDebug() << "Criando o grafo";
    if(mGraph)
        delete mGraph;
    mGraph = new Graph();

    while(mGraph->V.size() < numberOfNodes)
    {
        Node *n;
        do
        {
            n = new Node(mGraph->V.size());
            n->mPose->setPose(rand()%mMapSize,rand()%mMapSize);
        } while(!checkNodeAreaIsEmpty(n)); //Verificar se é ponto livre no mapa.
        mGraph->V.push_back(n);
    }

    for(int i=0;i<mGraph->V.size();i++)
    {
        vector<Node*> Nq = mGraph->V.at(i)->sortedClosest(mGraph,numberClosestNeighbors);

        //qDebug() << "Near: " << Nq.size() ;
        for(int j=0; j<Nq.size();j++)
        {
            if( !mGraph->hasEdge(mGraph->V.at(i),Nq.at(j)) && delta(mGraph->V.at(i),Nq.at(j)) != NULL)
            {
                //qDebug() << "Add Edge";
                Edge *edge = new Edge(mGraph->V.at(i),Nq.at(j));
                mGraph->V.at(i)->neighbors.push_back(edge);
                Nq.at(j)->neighbors.push_back(new Edge(Nq.at(j),mGraph->V.at(i)));
                mGraph->E.push_back(edge);
            }
        }
    }
    gettimeofday(&end,NULL);

    qDebug() << "Grafo criado!";
    qDebug() << "Tempo criacao: " << ((double)(end.tv_usec-begin.tv_usec))/1000000 + (double)(end.tv_sec-begin.tv_sec);
    qDebug() << "Nos: " << mGraph->V.size();
    qDebug() << "Edges: " << mGraph->E.size();

}

vector<Edge*> PRM::query(int numberClosestNeighbors)
{
    path.erase(path.begin(),path.end());

    struct timeval begin,end;
    gettimeofday(&begin,NULL);
    qDebug() << "Query começando";
    mGraph->V.push_back(mGoalNode);
    mGraph->V.push_back(mInitNode);


    vector<Node*> Nq = mInitNode->sortedClosest(mGraph,numberClosestNeighbors);
    Edge *edge = NULL;
    do
    {
        if(delta(mInitNode,Nq.at(0)) != NULL)
        {
            edge = new Edge(mInitNode,Nq.at(0));
            mInitNode->neighbors.push_back(edge);
            mGraph->E.push_back(edge);
        }
        else
        {
            Nq.erase(Nq.begin());
        }
    }while(Nq.size() && (edge == NULL));


    edge = NULL;
    Nq = mGoalNode->sortedClosest(mGraph,numberClosestNeighbors);
    do
    {
        if(delta(mGoalNode,Nq.at(0)) != NULL)
        {
            edge = new Edge(Nq.at(0),mGoalNode);
            Nq.at(0)->neighbors.push_back(edge);
            mGraph->E.push_back(edge);
        }
        else
        {
            Nq.erase(Nq.begin());
        }
    }while(Nq.size() && (edge == NULL));

    AStar search;
    path = search.shortestPath(mInitNode,mGoalNode); //Run shortest path

    if(path.size() == 0)
    {
        delete mInitNode;
        delete mGoalNode;
        mInitNode = mGoalNode = NULL;
    }

    Nq.at(0)->neighbors.pop_back();
    mGraph->E.pop_back();
    mGraph->E.pop_back();
    mGraph->V.pop_back();
    mGraph->V.pop_back();
    gettimeofday(&end,NULL);

    qDebug() << "Path acabando!";
    qDebug() << "Tempo busca: " << ((double)(end.tv_usec-begin.tv_usec))/1000000 + (double)(end.tv_sec-begin.tv_sec);
    return path;
}

int PRM::delta(Node *n1, Node *n2)
{
    double deltaX = n2->mPose->getX() - n1->mPose->getX(), deltaY = n2->mPose->getY() - n1->mPose->getY();
    double m;
    if(fabs(deltaX) > fabs(deltaY))
        m = deltaX;
    else
        m = deltaY;
    double step = fabs(1/m);
    for (double percent = 0.0;percent <= 1.0;percent += step)
    {
        int x = (int)round((n2->mPose->getX() - n1->mPose->getX())*percent+n1->mPose->getX()),
                y = (int)round((n2->mPose->getY() - n1->mPose->getY())*percent+n1->mPose->getY());

        if(mMap[x][y] == 0.0)
            return NULL;
    }
    return 1;
}

bool PRM::checkNodeAreaIsEmpty(Node *n1)
{
    return checkNodeAreaIsEmpty((int)n1->mPose->getX(),(int)n1->mPose->getY());
}

bool PRM::checkNodeAreaIsEmpty(int x, int y)
{
    for(int nx =max(x-2,0);nx <= min(x+2,mMapSize-1);nx++)
    {
        for(int ny =max(y-2,0);ny <= min(y+2,mMapSize-1);ny++)
        {
            if(mMap[nx][ny] == 0.0)
            {
                return false;
            }
        }
    }
    return true;
}

void PRM::render()
{
    //Desenhando o mapa em si
    glBegin(GL_QUADS);

    for(int x=0;x<mMapSize;x++)
    {
        for(int y=0;y<mMapSize;y++)
        {
            if(mMap[x][y] != 1.0)
            {
                int value = 255*mMap[x][y];
                drawBox(
                            (x-1-mMapSize/2)*celRange,
                            (mMapSize/2 - y+1)*celRange,
                            celRange,
                            celRange,
                            QColor(value,value,value)
                            );
            }
        }
    }
    glEnd();

    if(mGraph)
    {
        //Desenhando os Arcos
        glColor3f(0.0f,0.0f,1.0f);
        glBegin(GL_LINES);

        for(int i =0; i<mGraph->E.size();i++)
        {
            Pose *pL = mGraph->E.at(i)->mNodeL->mPose, *pR = mGraph->E.at(i)->mNodeR->mPose;
            glVertex2f((pL->getX()-mMapSize/2)*celRange,(mMapSize/2 - pL->getY())*celRange);
            glVertex2f((pR->getX()-mMapSize/2)*celRange,(mMapSize/2 - pR->getY())*celRange);
        }
        glEnd();

        //Desenhando os  nodos
        glBegin(GL_QUADS);
        for(int i =0;i<mGraph->V.size();i++)
        {
            Pose *p = mGraph->V.at(i)->mPose;

            drawBox(
                (p->getX() - 1 - mMapSize/2)*celRange,
                (mMapSize/2 - 1 - p->getY())*celRange,
                celRange*2,
                celRange*2,
                QColor(0,255,255)
                );
        }
        glEnd();
    }


    if(mInitNode && mGoalNode && path.size())
    {
        //Desenhando os Arcos
        glColor3f(1.0f,0.0f,1.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);

        for(int i =0; i<path.size();i++)
        {
            Pose *pL = path.at(i)->mNodeL->mPose, *pR = path.at(i)->mNodeR->mPose;
            glVertex2f((pL->getX()-mMapSize/2)*celRange,(mMapSize/2 - pL->getY())*celRange);
            glVertex2f((pR->getX()-mMapSize/2)*celRange,(mMapSize/2 - pR->getY())*celRange);
        }
        glEnd();
        glLineWidth(1.0f);
    }

    //Desenhando os objetivo e posicao inicial
    if(mInitNode)
    {
        glBegin(GL_QUADS);
        drawBox(
            (mInitNode->mPose->getX() - 2 - mMapSize/2)*celRange,
            (mMapSize/2 - 1 - mInitNode->mPose->getY())*celRange,
            celRange*3,
            celRange*3,
            QColor(0,150,0)
            );
        glEnd();
    }
    if(mGoalNode)
    {
        glBegin(GL_QUADS);
        drawBox(
            (mGoalNode->mPose->getX() - 2 - mMapSize/2)*celRange,
            (mMapSize/2 - 1 - mGoalNode->mPose->getY())*celRange,
            celRange*3,
            celRange*3,
            QColor(255,0,0)
            );
        glEnd();
    }
}

void PRM::drawBox(double x, double y, double width, double height,QColor color)
{
    glColor3f(color.redF(),color.greenF(),color.blueF());

    glVertex2f(x,y);
    glVertex2f(x+width,y);
    glVertex2f(x+width,y+height);
    glVertex2f(x,y+height);
}

void PRM::setGoalNode(double x, double y)
{
    x = x/celRange+mMapSize/2;
    y = mMapSize/2-y/celRange;
    if(checkNodeAreaIsEmpty(x,y))
    {
        if(mGoalNode)
            delete mGoalNode;
        mGoalNode= new Node();
        mGoalNode->mPose->setPose(x,y);
        //mGoalNode->mPose->setPose(mMapSize-20,20);
    }
}

void PRM::setInitNode(double x, double y)
{
    x = x/celRange+mMapSize/2;
    y = mMapSize/2-y/celRange;
    if(checkNodeAreaIsEmpty(x,y))
    {
        if(mInitNode)
            delete mInitNode;
        mInitNode= new Node();
        mInitNode->mPose->setPose(x,y);
        //mInitNode->mPose->setPose(20,mMapSize-20);
    }
}
