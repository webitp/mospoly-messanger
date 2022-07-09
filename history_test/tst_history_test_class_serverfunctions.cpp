#include <QtTest>
#include <QString>
#include <QStringList>
#include "../server/database.h"
#include "../server/serverfunctions.h"

// add necessary includes here

class history_test_class_serverfunctions : public QObject
{
    Q_OBJECT

public:
    history_test_class_serverfunctions();
    ~history_test_class_serverfunctions();

private slots:
    void test_case_history_1_2();

};

history_test_class_serverfunctions::history_test_class_serverfunctions()
{

}

history_test_class_serverfunctions::~history_test_class_serverfunctions()
{

}

void history_test_class_serverfunctions::test_case_history_1_2()
{
   QString str = "{\n    \"message 1\": {\n        \"created_at\": \"2022-06-17T23:48:00.298\",\n        \"message\": \"hello\",\n        \"user1_id\": \"1\",\n        \"user2_id\": \"2\"\n    },\n    \"message 2\": {\n        \"created_at\": \"2022-06-20T19:18:54.821\",\n        \"message\": \"not_hello\",\n        \"user1_id\": \"2\",\n        \"user2_id\": \"1\"\n    },\n    \"message 3\": {\n        \"created_at\": \"2022-06-20T19:19:14.788\",\n        \"message\": \"who are you\",\n        \"user1_id\": \"2\",\n        \"user2_id\": \"1\"\n    },\n    \"message 4\": {\n        \"created_at\": \"2022-06-20T19:19:37.425\",\n        \"message\": \"i am you\",\n        \"user1_id\": \"1\",\n        \"user2_id\": \"2\"\n    }\n}\n";
   QStringList str_list = {};
   str_list.append("1");
   str_list.append("2");
   QCOMPARE(str,ServerFunctions::history(str_list));
}

QTEST_APPLESS_MAIN(history_test_class_serverfunctions)

#include "tst_history_test_class_serverfunctions.moc"
