#include <event.h>
#include <event2/listener.h>
#include <server.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef PERR

#define PERR(fmt,arg ...) fprintf(stderr,"[%s:%d]"fmt,__FUNCTION__,__LINE__, ## arg)

#endif

int ServerInit(struct Server_t *s)
{
        struct sockaddr_in addr={0};
        int ret=0;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(s->port);
        s->base = event_base_new();
        if(s->base==NULL) {
                PERR("event_base_new_err\n");
                goto event_base_new_err;
        }
        s->listener=evconnlistener_new_bind(s->base, ServerListen, s,LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,10, (struct sockaddr*)&addr,sizeof(addr));
        if(s->listener==NULL) {
                PERR("evconnlistener_new_bind_err");
                goto evconnlistener_new_bind_err;
        }
        ret=event_base_dispatch(s->base);
        if(ret<0) {
                PERR("event_base_dispatch_err");
                goto event_base_dispatch_err;
        }
        return 0;
event_base_dispatch_err:
        evconnlistener_free(s->listener);
evconnlistener_new_bind_err:
        event_base_free(s->base);
event_base_new_err:
        return ret;
}

void ServerListen(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sock, int socklen, void *arg)
{
        struct Server_t *s=arg;
        struct bufferevent *bev =  bufferevent_socket_new(s->base, fd,BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, ServerRead, ServerWrite, ServerEvent, s);
        bufferevent_enable(bev, EV_READ | EV_PERSIST);
}

void ServerRead(struct bufferevent *bev, void *arg)
{

}

void ServerWrite(struct bufferevent *bev,void *arg)
{

}

void ServerEvent(struct bufferevent *bev, short events, void *arg)
{
        if (events & BEV_EVENT_EOF)
                printf("connection closed\n");
        else if (events & BEV_EVENT_ERROR)
                printf("some other error\n");
        bufferevent_free(bev);
}
