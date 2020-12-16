#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include <QDialog>

/**
  * @file
  * @brief Defines a class that implements dialog at game start.
  */

namespace Ui {
class StartDialog;
}

namespace Game {


class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = nullptr);
    ~StartDialog();
signals:
    std::string sendData(std::string name);

private slots:
    /**
     * @brief done is override so that the input from user may be checked
     * @param pressed buttons numerical value (Accepted/Rejected)
     */
    void done(int r) override;

private:
    Ui::StartDialog *ui;


    // QDialog interface
public slots:
    void accept() override;
    void reject() override;

};
} // namespace Game
#endif // STARTDIALOG_HH
