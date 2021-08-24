/* 
DEPARTAMENTO DE ENGENHARIA MECANICA
PROF: PABLO JAVIER ALSINA DISCIPLINA:INTRODUCAO A ROBOTICA
ALUNOS: FELIPE FIGUEREDO  e GERALDO REBOUCAS
PROGRAMA:ROBOTPATH USANDO MÉTODO MANHATTAN, INTEGRANDO QT E OPENGL

Este ó arquivo do programa principal, na verdade ele se resume na instaciação do objeto window da 
classe MainWindow que já tem toda a interface já configurada.
*/

#include <QApplication>

#include "mainwindow.h"

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     MainWindow window;
     window.setStyle(QApplication::setStyle("plastique")); // altera o estilo da janela
     window.show(); 
     return app.exec();
 } 
