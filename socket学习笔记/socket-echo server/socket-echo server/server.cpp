//
//  server.cpp
//  socket-echo server
//
//  Created by 杜寻 on 2022/7/24.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <ctype.h>

#define SERVER_PORT 6666   //宏定义后面不加分号
#define MAX_LINE 100

int main(){
    /*
     首先定义好服务器端需要的socket
     用于客户端的socket cfd
     用于服务端的socket sfd
     用于保存客户端socket地址信息的结构体 client_addr
     用于保存服务端的socket地址信息的结构体 serv_addr
     
     */
    int sfd,cfd;
    
    struct sockaddr_in server_addr,client_addr;
    
    bzero(&server_addr,sizeof(server_addr)); //先将结构体全部置0
    server_addr.sin_family = AF_INET; //设置IPV4地址族
    server_addr.sin_port = htons(SERVER_PORT); //设置端口号，用网络字节序表示
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//设置IP地址
    //创建服务器端socket
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    //对服务器端socket命名，将它绑定到服务器地址结构体上
    bind(sfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
    //将服务器端socket置于监听状态
    listen(sfd, 21);
    
    socklen_t client_len;
    char buff[MAX_LINE];
    ssize_t nbytes;
    //用accept函数将收到的客户端socket接收下来
    cfd = accept(sfd, (struct sockaddr*)&client_addr, &client_len);
    while(1){
        client_len = sizeof(client_addr);

        //读出客户端所发来的buff上的信息
        nbytes = read(cfd, buff, MAX_LINE);
        
        //对buff中的字符进行改成大写的操作
        for(int i=0;i<(int)nbytes;++i)
            buff[i] = toupper(buff[i]);
        
        
        //将处理好的信息重新写入socket,交给客户端socket
        write(cfd, buff, nbytes);

        
    }
    close(cfd);
    return 0;
}



