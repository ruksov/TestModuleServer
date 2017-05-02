#include "server.h"
#include <QDebug>
#include <openssl/ssl.h>
#include <openssl/err.h>

Server::Server(QObject *parent) : QObject(parent)
{
    m_pServer = std::shared_ptr<QTcpServer>(new QTcpServer(this));
    if(!m_pServer.get()->listen(QHostAddress::Any, 1234))
    {
        qDebug()<<m_pServer.get()->errorString();
        m_pServer.get()->close();
    }
    connect(this, Server::destroyed, this, Server::SlotFinishSSL);
    connect(m_pServer.get(), QTcpServer::newConnection, this, Server::SlotNewConnection);

    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_CONFIG, NULL);
    qDebug()<<"Server started";
}

void Server::SlotNewConnection()
{
    qDebug()<<"New connection";
    Client* client = new Client(this);
    client->SetSocket(*(m_pServer->nextPendingConnection()));
    if(!client->DoHandShake())
    {
        emit client->destroyed();
    }
}

void Server::SlotFinishSSL()
{
    ERR_free_strings();
}

