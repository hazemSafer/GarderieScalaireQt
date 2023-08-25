#include "eleve_ui.h"
#include "ui_eleve_ui.h"

Eleve_ui::Eleve_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Eleve_ui)
{
    ui->setupUi(this);
}

Eleve_ui::~Eleve_ui()
{
    delete ui;
}
