#include "MyPolygon.h"

MyPolygon::MyPolygon(int n)
      {
      np=n;
      p=new MyPoint[np+1];
      ymax=0;
      ymin=99999;
      xmax=0;
      xmin=99999;
      }


void MyPolygon::add(MyPoint a,int i)
{
     if(i<np){

     //classifica maximos e minimos
     if(a.getx()>xmax) xmax=a.getx();
     if(a.getx()<xmin) xmin=a.getx();
     if(a.gety()>ymax) ymax=a.gety();
     if(a.gety()<ymin) ymin=a.gety();

     if(i==0) { p[i]=a; p[np]=a; } //inicio igual ao fim
     else {p[i]=a;}
     }

     }

bool MyPolygon::isInside(MyPoint q)
{
     float d0=10000; //valor grande
     float a,b,c,d;

     //algoritmo de teste de colisão
     for(int k=0;k<np;k++)
     {
     a=p[k].gety()-p[k+1].gety();
     b=p[k+1].getx()-p[k].getx();
     c=p[k].getx()*p[k+1].gety()-p[k].gety()*p[k+1].getx();
     d=(a*q.getx()+b*q.gety()+c)/sqrt(a*a+b*b);
     if(d<d0) d0=d;
                      }

     if (d0>=0) return 1; // conservador no contorno
     else return 0;

     }

