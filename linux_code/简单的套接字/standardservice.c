// 连接到标准服务
// 头文件
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char*argv[])
{
	char* host;
	int sockfd;
	int len, result;
	struct sockaddr_in address;
	struct hostent *hostinfo;
	struct servent *servinfo;
	char buffer[128];
	if(argc==1)
		host = "localhost";
	else
		host = argv[1];
	hostinfo = gethostbyname(host);
	// 查找主机地址，如果找不到，打印一条错误。
	if(!hostinfo){
		fprintf(stderr,"no host:%s\n",host);
		exit(1);
	}
	// 检查主机上是否有daytime服务。
	servinfo = getservebyname("daytime","tcp");
	if(!servinfo){
		fprintf(stderr,"no daytime service\n");
		exit(1);
	}
	printf("daytime port is %d\n", ntohs(servinfo->s_port));
	// 创建一个套接字
	sockfd = socket(AF_INET,SOCK_SREAM,0);
	// 构造connect调用要使用的地址
	address.sin_family = AF_INET;
	address.sin_port = servinfo->s_port;
	address.sin_addr = *(struct inaddr*)*hostinifo->haddr_list;
	len = sizeof(address);
	// 建立连接并取得有关信息。
	result = connect(sockfd,(struct sockaddr*)&address, len);
	if(result==-1){
		perror("oops:getdate");
		exit(1);
	}
	result = read(sockfd,buffer,sizeof(buffer));
	buffer(result) = '\0';
	printf("read %d bytes:%s",result,buffer);
	
	close(sockfd);
	exit(0);
} 
	