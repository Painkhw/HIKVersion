#ifndef IPC_H
#define IPC_H

#include <QObject>
#include <QWidget>

class IPC
{

public:
    IPC();
    ~IPC();
    int LoginToDevice(QString UserName, QString Password, QString IPAddress, int Port);
    int GetLastError(void);
    int StartRealPlay(int dev_id, WId win_id);
    void Logout(int device_id);

private:

};

#endif // IPC_H
