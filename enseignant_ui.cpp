#include "enseignant_ui.h"
#include "ui_enseignant_ui.h"
#include "Enseignant.h"
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


Enseignant_ui::Enseignant_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Enseignant_ui)
{
    ui->setupUi(this);
    ui->iDLineEdit->setValidator(new QIntValidator(0, 999999, this)); // only input int
    ui->prNomLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input int
    ui->nomLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input alphabetic characters
    ui->salaireLineEdit->setValidator(new QDoubleValidator(0, 99999999.99, 2, this)); // only input int
    ui->ancienneteLineEdit->setValidator(new QIntValidator(0, 999999, this)); // only input alphabetic characters
    ui->tableView->setModel(Enseignant::afficher());

}

Enseignant_ui::~Enseignant_ui()
{
    delete ui;
}

void Enseignant_ui::on_pushButton_back_clicked()
{
    MainWindow *MainWindowDialog = new MainWindow();
    MainWindowDialog->show();

    close();
}

void Enseignant_ui::on_pushButton_ajout_clicked()
{
    // Get input values
    int id = ui->iDLineEdit->text().toInt();
    QString prenom = ui->prNomLineEdit->text();
    QString nom = ui->nomLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QDate date = ui->dateDeNaissanceDateEdit->date();
    double salaire= ui->salaireLineEdit->text().toDouble();
    int anciennete = ui->ancienneteLineEdit->text().toInt();

    // Input validation
    if (id <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Enseignant non ajouté. ID invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (salaire <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Enseignant non ajouté. Salaire invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (prenom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Enseignant non ajouté. Prénom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Enseignant non ajouté. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (adresse.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Enseignant non ajouté. Adresse invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (anciennete <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout élève"),
                    QObject::tr("Enseignant non ajouté. Anciennete invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }




    Enseignant existing = Enseignant::findById(id);
    if(existing.getId() != 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajout enseignant"),
                    QObject::tr("Enseignant non ajouté. ID déjà existant.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    Enseignant e(id, prenom, nom, date, adresse, salaire, anciennete);

    if(e.ajouter())
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout enseignant"),
                    QObject::tr("Enseignant ajouté.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->tableView->setModel(Enseignant::afficher());
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Ajout enseignant"),
                    QObject::tr("Enseignant non ajouté.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}


void Enseignant_ui::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_3->text().toInt();

    Enseignant e = Enseignant::findById(id);

    if (e.getId() != 0) {
        if (Enseignant::supprimer(id)) {
            QMessageBox::information(nullptr, QObject::tr("Supprime"),
                        QObject::tr("Supprimé.\n"
                                    "Cliquer quitter."), QMessageBox::Cancel);
            ui->lineEdit_3->setText("");
            ui->tableView->setModel(Enseignant::afficher());
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Supprime"),
                        QObject::tr("Enseignant pas supprimé.\n"
                                    "Cliquer quitter."), QMessageBox::Cancel);
        }
    } else {

        QMessageBox::warning(nullptr, QObject::tr("Supprime"),
                    QObject::tr("L'enseignant avec ce ID n'existe pas.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}

void Enseignant_ui::on_pushButton_refresh_clicked()
{
    ui->tableView->setModel(Enseignant::afficher());
}

void Enseignant_ui::on_tableView_activated(const QModelIndex &index)
{

    // Get the selected row data
    QAbstractItemModel *model = ui->tableView->model();
    int id = model->data(model->index(index.row(), 0)).toInt();
    QString prenom = model->data(model->index(index.row(), 1)).toString();
    QString nom = model->data(model->index(index.row(), 2)).toString();
    QDate date = model->data(model->index(index.row(), 3)).toDate();
    QString adresse = model->data(model->index(index.row(), 4)).toString();
    double salaire = model->data(model->index(index.row(), 5)).toDouble();
    int anciennete = model->data(model->index(index.row(), 6)).toInt();

    // Populate the add section fields
    ui->iDLineEdit->setText(QString::number(id));
    ui->lineEdit_pdf->setText(QString::number(id));
    ui->prNomLineEdit->setText(prenom);
    ui->nomLineEdit->setText(nom);
    ui->dateDeNaissanceDateEdit->setDate(date);
    ui->adresseLineEdit->setText(adresse);
    ui->salaireLineEdit->setText(QString::number(salaire));
    ui->ancienneteLineEdit->setText(QString::number(anciennete));

}

void Enseignant_ui::on_pushButton_modifier_clicked()
{
    int id = ui->iDLineEdit->text().toInt();
    QString prenom = ui->prNomLineEdit->text();
    QString nom = ui->nomLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QDate date = ui->dateDeNaissanceDateEdit->date();
    double salaire = ui->salaireLineEdit->text().toDouble();
    int anciennete = ui->ancienneteLineEdit->text().toInt();

    if (id <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non Modifie. ID invalid.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (salaire <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non Modifie. Salaire invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (prenom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non Modifie. Prénom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }
    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non Modifie. Nom invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (adresse.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non Modifie. Adresse invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }

    if (anciennete <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non Modifie. Anciennete invalide.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        return;
    }





    Enseignant existing = Enseignant::findById(id);
    if(existing.getId() == 0) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non modifier car il n'existe pas."), QMessageBox::Cancel);
        return;
    }

    Enseignant e(id, prenom, nom, date, adresse, salaire, anciennete);

    if(e.modifier()) {
        QMessageBox::information(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
        ui->tableView->setModel(Enseignant::afficher());
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Modifier enseignant"),
                    QObject::tr("Enseignant non modifié.\n"
                                "Cliquer quitter."), QMessageBox::Cancel);
    }
}

void Enseignant_ui::on_pushButton_pdf_clicked()
{
    qDebug() << "Clicked!!" ;
    int id = ui->lineEdit_pdf->text().toInt();
    Enseignant e = Enseignant::findById(id);
    if(e.getId() != 0) {
        Enseignant::imprimer(id);

        QMessageBox::information(nullptr, QObject::tr("PDF File created"),
                    QObject::tr("PDF File created.\n"
                                "Check your debug directory."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::warning(this, "Enseignant Not Found", "The specified enseignant was not found in the database.");
    }
}


void Enseignant_ui::on_radioButton_clicked()
{

    if(ui->comboBox->currentText() != "Choisir")
      ui->tableView->setModel(Enseignant::trie("ASC",ui->comboBox->currentText()));
    else  ui->tableView->setModel(Enseignant::afficher());
}

void Enseignant_ui::on_radioButton_2_clicked()
{
    if(ui->comboBox->currentText() != "Choisir")
        ui->tableView->setModel(Enseignant::trie("DESC",ui->comboBox->currentText()));
    else  ui->tableView->setModel(Enseignant::afficher());
}

void Enseignant_ui::on_search_field_textChanged(const QString &arg1)
{
    QString searchText = arg1.trimmed(); // Remove leading/trailing whitespaces

    // Check if the search text is empty, and if so, display the full list
    if (searchText.isEmpty()) {
        ui->tableView->setModel(Enseignant::afficher());
        return;
    }

    // Attempt to convert the search text to an integer (ID search)
    bool isNumeric;
    int searchId = searchText.toInt(&isNumeric);

    // Use QSqlQuery to perform a more complex search query
    QSqlQuery query;
    if (isNumeric) {
        query.prepare("SELECT * FROM Enseignant WHERE id = :id OR prenom LIKE :search OR nom LIKE :search");
        query.bindValue(":id", searchId);
    } else {
        query.prepare("SELECT * FROM Enseignant WHERE prenom LIKE :search OR nom LIKE :search");
    }

    query.bindValue(":search", "%" + searchText + "%"); // Search for partial matches

    if (query.exec()) {
        QStandardItemModel *newModel = new QStandardItemModel(0, 7, this);
        newModel->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
        newModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Prenom")));
        newModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Nom")));
        newModel->setHorizontalHeaderItem(3, new QStandardItem(QString("Date de Naissance")));
        newModel->setHorizontalHeaderItem(4, new QStandardItem(QString("Adresse")));
        newModel->setHorizontalHeaderItem(5, new QStandardItem(QString("Salaire")));
        newModel->setHorizontalHeaderItem(6, new QStandardItem(QString("Anciennete")));

        while (query.next()) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(query.value("ID").toString()));
            rowItems.append(new QStandardItem(query.value("Prenom").toString()));
            rowItems.append(new QStandardItem(query.value("Nom").toString()));
            rowItems.append(new QStandardItem(query.value("DateNaissance").toString()));
            rowItems.append(new QStandardItem(query.value("Adresse").toString()));
            rowItems.append(new QStandardItem(query.value("Salaire").toString()));
            rowItems.append(new QStandardItem(query.value("Anciennete").toString()));
            newModel->appendRow(rowItems);
        }

        ui->tableView->setModel(newModel);
        ui->tableView->show();
    } else {
        // Handle the case where the query execution fails
        qDebug() << "Query execution failed: " << query.lastError();
    }
}

void Enseignant_ui::on_pushButton_stats_clicked()
{
    // Créez un modèle de données pour le graphique circulaire
        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

        // Ajoutez des tranches (slices) pour chaque groupe d'âge
        // Vous devrez obtenir les données de votre base de données ici
        // Par exemple, supposons que vous ayez une fonction "getAgeDistribution()" qui renvoie un QHash<QString, int>
        QHash<QString, int> Distribution = Enseignant::getAncienneteDistribution();

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



