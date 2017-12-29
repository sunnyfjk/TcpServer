
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <server.h>

#ifndef PERR

#define PERR(fmt,arg ...) fprintf(stderr,"[%s:%d]"fmt,__FUNCTION__,__LINE__, ## arg)

#endif

int ServerCreate(struct Server_t *s)
{
        struct sockaddr_in addr={0};
        int ret=-1;
        int
        evthread_use_pthreads();
        addr.sin_family=AF_INET;
        addr.sin_port=htons(s->port);
        s->base = event_base_new();
        if(s->base==NULL) {
                PERR("event_base_new_err\n");
                goto event_base_new_err;
        }
        s->listener=evconnlistener_new_bind(s->base, ServerListen, s,LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE|LEV_OPT_THREADSAFE,-1, (struct sockaddr*)&addr,sizeof(addr));
        if(s->listener==NULL) {
                PERR("evconnlistener_new_bind_err");
                goto evconnlistener_new_bind_err;
        }
        s->signal_event=evsignal_new(s->base, SIGINT, ServerSignalEvent, s);
        if(s->signal_event==NULL) {
                PERR("evsignal_new_err\n");
                goto evsignal_new_err;
        }
        ret=event_add(s->signal_event, NULL);
        if(ret<0) {
                PERR("event_add_err\n");
                goto event_add_err;
        }
        ret=event_base_dispatch(s->base);
        if(ret<0) {
                PERR("event_base_dispatch_err");
                goto event_base_dispatch_err;
        }
        return 0;

event_base_dispatch_err:
        event_del(s->signal_event);
event_add_err:
        event_free(s->signal_event);
evsignal_new_err:
        evconnlistener_free(s->listener);
evconnlistener_new_bind_err:
        event_base_free(s->base);
event_base_new_err:
        return ret;
}
void ServerClose(struct Server_t *s)
{
        event_del(s->signal_event);
        event_del(s->signal_event);
        evconnlistener_free(s->listener);
        event_base_free(s->base);
}
void ServerListen(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sock, int socklen, void *arg)
{
        struct Server_t *s=arg;
        struct bufferevent *bev =  bufferevent_socket_new(s->base, fd,BEV_OPT_CLOSE_ON_FREE|BEV_OPT_THREADSAFE|BEV_OPT_DEFER_CALLBACKS);
        bufferevent_setcb(bev, ServerRead, NULL, ServerEvent, s);
        bufferevent_enable(bev, EV_READ | EV_WRITE);
}

void ServerRead(struct bufferevent *bev, void *arg)
{

        struct evbuffer *input = bufferevent_get_input(bev);
        struct evbuffer *output = bufferevent_get_output(bev);
        evbuffer_add_buffer(output, input);
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
void ServerSignalEvent(evutil_socket_t sig, short events, void * arg){
        struct Server_t *s=arg;
        struct timeval delay={2,0};
        event_base_loopexit(s->base,&delay);
}
