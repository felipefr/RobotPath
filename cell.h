//Objeto célula é responsável pela geração malha de manhattan
#include "mypolygon.h"

class Cell
{
      //dados
      private:
      MyPoint center; // ponto central
      int i,j; // posição na malha
      int value; // potencial
      float h;
      Cell *right,*left,*top,*botton; //celulas vizinhos
      public:
      //construtores
      Cell(int ic=0,int jc=0,float hc=1) {value=-1; i=ic; j=jc; h=hc; center.set(j*h+h/2,i*h+h/2);}
      Cell(MyPoint *q,float hc) {value=-1; h=hc; i=ceil(q->gety()/h-1); j=ceil(q->getx()/h-1); center.set(j*h+h/2,i*h+h/2);}
      bool collide(MyPolygon *p);//testa colisão com um poligono
      //métodos sets e gets
      int getValue() {return value;}
      void setValue(int v) {value=v;}
      int geti() {return i;}
      int getj() {return j;}
      void setNeighbor(Cell *r,Cell *l,Cell *t,Cell *b) {right=r; left=l; top=t; botton=b;}
      Cell *getRight() {return right;}
      Cell *getLeft() {return left;}
      Cell *getTop() {return top;}
      Cell *getBotton() {return botton;}
      MyPoint getCenter() {return center;}

       };
      

