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

private:
    Ui::Eleve_ui *ui;
};

#endif // ELEVE_UI_H
