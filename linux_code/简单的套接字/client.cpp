#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch='A';
	// 为客户创建一个套接字
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	// 根据服务器情况给套接字命名：
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "server_socket");
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
/* 套接字三个属性：域，类型，协议。
地址作为名字，格式随域（又叫协议族）变化。每个协议族可以使用一个或过个地址族定义地址格式。
1. 套接字的域
	1.1 最常见的是AF_INET,指internet网络。其地址族是IP。 
		IP+端口 连接指定服务
		标准服务：打印机 515，rlogin 513，ftp 21， httpd 80
	1.2 AF_UNIX 是UNIX文件系统域。 底层协议就是文件输入\输出,地址就是文件名。本例子服务器套接字的地址是server_socket,当运行服务器程序，可以在当前目录下看到。
2. 套接字的类型
	2.1 流套接字 SOCK_STREAM
		有序、双向字节流。
	2.2 数据报套接字 SOCL_DGRAM
		限制发送长度
3. 套接字协议
	3.1 只要传输机制允许就可以选择特定的协议。
	本章中使用UNIX网络套接字和文件系统套接字，使用默认值即可。
	
4. 创建套接字
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	返回一个描述符，类似底层文件描述符，当连接之后可以read和write。close关闭。
5. 套接字地址
	unix
	struct sockaddr_un{
		sa_family_t sun_family;
		char sunpath[];
	}
	
	inet
	struct sockaddr_in{
		short int sin_family; 
		unsigned short int sin_port; // 端口 
		struct in_addr sin_addr; // IP
	}
	IP结构
	struct in_addr{
		unsigned long int s_addr;
	}
	
6. 命名套接字
	想让socket被其他进程使用，服务器程序必须给套接字命名。
	int bind(int socket,const struct sockaddr *address, size_t address_len);
	需要将特定的地址结构指针转换为指向通用地址类型(struct sockaddr*)
	返回0成功，返回1失败并设置errno。
7. 创建套接字队列
	#include <sys/socket.h>
	
	int listen(int socket, int backlog);
	等待处理的连接个数不超过backlog，后面的连接都被拒绝。
	此函数允许服务器程序处理前一个客户请求时，将后续客户放入队列等待处理。
8. 接受连接
	#include <sys/socket.h>
	int accept(int socket, struct sockaddr *address, size_t* address_len);
	accept系统调用只有当客户程序试图连接到由socket参数指定的套接字上时才返回。
	这里的客户指，在套接字队列中排在第一个未处理的连接。
	如果队列中没有连接，accept将阻塞（程序暂停）直到有客户建立连接为止。
	可以通过对套接字文件描述符设置O_NONBLOCK标志来改变这一行为。
	int flags = fcntl(socket,F_GETFL,0);
	fcntl(socket,F_SETFL,O_NONBLOCK|flags);
	*返回值 0 成功，-1 失败，并设置errono
9. 关闭套接字
	可以用close
	对于服务器，应该在read返回0时关闭。
*/
	
/* 面临的问题
1. 主机字节序和网络字节序
	unsigned long int htonl(unsigned long int hostlong);    // 主机->网络
	unsigned short int htons(unsigned short int hostshort);
	unsigned long int ntohl(unsigned long int netlong);     // 网络->主机
	unsigned short int ntohs(unsigned short int netshort);
	为了不同结构的计算机都能正确使用服务，需要此转换。
*/

/*
1. 网络信息
	主机数据库函数在接口头文件netdb.h中声明。
	#include <netdb.h>
	struct hostent *gethostbyaddr(const void*addr, size_t len, int type);
	struct hostent *gethostbyname(const char* name);
	函数返回值包含以下成员
	struct hostent{
		char* h_name       // 主机名
		char** h_aliases   // 别名表
		int h_addrtype;    // 地址类型
		int h_length;      // 地址长度
		char** h_addr_list // 地址表
	}
	如果没有我们查询的主机或地址，返回一个空指针。
	服务名称和端口也可以查询
	#include <netdb.h>
	struct servent *getservbyname(const char* name, const char* proto);
	struct servent *getservbyport(int port, const char* proto);
	proto 参数指定连接该服务的协议。tcp和udp
	函数返回值包含以下成员
	struct servent{
		char* s_name;     // 服务名
		char** s_aliases; // 别名表
		int s_port;       // the ip port number
		char* s_proto;    //servece type,"tcp" or "udp"

*/

/*
1. 因特网守护进程（xinetd/inetd)
	linux 采用xinetd
2. 设置套接字选项
	#include <sys/socket.h>
	int setsockopt(int socket, int level, int option_name, const void* option_value, size_t option_len);
	leivel指定设置哪个协议。
3. 多个客户