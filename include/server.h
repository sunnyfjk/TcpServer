#ifndef SERVER_H
#define SERVER_H

struct Server_t {
        const char *ip;
        int port;
        struct event_base *base;
        struct evconnlistener *listener;
        struct event *signal_event;
};

int ServerInit(struct Server_t *s);

void ServerListen(struct evconnlistener *listener,evutil_socket_t fd,struct sockaddr *sock,int socklen,void *arg);

void ServerRead(struct bufferevent *bev,void *arg);

void ServerWrite(struct bufferevent *bev,void *arg);

void ServerEvent(struct bufferevent *bev,short events,void *arg);

void ServerSignalEvent(evutil_socket_t sig, short events, void * arg);

#endif // SERVER_H
