#include "highscoredialog.hh"
#include "ui_highscoredialog.h"
#include "statistics.hh"

#include <algorithm>
#include <string>
#include <fstream>
#include <QDebug>
#include <QString>

namespace Game {

HighScoreDialog::HighScoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScoreDialog)
{
    ui->setupUi(this);
    readHighScoreData();
    createHighScoreUI();
    connect(ui->pushButton, &QPushButton::clicked, this, &HighScoreDialog::reject);
}

HighScoreDialog::~HighScoreDialog()
{
    delete ui;
}


void Game::HighScoreDialog::receiveStatistics(std::shared_ptr<Statistics> statistics)
{
    statistics_ = statistics;
    showPlayerScore();
}

void HighScoreDialog::readHighScoreData()
{
    std::ifstream file;
    file.open("highscore.txt");
    if (!file){
        createNewHighScoreFile();
    } else {
        std::string row;
        qDebug() << "Found highscore.txt";
        while (getline (file, row)) {
            if (highscores_.size() > 10){
                sortHighscoresByScore();
                return;
            }
            QString qrow = QString::fromStdString(row);
            QStringList list = splitString(qrow);
            Data data = createDataStruct(list[0], list[1].toUInt(), list[2].toUInt());
            highscores_.push_back(data);
        }
    }
}

void HighScoreDialog::createNewHighScoreFile()
{
    qDebug() << "File not found or could not be opened";
    qDebug() << "Generating new time highscore.txt";
    std::ofstream newfile {"highscore.txt"};

    for (unsigned int i = 0; i < 10; i++){
        unsigned int score = rand()% (300-100 + 1) + 100;
        unsigned int accuracy = rand()% (100-0 + 1);
        std::string name = "player" + std::to_string(i);

        std::string s = formInputString(name, score, accuracy);
        newfile << s << std::endl;

        QString qname = QString::fromStdString(name);
        Data data = createDataStruct(qname, score, accuracy);
        highscores_.push_back(data);
    }
    newfile.close();
    sortHighscoresByScore();
}

QStringList HighScoreDialog::splitString(QString row)
{
    QStringList list = row.split(",", QString::SkipEmptyParts);
    return list;
}

std::string HighScoreDialog::formInputString(std::string name, unsigned int score, unsigned int accuracy)
{
    std::string CSVstring = name + ","
                            + std::to_string(score) + ","
                            + std::to_string(accuracy);
    return CSVstring;
}

HighScoreDialog::Data HighScoreDialog::createDataStruct(QString name, unsigned int score, unsigned int accuracy)
{
    Data data;
    data.name = name;
    data.score = score;
    data.accuracy = accuracy;
    return data;
}

void HighScoreDialog::sortHighscoresByScore()
{
    std::sort(highscores_.begin(), highscores_.end(), [](const Data&data1, const Data &data2)
    {
        return data1.score > data2.score;
    });
}

void HighScoreDialog::createHighScoreUI()
{
    // Add each value to listwidgets
    for (unsigned long int idx = 0; idx < highscores_.size(); idx++){
        ui->nameListWidget->addItem(highscores_[idx].name);
        ui->scoreListWidget->addItem(QString::number(highscores_[idx].score));
        ui->accuracyListWidget->addItem(QString::number(highscores_[idx].accuracy));
    }
}

void HighScoreDialog::showPlayerScore()
{
    ui->playernameLabel->setText(QString::fromStdString(statistics_->getName()));
    ui->playerscoreLabel->setText(QString::number(statistics_->getScore()));
    ui->playeraccuracyLabel->setText(QString::number(statistics_->getAccuracy()));
    ui->nyssesdestroyedLabel->setText(QString::number(statistics_->getNyssesDestroyed()));
}

void HighScoreDialog::on_pushButton_clicked()
{
    Data currentplayer = createDataStruct(QString::fromStdString(statistics_->getName()),
                                 statistics_->getScore(),
                                 statistics_->getAccuracy());
    highscores_.push_back(currentplayer);
    sortHighscoresByScore();

    while (highscores_.size() > 10){
        highscores_.pop_back();
    }

    std::ofstream file {"highscore.txt", std::ofstream::trunc};
    for (unsigned long int idx = 0; idx < highscores_.size(); idx++){
        std::string row = formInputString(highscores_[idx].name.toStdString(),
                                        highscores_[idx].score,
                                        highscores_[idx].accuracy);
        file << row << std::endl;
    }
    file.close();
}

} // namespace Game
