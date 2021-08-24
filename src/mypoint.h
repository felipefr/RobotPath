//Objeto MyPoint é responsável com manipular os pontos dos programas
class MyPoint
{
      private:
      const static float e;
      float x,y;
      public:
      MyPoint(float a=0,float b=0) {x=a; y=b;}
      void set(float a,float b) {x=a;y=b;}
      float getx () {return x;}
      float gety () {return y;}
         
      };
