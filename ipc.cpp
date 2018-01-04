#include "ipc.h"
#include "HCNetSDK.h"

#include <string.h>

IPC::IPC()
{
    NET_DVR_Init();
}

IPC::~IPC()
{
    NET_DVR_Cleanup();
}

//QString UserName, QString Password, QString IPAddress, int Port

int IPC::LoginToDevice(QString UserName, QString Password, QString IPAddress, int Port)
{
    NET_DVR_USER_LOGIN_INFO user_info;
    NET_DVR_DEVICEINFO_V40 device_info;

    strcpy(user_info.sDeviceAddress, IPAddress.toLocal8Bit().data());
    user_info.wPort = Port;
    strcpy(user_info.sUserName, UserName.toLocal8Bit().data());
    strcpy(user_info.sPassword, Password.toLocal8Bit().data());

    return NET_DVR_Login_V40(&user_info, &device_info);
}


int IPC::StartRealPlay(int dev_id, WId win_id)
{
   NET_DVR_CLIENTINFO client_info;

   client_info.lChannel =  1;
   client_info.lLinkMode = 0;
   client_info.hPlayWnd = win_id;

   return NET_DVR_RealPlay_V30(dev_id, &client_info, NULL, NULL, 1);
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
