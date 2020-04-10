/*
 * epollClient.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: echgchi
 */
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "epollClient.h"

epollClient::epollClient() {
	// TODO Auto-generated constructor stub

}

epollClient::~epollClient() {

}


int epollClient::startEpollClient() {
	int sockfd;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, IPADDRESS, &servaddr.sin_addr);
	connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	handle_connection(sockfd);
	close(sockfd);
	return 0;
}

void epollClient::handle_connection(int sockfd) {
	int epollfd;
	struct epoll_event events[EPOLLEVENTS];
	char buf[MAXSIZE];
	int ret;
	//epoll_create will create an epoll handler
	epollfd = epoll_create(FDSIZE);
	//add_event use epoll_ctl to control add op operation to specified descriptor
	//below line monitor read operation for standard input descriptor (key board)
	add_event(epollfd, STDIN_FILENO, EPOLLIN);
	for (;;) {
		//epoll_wait will check the ready list
		ret = epoll_wait(epollfd, events, EPOLLEVENTS, -1);


		handle_events(epollfd, events, ret, sockfd, buf);
	}
	close(epollfd);
}

void epollClient::handle_events(int epollfd, struct epoll_event *events,
		int num, int sockfd, char *buf) {
	int fd;
	int i;
	for (i = 0; i < num; i++) {
		fd = events[i].data.fd;
		if (events[i].events & EPOLLIN)
			do_read(epollfd, fd, sockfd, buf);
		else if (events[i].events & EPOLLOUT)
			do_write(epollfd, fd, sockfd, buf);
	}
}

void epollClient::do_read(int epollfd, int fd, int sockfd, char *buf) {
	int nread;
	nread = read(fd, buf, MAXSIZE);
	if (nread == -1) {
		perror("read error:");
		close(fd);
	} else if (nread == 0) {
		fprintf(stderr, "server close.\n");
		close(fd);
	} else {
		if (fd == STDIN_FILENO)
			add_event(epollfd, sockfd, EPOLLOUT);
		else {
			delete_event(epollfd, sockfd, EPOLLIN);
			add_event(epollfd, STDOUT_FILENO, EPOLLOUT);
		}
	}
}

void epollClient::do_write(int epollfd, int fd, int sockfd, char *buf) {
	int nwrite;
	nwrite = write(fd, buf, strlen(buf));
	if (nwrite == -1) {
		perror("write error:");
		close(fd);
	} else {
		if (fd == STDOUT_FILENO)
			delete_event(epollfd, fd, EPOLLOUT);
		else
			modify_event(epollfd, fd, EPOLLIN);
	}
	memset(buf, 0, MAXSIZE);
}

void epollClient::add_event(int epollfd, int fd, int state) {
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void epollClient::delete_event(int epollfd, int fd, int state) {
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

void epollClient::modify_event(int epollfd, int fd, int state) {
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}
