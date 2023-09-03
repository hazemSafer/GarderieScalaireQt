#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eleve_ui.h" // Include the header for Eleve_ui
#include "enseignant_ui.h" // Include the header for Enseignant_ui

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openEleveUI(); // Declaration for opening the Eleve_ui
    void openEnseignantUI(); // Declaration for opening the Enseignant_ui

private:
    Ui::MainWindow *ui;
    Eleve_ui *eleveUI; // Pointer to Eleve_ui dialog
    Enseignant_ui *enseignantUI; // Pointer to Enseignant_ui dialog
};

#endif // MAINWINDOW_H
