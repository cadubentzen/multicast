#include "multicast_receiver.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

MulticastReceiver::MulticastReceiver(const char* ip, int port)
{
    m_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sd < 0) {
        perror("Error opening datagram socket");
        exit(1);
    }
    
    int reuse = 1;
    if (setsockopt(m_sd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0) {
       perror("Error setting SO_REUSEADDR");
       close(m_sd);
       exit(1);
    }

    memset((char*)&m_sock, 0, sizeof(m_sock));
    m_sock.sin_family = AF_INET;
    m_sock.sin_addr.s_addr = INADDR_ANY;
    m_sock.sin_port = htons(port);

    if (bind(m_sd, (struct sockaddr*)&m_sock, sizeof(m_sock))) {
        perror("Error binding datagram socket");
        close(m_sd);
        exit(1);
    }

    memset((char*)&m_group, 0, sizeof(m_group));
    m_group.imr_multiaddr.s_addr = inet_addr(ip);
    m_group.imr_interface.s_addr = INADDR_ANY;

    if (setsockopt(m_sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&m_group,
                   sizeof(m_group)) < 0) {
        perror("Error adding multicast group");
        close(m_sd);
        exit(1);
    }
}

MulticastReceiver::~MulticastReceiver()
{
    close(m_sd);
}

void MulticastReceiver::receive(void* buf, size_t len)
{
    if (read(m_sd, buf, len) < 0) {
        perror("Error reading message");
        close(m_sd);
        exit(1);
    }
}
