#include <QCoreApplication>

#include "server_answer.h"
#include "reply_comparison.h"
#include "output_json.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString first_branch = "sisyphus";
    QString second_branch = "p10";

    Server_answer server_answer("https://rdb.altlinux.org/api/export/branch_binary_packages/" + first_branch);                         //создаём класс и передаём запрос
    Server_answer server_answer1("https://rdb.altlinux.org/api/export/branch_binary_packages/" + second_branch);

    while(!server_answer.ready_flag || !server_answer1.ready_flag) {}                                                           //ожидаем, пока обы потока завершат действие

    Reply_Comparison *comparison = new Reply_Comparison(server_answer.get_reply_struct(), server_answer1.get_reply_struct());   //передаём по структуре данных из каждого класса для сравнения

    Output_JSON *output_json = new Output_JSON;                                                                                 //класс для вывода

    QObject::connect(comparison, &Reply_Comparison::comparison_finished, [&comparison, &output_json] {
        output_json->output(comparison->get_My_Comparison()->get_output_struct());
    });                                                                                                                          // дожидаемся конца сравнения данных и передаём результат на вывод

    QObject::connect(output_json, &Output_JSON::output_finished, [] {exit(0);});                                                 // после вывода завершаем программу

    return a.exec();
}
