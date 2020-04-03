// UDP客户端.cpp : 定义控制台应用程序的入口点。
//
 
#include "stdafx.h"
#include<stdio.h>
#include<winsock2.h>
#pragma comment (lib,"ws2_32")
	//静态加入一个lib文件,也就是库文件ws2_32.lib文件，提供了对网络相关API的支持
int main()
{
	//WSA是web server API的简写
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//在使用winsock相关函数时需要对winsock库进行初始化，而在使用完成后需要对winsock库进行释放
	//需要初始化winsock库的版本号
	//一个指向WSADATA的指针。该函数的返回值为0，说明函数调用成功。如果调用失败，则返回其他值
	//MAKEWORD是合成一个字，用来表示版本信息的
 
	SOCKET sClient = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//创建套接字
	//指定地址族  AF表示地址族，PF表示协议族
	//指定新套接字描述符的类型
	//指定应用程序所使用的通信协议	
	//sServer就成了一个套接字描述符
	
	printf("socket create successfully\n");
 
	struct sockaddr_in ServerAddr;
 
	printf("init connect ...\n");
 
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(1234);
		//htons() 转换字节序
	//对sockaddr_in结构体填充地址、端口等信息
 
 
	char szMsg[MAXBYTE] = { 0 };
	lstrcpy(szMsg, "Hello Server!\r\n");
	int nSize = sizeof(ServerAddr);
	sendto(sClient, szMsg, strlen(szMsg) + sizeof(char), 0, (SOCKADDR*)&ServerAddr, nSize);
	//该函数是UDP协议双方用来接受数据的函数
	//套接字描述符
	//要发送数据的缓冲区
	//指定第二个参数的长度
	//通常赋0值
	//一个指向sockaddr结构体的指针，这里给出接受消息的地址信息    
	//指定第五个参数的长度
	//之后ServerAddr存的就是接收到的地址信息
 
	nSize = sizeof(ServerAddr);
	recvfrom(sClient, szMsg, MAXBYTE, 0, (SOCKADDR*)&ServerAddr, &nSize);
 
	printf("Server Msg: %s \r\n", szMsg);
	//该函数是UDP协议双方用来接受数据的函数,用法与sendto相同
	WSACleanup();//释放winsock库
 
 
	system("pause");
 
	return 0;
}