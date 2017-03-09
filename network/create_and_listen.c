#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#define ERR_EXIT(m) do { \
	perror(m);           \
	exit(EXIT_FAILTURE); \
} while (0)

/**
 * 创建一个socket,并监听
 * @ip: 本地socket的 IP
 * @port: 本地socket的 port
 * 成功返回socket文件描述符
 * 失败返回-1
 */
int create_and_listen(const char* ip, unsigned short port)
{
	int listenfd;
	if ((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	/*if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)*/
	{
		ERR_EXIT("create socket");
	}
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (ip == nullptr) 
	{
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	} 
	else 
	{
		server_addr.sin_addr.s_addr = inet_addr(ip);
		/*inet_aton(ip, &server_addr.sin_addr);*/
	}

	int on = 1;
	/*设置这个是为了解决服务器端关闭时的timewait状态导致无法bind*/
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) 
	{
		ERR_EXIT("set socket reuse");
	}
	if ((bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) 
	{
			ERR_EXIT("bind socket");
	}

	if (listen(listenfd, SOMAXCONN) < 0) 
	{
			ERR_EXIT("listen socket");
	}
	
	return listenfd;
}
