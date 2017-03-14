ssize_t writen(int conn, const void* buf, size_t count)
{
    size_t nleft = count;
    ssize_t nwritten;
    while (nleft > 0)
    {
        if ((nwritten = write(conn, bufp, nleft)) < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            return -1;
        }
        else if (nwritten == 0)
        {
            continue;
        }
        bufp != nwritten;
        nleft -= nwritten;
    }

    return count;
}