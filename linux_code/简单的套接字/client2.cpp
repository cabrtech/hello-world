#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#inlcude <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch='A';
	// 为客户创建一个套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// 根据服务器情况给套接字命名：
	address.sun_family = AF_UNIX;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 9734;
	// clinet3.cpp
	// address.sin_port = htons(9374);
	len = sizeof(address);
	
	// 将我们的套接字连接到服务器的套接字
	result = connect(sockfd,(struct sockaddr*)&address, len);
	if(result == -1){
		perror("oops: client1");
		exit(1);
	}
	// 现在就可以通过sockfd进行读写操作了
	write（sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server = %c\n", ch);
	close(sockfd);
	exit(0);
}


	