void do_service(int conn)
{
	char recvbuf[1024];
	while (1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		int ret = read(conn, recvbuf, sizeof(recvbuf));
		if (ret == 0)
		{
			printf("client close");
		}
		else if (ret == -1)
		{
			ERR_EXIT("recive data error");
		}
		/*process data here*/
		fputs(recvbuf, stdout);
		write(conn, recvbuf, ret);
	}
}

void accept_and_do_service(int listenfd)
{
	int conn;
	pid_t pid;
	struct sockaddr_in peeraddr;
	memset(&peeraddr, 0, sizeof(peeraddr));
	socklen_t peerlen = sizeof(peeraddr);
	while (1)
	{
		if (conn = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen) < 0)
		{
			ERR_EXIT("accept connection");
		}
		printf("peer ip = %s port= %s\n",
			inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
		pid = fork();
		if (pid == -1)
		{
			ERR_EXIT("fork");
		}
		else if (pid == 0)
		{
			close(listenfd);
			/*这个是子进程处理具体任务的函数*/
			do_service(conn);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(conn);
		}
	}
}