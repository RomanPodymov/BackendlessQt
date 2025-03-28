#include <QtTest>
#include <QSignalSpy>

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

void BackendlessQtTests::test() {
    QVERIFY(true);
    QCOMPARE(1, 1);
}

void BackendlessQtTests::cleanupTestCase() {

}

QTEST_MAIN(BackendlessQtTests)

#include "test.moc"
