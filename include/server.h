#ifndef SERVER_H
#define SERVER_H

struct Server_t {
        struct event_base *base;
        const char *ip;
        int port;
        struct evconnlistener *listener;
};

int ServerInit(struct Server_t *s);

void ServerListen(struct evconnlistener *listener,evutil_socket_t fd,struct sockaddr *sock,int socklen,void *arg);

void ServerRead(struct bufferevent *bev,void *arg);

void ServerError(struct bufferevent *bev,short events,void *arg);

#endif // SERVER_H
