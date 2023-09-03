#include "Eleve.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QPrinter>
#include<QPrintDialog>
#include<QPainter>

Eleve::Eleve(){
    id = 0;
}

Eleve::Eleve(int id, QString prenom, QString nom, QDate dateNaissance, QString Adresse, int niveau, QString responsableLegal)
{
    this->id = id;
    this->prenom = prenom;
    this->nom = nom;
    this->dateNaissance = dateNaissance;
    this->Adresse = Adresse;
    this->niveau = niveau;
    this->responsableLegal = responsableLegal;
}

// Getters
int Eleve::getId() const {
    return id;
}

QString Eleve::getPrenom() const {
    return prenom;
}

QString Eleve::getNom() const {
    return nom;
}

QDate Eleve::getDateNaissance() const {
    return dateNaissance;
}

QString Eleve::getAdresse() const {
    return Adresse;
}

int Eleve::getNiveau() const {
    return niveau;
}

QString Eleve::getRespLegal() const {
    return responsableLegal;
}

// Setters
void Eleve::setId(int id) {
    this->id = id;
}

void Eleve::setPrenom(const QString &prenom) {
    this->prenom = prenom;
}

void Eleve::setEtatNom(const QString &nom) {
    this->nom = nom;
}

void Eleve::setDateNaissance(const QDate &dateNaissance) {
    this->dateNaissance = dateNaissance;
}

void Eleve::setAdresse(const QString &Adresse) {
    this->Adresse = Adresse;
}

void Eleve::setNiveau(int niveau) {
    this->niveau = niveau;
}

void Eleve::setRespLegal(const QString &responsableLegal) {
    this->responsableLegal = responsableLegal;
}

//CRUD
bool Eleve::ajouter()
{
    QSqlQuery q;
    q.prepare("INSERT INTO Eleve (ID, PRENOM, NOM, DATENAISSANCE, ADRESSE, NIVEAU, RESPONSABLELEGAL) VALUES (:id, :prenom, :nom, :dateNaissance, :Adresse, :niveau, :responsableLegal)");
    q.bindValue(":id", id);
    q.bindValue(":prenom", prenom);
    q.bindValue(":nom", nom);
    q.bindValue(":dateNaissance", dateNaissance);
    q.bindValue(":Adresse", Adresse);
    q.bindValue(":niveau", niveau);
    q.bindValue(":responsableLegal", responsableLegal);

    return q.exec();
}

QSqlQueryModel* Eleve::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Eleve");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Niveau"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Responsable Légal"));

    return model;
}

bool Eleve::supprimer(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM Eleve WHERE ID = :id");
    q.bindValue(":id", id);

    return q.exec();
}

Eleve Eleve::findById(int id)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM Eleve WHERE ID = :id");
    q.bindValue(":id", id);

    if (q.exec() && q.next()) {
        QString prenom = q.value("PRENOM").toString();
        QString nom = q.value("NOM").toString();
        QDate dateNaissance = q.value("DATENAISSANCE").toDate();
        QString Adresse = q.value("ADRESSE").toString();
        int niveau = q.value("NIVEAU").toInt();
        QString respLegal = q.value("RESPONSABLELEGAL").toString();
        return Eleve(id, prenom, nom, dateNaissance, Adresse, niveau, respLegal);
    }

    return Eleve();
}

bool Eleve::modifier()
{
    QSqlQuery q;
    q.prepare("UPDATE Eleve SET PRENOM = :prenom, NOM = :nom, DATENAISSANCE = :dateNaissance, ADRESSE = :Adresse, NIVEAU = :niveau, RESPONSABLELEGAL = :responsableLegal WHERE ID = :id");
    q.bindValue(":prenom", prenom);
    q.bindValue(":nom", nom);
    q.bindValue(":dateNaissance", dateNaissance);
    q.bindValue(":Adresse", Adresse);
    q.bindValue(":niveau", niveau);
    q.bindValue(":responsableLegal", responsableLegal);
    q.bindValue(":id", id);

    return q.exec();
}

