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

QString Eleve::getEtatNom() const {
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
        QString etatnom = q.value("NOM").toString();
        QDate dateNaissance = q.value("DATENAISSANCE").toDate();
        QString Adresse = q.value("ADRESSE").toString();
        int niveau = q.value("NIVEAU").toInt();
        QString respLegal = q.value("RESPONSABLELEGAL").toString();
        return Eleve(id, prenom, etatnom, dateNaissance, Adresse, niveau, respLegal);
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
