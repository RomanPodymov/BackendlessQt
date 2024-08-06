#include <QTest>

class Foo : public QObject {
    Q_OBJECT
private slots:
    void t1() { QVERIFY(true); }
};

QTEST_MAIN(Foo)
#include "test.moc"
