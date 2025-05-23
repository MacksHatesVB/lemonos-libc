#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/syscall.h>

// this shit boring as fuck

int socket(int domain, int type, int protocol) {
	return syscall(SYSCALL_SOCKET, domain, type, protocol);
}

int connect(int sockfd, struct sockaddr * addr, socklen_t addrlen) {
	return syscall(SYSCALL_CONNECT, sockfd, addr, addrlen);
}

int bind(int sockfd, const struct sockaddr * addr, socklen_t addrlen) {
	return syscall(SYSCALL_BIND, sockfd, addr, addrlen);
}

ssize_t sendto(int sockfd, const void * buf, size_t len, int flags, const struct sockaddr * dest_addr, socklen_t addrlen) {
	return syscall(SYSCALL_SENDTO, sockfd, buf, len, flags, dest_addr, addrlen);
}

ssize_t recvfrom(int sockfd, void * buf, size_t len, int flags, struct sockaddr * src_addr, socklen_t * addrlen) {
	return syscall(SYSCALL_RECVFROM, sockfd, buf, len, flags, src_addr, addrlen);
}

int getsockopt(int sockfd, int level, int name, void * value, socklen_t * len) {
	return syscall(SYSCALL_GETSOCKOPT, sockfd, level, name, value, len);
}

int setsockopt(int sockfd, int level, int name, const void * value, socklen_t len) {
	return syscall(SYSCALL_SETSOCKOPT, sockfd, level, name, value, len);
}
