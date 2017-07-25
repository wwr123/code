int Socket(const char *host, int clientPort)  
{  
    int sock;  
    unsigned long inaddr;  
    struct sockaddr_in ad;  
    struct hostent *hp;  
  
    /* 初始化地址 */  
    memset(&ad, 0, sizeof(ad));  
    ad.sin_family = AF_INET;   //ipv4
  
    /* 尝试把主机名转化为数字 */  
    inaddr = inet_addr(host);  //把ip地址转化为网络字节序
    if (inaddr != INADDR_NONE)  //INADDR_NONE是0xffffffff
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));  
    else  
    {  
        /* 取得 ip 地址 */  
        hp = gethostbyname(host);  //百度一下
        if (hp == NULL)  
            return -1;  
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);  //hp->h->addr中以二进制存储的ip地址
    }  
    ad.sin_port = htons(clientPort);  
  
    /* 建立 socket */  
    sock = socket(AF_INET, SOCK_STREAM, 0);  
    if (sock < 0)  
        return sock;  
    /* 建立链接 */  
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)  
        return -1;  
    return sock;  
}  