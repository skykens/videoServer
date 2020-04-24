/* File Name: client.c */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "../CommonProto.pb.h"
using namespace std;
#define MAXLINE 4096


int main(int argc, char** argv)
{
    int    sockfd;
    struct sockaddr_in    servaddr;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
    printf("inet_pton error for %s\n","127.0.0.1");
    exit(0);
    }
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }


    while(1)
    {
        NetWork::head hea;
        NetWork::tail tai;
        NetWork::clientLogin login;
        login.set_name("nihao");
        login.set_psw("123123");
        hea.set_func_id(1);
        hea.set_error_msg("hello:");
        hea.set_optid(NetWork::T_login);
        size_t head_size=hea.ByteSize(),body_size=login.ByteSize(),tail_size=tai.ByteSize();
        char str[head_size+body_size+tail_size];
        hea.SerializeToArray(str,head_size);
        login.SerializeToArray(str+head_size,body_size);
        tai.SerializeToArray(str+head_size+body_size,tail_size);

        if(send(sockfd,str,head_size+body_size+tail_size,0)!=head_size+body_size+tail_size)
            cout<<"error!"<<endl;
        else
            cout<<"successful"<<endl;
        sleep(1);

    }


}


