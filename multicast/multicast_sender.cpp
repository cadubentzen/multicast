#include "multicast_sender.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

MulticastSender::MulticastSender(const char* ip, int port)
{
    m_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sd < 0) {
        perror("Error opening datagram socket");
        exit(1);
    }

    memset((char*)&m_sock, 0, sizeof(m_sock));
    m_sock.sin_family = AF_INET;
    m_sock.sin_addr.s_addr = inet_addr(ip);
    m_sock.sin_port = htons(port);
}

MulticastSender::~MulticastSender()
{
    close(m_sd);
}

void MulticastSender::send(const void* buf, size_t len)
{
    if (sendto(m_sd, buf, len, 0, (struct sockaddr*)&m_sock,
               sizeof(m_sock)) < 0) {
        perror("Error sending datagram message");
        close(m_sd);
        exit(1);
    }
}
