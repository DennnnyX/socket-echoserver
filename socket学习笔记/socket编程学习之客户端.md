# socket编程学习之客户端

整个客户端socket的进程为：

Socket()-->connect()-->read()/write()-->close()

```c++
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
  //需要连接的服务器的地址信息设置完毕
  //客户端一般不需要bind函数来命名socket，只有服务器需要
  
  
  //客户端通过connect函数主动与服务器建立连接
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    //读取服务器传回的数据
    char buffer[40];
    read(sock, buffer, sizeof(buffer)-1);
   
    printf("Message form server: %s\n", buffer);
   
    //关闭套接字
    close(sock);

    return 0;
}
```

socket函数创建socket

```c++
int sock = socket(AF_INET,SOCK_STREAM,0);
```

​	先在客户端创建一个socket接口。它的地址族是AF_INET，代表的是使用IPV4地址协议，SOCK_STREAM代表传输层使用TCP协议。最后一个参数是协议参数，默认设置为0；

定义客户端需要连接到服务端的socket地址结构体sockaddr_in

```c++
struct sockaddr_in
{
  sa_family_t sin_family;//定义地址族类型AF_INET
  u_int16_t sin_port;//定义16端口号，需要用来在网络中传输，所以需要的是网络字节序，也就是大端序
  struct in_addr sin_addr //定义了一个IPV4的地址结构体，里面保存了一个ipv4地址;
};serv_addr
struct in_addr
{
  u_int32_t s_addr = inet_addr("127.0.0.1");//32为ipv4地址
};sin_addr
  /*这里涉及到一个inet_addr(const char* strptr)函数，这个函数将输入的点分十进制的ip地址转化为网络字节序表示的ipv4地址
  */
```

客户端如何与服务器建立连接：connect函数

```c++
int connect(int sockfd,const struct sockaddr_in* serv_addr,socklen_t addrlen);
/*
这里的sockfd实际上就是我们开头创建的客户端的socket。
serv_addr是一个sockaddr_in类型的struct指针，意思是服务器所监听的地址，addrlen指的是地址的长度，指定了客户端所要连接的服务器的地址信息。
addrlen指的是这个地址信息的大小
*/
```

客户端读函数读取信息：read()函数

```c++
ssize_t read(int fd,void *buff,size_t nbytes);
/*fd表示读取内容的socket，buff表示存放数据的缓冲区地址，nbytes表示要读取的数据的长度。
	函数读取成功，则返回所读取的字节数
*/
```

