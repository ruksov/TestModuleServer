#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <memory>
#include <openssl/ssl.h>
#include <openssl/err.h>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();
    void SetSocket(QTcpSocket& t_socket);
    bool DoHandShake();
private:


    QTcpSocket* m_pSocket;
    SSL* m_pSSL;
    SSL_CTX* m_pCtx;
};

#endif // CLIENT_H
