#include "Enseignant.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>


Enseignant::Enseignant() {
    id = 0;
    salaire = 0.0;
    anciennete = 0;
}

Enseignant::Enseignant(int id, QString prenom, QString nom, QDate dateNaissance, QString adresse, double salaire, int anciennete)
{
    this->id = id;
    this->prenom = prenom;
    this->nom = nom;
    this->dateNaissance = dateNaissance;
    this->adresse = adresse;
    this->salaire = salaire;
    this->anciennete = anciennete;
}

// Getters
int Enseignant::getId() const {
    return id;
}

QString Enseignant::getPrenom() const {
    return prenom;
}

QString Enseignant::getNom() const {
    return nom;
}

QDate Enseignant::getDateNaissance() const {
    return dateNaissance;
}

QString Enseignant::getAdresse() const {
    return adresse;
}

double Enseignant::getSalaire() const {
    return salaire;
}

int Enseignant::getAnciennete() const {
    return anciennete;
}

// Setters
void Enseignant::setId(int id) {
    this->id = id;
}

void Enseignant::setPrenom(const QString &prenom) {
    this->prenom = prenom;
}

void Enseignant::setNom(const QString &nom) {
    this->nom = nom;
}

void Enseignant::setDateNaissance(const QDate &dateNaissance) {
    this->dateNaissance = dateNaissance;
}

void Enseignant::setAdresse(const QString &adresse) {
    this->adresse = adresse;
}

void Enseignant::setSalaire(double salaire) {
    this->salaire = salaire;
}

void Enseignant::setAnciennete(int anciennete) {
    this->anciennete = anciennete;
}

// CRUD
bool Enseignant::ajouter()
{
    QSqlQuery q;
    q.prepare("INSERT INTO Enseignant (id, prenom, nom, dateNaissance, adresse, salaire, anciennete) VALUES (:id, :prenom, :nom, :dateNaissance, :adresse, :salaire, :anciennete)");
    q.bindValue(":id", id);
    q.bindValue(":prenom", prenom);
    q.bindValue(":nom", nom);
    q.bindValue(":dateNaissance", dateNaissance);
    q.bindValue(":adresse", adresse);
    q.bindValue(":salaire", salaire);
    q.bindValue(":anciennete", anciennete);

    return q.exec();
}

QSqlQueryModel* Enseignant::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Enseignant");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Ancienneté"));

    return model;
}

bool Enseignant::supprimer(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM Enseignant WHERE id = :id");
    q.bindValue(":id", id);

    return q.exec();
}

Enseignant Enseignant::findById(int id)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM Enseignant WHERE id = :id");
    q.bindValue(":id", id);

    if (q.exec() && q.next()) {
        QString prenom = q.value("prenom").toString();
        QString nom = q.value("nom").toString();
        QDate dateNaissance = q.value("dateNaissance").toDate();
        QString adresse = q.value("adresse").toString();
        double salaire = q.value("salaire").toDouble();
        int anciennete = q.value("anciennete").toInt();
        return Enseignant(id, prenom, nom, dateNaissance, adresse, salaire, anciennete);
    }

    return Enseignant();
}

bool Enseignant::modifier()
{
    QSqlQuery q;
    q.prepare("UPDATE Enseignant SET prenom = :prenom, nom = :nom, dateNaissance = :dateNaissance, adresse = :adresse, salaire = :salaire, anciennete = :anciennete WHERE id = :id");
    q.bindValue(":prenom", prenom);
    q.bindValue(":nom", nom);
    q.bindValue(":dateNaissance", dateNaissance);
    q.bindValue(":adresse", adresse);
    q.bindValue(":salaire", salaire);
    q.bindValue(":anciennete", anciennete);
    q.bindValue(":id", id);

    return q.exec();
}

void Enseignant::imprimer(int id)
{
    QString nom;
    int y0 = 2000;
    Enseignant e = findById(id);

    QString pdfFileName = QString::number(e.getId()) + "_" + e.getNom() + "_" + e.getPrenom() + ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setFullPage(QPrinter::A4);
    printer.setOutputFileName(pdfFileName);

    QPainter painter(&printer);
    painter.setFont(QFont("Verdana", 30));
    painter.drawText(200, 1000, "Fiche d'enseignant");

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
        QString::number(e.getSalaire()),
        QString::number(e.getAnciennete())
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



QSqlQueryModel* Enseignant::trie(QString croissance, QString critere)
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery query;

    QString sqlQuery = "SELECT * FROM Enseignant ORDER BY %1 %2";
    sqlQuery = sqlQuery.arg(critere).arg(croissance);

    query.prepare(sqlQuery);
    if (query.exec()) {
        modal->setQuery(query);
    }

    return modal;
}

QHash<QString, int> Enseignant::getAncienneteDistribution()
{
    QHash<QString, int> ancienneteDistribution;

    // Récupérez la liste des élèves depuis votre base de données
    // Par exemple, vous pouvez utiliser votre fonction afficher() pour obtenir une liste de tous les élèves.
    QSqlQueryModel* model = afficher();

    // Calculez l'âge de chaque élève et mettez à jour la répartition par âge
    QDateTime now = QDateTime::currentDateTime();
    for (int row = 0; row < model->rowCount(); ++row) {
        int anciennete = model->data(model->index(row, 6)).toInt(); // Supposons que la date de naissance est dans la colonne 3

        // Classifiez l'âge dans des groupes
        QString ancienneteGroup;
        if (anciennete < 2) {
            ancienneteGroup = "Moins de 2 ans";
        } else if (anciennete < 4) {
            ancienneteGroup = "2-4 ans";
        } else if (anciennete < 6) {
            ancienneteGroup = "4-6 ans";
        } else {
            ancienneteGroup = "6 ans et plus";
        }

        // Mettez à jour la répartition par âge
        if (ancienneteDistribution.contains(ancienneteGroup)) {
            ancienneteDistribution[ancienneteGroup]++;
        } else {
            ancienneteDistribution[ancienneteGroup] = 1;
        }
    }

    return ancienneteDistribution;
}

