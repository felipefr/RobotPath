#include <QtGui>
#include "windowgl.h"
#include "mainwindow.h"
#include <fstream.h> //manipulação de arquivos



MainWindow::MainWindow()
{
 windowgl=new WindowGL;

double p=QInputDialog::getDouble(this,"pega numero","digite numero");
qDebug() << p ;
createActions(); // cria todas açoes
createToolbars(); // cria todas toolbars
createMenus(); // cria todos os menus

this->statusBar()->addWidget(windowgl->statusMsg);
this->statusBar()->addWidget(windowgl->mousePosition);

setCentralWidget(windowgl); // escolhe a widget central

}

void MainWindow::updateWindowGL() // funçao responsavel por setar os dados configurados na janela openGL
{
windowgl->setn(row->value());
windowgl->setm(col->value());
windowgl->seth(cellSize->value());
windowgl->setpi(pix->value(),piy->value());
windowgl->setpf(pfx->value(),pfy->value());
windowgl->updateGLWidget();
}

void MainWindow::restart() // funçao por reiniciar
{
this->windowgl->read("default.txt");
}



void MainWindow::confirmExit() // funçao responsavel pela confirmção pra sair
{

    int r = QMessageBox::warning(this, tr("Confirmação"),
         tr("Você Realmente deseja deixar o programa? Lembre-se de salvar suas alterações"),
         QMessageBox::Yes,
         QMessageBox::Save,
         QMessageBox::Cancel | QMessageBox::Escape);
     
     if (r==QMessageBox::Save) {this->saveFile(); qApp->quit();} // opção de salvar
     if (r==QMessageBox::Yes) qApp->quit(); // quando sim,sai do programa

 }

void MainWindow::aboutWindow() // esta janela é onde é mostrada as informações sobre os criadores
{
   
     QMessageBox::about(this,tr("Sobre os Criadores"),
     tr("Titulo: RobotPath - aplicativo que gera a trajetória de um robo usando o método Manhattan\n"
     "Autor: Felipe Figueredo,Geraldo Rebolças,Edmundo 'Karaubas',Douglas\n"
     " Prof: Prof.Dr. Pablo Javier Alsina \n"
     " Disciplina: Introdução a robótica \n"
     " Curso:Engenharia da Computação/Mecânica \n"
     " e-mail:felipemech@gmail.com \n"));

                        
     }

void MainWindow::openFile() // Abre o dialogo de abertura de arquivos
{
//atribui a filename a url do arquivo
QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir Configuracao"),
                                                         "/home",tr("ConfigFile (*.cfg *.txt)"));

//se o caminho não for nulo inicia o processo de cópia de informações
if(fileName!=NULL) windowgl->read(fileName);


}

void MainWindow::saveFile() // Abre o dialogo de Salvar arquivo
{
    //atribui a filename a url do arquivo
    QString fileName = QFileDialog::getSaveFileName(this,tr("Salvar Congiguracao"),"/home",tr("ConfigFile (*.cfg *.txt)"));

    //se o caminho não for nulo inicia o processo de armazenamento em um arquivo
    if(fileName!=NULL) windowgl->save(fileName);
}



