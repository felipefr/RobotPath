/*
DEPARTAMENTO DE ENGENHARIA MECANICA
PROF: PABLO JAVIER ALSINA DISCIPLINA:INTRODUCAO A ROBOTICA
ALUNOS: FELIPE FIGUEREDO  e GERALDO REBOUCAS
PROGRAMA:ROBOTPATH USANDO MÉTODO MANHATTAN, INTEGRANDO QT E OPENGL

Esta classe será responsável pela janela openGl em uma aplicação Qt,
no campo protected temos os metodos virtuais da classe derivada, PaintGL,initializeGL,resizeGL,mousePressEvent,mouseMoveEvent e wheelEvent
estes são funções semelhantes às funções conhecidas do openGL .
Há slots na classe, alguns destes sets, e outros de controle como start e restart.

Em InitializeGL estao operações como as realizadas na classica "init" no openGl. Em paintGL , estao operações de renderização dos objetos na tela
como as função callback display em openGL. As Funçoes mousePressEvent,mouseMoveEvent,wheelEvent, são funçoes que capturam
movimentos no mouse,como as do openGl.
*/


#ifndef HEAT_GL_H
#define HEAT_GL_H
#include <QGLWidget>  // responsável pela janela GL
#include <QTimer> // responsável pela animação
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
void manhattan(); //cálculos de potencial e geração de trajetoria por Manhattan
void read(QString t); // ler um arquivo
void save(QString t); // salva arquivo como está na tela
//funções callback do openGL
void initializeGL(); //Inialicializa os dados
void paintGL(); //Mostra na tela os dados correntes
void mousePressEvent(QMouseEvent *event); //função callback para os botoes do mouse
void mouseMoveEvent(QMouseEvent *event); //função callback para o movimento do cursor

//métodos set
void setm(int m) {this->m=m;} 
void setn(int n) {this->n=n;}
void seth(float h) {this->h=h;}
void setpi(float pix,float piy) {this->start->set(pix,piy);}
void setpf(float pfx,float pfy) {this->final->set(pfx,pfy);}
//dados publicos
QLabel *statusMsg; //mensagem da barra de status
QLabel *mousePosition; //mensagem da barra de status
public slots:
void updateGLWidget() {manhattan(); glInit(); glDraw();} //slot de atualização do gráfico
//associa os estados da checkbox
void setPotentialState(int v) {showPotential=v; glDraw();} 
void setPathState(int v) {showPath=v; glDraw();}
void setGridState(int v) {showGrid=v; glDraw();}
void undo(){P.pop_back(); updateGLWidget();}
//dados
private:
bool insert; //se está capturando pontos (botao direito)
bool showPath,showPotential,showGrid; //refentes ao checkboxes
vector<MyPolygon> P; //vetor dos poligonos
vector<MyPoint> path; // vetor de pontos que dá o caminho
MyPoint *start,*final; // ponto inicial e final
vector<MyPoint> temp; // vetor auxiliar para capturar pontos
int m,n; // n linhas e m colunas
float h; // espaçamento da célula
Cell ***c; // Matriz de ponteiros de celulas,ponteiros para serem alocado dinamicamente
int startValue; //valor da celula do começo,usado para normalizar a cor
};

 #endif
