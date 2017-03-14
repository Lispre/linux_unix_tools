ssize_t peek_msg(int conn, void* buf, size_t len)
{
    while (1) 
    {
        int ret = recv(conn, buf, len, MSG_PEEK);
        // 表示被信号中断
        if (ret == -1 && errno == EINTR)
        {
            continue;
        }
        return ret;
    }
}