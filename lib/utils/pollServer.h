/*
 * pollServer.h
 *
 *  Created on: Dec 16, 2014
 *      Author: echgchi
 */

#ifndef POLLSERVER_H_
#define POLLSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define IPADDRESS   "127.0.0.1"
#define PORT        8787
#define MAXLINE     1024
#define LISTENQ     5
#define OPEN_MAX    1000
#define INFTIM      -1

class pollServer {
public:
	pollServer();
	virtual ~pollServer();
	int startPollServer();
private:

	static int socket_bind(const char* ip, int port);

	static void do_poll(int listenfd);

	static void handle_connection(struct pollfd *connfds, int num);

};

#endif /* POLLSERVER_H_ */
