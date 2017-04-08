#pragma once

#include "clientinfo.h"


enum {L_REG, L_LOG, L_MESS, L_OK, L_ERROR, L_NEWCLIENT, L_LOGINEXIST, L_FILE};

class Model : public QObject
{
    Q_OBJECT

    QScopedPointer<QTcpSocket> socket;
    quint32 blockSize = 0;
    QMap<QString, clientInfo> clientsList;
    int port;


    void Parser(QDataStream & mess);

public:

    explicit Model(QObject *parent = 0);
    ~Model();

    void connectToHost(const QString &hostIP);
    void SendMessage(const int & label, const QString & message, const QByteArray &file = QByteArray());
    QMap<QString, clientInfo>*GetClients();

signals:

    //signals for GUI
    void signalOK();
    void signalNewClient(const QPair<QString, clientInfo> & newClient);
    void signalNewMessage(const QString & sender, const QTime &time, const QString & message);
    void signalNewFile(const QString &sender, const QTime &time,const QString & fileName, const QByteArray &file);
    void signalConnect(const QString & err);
    void signalWrongLogin();
    void signalLoginExist();
    void signalMessageError();

public slots:

    void slotRead();
    void slotConnectError(QAbstractSocket::SocketError);
    void slotConnected();
};


