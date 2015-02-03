#include "wzcache.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void setupConnection()
{
    int server_sockfd;//server socket fd
    int client_sockfd;//client socket fd
    int len;
    struct sockaddr_in my_addr;   //structure of server socket
    struct sockaddr_in remote_addr; //structure of client socket
    int sin_size;
    char buf[BUFSIZ];  //data buffer size
    memset(&my_addr,0,sizeof(my_addr)); //set buffer conent to 0
    my_addr.sin_family=AF_INET; //set to IP protocol
    my_addr.sin_addr.s_addr=INADDR_ANY;//Allow all connections from any address
    my_addr.sin_port=htons(8000); //server listening port

    /*Create TCP based socket connection*/
    if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        return 1;
    }

    /*Bind the socket to the network address*/
    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind");
        return 1;
    }

    /*Listening to the incoming request, size is 5 TODO#make it configurable*/
    listen(server_sockfd,5);

    sin_size=sizeof(struct sockaddr_in);

    /*Wait for connection*/
    if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0)
    {
        perror("accept");
        return 1;
    }
    printf("accept client %s/n",inet_ntoa(remote_addr.sin_addr));
    len=send(client_sockfd,"Welcome to my server/n",21,0);//发送欢迎信息

    /*TODO#handler logic here*/
    close(client_sockfd);
    close(server_sockfd);
    return 0;
}

int main(int argc, char *argv[])
{
    setupConnection();

}
