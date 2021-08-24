/*
DEPARTAMENTO DE ENGENHARIA MECANICA
PROF: PABLO JAVIER ALSINA DISCIPLINA:INTRODUCAO A ROBOTICA
ALUNOS: FELIPE FIGUEREDO  e GERALDO REBOUCAS
PROGRAMA:ROBOTPATH USANDO M�TODO MANHATTAN, INTEGRANDO QT E OPENGL

A classe MainWindow � derivada da classe QMainWindow, ela configura os menus,toolbars e outras Widgets existentes, bem como
a diagrama��o da janela.
Esta Classe possui apenas dois slots,confirmExit e aboutWindow que definem as caixas de dialogo.
H� Apenas um construtor o default. H� tr�s fun�oes private createToolbars,createMenus,createActions que mudularizam as defini�oes
dos toolbars, menus e actions.
Em dados , temos um objeto do tipo WindowGL, que � exatamente a janela openGL no Qt, Os objetos de QMenu,QToolBar,QAction,AdjustSlider
Este arquivo � a implement��o das fun��es da classe MainWindow , como a classe � grande detalhes
da implementa��o est� resevado para os coment�rios no corpo do codigo.

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMdiArea>
#include "windowgl.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QInputDialog>
#include <QCheckBox>
#include <QPushButton>

class MainWindow : public QMainWindow
{
Q_OBJECT
public:

MainWindow(); // Construtor

public slots:
void confirmExit();
void aboutWindow();
void saveFile();
void openFile();
void restart();
void updateWindowGL();

private:
void createToolbars(); //cria todos os toolbars
void createMenus(); //cria todos os menus
void createActions(); // cria todas as a��es
//Widgets
WindowGL *windowgl;
QAction *newConf,*about,*exit,*start,*open,*save,*undo;
QMenu *file,*help;
QToolBar *top,*left;
QSpinBox *row,*col;
QDoubleSpinBox *cellSize,*pix,*piy,*pfx,*pfy;
QLabel *rowText,*colText;
QLabel *cellSizeText,*pixText,*piyText,*pfxText,*pfyText;
QPushButton *update;
QCheckBox *showPotential,*showPath,*showGrid;


};
#endif

