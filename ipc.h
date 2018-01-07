#ifndef IPC_H
#define IPC_H

#include <QObject>
#include <QWidget>
#include <QThread>

#include <HCNetSDK.h>
#include <PlayM4.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "featuretracker.h"

class IPC : public QThread
{
    Q_OBJECT

public:
    explicit IPC(QObject *parent = nullptr);
    ~IPC();
    int LoginToDevice(QString UserName, QString Password, QString IPAddress, int Port);
    int GetLastError(void);
    int StartRealPlay(int dev_id, WId win_id);
    void Logout(int device_id);

private:

    void run();

    static void RealDataCallBack(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD  dwBufSize, void* dwUser);
    static void PlayM4DecodeCallBack(LONG nPort, char* pBuffer, LONG nSize, FRAME_INFO* frameInfo, void* userData, LONG res);

    bool isStartRealPlay;
    LONG device_id;
    LONG realplay_id;
    QImage image;

    FeatureTracker tracker;

signals:
    void imageReady(QImage image);
};

#endif // IPC_H
