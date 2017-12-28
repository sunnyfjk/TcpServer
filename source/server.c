#include <event.h>
#include <event2/listener.h>

#include "server.h"
#include <arpa/inet.h>


#ifndef PERR

#define PERR(fmt,arg ...) fprintf(stderr,"[%s:%d]"fmt,__FUNCTION__,__LINE__, ## arg)

#endif

int ServerInit(struct Server_t *s)
{
        struct sockaddr_in addr={0};
        int ret=0;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(s->port);
        ret=inet_pton(AF_INET,s->ip,&addr.sin_addr);
        if(ret<0) {
                PERR("inet pton err! ip=%s\n",s->ip);
                goto inet_pton_err;
        }
        return 0;
inet_pton_err:
        return ret;
}

void ServerListen(struct evconnlistener *listener, int fd, struct sockaddr_in *sock, int socklen, void *arg)
{

}

void ServerRead(struct bufferevent *bev, void *arg)
{

}

void ServerError(struct bufferevent *bev, short events, void *arg)
{

}
