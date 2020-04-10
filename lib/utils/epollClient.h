/*
 * epollClient.h
 *
 *  Created on: Dec 15, 2014
 *      Author: echgchi
 */

#ifndef EPOLLCLIENT_H_
#define EPOLLCLIENT_H_

#define MAXSIZE     1024
#define IPADDRESS   "127.0.0.1"
#define SERV_PORT   8787
#define FDSIZE        1024
#define EPOLLEVENTS 20

class epollClient {
public:
	epollClient();
	virtual ~epollClient();
	int startEpollClient();
private:
	void handle_connection(int sockfd);
	void handle_events(int epollfd, struct epoll_event *events, int num,
			int sockfd, char *buf);
	void do_read(int epollfd, int fd, int sockfd, char *buf);
	void do_write(int epollfd, int fd, int sockfd, char *buf);
	void add_event(int epollfd, int fd, int state);
	void delete_event(int epollfd, int fd, int state);
	void modify_event(int epollfd, int fd, int state);

};

#endif /* EPOLLCLIENT_H_ */
