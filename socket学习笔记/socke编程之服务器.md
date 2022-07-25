# socke编程之服务器

```c++
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    //向客户端发送数据
    char str[] = "http://c.biancheng.net/socket/";
    write(clnt_sock, str, sizeof(str));
   
    //关闭套接字
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
```



服务器上命名socket：bind()函数

```c++
int bind(int sockfd,const struct sockaddr* my_addr,socklen_t addrlen);
/*
sockfd表示的是socket；
my_addr就是这个socket所要绑定的地址信息；
addrlen指的是这个socket地址的长度
如果绑定成功，则函数返回0，否则返回-1;
*/
bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
//此处服务器内这一行代码是为了，将服务器的地址信息结构体serv_addr与之前创建的serv_sock的socket绑定起来
```

​	bind函数将my_addr所指向的socket地址分配给未命名的socket。在创建socket时，我们只是制定了地址族，并没有具体地指定具体的地址。通过bind函数，将socket与地址进行绑定。这样客户端才知道如何连接。而客户端一般不需要bind函数，只有服务器才需要bind函数。



服务器监听socket：listen函数

```c++
int listen(int sockfd,int backlog);
/*
sockfd指的是希望进入等待连接请求状态的socket，传入的fd也就会成为服务器端的socket
backlog指的是等待连接的队列的长度

*/
```

​	服务器在设置为监听状态之后，就处于等待连接请求状态，

服务器接收连接：accept()函数

```c++
int accept(int sockfd,struct sockaddr* addr,socklen_t* addrlen);
/*
sockfd指的是服务器端的socket
add指的是发起连接请求的客户端的socket地址结构体
addrlen指的是第二个参数的地址结构体的大小
*/
//accept函数返回值是一个客户端的socket

```



服务器写入信息：write()函数

```c++
ssize_t write(int sockfd,const void* buff,ssize_t nbytes);
/*
sockfd指的是所要写入的目标socket；
buff保存着所要写入的文件信息；
nbytes指的是写入信息的大小
*/
//write函数返回的是写入的字节数

```

