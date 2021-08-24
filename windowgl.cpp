#include "windowgl.h"


// Construtor
WindowGL::WindowGL(QWidget *ancestral) : QGLWidget(ancestral)
{

    insert=false;
    showPath=false;
    showPotential=false;
    showGrid=false;
    statusMsg=new QLabel("programa aberto");
    mousePosition=new QLabel("coordenada x,coordenada y");
    read("default.txt"); //ler um arquivo padrao inicial
    this->setMouseTracking(1); //habilita a captura da posição do mouse
    setFixedSize(800,600); //tamanho da janela

}

void WindowGL::initializeGL() //Inicia os dados do openGl
{
    glClearColor(0.6, 0.6, 0.6, 1.0); //cor de fundo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,m*h,0,n*h);//intervalo de coordenadas de x e y
}

void WindowGL::paintGL() //desenha na tela
{	

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    if(showPotential) // mostra ou não potencial
    {
        float color;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++){

                if(c[i][j]->getValue()==999) glColor3f(1.0,0.0,0.0); //vermelho para os obstáculos
                else{
                    color=float(c[i][j]->getValue())/float(startValue); //normaliza a cor
                    glColor3f(color,color,color);}

                glBegin(GL_POLYGON); // desenha o quadrado de cada celula de acordo com a cor
                glVertex2f(c[i][j]->getCenter().getx()-h/2,c[i][j]->getCenter().gety()-h/2);
                glVertex2f(c[i][j]->getCenter().getx()+h/2,c[i][j]->getCenter().gety()-h/2);
                glVertex2f(c[i][j]->getCenter().getx()+h/2,c[i][j]->getCenter().gety()+h/2);
                glVertex2f(c[i][j]->getCenter().getx()-h/2,c[i][j]->getCenter().gety()+h/2);
                glEnd();

            }
        }
    }

    //não discretiza os poligonos
    else{
        glColor3f(1.0,0.0,0.0);
        for(int i=0;i<P.size();i++){
            glBegin(GL_POLYGON); // desenha o poligono
            for(int j=0;j<P[i].getnp();j++) glVertex2f(P[i].getpoint(j).getx(),P[i].getpoint(j).gety());
            glEnd();
        }
    }

    //desenha ponto inicial e final
    glPointSize(7.0);
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);//inicial verde
    glVertex2f(start->getx(),start->gety());
    glColor3f(0.0,0.0,1.0);//final azul
    glVertex2f(final->getx(),final->gety());
    glEnd();

    //mostra ou não o caminho
    if(showPath){
        glLineWidth(5.0);
        glBegin(GL_LINE_STRIP);
        for(int i=0;i<path.size();i++) glVertex2f(path[i].getx(),path[i].gety());
        glEnd();
    }


    //mostra ou não o grid
    if(showGrid){
    glLineWidth(1.0);
    glColor3f(1.0,1.0,1.0);
        for(int i=0;i<n;i++)
        {
            glBegin(GL_LINES);
            glVertex2f(0,i*h);
            glVertex2f(m*h,i*h);
            glEnd();
        }
        for(int j=0;j<m;j++)
        {
            glBegin(GL_LINES);
            glVertex2f(j*h,0);
            glVertex2f(j*h,n*h);
            glEnd();
        }
    }

}



void WindowGL::mousePressEvent(QMouseEvent *event) // captura a posiçao do mouse quando clicado
{
    if(event->buttons()==Qt::RightButton && !insert) {insert=true;statusMsg->setText("Inicia captura");} //começa a captura
    else if(event->buttons()==Qt::RightButton && insert) // termina a captura e grava
    {
        insert=false;
        if(temp.size()==1) {*start=temp[0]; statusMsg->setText("Ponto inicial Criado");}
        if(temp.size()==2) {*start=temp[0]; *final=temp[1]; statusMsg->setText("Ponto inicial e final criados");}
        if(temp.size()>2)
        {
            P.push_back(MyPolygon(temp.size()));
            for(int i=0;i<temp.size();i++) {P.back().add(temp[i],i);}
            statusMsg->setText("Poligono Criado com sucesso");
        }
        this->updateGLWidget();
        temp.clear();
    }
    if(insert && event->buttons()==Qt::LeftButton) //captura ponto a ponto (obs:tem que inverter em y)
    {
        temp.push_back(MyPoint((event->pos().x()*m*h)/size().width(),n*h-(event->pos().y()*n*h)/size().height()));
        statusMsg->setText("Ponto capturado");
    }


}

void WindowGL::mouseMoveEvent(QMouseEvent *event) //captura o movimento do mouse
{
mousePosition->setText("x:" + QString::number((event->pos().x()*m*h)/size().width())
                      + ",y:" +QString::number(n*h-(event->pos().y()*n*h)/size().height()));

}

void WindowGL::read(QString t) // ler do arquivo
{
    ifstream infile(t.toLatin1());

    //auxiliares
    float a,b;
    int nvertex,numPol;

    //leitura
    infile >> m;
    infile >> n;
    infile >> h;
    infile >> a;
    infile >> b;
    start=new MyPoint(a,b);
    infile >> a;
    infile >> b;
    final=new MyPoint(a,b);
    infile >> numPol;
    P.resize(numPol);

    for(int i=0;i<numPol;i++)
    {
        infile >> nvertex;
        P[i]=MyPolygon(nvertex);
        for(int j=0;j<nvertex;j++)
        {
            infile >> a;
            infile >> b;
            P[i].add(MyPoint(a,b),j);
        }
    }

    this->updateGLWidget(); //atualiza
    statusMsg->setText("arquivo lido com sucesso");
}

