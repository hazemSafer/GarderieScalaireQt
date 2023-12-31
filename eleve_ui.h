#ifndef ELEVE_UI_H
#define ELEVE_UI_H

#include <QDialog>

namespace Ui {
class Eleve_ui;
}

class Eleve_ui : public QDialog
{
    Q_OBJECT

public:
    explicit Eleve_ui(QWidget *parent = nullptr);
    ~Eleve_ui();

private :
    Ui::Eleve_ui *ui;

private slots :
   void on_pushButton_back_clicked();
   void on_pushButton_ajout_clicked();
   void on_pushButton_supprimer_clicked();
   void on_pushButton_refresh_clicked();
   void on_pushButton_modifier_clicked();
   void on_radioButton_clicked();
   void on_radioButton_2_clicked();
   void on_search_field_textChanged(const QString &arg1);
   void on_pushButton_stats_clicked();


   void on_pushButton_pdf_clicked();
   void on_tableView_activated(const QModelIndex &index);

};

#endif // ELEVE_UI_H
