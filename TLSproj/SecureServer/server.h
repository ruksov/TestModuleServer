#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <memory>
#include <map>
#include "client.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

signals:

public slots:
    void SlotNewConnection();
    void SlotFinishSSL();
private:
    std::shared_ptr<QTcpServer> m_pServer;
};

#endif // SERVER_H
