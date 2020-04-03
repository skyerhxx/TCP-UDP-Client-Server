// TCP客户端.cpp : 定义控制台应用程序的入口点。
//
#include"stdafx.h"
#include<stdio.h>
#include<winsock2.h>
#include<iostream>
#pragma comment (lib,"ws2_32")
using namespace std;
int main()
{
	//WSA是web server API的简写
 
	WSADATA wsaData;
		//给WSAStartup初始化用的数据结构
 
	printf("init socket ...\n");
 
 
	WSAStartup(MAKEWORD(2,2), &wsaData);
	    //MAKEWORD是合成一个字，用来表示版本信息的
		//指向一个WSADATA的指针。
 
	printf("init successfully\n");
	printf("create TCP socket...\n");
 
	SOCKET sLisent = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//socket函数调用成功会返回一个套接字描述符,失败则返回INVALID_SOCKET
		//调用socket时应该使用PF_INET (协议族)
		//指定新套接字描述符的类型  SOCK_STREAM是流套接字
		//指定应用程序所使用的通信协议
	
	printf("socket create successfully\n");
	
	
	struct sockaddr_in ServerAddr;
	   //sockaddr结构体是为了保持各个特定协议之间的兼容性而设计的
	   //是一个用来存储地址信息的结构体
	   //为bind()函数指定地址和端口时，向sockaddr_in结构体填充相应的内容
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		//inet_addr转换函数把点分十进制表示的IP地址转换为in_addr结构体可以接受的类型
	ServerAddr.sin_port = htons(1234);
		//htons() 转换字节序
	
	bind(sLisent, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
    //绑定套接字与地址信息
	    //新建的套接字描述符
		//一个sockaddr的结构体
		//sockaddr结构体的大小
 
	printf("bind successfully\n");
 
	listen(sLisent, SOMAXCONN);
	//端口监听
		//要监听的套接字描述符
		//允许进入请求连接队列的个数，其最大值由系统指定,在winsock2.h中,其最大值由SOMAXCONN表示
	sockaddr_in ClientAddr;
	int nSize = sizeof(ClientAddr);
	
	printf("wait for a connection on port %d\n", 1234);
 
 
	SOCKET sClient;
	sClient = accept(sLisent, (SOCKADDR *)&ClientAddr, &nSize);
	//获取连接请求----该函数从请求队列中获取连接信息，创建新的套接字描述符，获取客户端地址。新创建的套接字用于和客户端通信
		//处于监听的套接字描述符
		//指向一个sockaddr结构体的指针，用来返回客户端的地址信息
		//指向int型的指针变量,用来传入sockaddr结构体的指针大小
    //sClient获得接受的套接字描述符
	printf("ClientIP=%s:%d\r\n", inet_ntoa(ClientAddr.sin_addr),
		ntohs(ClientAddr.sin_port));
 
 
	char szMsg[MAXBYTE] = { 0 };
	lstrcpy(szMsg, "hello Client!\r\n");
	send(sClient, szMsg, strlen(szMsg) + sizeof(char), 0);
	//发送消息
		//accept()函数返回的套接字描述符
		//发送消息的缓冲区
		//缓冲区的长度
		//通常赋0
	 
	recv(sClient, szMsg, MAXBYTE, 0);
	//接受消息
		//使用方法与send相同
	printf("Client Msg : %s \r\n", szMsg);
 
 
 
	WSACleanup();
	system("pause");
	return 0;
}
 