/*
 * pollClient.h
 *
 *  Created on: Dec 15, 2014
 *      Author: echgchi
 */

#ifndef POLLCLIENT_H_
#define POLLCLIENT_H_

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>


#define MAXLINE     1024
#define IPADDRESS   "127.0.0.1"
#define SERV_PORT   8787

#define max(a,b) (a > b) ? a : b


class pollClient {
public:
	pollClient();
	virtual ~pollClient();
	int startPollClient();
private:
	void handle_connection(int sockfd);


};

#endif /* POLLCLIENT_H_ */