void WindowGL::save(QString t) //Salva no arquivo
{
    ofstream outfile(t.toLatin1());

    outfile << m << " " << n << "\n" ;
    outfile << h << "\n";
    outfile << start->getx() << " " << start->gety() << "\n";
    outfile << final->getx() << " " << final->gety() << "\n";
    outfile << P.size() << "\n";

    for(int i=0;i<P.size();i++)
    {
        outfile << P[i].getnp() << "\n";
        for(int j=0;j<P[i].getnp();j++)
        {
            outfile << P[i].getpoint(j).getx() << " " << P[i].getpoint(j).gety() << "\n";

        }
    }
    statusMsg->setText("arquivo salvo com sucesso");
}

void WindowGL::manhattan() //função do calculo dos potenciais e geração da trajetoria
{
    //declaração de variáveis
    Cell *finalcell,*startcell; //celulas associadas aos pontos finais e iniciais
    queue<pCell> wave; // fila para a frente de onda
    queue<pCell> pathCell; // caminho de células


    //aloca dinamicamente a matriz de ponteiros
    c=new Cell**[n];
    for(int i=0;i<n;i++) c[i]=new Cell*[m];

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            c[i][j]=new Cell(i,j,h);
        }
    }


    //associa os vizinhos do meio do domínio
    for(int i=1;i<(n-1);i++)
    {
        for(int j=1;j<(m-1);j++)
        {
            c[i][j]->setNeighbor(c[i][j+1],c[i][j-1],c[i+1][j],c[i-1][j]);
        }
    }
    //qd é na fronteira inválida apontar pra mesma Cell
    for(int i=1;i<(n-1);i++){
        c[i][0]->setNeighbor(c[i][1],c[i][0],c[i+1][0],c[i-1][0]);
        c[i][m-1]->setNeighbor(c[i][m-1],c[i][m-2],c[i+1][m-1],c[i-1][m-1]);
    }

    //qd é na fronteira inválida apontar pra mesma Cell
    for(int j=1;j<(m-1);j++){
        c[0][j]->setNeighbor(c[0][j+1],c[0][j-1],c[1][j],c[0][j]);
        c[n-1][j]->setNeighbor(c[n-1][j+1],c[n-1][j-1],c[n-1][j],c[n-2][j]);
    }

    //qd é na fronteira inválida apontar pra mesma Cell
    c[0][0]->setNeighbor(c[0][1],c[0][0],c[1][0],c[0][0]);
    c[0][m-1]->setNeighbor(c[0][m-1],c[0][m-2],c[1][m-1],c[0][m-1]);
    c[n-1][m-1]->setNeighbor(c[n-1][m-1],c[n-1][m-2],c[n-1][m-1],c[n-2][m-1]);
    c[n-1][0]->setNeighbor(c[n-1][1],c[n-1][0],c[n-1][0],c[n-2][0]);

    //testa a colisão das celulas com os polignos
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<P.size();k++) c[i][j]->collide(&P[k]);
        }

    }



    // associa à celula final e inicial correspondente na matriz c;
    finalcell=c[Cell(final,h).geti()][Cell(final,h).getj()];
    startcell=c[Cell(start,h).geti()][Cell(start,h).getj()];

    if(finalcell->getValue()==999 || startcell->getValue()==999)//testa se não está dentro do polígono
    {QMessageBox::critical(this,"Erro","Ponto dentro do poligono,especifique um válido",QMessageBox::Ok);
        return;
    }

    //inicio da frente de onda
    //seta 0 na posição final
    finalcell->setValue(0);
    wave.push(finalcell);

    int numFrontWave=1,k=1;//numero de elementos da frente e potencial associado k
    while(wave.size()!=0)
    {
        numFrontWave=wave.size();
        for(int i=0;i<numFrontWave;i++)
        {
            if(wave.front()->getRight()->getValue()==-1)
            {
                wave.push(wave.front()->getRight());
                wave.back()->setValue(k);
            }

            if(wave.front()->getLeft()->getValue()==-1)
            {
                wave.push(wave.front()->getLeft());
                wave.back()->setValue(k);
            }

            if(wave.front()->getTop()->getValue()==-1)
            {
                wave.push(wave.front()->getTop());
                wave.back()->setValue(k);
            }

            if(wave.front()->getBotton()->getValue()==-1)
            {
                wave.push(wave.front()->getBotton());
                wave.back()->setValue(k);
            }
            wave.pop();
        }
        k++;
    }

    if(startcell->getValue()==-1) //se não encontrou o começo, não tem caminho
    {QMessageBox::critical(this,"Erro","Não tem caminho",QMessageBox::Ok);
        return;
    }

    startValue=startcell->getValue(); //pega o potencial da primeira celula

    //inicia a pilha do caminho
    pathCell.push(startcell);

    while(pathCell.back()->getValue()!=0) // pesquisa a descida até encontrar o final
    {

        //ondem de pesquisa:direita,cima,baixo,esquerda
        if(pathCell.back()->getRight()->getValue()<pathCell.back()->getValue())
        {pathCell.push(pathCell.back()->getRight());}


        else if(pathCell.back()->getTop()->getValue()<pathCell.back()->getValue())
        {pathCell.push(pathCell.back()->getTop());}

        else if(pathCell.back()->getBotton()->getValue()<pathCell.back()->getValue())
        {pathCell.push(pathCell.back()->getBotton());}


        else if(pathCell.back()->getLeft()->getValue()<pathCell.back()->getValue())
        {pathCell.push(pathCell.back()->getLeft());}

    }

    path.clear();//limpa o caminho anterior
    //pega os pontos centrais do caminho
    while(pathCell.size()!=0){
        path.push_back(pathCell.front()->getCenter());
        pathCell.pop();
    }


}

