#pragma once

#include "databasemanager.h"
#include "dialog.h"

namespace YAServer{



enum
{
    REG,
    LOGIN,
    MESSAGE,
    OK,
    LOG_ERROR,
    UPDATE,
    REG_ERROR,
    L_FILE
};

class YAServer : public QObject
{
    Q_OBJECT
public:
    explicit YAServer(QObject *parent = 0);

    bool StartServer(int nPort);
    QString GetIP();

public slots:
    void slotNewConnection();
    void slotReadClient();
    void slotDissconnectClient();

private:
    QTcpServer* m_pTcpServer;
    DatabaseManager::DatabaseManager m_dbManager;
    QMap<QString, ClientInfo::ClientInfo> m_mapClients;
    Dialog m_dialog;
    quint32 m_nNextBlockSize;


    void ReadClientREG_LOG(QDataStream& in, QTcpSocket* pClientSocket,const int& typeMsg);
    void ReadClientMESSAGE(QDataStream& in, const int &typeMsg);


    void SendToClient(QTcpSocket* pClientSocket, const int& type, const QByteArray& arrBlockMsg);
};

}
