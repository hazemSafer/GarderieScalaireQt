#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eleve_ui.h"
#include "enseignant_ui.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openEleveUI);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::openEnseignantUI);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openEleveUI()
{
    Eleve_ui *eleveDialog = new Eleve_ui();
    eleveDialog->show();

    close();
}

void MainWindow::openEnseignantUI()
{
    Enseignant_ui *enseignantDialog = new Enseignant_ui();
    enseignantDialog->show();

    close();
}
