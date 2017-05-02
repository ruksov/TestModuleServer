#ifndef SESSION_H
#define SESSION_H
#include <QtNetwork>
#include <openssl/ssl.h>
#include <openssl/err.h>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(qintptr t_descriptor, QObject *parent = 0);
    ~Session();
    void SetSocket(qintptr t_descriptor);
    bool DoHandShake();
private slots:
    void slotReadClient();
private:
    QTcpSocket* m_Socket;
    SSL* m_pSSL;
    SSL_CTX* m_pCtx;
    uint m_nextBlockBytes;


};

#endif // SESSION_H
