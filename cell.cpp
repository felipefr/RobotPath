

#include "cell.h"

bool Cell::collide(MyPolygon *pol)
      {
      //se a celula estiveres fora de "moldura" do poligono retorna
      if(pol->getxmin()>(center.getx()+h)) return 0;
      if(pol->getxmax()<(center.getx()-h)) return 0;
      if(pol->getymin()>(center.gety()+h)) return 0;
      if(pol->getymax()<(center.gety()-h)) return 0;

      //testa a colisão de cada vertice da celula a do centro
      if(pol->isInside(MyPoint(j*h,i*h))) {value=999; return 1;}
      if(pol->isInside(MyPoint((j+1)*h,i*h))) {value=999; return 1;}
      if(pol->isInside(MyPoint((j+1)*h,(i+1)*h))) {value=999; return 1;}
      if(pol->isInside(MyPoint(j*h,(i+1)*h))) {value=999; return 1;}
      if(pol->isInside(center)) {value=999; return 1;}


      return 0;
           }
