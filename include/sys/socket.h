#pragma once

#include <stdint.h>
#include <arpa/inet.h>

typedef struct {
	uint32_t s_addr;
} sockaddr_address_t;

#define sockaddr_macro(name) typedef struct name { \
		uint16_t sin_family; \
		uint16_t sin_port; \
		sockaddr_address_t sin_addr; \
		char sin_zero[8]; \
	} name##_t;

sockaddr_macro(sockaddr);
sockaddr_macro(sockaddr_in);

enum {
	SOCK_STREAM = 1,
	SOCK_DGRAM,
	SOCK_RAW,
	SOCK_RDM,
	SOCK_SEQPACKET,
	SOCK_DCCP,
	SOCK_PACKET = 10,
	SOCK_CLOEXEC = 02000000,
	SOCK_NONBLOCK = 00004000,
};

enum {
	PF_UNSPEC = 0,
	PF_LOCAL = 1,
	PF_UNIX = 1,
	PF_FILE = 1,
	PF_INET = 2,
	PF_INET6 = 10,
	PF_PACKET = 17,
	PF_LLC = 26,
	PF_CAN = 29,
	PF_BLUETOOTH = 31,
};

enum {
	AF_UNSPEC = 0,
	AF_LOCAL = 1,
	AF_UNIX = 1,
	AF_FILE = 1,
	AF_INET = 2,
	AF_INET6 = 10,
	AF_PACKET = 17,
	AF_LLC = 26,
	AF_CAN = 29,
	AF_BLUETOOTH = 31,
};

int socket(int domain, int type, int protocol);
int connect(int sockfd, struct sockaddr * addr, socklen_t addrlen);
int bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen);
ssize_t sendto(int sockfd, const void * buf, size_t len, int flags, const struct sockaddr * dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void * buf, size_t len, int flags, struct sockaddr * src_addr, socklen_t * addrlen);
