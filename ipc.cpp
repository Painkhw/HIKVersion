#include "ipc.h"

#include <string.h>

#include <QSemaphore>
#include <QImage>

LONG port;
QSemaphore imgReady;
cv::Mat img;

IPC::IPC(QObject* parent) : QThread(parent)
{
    NET_DVR_Init();
    device_id = -1;
    isStartRealPlay = false;
}

IPC::~IPC()
{
    NET_DVR_Cleanup();
}

void IPC::PlayM4DecodeCallBack(LONG nPort, char* pBuffer, LONG nSize, FRAME_INFO* frameInfo, void* userData, LONG res)
{
    if(frameInfo->nType == T_YV12)
    {
       img = cv::Mat(frameInfo->nHeight, frameInfo->nWidth, CV_8UC3);
       cv::Mat src(frameInfo->nHeight+frameInfo->nHeight/2, frameInfo->nWidth, CV_8UC1, pBuffer);
       cv::cvtColor(src, img, CV_YUV2RGB_YV12);
       cv::resize(img, img, cv::Size(1024,576), 0, 0);

       imgReady.release();
    }
}

void IPC::RealDataCallBack(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD  dwBufSize, void* dwUser)
{
    (void)dwUser;
    (void)lRealHandle;

    switch (dwDataType)
    {
        case NET_DVR_SYSHEAD:
            if(!PlayM4_GetPort(&port))
            {
                break;
            }

            if(dwBufSize > 0)
            {
                if(!PlayM4_SetStreamOpenMode(port, STREAME_REALTIME))
                {
                    break;
                }

                if(!PlayM4_OpenStream(port, pBuffer, dwBufSize, 1024*1024))
                {
                    break;
                }

                if(!PlayM4_Play(port, NULL))
                {
                   break;
                }

                if(!PlayM4_SetDecCallBack(port, &PlayM4DecodeCallBack))
                {
                   break;
                }
            }

            break;

        case NET_DVR_STREAMDATA:
            if((dwBufSize > 0) && port != -1)
            {
                if(!PlayM4_InputData(port, pBuffer, dwBufSize))
                {
                    break;
                }
            }
            break;

        default:
            break;
    }
}
//QString UserName, QString Password, QString IPAddress, int Port
void IPC::run()
{
    while(1)
    {
        if(device_id != -1)
        {
            if(!isStartRealPlay)
            {
                NET_DVR_CLIENTINFO client_info;

                client_info.lChannel =  1;
                client_info.lLinkMode = 0;
                client_info.hPlayWnd = NULL;

                realplay_id = NET_DVR_RealPlay_V30(device_id, &client_info, &RealDataCallBack, NULL, 1);

                isStartRealPlay = true;
            }

            imgReady.acquire();
            image = QImage((const unsigned char*)(img.data),
                          img.cols, img.rows, QImage::Format_RGB888);

            emit imageReady(image);
        }
    }
}

int IPC::LoginToDevice(QString UserName, QString Password, QString IPAddress, int Port)
{
    NET_DVR_USER_LOGIN_INFO user_info;
    NET_DVR_DEVICEINFO_V40 device_info;

    strcpy(user_info.sDeviceAddress, IPAddress.toLocal8Bit().data());
    user_info.wPort = Port;
    strcpy(user_info.sUserName, UserName.toLocal8Bit().data());
    strcpy(user_info.sPassword, Password.toLocal8Bit().data());

    device_id = NET_DVR_Login_V40(&user_info, &device_info);
    return device_id;
}


int IPC::StartRealPlay(int dev_id, WId win_id)
{
   NET_DVR_CLIENTINFO client_info;

   client_info.lChannel =  1;
   client_info.lLinkMode = 0;
   client_info.hPlayWnd = win_id;

   return NET_DVR_RealPlay_V30(dev_id, &client_info, &RealDataCallBack, NULL, 1);
}

int IPC::GetLastError(void)
{
    int error_code;
    printf("error: %s", NET_DVR_GetErrorMsg(&error_code));
    return error_code;
}

void IPC::Logout(int device_id)
{
    NET_DVR_Logout_V30(device_id);
}
