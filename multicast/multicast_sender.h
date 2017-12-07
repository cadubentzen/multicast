#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class MulticastSender {
public:
    MulticastSender(const char* ip, int port);
    ~MulticastSender();

    void send(const void* buf, size_t len);

private:
    int m_sd;
    struct sockaddr_in m_sock;
};
