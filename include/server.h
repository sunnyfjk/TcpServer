/**
 * @Author: fjk
 * @Date:   2017-12-29T23:23:46+08:00
 * @Email:  sunnyfjk@gmail.com
 * @Filename: server.h
 * @Last modified by:   fjk
 * @Last modified time: 2017-12-30T11:44:37+08:00
 */

#ifndef SERVER_H
#define SERVER_H

#include <event.h>
#include <event2/listener.h>
#include <list.h>
#include <pthread.h>
struct EventBaseNode_t {
        pthread_t pt;
        size_t cout;
        struct list_head node;
        struct event_base *base;
};
struct Server_t {
        const char *ip;
        int port;
        struct event_base *base;
        struct evconnlistener *listener;
        struct event *signal_event;
        struct list_head root;
};

int ServerCreate(struct Server_t *s);

void ServerClose(struct Server_t *s);

void ServerListen(struct evconnlistener *listener,evutil_socket_t fd,struct sockaddr *sock,int socklen,void *arg);

void ServerRead(struct bufferevent *bev,void *arg);

void ServerWrite(struct bufferevent *bev,void *arg);

void ServerEvent(struct bufferevent *bev,short events,void *arg);

void ServerSignalEvent(evutil_socket_t sig, short events, void * arg);

#endif // SERVER_H
