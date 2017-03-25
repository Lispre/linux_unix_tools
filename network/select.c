int main(void)
{
    int nready;
    int maxfd = listenfd;
    fd_set rset;
    fd_set allset;
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    //定义一个保存文件描述符的数组
    int i = 0;
    for (i = 0; i < FD_SIZE; i++)
    {
        //-1表示空闲
        client[i] = -1;
    }
    int client[FD_SETSIZE];
    while (1)
    {
        rset = allset;
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if (nready == -1) 
        {
            //中断
            if (errno == EINTR)
            {
                continue;
            }
            ERR_EXIT("select");
        }
        //超时
        if (nready == 0)
        {
            continue;
        }
        //检查是否是listenfd产生了事件
        if (FD_ISSET(listenfd, &rset))
        {
            conn = accept();
            if (conn == -1)
            {
                ERR_EXIT("accept");
            }
            for (i = 0; i < FD_SIZE; i++)
            {
                if(client[i] < 0)
                {
                    client[i] = conn;
                    break;
                }
                if (i == FD_SIZE)
                {
                    fprintf(stderr, "too many clients\n");
                    exit(EXIT_FAILURE);
                }
                FD_SET(conn, &allset);
                if (--nready <= 0)
                {
                    continue;
                }
            }
            for (i = 0; i < FD_SIZE; i++)
            {
                conn = client[i];
                if (conn == -1)
                {
                    continue;
                }
                if (FD_ISSET(conn, &reset))
                {
                    
                }
            }
        }
    }
}
