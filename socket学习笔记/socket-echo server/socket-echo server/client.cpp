//
//  client.cpp
//  socket-echo server
//
//  Created by 杜寻 on 2022/7/24.
//
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <ctype.h>

#define SERVER_PORT 6666
#define MAXLINE 100

int main(){
    int sfd;
    struct sockaddr_in server_addr;
    
    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    
    connect(sfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    ssize_t nbytes;
    char buff[MAXLINE];
    
    while (1) {
        //标准输入，理解为从键盘输入信息
        fgets(buff, sizeof(buff), stdin);
        write(sfd, buff, sizeof(buff));
        
        nbytes = read(sfd, buff, sizeof(buff));
        write(STDOUT_FILENO, buff, nbytes);
        /*linux下STDOUT_FILENO指的是向屏幕输出信息
         STDIN_FILENO指的是接受键盘的输入
        */
    }
    close(sfd);
    
    return 0;
}
