#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QVector>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "session.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

signals:



private:
    SSL_CTX* m_pCtx;
    void incomingConnection(qintptr t_descriptor);

};

#endif // SERVER_H
