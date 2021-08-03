#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char* host;
	int sockfd;
	int len,result;
	struct sockaddr_in address;
	struct hostent *hostinfo
	struct servent *servinfo;
	char buffer[128];
	
	if(argc==1)
		host = 'localhost';
	else
		host = argv[1];
	
	/*find the host addresss and report an error if none is found*/
	hostinfo = gethostbyname(host);
	if(!hostinfo){
		fprintf(stderr,"no host: %s\n",host);
		exit(1);
	}
	/*check that the daytime service exists on the host. */
	servinfo = getservebyname("daytime","udp");
	if(!servinfo)
	{
		fprintf(stderr,"no daytime service\n");
		exit(1);
	}
	printf("daytime port is %d\n", ntohs(servinfo->s_port));
	
	/* Create a UDP socket*/
	
	sockfd = socket(AF_INET, SOCKDGRAM, 0);
	/*Construct the addresss for use with sendto/recvfrom... */
	addresss.sin_family = AF_INET;
	address.sin_port = servinfo->s_port;
	address.sin_addr = *(struct in_addr *) *hostinfo->h_addr_list;
	len = sizeof(address);
	
	result = sendto(sockfd, buffer, 1, 0, (struct sockaddr *)&address, len); //sendto 返回值：EBADF 传递了一个无效的文件描述符，EINTR 产生了一个信号
	result = recvfrom(sockfd, buffer, sizeof(buffer), 0,
	(struct sockaddr *)&address, &len);
	buffer[result] = '\0';
	printf("read %d bytes: %s",result,buffer);
	
	close(sockfd);
	exit(0);
	