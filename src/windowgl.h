/*
DEPARTAMENTO DE ENGENHARIA MECANICA
PROF: PABLO JAVIER ALSINA DISCIPLINA:INTRODUCAO A ROBOTICA
ALUNOS: FELIPE FIGUEREDO  e GERALDO REBOUCAS
PROGRAMA:ROBOTPATH USANDO M�TODO MANHATTAN, INTEGRANDO QT E OPENGL

Esta classe ser� respons�vel pela janela openGl em uma aplica��o Qt,
no campo protected temos os metodos virtuais da classe derivada, PaintGL,initializeGL,resizeGL,mousePressEvent,mouseMoveEvent e wheelEvent
estes s�o fun��es semelhantes �s fun��es conhecidas do openGL .
H� slots na classe, alguns destes sets, e outros de controle como start e restart.

Em InitializeGL estao opera��es como as realizadas na classica "init" no openGl. Em paintGL , estao opera��es de renderiza��o dos objetos na tela
como as fun��o callback display em openGL. As Fun�oes mousePressEvent,mouseMoveEvent,wheelEvent, s�o fun�oes que capturam
movimentos no mouse,como as do openGl.
*/


#ifndef HEAT_GL_H
#define HEAT_GL_H
#include <QGLWidget>  // respons�vel pela janela GL
#include <QTimer> // respons�vel pela anima��o
#include <QMouseEvent> // captura os movimentos e botoes do mouse
#include "cell.h"
#include <fstream>
#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <queue>
#include <vector>
#include <cmath>


typedef Cell *pCell;

class WindowGL : public QGLWidget
{
Q_OBJECT

public:
WindowGL(QWidget * ancestral=0); // construtor
void manhattan(); //c�lculos de potencial e gera��o de trajetoria por Manhattan
void read(QString t); // ler um arquivo
void save(QString t); // salva arquivo como est� na tela
//fun��es callback do openGL
void initializeGL(); //Inialicializa os dados
void paintGL(); //Mostra na tela os dados correntes
void mousePressEvent(QMouseEvent *event); //fun��o callback para os botoes do mouse
void mouseMoveEvent(QMouseEvent *event); //fun��o callback para o movimento do cursor

//m�todos set
void setm(int m) {this->m=m;} 
void setn(int n) {this->n=n;}
void seth(float h) {this->h=h;}
void setpi(float pix,float piy) {this->start->set(pix,piy);}
void setpf(float pfx,float pfy) {this->final->set(pfx,pfy);}
//dados publicos
QLabel *statusMsg; //mensagem da barra de status
QLabel *mousePosition; //mensagem da barra de status
public slots:
void updateGLWidget() {manhattan(); glInit(); glDraw();} //slot de atualiza��o do gr�fico
//associa os estados da checkbox
void setPotentialState(int v) {showPotential=v; glDraw();} 
void setPathState(int v) {showPath=v; glDraw();}
void setGridState(int v) {showGrid=v; glDraw();}
void undo(){P.pop_back(); updateGLWidget();}
//dados
private:
bool insert; //se est� capturando pontos (botao direito)
bool showPath,showPotential,showGrid; //refentes ao checkboxes
vector<MyPolygon> P; //vetor dos poligonos
vector<MyPoint> path; // vetor de pontos que d� o caminho
MyPoint *start,*final; // ponto inicial e final
vector<MyPoint> temp; // vetor auxiliar para capturar pontos
int m,n; // n linhas e m colunas
float h; // espa�amento da c�lula
Cell ***c; // Matriz de ponteiros de celulas,ponteiros para serem alocado dinamicamente
int startValue; //valor da celula do come�o,usado para normalizar a cor
};

 #endif
