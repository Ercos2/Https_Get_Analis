#include <QCoreApplication>

#include "server_answer.h"
#include "reply_comparison.h"
#include "output_json.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Server_answer server_answer("https://rdb.altlinux.org/api/version");
    //Server_answer server_answer("https://httpbin.org/get");
    Server_answer server_answer("https://rdb.altlinux.org/api/export/branch_binary_packages/sisyphus");
    //Server_answer server_answer("https://rdb.altlinux.org/api/task/progress/all_tasks_branches");
    Server_answer server_answer1("https://rdb.altlinux.org/api/export/branch_binary_packages/p10");

    while(!server_answer.ready_flag || !server_answer1.ready_flag) {}

    //qDebug() << "*comparison*";

    Reply_Comparison *comparison = new Reply_Comparison(server_answer.get_json(), server_answer1.get_json());

    Output_JSON *output_json = new Output_JSON;

    QObject::connect(comparison, &Reply_Comparison::comparison_finished, [&comparison, &output_json] {
        output_json->output(comparison->get_My_Comparison()->get_output_struct());
    });

    QObject::connect(output_json, &Output_JSON::output_finished, [] {exit(0);});

    return a.exec();
}
