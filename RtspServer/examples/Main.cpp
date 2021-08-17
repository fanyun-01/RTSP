/*****************************************************************************
* Copyright (C) 2017-2020 Hanson Yu  All rights reserved.
------------------------------------------------------------------------------
* File Module       : 	Main.cpp
* Description       : 	RtspServer Demo

���˼·:
����ƵԴ��socket����������Ϊrtspserver�Ĳ���
�����ĻỰ�ȴ��̵߳õ��µ�socket����newһ��rtspserver
Ȼ���new���������rtspserver������socket���� Ҳ���ǻỰ���浽������
ͬʱ��һ���̲߳���ȥ��������Ự���С�
����,rtsp������Գ�������ŵ�������е����С�

�����ƣ�
1.ʹ��vlc��Ϊ�ͻ����޷����ţ�ֻ��ʹ�ö�Ӧ�Ŀͻ���
2.����URLĿǰ����RTSP_SERVER_URL�궨��д���ģ�����Ҫ��Ϊ������
�����Ż�Ϊ���ô�ip��Ĭ�϶˿ڵķ�ʽ��
3.rtspĿǰֱ������MediaHandle VideoHandle�������������ģʽ
4.MediaHandle��ȡý�������Ϣ�����߳̿��Ǽ�����

* Created           : 	2017.11.21.
* Author            : 	Yu Weifeng
* Function List     : 	
* Last Modified     : 	
* History           : 	
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/11/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Definition.h"
#include "RtspServer.h"

using std::cout;
using std::endl;


#define MAX_CHANNEL     16
#define RTSP_SERVER_URL "rtsp://%s:8554/1"
#define RTSP_SERVER_PORT 8554

static void PrintUsage(char *i_strProcName);

/*****************************************************************************
-Fuction        : main
-Description    : main
-Input          : 
-Output         : 
-Return         : 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/11/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
int main(int argc,char **argv)
{
    int iRet = FALSE;
    RtspServer * pRtspServer = NULL; 
    char strURL[128];
    
    if (argc != 3) //��������������ݴ���
    {
        PrintUsage(argv[0]);
    }
    else
    {
        memset(strURL,0,sizeof(strURL));
        snprintf(strURL,sizeof(strURL),RTSP_SERVER_URL,argv[1]);
        cout<<"Rtsp server url:"<<strURL<<endl;
        pRtspServer = new RtspServer();
        if(pRtspServer!=NULL)
        {
            iRet = pRtspServer->Init((char *)strURL,argv[2]);//��������������ڲ��ᱣ��Ự������,�����̹߳���ö���
        }
        if(iRet == TRUE)
        {
            while(1)
            {
                pRtspServer->WaitConnectHandle();//��������������ڲ��ᱣ��Ự������,�����̹߳���ö���
            }
        }
        else
        {
            PrintUsage(argv[0]);
        }
    }
    //process exit handle
    if(pRtspServer!=NULL)
    {
        delete pRtspServer;
    }
    return 0;
}

/*****************************************************************************
-Fuction        : PrintUsage
-Description    : PrintUsage
-Input          : 
-Output         : 
-Return         : 
* Modify Date	  Version		 Author 		  Modification
* -----------------------------------------------
* 2017/11/21	  V1.0.0		 Yu Weifeng 	  Created
******************************************************************************/
static void PrintUsage(char *i_strProcName)
{
    cout<<"Usage: "<<i_strProcName<<" 192.168.7.199"<<" <H264FILE> "<<endl;
    cout<<"Usage: "<<i_strProcName<<" 192.168.7.199"<<" <G711AFILE>"<<endl;
    cout<<"Usage: "<<i_strProcName<<" 192.168.7.199"<<" <H265FILE>"<<endl;
    cout<<"eg: "<<i_strProcName<<" 192.168.7.199"<<" sintel.h264"<<endl;    
}

