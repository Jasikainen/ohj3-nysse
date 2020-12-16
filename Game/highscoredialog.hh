#ifndef HIGHSCOREDIALOG_HH
#define HIGHSCOREDIALOG_HH
#include "statistics.hh"

#include <QDialog>
#include <vector>

/**
  * @file
  * @brief Defines a class that implements dialog at game end.
  */

namespace Ui {
class HighScoreDialog;
}

namespace Game {

class HighScoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoreDialog(QWidget *parent = nullptr);
    ~HighScoreDialog();
public slots:
    /**
     * @brief receiveStatistics is used to receive set object
     * @param statistics a shared pointer for in game statistics
     */
    void receiveStatistics(std::shared_ptr<Statistics> statistics);
private slots:
    /**
     * @brief on_pushButton_clicked is used to rewrite highscores and closes program
     */
    void on_pushButton_clicked();

private:
    // Represents players statistic for highscores
    struct Data {
          QString name;
          unsigned int score;
          unsigned int accuracy;
    };
    /**
     * @brief readHighScoreData is used to read highscore data txt file
     */
    void readHighScoreData();
    /**
     * @brief createNewHighScoreFile is used to create highscores if none exists.
     * Used to create generic random statistics between wanted range.
     */
    void createNewHighScoreFile();
    /**
     * @brief splitString splits string at "," to parts
     * @param row to be split apart
     * @return list of strings that were split from input
     */
    QStringList splitString(QString row);
    /**
     * @brief formInputString is used to format values to CSV style of format
     * @param name players name
     * @param score players score
     * @param accuracy players accuracy after game
     * @return CSV format string. "," Is used as delimiter
     */
    std::string formInputString(std::string name, unsigned int score, unsigned int accuracy);
    /**
     * @brief createDataStruct is used to create struct of data of the player
     * @param name of player
     * @param score player has achieved
     * @param accuracy after finishing game
     * @return struct of Data
     */
    Data createDataStruct(QString name, unsigned int score, unsigned int accuracy);
    /**
     * @brief sortHighscoresByScore sorts the highscores_ vector to descending order by score
     */
    void sortHighscoresByScore();
    /**
     * @brief createHighScoreUI display current highscore statistics in UI
     */
    void createHighScoreUI();
    /**
     * @brief showPlayerScore display the score of player in UI
     */
    void showPlayerScore();
    Ui::HighScoreDialog *ui;
    std::shared_ptr<Statistics> statistics_;
    /**
     * @brief highscores_ structs of highscore players
     */
    std::vector<Data> highscores_;
};
} // namespace Game
#endif // HIGHSCOREDIALOG_HH
