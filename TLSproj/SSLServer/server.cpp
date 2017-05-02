#include "server.h"
#include <QDebug>
Server::Server(QObject *parent) : QTcpServer(parent)
{
    if(!listen(QHostAddress::Any, 1234))
    {
        qDebug()<<errorString();
        close();
    }


    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_CONFIG, NULL);
    qDebug()<<"Server started";
}

void Server::incomingConnection(qintptr t_descriptor)
{

        qDebug()<<"Connect new client";
        Session* client = new Session(t_descriptor, this);
//        client->SetSocket(t_descriptor);
        client->DoHandShake();
}

