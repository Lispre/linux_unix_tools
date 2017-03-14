int getlocalip(char* ip)
{
    struct hostent* hp;
    char host[100];
    if ((hp = gethostbyname(host)) == NULL)
    {
        return -1;
    }
    strcpy(ip, inet_ntoa(*(struct in_addr*)hp->h_addr_list[0]));
    return 0;
}