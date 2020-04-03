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
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//MAKEWORD是合成一个字，用来表示版本信息的
	//指向一个WSADATA的指针。
	SOCKET sServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//socket函数调用成功会返回一个套接字描述符,失败则返回INVALID_SOCKET
	//调用socket时应该使用PF_INET (协议族)
	//指定新套接字描述符的类型  SOCK_STREAM是流套接字
	//指定应用程序所使用的通信协议
 
	printf("socket create successfully\n");
	struct sockaddr_in ServerAddr;
	//sockaddr结构体是为了保持各个特定协议之间的兼容性而设计的
	//是一个用来存储地址信息的结构体
	//为bind()函数指定地址和端口时，向sockaddr_in结构体填充相应的内容
	
 
	printf("init connect ...\n");
 
 
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//inet_addr转换函数把点分十进制表示的IP地址转换为in_addr结构体可以接受的类型
	ServerAddr.sin_port = htons(1234);
	//htons() 转换字节序
	int err_log=connect(sServer, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
    //将套接字进行连接
		//创建好的套接字描述符
		//指向sockaddr结构体的指针。sockaddr结构体中保存了服务器的IP地址和端口号
		//指定sockaddr结构体的长度
	if(err_log==0) printf("connect successfully\n");
 
	char szMsg[MAXBYTE] = { 0 };
 
 
	recv(sServer, szMsg, MAXBYTE, 0);
    
	cout << szMsg << endl;
	//接受消息
	//使用方法与send相同
	printf("Client Msg : %s \r\n", szMsg);
 
 
	lstrcpy(szMsg, "hello Server!\r\n");
	send(sServer, szMsg, strlen(szMsg) + sizeof(char), 0);
 
 
	WSACleanup();
	system("pause");
	return 0;
}
 