void MainWindow::createToolbars() // define as toolbars
{
     //top
top=new QToolBar;
top->setFloatable(0); // nao é flutuante nem movível ,ou seja, é fixa
top->setMovable(0);
top->setOrientation(Qt::Horizontal); 
top->addAction(newConf); // adciona as widget
top->addSeparator();
top->addAction(exit);
top->addSeparator();
top->addAction(start);
top->addSeparator();
top->addSeparator();
top->addAction(open);
top->addSeparator();
top->addAction(save);
top->addSeparator();
top->addAction(undo);
addToolBar(Qt::TopToolBarArea,top); // adciona toolbar na posiçao TopToolBarArea 

row=new QSpinBox; rowText=new QLabel("numero de linhas");
row->setRange(0,100);
row->setValue(20);

col=new QSpinBox; colText=new QLabel("numero de colunas");
col->setRange(0,100);
col->setValue(20);

cellSize=new QDoubleSpinBox; cellSizeText=new QLabel("tamanho da celula");
cellSize->setRange(0,3);
cellSize->setValue(1);

pix=new QDoubleSpinBox; pixText=new QLabel("Ponto incial x");
pix->setRange(0,100);
pix->setValue(1);

piy=new QDoubleSpinBox; piyText=new QLabel("Ponto incial y");
piy->setRange(0,100);
piy->setValue(1);

pfx=new QDoubleSpinBox; pfxText=new QLabel("Ponto final x");
pfx->setRange(0,100);
pfx->setValue(19);

pfy=new QDoubleSpinBox; pfyText=new QLabel("Ponto final y");
pfy->setRange(0,100);
pfy->setValue(19);

update=new QPushButton("atualizar");
connect(update,SIGNAL(clicked()),this,SLOT(updateWindowGL()));

//Inicialização das CheckBox
showPotential=new QCheckBox("Mostra Potencial");
showPotential->setTristate(FALSE); // não marcado
showPath=new QCheckBox("Mosta caminho");
showPath->setTristate(FALSE); //não marcado
showGrid=new QCheckBox("Mosta Grade");
showGrid->setTristate(FALSE); //não marcado

//faz as conexões dos checkboxes com as janelas
connect(showPotential,SIGNAL(stateChanged(int)),this->windowgl,SLOT(setPotentialState(int)));
connect(showPath,SIGNAL(stateChanged(int)),this->windowgl,SLOT(setPathState(int)));
connect(showGrid,SIGNAL(stateChanged(int)),this->windowgl,SLOT(setGridState(int)));


//left
left=new QToolBar;
left->setFloatable(1);// toolbar não fixa e é movível
left->setMovable(1);
left->setOrientation(Qt::Vertical);
// adciona as widgets
left->addWidget(rowText); left->addWidget(row);
left->addWidget(colText); left->addWidget(col);
left->addWidget(cellSizeText); left->addWidget(cellSize);
left->addWidget(pixText); left->addWidget(pix);
left->addWidget(piyText); left->addWidget(piy);
left->addWidget(pfxText); left->addWidget(pfx);
left->addWidget(pfyText); left->addWidget(pfy);
left->addWidget(update);
left->addWidget(showPotential);
left->addWidget(showPath);
left->addWidget(showGrid);

addToolBar(Qt::LeftToolBarArea,left); // Fixa-o na LeftToolBarArea       
     
     }
     
     
void MainWindow::createMenus() //Responsável pela definição dos Menus
{
// menu file     
file=new QMenu(tr("&Arquivo"));
menuBar()->addMenu(file);
file->addAction(save);
file->addAction(open);
file->addSeparator();
file->addAction(newConf);
file->addAction(undo);
file->addSeparator();
file->addAction(exit);

     
// menu help
help=new QMenu(tr("&Ajuda"));
menuBar()->addMenu(help);
help->addAction(about);
     
     }
     
     
void MainWindow::createActions() // Função responsável pelas definiçoes das ações
{

//newConf
newConf=new QAction(tr("RECOMEÇAR"),this);
newConf->setShortcut(tr("Ctrl+N"));
newConf->setIcon(QIcon(":/images/filenew.png"));
newConf->setStatusTip(tr("Recomeçar"));
connect(newConf,SIGNAL(triggered()),this,SLOT(restart()));

//exit
exit=new QAction(tr("SAIR"),this);
exit->setShortcut(tr("Esc"));
exit->setIcon(QIcon(":/images/exit.png"));
exit->setStatusTip(tr("Sair do Aplicativo"));
connect(exit, SIGNAL(triggered()), this, SLOT(confirmExit())); //conecta com a janela GL

//about
about=new QAction(tr("SOBRE"),this);
about->setStatusTip(tr("Informações sobre os criadores"));
connect(about,SIGNAL(triggered()),this,SLOT(aboutWindow())); //conecta com a janela GL

//start
start=new QAction(tr("START"),this);
start->setShortcut(tr("Ctrl+C"));
start->setIcon(QIcon(":/images/start.png"));
start->setStatusTip(tr("calcular"));
connect(start,SIGNAL(triggered()),this->windowgl,SLOT(updateGLWidget())); //conecta com a janela GL

//open
open = new QAction(tr("Abrir"),this);
open->setShortcut(tr("Ctrl+O"));
open->setIcon(QIcon(":/images/folder.png"));
open->setStatusTip(tr("Abrir"));
connect(open,SIGNAL(triggered()),this,SLOT(openFile()));

//save
save = new QAction(tr("Salvar"),this);
save->setShortcut(tr("Ctrl+S"));
save->setIcon(QIcon(":/images/filesave.png"));
save->setStatusTip(tr("Salvar"));
connect(save,SIGNAL(triggered()),this,SLOT(saveFile()));

//undo
undo = new QAction(tr("Desfazer"),this);
undo->setShortcut(tr("Ctrl+B"));
undo->setIcon(QIcon(":/images/undo.PNG"));
undo->setStatusTip(tr("Desfazer"));
connect(undo,SIGNAL(triggered()),this->windowgl,SLOT(undo()));


     }




