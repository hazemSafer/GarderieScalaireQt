#include "eleve_ui.h"
#include "ui_eleve_ui.h"
#include "Eleve.h"
#include "mainwindow.h"

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QIntValidator>
#include<QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

Eleve_ui::Eleve_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Eleve_ui)
{
    ui->setupUi(this);
    ui->iDLineEdit->setValidator(new QIntValidator(0, 999999, this)); // only input int
    ui->prNomLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input int
    ui->nomLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input alphabetic characters
    ui->niveauLineEdit->setValidator(new QIntValidator(0, 999999, this)); // only input int
    ui->responsableLegaleLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input alphabetic characters
    ui->tableView->setModel(Eleve::afficher());

}

Eleve_ui::~Eleve_ui()
{
    delete ui;
}

void Eleve_ui::on_pushButton_back_clicked()
{
    MainWindow *MainWindowDialog = new MainWindow();
    MainWindowDialog->show();

    close();
}


void Eleve_ui::on_pushButton_ajout_clicked()
{
    // Get input values
    int id = ui->iDLineEdit->text().toInt();
    QString prenom = ui->prNomLineEdit->text();
    QString nom = ui->nomLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QDate date = ui->dateDeNaissanceDateEdit->date();
    int niveau = ui->niveauLineEdit->text().toInt();
    QString respLegal = ui->responsableLegaleLineEdit->text();

    // Input validation
    if (id <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Eleve non ajouté. ID invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (niveau <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Eleve non ajouté. Niveau invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (prenom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Eleve non ajouté. Prénom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Eleve non ajouté. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (adresse.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Eleve non ajouté. Adresse invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (respLegal.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Eleve non ajouté. Responsable Legal invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }


    Eleve existing = Eleve::findById(id);
    if(existing.getId() != 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Eleve non ajouté. ID déjà existant.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    // Create a new Medicament object and add it to the database
    Eleve e(id, prenom, nom, date, adresse, niveau, respLegal);

    if(e.ajouter())
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Elève ajouté.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->tableView->setModel(Eleve::afficher());
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Elève non ajouté.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}


void Eleve_ui::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_3->text().toInt();

    Eleve e = Eleve::findById(id);

    if (e.getId() != 0) {
        if (Eleve::supprimer(id)) {
            QMessageBox::information(nullptr, QObject::tr("Supprime"),
                        QObject::tr("Supprimé.\n"
                                    "Cliquer quitter."), QMessageBox::Cancel);
            ui->lineEdit_3->setText("");
            ui->tableView->setModel(Eleve::afficher());
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Supprime"),
                        QObject::tr("Elève pas supprimé.\n"
                                    "Cliquer quitter."), QMessageBox::Cancel);
        }
    } else {

        QMessageBox::warning(nullptr, QObject::tr("Supprime"),
                    QObject::tr("L'Elève avec ce ID n'existe pas.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}

void Eleve_ui::on_pushButton_refresh_clicked()
{
    ui->tableView->setModel(Eleve::afficher());
}

void Eleve_ui::on_tableView_activated(const QModelIndex &index)
{

    // Get the selected row data
    QAbstractItemModel *model = ui->tableView->model();
    int id = model->data(model->index(index.row(), 0)).toInt();
    QString prenom = model->data(model->index(index.row(), 1)).toString();
    QString nom = model->data(model->index(index.row(), 2)).toString();
    QDate date = model->data(model->index(index.row(), 3)).toDate();
    QString adresse = model->data(model->index(index.row(), 4)).toString();
    int niveau = model->data(model->index(index.row(), 5)).toInt();
    QString respLegal = model->data(model->index(index.row(), 6)).toString();

    // Populate the add section fields
    ui->iDLineEdit->setText(QString::number(id));
    ui->lineEdit_pdf->setText(QString::number(id));
    ui->prNomLineEdit->setText(prenom);
    ui->nomLineEdit->setText(nom);
    ui->dateDeNaissanceDateEdit->setDate(date);
    ui->adresseLineEdit->setText(adresse);
    ui->niveauLineEdit->setText(QString::number(niveau));
    ui->responsableLegaleLineEdit->setText(respLegal);

}

void Eleve_ui::on_pushButton_modifier_clicked()
{
    int id = ui->iDLineEdit->text().toInt();
    QString prenom = ui->prNomLineEdit->text();
    QString nom = ui->nomLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QDate date = ui->dateDeNaissanceDateEdit->date();
    int niveau = ui->niveauLineEdit->text().toInt();
    QString respLegal = ui->responsableLegaleLineEdit->text();

    if (id <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non Modifie. ID invalid.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (niveau <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non Modifie. Niveau invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (prenom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non Modifie. Prénom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }
    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non Modifie. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (adresse.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non Modifie. Adresse invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (respLegal.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non Modifie. Reponsable Legal invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }




    Eleve existing = Eleve::findById(id);
    if(existing.getId() == 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non modifier car il n'existe pas."), QMessageBox::Cancel);
        return;
    }

    Eleve e(id, prenom, nom, date, adresse, niveau, respLegal);

    if(e.modifier()) {
        QMessageBox::information(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->tableView->setModel(Eleve::afficher());
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Modifier élève"),
                    QObject::tr("Elève non modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}

void Eleve_ui::on_pushButton_pdf_clicked()
{
    int id = ui->lineEdit_pdf->text().toInt();
    Eleve e = Eleve::findById(id);
    if(e.getId() != 0) {
        Eleve::imprimer(id);
        QMessageBox::information(nullptr, QObject::tr("PDF File created"),
                    QObject::tr("PDF File created.\n"
                                "Check your debug directory."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::warning(this, "Student Not Found", "The specified Student was not found in the database.");
    }
}


void Eleve_ui::on_radioButton_clicked()
{

    if(ui->comboBox->currentText() != "Choisir")
  ui->tableView->setModel(Eleve::trie("ASC",ui->comboBox->currentText()));
  else  ui->tableView->setModel(Eleve::afficher());
}

void Eleve_ui::on_radioButton_2_clicked()
{
    if(ui->comboBox->currentText() != "Choisir")
  ui->tableView->setModel(Eleve::trie("DESC",ui->comboBox->currentText()));
  else  ui->tableView->setModel(Eleve::afficher());
}

void Eleve_ui::on_search_field_textChanged(const QString &arg1)
{
    QString searchText = arg1.trimmed(); // Remove leading/trailing whitespaces

    // Check if the search text is empty, and if so, display the full list
    if (searchText.isEmpty()) {
        ui->tableView->setModel(Eleve::afficher());
        return;
    }

    // Attempt to convert the search text to an integer (ID search)
    bool isNumeric;
    int searchId = searchText.toInt(&isNumeric);

    // Use QSqlQuery to perform a more complex search query
    QSqlQuery query;
    if (isNumeric) {
        query.prepare("SELECT * FROM Eleve WHERE id = :id OR prenom LIKE :search OR nom LIKE :search");
        query.bindValue(":id", searchId);
    } else {
        query.prepare("SELECT * FROM Eleve WHERE prenom LIKE :search OR nom LIKE :search");
    }

    query.bindValue(":search", "%" + searchText + "%"); // Search for partial matches

    if (query.exec()) {
        QStandardItemModel *newModel = new QStandardItemModel(0, 7, this);
        newModel->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
        newModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Prenom")));
        newModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Nom")));
        newModel->setHorizontalHeaderItem(3, new QStandardItem(QString("Date de Naissance")));
        newModel->setHorizontalHeaderItem(4, new QStandardItem(QString("Adresse")));
        newModel->setHorizontalHeaderItem(5, new QStandardItem(QString("Niveau")));
        newModel->setHorizontalHeaderItem(6, new QStandardItem(QString("Responsable Légal")));

        while (query.next()) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(query.value("ID").toString()));
            rowItems.append(new QStandardItem(query.value("Prenom").toString()));
            rowItems.append(new QStandardItem(query.value("Nom").toString()));
            rowItems.append(new QStandardItem(query.value("DateNaissance").toString()));
            rowItems.append(new QStandardItem(query.value("Adresse").toString()));
            rowItems.append(new QStandardItem(query.value("Niveau").toString()));
            rowItems.append(new QStandardItem(query.value("ResponsableLegal").toString()));
            newModel->appendRow(rowItems);
        }

        ui->tableView->setModel(newModel);
        ui->tableView->show();
    } else {
        // Handle the case where the query execution fails
        qDebug() << "Query execution failed: " << query.lastError();
    }
}


void Eleve_ui::on_pushButton_stats_clicked()
{
    // Créez un modèle de données pour le graphique circulaire
        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

        // Ajoutez des tranches (slices) pour chaque groupe d'âge
        // Vous devrez obtenir les données de votre base de données ici
        // Par exemple, supposons que vous ayez une fonction "getAgeDistribution()" qui renvoie un QHash<QString, int>
        QHash<QString, int> Distribution = Eleve::getNiveauDistribution();

        for (const QString &Group : Distribution.keys()) {
            QtCharts::QPieSlice *slice = series->append(Group, Distribution.value(Group));
            // Vous pouvez personnaliser l'apparence de chaque tranche si vous le souhaitez
        }

        // Créez un graphique circulaire et configurez-le
        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition par Niveau");

        // Créez une vue de graphique pour afficher le graphique circulaire
        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Affichez la vue du graphique dans une nouvelle fenêtre
        QMainWindow *chartWindow = new QMainWindow(this);
        chartWindow->setCentralWidget(chartView);
        chartWindow->resize(800, 600);
        chartWindow->show();
}


