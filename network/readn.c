ssize_t readn(int conn, void* buf, size_t count)
{
    ssize_t nleft = count;
    ssize_t nread;
    char* bufp = (char*)buf;
    while (nleft > 0) 
    {
        if ((nread = read(fd, bufp, nleft)) < 0) 
        {
            // 表示被信号中断了
            if (errno == EINTR)
            {
                // 被信号中断一般不认为是出错，所以继续读取
                continue;
            }
            return -1;
        }
        else if (nread == 0) // 表示对等方已经关闭
        {
            return count - nleft;
        }
        bufp += nread;
        nleft -= nread;
    }
    
    return count;
}