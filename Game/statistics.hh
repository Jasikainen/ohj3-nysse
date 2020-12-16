#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "interfaces/istatistics.hh"
#include <QDebug>

/**
  * @file
  * @brief Defines a class that implements statistics recording for game.
  */

namespace Game {

class Statistics : public Interface::IStatistics
{
public:
    Statistics();

    // IStatistics interface
public:
    // @copydoc Interface::IStatistics::morePassengers()
    void morePassengers(int num) override;
    // @copydoc Interface::IStatistics::nysseRemoved()
    void nysseRemoved() override;
    // @copydoc Interface::IStatistics::newNysse()
    void newNysse() override;
    // @copydoc Interface::IStatistics::nysseLeft()
    void nysseLeft() override;

    // Statistics interface
    /**
     * @brief shotProjectile keeps count of projectiles shot by player
     */
    void shotProjectile();
    /**
     * @brief nysseDestroyed keeps count of nysses destroyed by player
     */
    void nysseDestroyed();
    /**
     * @brief calculateAccuracy calculates players shot accuracy.
     */
    void calculateAccuracy();
    /**
     * @brief calculateScore calculates current score of player
     */
    void calculateScore(unsigned int addscore);
    /**
     * @brief getScore is used to return the players score
     * @return current score
     */
    unsigned int getScore() const;
    /**
     * @brief getAccuracy is used to return the players accuracy
     * @return
     */
    double getAccuracy() const;
    /**
     * @brief setName
     * @param name players name
     */
    void setName(std::string name);
    /**
     * @brief getName is used to set current players name to statistics
     * @return players name
     */
    std::string getName() const;
    /**
     * @brief getNyssesDestroyed is used to get amount of destroyed nysses
     * @return amount of nysses destroyed
     */
    unsigned int getNyssesDestroyed() const;

private:
    unsigned int passengers_;
    unsigned int nysses_;
    unsigned int nyssesleft_;
    unsigned int nyssesdestroyed_;
    double accuracy_;
    unsigned int projectiles_;
    unsigned int score_;
    std::string playername_;
    /*!
    * \class Statistics
    * \internal
    * \invariant accuracy_ is between 0-100, nysses_ >= (nyssesdestroyed_ + nyssesleft_)
    **/

    /*!
    * \brief tests the class invariant
    */
    void invariant() const;
};

} // namespace Game
#endif // STATISTICS_HH
