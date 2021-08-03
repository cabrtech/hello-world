#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char* host,**names,**addrs;
	struct hostent *hostinfo;
	// 1)host变量设置为getname程序所提供的命令行参数，或默认设置为用户主机的主机名。
	if(argc == 1){
		char myname[256];
		gethostname(myname,255);
		host = myname;
	}
	else
		host = argv[1];
	// 2)调用gethostbyname 如果没找到相应的信息，就报告一条错误。
	hostinfo = gethostbyname(host);
	if(!hostinfo){
		fprintf(stderr,"cannot get info for host: %s\n, host");
		exit(1);
	}
	// 3)显示主机名和它可能有的别名
	printf("results for host %s:\n", host);
	printf("Name: %s\n", hostinfo->h_name);
	printf("Aliases:");
	names = hostinfo->h_aliases;
	while(*name){
		printf("%s",*names);
		names++;
	}
	printf("\n");
	// 4)如果查询的主机不是一个ip主机，就发出警告并退出：
	if(hostinfo->h_addrtype != AF_INET){
		fprintf(stderr, "not an IP host!\n");
		exit(1);
	}
	// 5)否则，显示它的所有IP地址
	addrs = hostinfo->h_addr_list;
	while(*addrs){
		printf("%s",inet_ntoa(*(struct in_addr*)*addrs));
		addrs++;
	}
	printf("\n");
	exit(0);