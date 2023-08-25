#include "Enseignant.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

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
