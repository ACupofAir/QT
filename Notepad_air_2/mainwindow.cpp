#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
   currentFile.clear();
   ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
   QString filename = QFileDialog::getOpenFileName(this, "Open the file");
   QFile file(filename);
   currentFile = filename;
   if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
       return;
   }
   setWindowTitle(filename);
   QTextStream in(&file);
   QString text = in.readAll();
   ui->textEdit->setText(text);
   file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
   if(!file.open(QFile::WriteOnly | QFile::Text)) {
       QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
       return;
   }
   currentFile = fileName;
   setWindowTitle(fileName);
   QTextStream out(&file);
   QString text = ui->textEdit->toPlainText();
   out << text;
   file.close();

}

void MainWindow::on_actionExit_triggered()
{
   QApplication::exit();
}

void MainWindow::on_actionCopy_triggered()
{
   ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
   ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
   ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
   ui->textEdit->redo();
}
