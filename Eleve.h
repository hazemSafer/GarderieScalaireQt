#ifndef ELEVE_H
#define ELEVE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Eleve {
public:
    Eleve();
    Eleve(int id, QString prenom, QString nom, QDate dateNaissance, QString Adresse, int niveau, QString respLegal);

    // Getters
    int getId() const;
    QString getPrenom() const;
    QString getNom() const;
    QDate getDateNaissance() const;
    QString getAdresse() const;
    int getNiveau() const;
    QString getRespLegal() const;

    // Setters
    void setId(int id);
    void setPrenom(const QString &prenom);
    void setEtatNom(const QString &etatnom);
    void setDateNaissance(const QDate &dateNaissance);
    void setAdresse(const QString &Adresse);
    void setNiveau(int niveau);
    void setRespLegal(const QString &respLegal);

    bool ajouter();
    static QSqlQueryModel* afficher();
    static bool supprimer(int id);
    static Eleve findById(int id);
    bool modifier();
    static void imprimer(int id);

    static QHash<QString, int> getAgeDistribution();
    static QHash<QString, int> getNiveauDistribution();

    static QSqlQueryModel* trie(QString croissance, QString critere);

private:
    int id;
    QString prenom;
    QString nom;
    QDate dateNaissance;
    QString Adresse;
    int niveau;
    QString responsableLegal;
};

#endif // ELEVE_H
