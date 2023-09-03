#ifndef ENSEIGNANT_UI_H
#define ENSEIGNANT_UI_H

#include <QDialog>

namespace Ui {
class Enseignant_ui;
}

class Enseignant_ui : public QDialog
{
    Q_OBJECT

public:
    explicit Enseignant_ui(QWidget *parent = nullptr);
    ~Enseignant_ui();

private:
    Ui::Enseignant_ui *ui;

private slots :
   void on_pushButton_back_clicked();
   void on_pushButton_ajout_clicked();
   void on_pushButton_supprimer_clicked();
   void on_pushButton_refresh_clicked();
   void on_pushButton_modifier_clicked();
   void on_radioButton_clicked();
   void on_radioButton_2_clicked();
   void on_search_field_textChanged(const QString &arg1);


   void on_pushButton_pdf_clicked();
   void on_tableView_activated(const QModelIndex &index);
   void on_pushButton_stats_clicked();
};

#endif // ENSEIGNANT_UI_H
