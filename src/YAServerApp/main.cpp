#include <QApplication>
#include "src/YAServerLib/yaserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YAServer::YAServer server;
    server.StartServer(3004);
    return a.exec();
}
