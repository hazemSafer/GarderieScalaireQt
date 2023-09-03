#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Enseignant {
public:
    Enseignant();
    Enseignant(int id, QString prenom, QString nom, QDate dateNaissance, QString adresse, double salaire, int anciennete);

    // Getters
    int getId() const;
    QString getPrenom() const;
    QString getNom() const;
    QDate getDateNaissance() const;
    QString getAdresse() const;
    double getSalaire() const;
    int getAnciennete() const;

    // Setters
    void setId(int id);
    void setPrenom(const QString &prenom);
    void setNom(const QString &nom);
    void setDateNaissance(const QDate &dateNaissance);
    void setAdresse(const QString &adresse);
    void setSalaire(double salaire);
    void setAnciennete(int anciennete);

    bool ajouter();
    static QSqlQueryModel* afficher();
    static bool supprimer(int id);
    static Enseignant findById(int id);
    bool modifier();


    static void imprimer(int id);
    static QSqlQueryModel* trie(QString croissance, QString critere);
    static QHash<QString, int> getAncienneteDistribution();

private:
    int id;
    QString prenom;
    QString nom;
    QDate dateNaissance;
    QString adresse;
    double salaire;
    int anciennete;
};

#endif // ENSEIGNANT_H
