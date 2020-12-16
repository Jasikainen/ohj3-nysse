#include "startdialog.hh"
#include "ui_startdialog.h"
#include "config.hh"

namespace Game {

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &StartDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &StartDialog::reject);

    ui->headerLabel->setText("Welcome to play the game");

    QPixmap pix(START_DIALOG_IMG);
    ui->labelPicture->setPixmap(pix);
    int w = ui->labelPicture->width();
    int h = ui->labelPicture->height();
    ui->labelPicture->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio, Qt::FastTransformation));

    int labelPicMoveHeight = 200;
    ui->labelPicture->move(PADDING, labelPicMoveHeight);

    setFixedSize(ui->labelPicture->width()-95, h + labelPicMoveHeight + PADDING);

    ui->buttonBox->move(this->width() - ui->buttonBox->width() - 2*PADDING, 50);
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::done(int r)
{
    // Accepted
    if (QDialog::Accepted == r){
        if (ui->nameEdit->text().size() > 0 && ui->nameEdit->text() != "Insert name!"){
            emit sendData(ui->nameEdit->text().toStdString());
            QDialog::done(r);
            return;
        } else {
            ui->nameEdit->setText("Insert name!");
            return;
        }
    // Rejected
    } else {
        QDialog::done(r);
        return;
    }
}

void StartDialog::accept()
{
    StartDialog::done(Accepted);
}
void StartDialog::reject()
{
    StartDialog::done(Rejected);
}

}



