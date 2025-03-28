#include <QtTest>
#include <QSignalSpy>
#include "../BackendlessAPI.hpp"

class BackendlessQtTests: public QObject {
    Q_OBJECT

public:
    BackendlessQtTests();
    ~BackendlessQtTests();

private slots:
    void initTestCase();
    void test();
    void cleanupTestCase();
};

BackendlessQtTests::BackendlessQtTests() {

}

BackendlessQtTests::~BackendlessQtTests() {

}

void BackendlessQtTests::initTestCase() {

}

void BackendlessQtTests::test() {
    //BackendlessAPI some(nullptr, "", "", "");
    //some.addItemToTable("", PostParams());

    QVERIFY(true);
    QCOMPARE(1, 2);
}

void BackendlessQtTests::cleanupTestCase() {

}

QTEST_MAIN(BackendlessQtTests)

#include "test.moc"
