#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class MulticastReceiver {
public:
    MulticastReceiver(const char* ip, int port);
    ~MulticastReceiver();

    void receive(void* buf, size_t len);

private:
    int m_sd;
    struct sockaddr_in m_sock;
    struct ip_mreq m_group;
};
