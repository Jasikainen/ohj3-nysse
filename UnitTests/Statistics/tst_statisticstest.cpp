#include <QtTest>
#include "statistics.hh"
#include <QDebug>

class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    StatisticsTest();
    ~StatisticsTest();

private Q_SLOTS:
    /**
     * @brief testAddScore is used to test the addition to score
     */
    void testAddScore();
    /**
     * @brief testAccuracy1 is used to compare accuracy double values
     * on one decimal accuracy
     */
    void testAccuracy1();
    /**
     * @brief testAccuracy2 is used to test various scenarios of shot projectiles
     * and destroyed nysses
     */
    void testAccuracy2();
private:
    /**
     * @brief compare is used to compare double values
     * @param val1 value to be compared
     * @param val2 value to be compared
     * @param precision precision of comparison
     * @return True if values are equal on given precision
     */
    bool compare(const double val1, const double val2, const int precision);
    unsigned int addednysses_ = 30;
    unsigned int score_ = 0;
};

StatisticsTest::StatisticsTest(){
}

StatisticsTest::~StatisticsTest(){
}


void StatisticsTest::testAddScore()
{
    Game::Statistics stats_;
    QCOMPARE(stats_.getScore(), score_);
    stats_.calculateScore(123);
    QCOMPARE(stats_.getScore(), score_+123);
}

void StatisticsTest::testAccuracy1()
{
    Game::Statistics stats_;
    //double calc
    for (unsigned int i = 0; i < addednysses_; i++){
        stats_.newNysse();
        stats_.shotProjectile();
        if (i < 20){
            stats_.nysseDestroyed();
        }
        stats_.calculateAccuracy();
    }
    bool comparison = compare(stats_.getAccuracy(), 66.6, 1);
    QCOMPARE(comparison, true);
}

void StatisticsTest::testAccuracy2()
{
    Game::Statistics stats_;
    // Initialization state
    QCOMPARE(stats_.getAccuracy(), 100);

    stats_.newNysse();
    // projectiles == nysses destroyed
    stats_.shotProjectile();
    stats_.nysseDestroyed();
    stats_.calculateAccuracy();
    QCOMPARE(stats_.getAccuracy(), 100);

    // projectiles == 2 and destroyed == 1
    stats_.shotProjectile();
    stats_.calculateAccuracy();
    QCOMPARE(stats_.getAccuracy(), 50);
}


bool StatisticsTest::compare(const double val1, const double val2, const int precision)
{
    int64_t magnitude = static_cast<int64_t>(std::pow(10, precision));
    int64_t intval1 = static_cast<int64_t>(val1 * magnitude);
    int64_t intval2 = static_cast<int64_t>(val2 * magnitude);
    return intval1 == intval2;
}

QTEST_APPLESS_MAIN(StatisticsTest)

#include "tst_statisticstest.moc"

