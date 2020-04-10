/*
 * epollServer.h
 *
 *  Created on: Dec 15, 2014
 *      Author: echgchi
 */

#ifndef EPOLLSERVER_H_
#define EPOLLSERVER_H_

#define IPADDRESS   "127.0.0.1"
#define PORT        8787
#define MAXSIZE     1024
#define LISTENQ     5
#define FDSIZE      1000
#define EPOLLEVENTS 100

class epollServer {
public:
	epollServer();
	virtual ~epollServer();
	void * startEpollServer();


private:

	int socket_bind(const char* ip, int port);

	void do_epoll(int listenfd);

	void
	handle_events(int epollfd, struct epoll_event *events, int num,
			int listenfd, char *buf);

	void handle_accpet(int epollfd, int listenfd);

	void do_read(int epollfd, int fd, char *buf);

	void do_write(int epollfd, int fd, char *buf);

	void add_event(int epollfd, int fd, int state);

	void modify_event(int epollfd, int fd, int state);

	void delete_event(int epollfd, int fd, int state);

};

#endif /* EPOLLSERVER_H_ */
