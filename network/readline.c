ssize_t readline(int conn, void* buf, size_t maxline)
{
    int ret;
    int nread;
    char* bufp = buf;
    int nleft = maxline;
    while (1)
    {
        ret = recv_peek(conn, bufp, nleft)
        if (ret < 0)
        {
            return ret;
        }
        else if (ret == 0)
        {
            return ret; 
        }
        nread = ret;
        int i;
        for (i = 0; i < nread; i++)
        {
            if (bufp[i] == '\n') {
                ret = readn(conn, bufp, i+1);
                if (ret != i+1)
                {
                    exit(EXIT_FAILTURE);
                }
                return ret;
            }
        }
        if (nread > nleft)
        {
            exit(EXIT_FAILTURE);
        }
        nleft -= nread;
        ret = readn(conn, bufp, nread);
        if (ret != nread)
        {
            exit(EXIT_FAILTURE);
        }
        bufp += nread;
    }
    return -1;
}