#include <QtTest>
#include <QString>
#include <QStringList>
#include "../server/database.h"
#include "../server/serverfunctions.h"

// add necessary includes here

class test_function_message : public QObject
{
    Q_OBJECT

public:
    test_function_message();
    ~test_function_message();

private slots:
    void test_message_1_2_hello();

};

test_function_message::test_function_message()
{

}

test_function_message::~test_function_message()
{

}

void test_function_message::test_message_1_2_hello()
{
    QStringList str_list = {};
    str_list.append("1");
    str_list.append("2");
    str_list.append("hello");
    QCOMPARE("message is added", ServerFunctions::message(str_list));
}

QTEST_APPLESS_MAIN(test_function_message)

#include "tst_test_function_message.moc"