void Eleve::imprimer(int id)
{
    QString nom;
    int y0 = 2000;
    Eleve e = findById(id);

    QString pdfFileName = QString::number(e.getId()) + "_" + e.getNom() + "_" + e.getPrenom() + ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setFullPage(QPrinter::A4);
    printer.setOutputFileName(pdfFileName);

    QPainter painter(&printer);
    painter.setFont(QFont("Verdana", 30));
    painter.drawText(200, 1000, "Fiche d'élève");

    painter.setFont(QFont("Verdana", 12));
    y0 += 250;
    painter.drawText(400, y0, "Nom de l'Application : Garderie Scalaire");
    y0 += 500;


    QFont titleFont("Verdana", 12, QFont::Bold);
    titleFont.setUnderline(true);
    titleFont.setCapitalization(QFont::AllUppercase);
    painter.setFont(titleFont);

    painter.setPen(QColor(Qt::darkBlue)); // Set color to dark blue

    QStringList subtitles = {
        "IDENTIFIANT",
        "PRENOM",
        "NOM",
        "DATE DE NAISSANCE",
        "ADRESSE",
        "SALAIRE",
        "ANCIENNETE"
    };

    QStringList contents = {
        QString::number(e.getId()),
        e.getPrenom(),
        e.getNom(),
        e.getDateNaissance().toString(),
        e.getAdresse(),
        QString::number(e.getNiveau()),
        e.getRespLegal()
    };

    for (int i = 0; i < subtitles.size(); ++i)
    {
        painter.drawText(400, y0, subtitles[i] + " :");
        painter.setFont(QFont("Verdana", 12)); // Set content font to normal
        painter.drawText(4000, y0, contents[i]);
        painter.setFont(titleFont); // Reset font to subtitle style
        y0 += 250;
    }

    painter.end();
}


QSqlQueryModel* Eleve::trie(QString croissance, QString critere)
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery query;

    QString sqlQuery = "SELECT * FROM Eleve ORDER BY %1 %2";
    sqlQuery = sqlQuery.arg(critere).arg(croissance);

    query.prepare(sqlQuery);
    if (query.exec()) {
        modal->setQuery(query);
    }

    return modal;
}

QHash<QString, int> Eleve::getAgeDistribution()
{
    QHash<QString, int> ageDistribution;

    // Récupérez la liste des élèves depuis votre base de données
    // Par exemple, vous pouvez utiliser votre fonction afficher() pour obtenir une liste de tous les élèves.
    QSqlQueryModel* model = afficher();

    // Calculez l'âge de chaque élève et mettez à jour la répartition par âge
    QDateTime now = QDateTime::currentDateTime();
    for (int row = 0; row < model->rowCount(); ++row) {
        QDate dateNaissance = model->data(model->index(row, 3)).toDate(); // Supposons que la date de naissance est dans la colonne 3

        int age = dateNaissance.daysTo(now.date()) / 365; // Calculez l'âge approximatif

        // Classifiez l'âge dans des groupes
        QString ageGroup;
        if (age < 8) {
            ageGroup = "Moins de 8 ans";
        } else if (age < 10) {
            ageGroup = "8-10 ans";
        } else if (age < 12) {
            ageGroup = "10-12 ans";
        } else {
            ageGroup = "12 ans et plus";
        }

        // Mettez à jour la répartition par âge
        if (ageDistribution.contains(ageGroup)) {
            ageDistribution[ageGroup]++;
        } else {
            ageDistribution[ageGroup] = 1;
        }
    }

    return ageDistribution;
}

QHash<QString, int> Eleve::getNiveauDistribution()
{
    QHash<QString, int> niveauDistribution;

    // Récupérez la liste des élèves depuis votre base de données
    // Utilisez votre fonction afficher() ou une autre méthode appropriée pour obtenir une liste de tous les élèves.
    QSqlQueryModel* model = afficher();

    // Parcourez les données et mettez à jour la répartition par niveau
    for (int row = 0; row < model->rowCount(); ++row) {
        QString niveau = model->data(model->index(row, 5)).toString();

        // Mettez à jour la répartition par niveau
        if (niveauDistribution.contains(niveau)) {
            niveauDistribution[niveau]++;
        } else {
            niveauDistribution[niveau] = 1;
        }
    }

    return niveauDistribution;
}
