//Objeto MyPolygon é responsável por tratar os poligonos do programa,sendo que contem n+1 pontos,onde
//é o número de vertices,ou seja,o ultimo vertice é igual ao primeiro

#include "mypoint.h"
#include <math.h>

class MyPolygon
{
    //dados
      private:
      MyPoint *p;
      int np;
      float ymax,ymin,xmin,xmax; //definição de uma "moldura" do poligono
      
      public:
      
      MyPolygon(int n=1); // construtor
      void add(MyPoint a,int i); //adiciona ponto na posição i
      bool isInside(MyPoint q); // testa se o ponto q está dentro do poligono
      //métodos gets
      float getymax(){return ymax;}
      float getymin(){return ymin;}
      float getxmax(){return xmax;}
      float getxmin(){return xmin;}
      int getnp(){return np;}
      MyPoint getpoint(int i) {return p[i];}

      
      };


