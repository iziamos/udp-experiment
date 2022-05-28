

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PORT 10001
#define BUFFER_LENGTH 64

void
write_ul_to_buffer(unsigned char * buffer, unsigned long l) {
    buffer[0] = (l >> 24) & 0xFF;
    buffer[1] = (l >> 16) & 0xFF;
    buffer[2] = (l >>  8) & 0xFF;
    buffer[3] =  l        & 0xFF;
}

int
main (int argv, char ** argc) {

    int fd;
    struct sockaddr_in address;
    char buffer[BUFFER_LENGTH];

    struct timespec pause;
    pause.tv_sec = 0;
    pause.tv_nsec = 999 * 1000 * 1000;

    if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("Failed to create socket\n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    // address.sin_addr.s_addr = inet_addr("239.193.4.0");
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    for(unsigned long i = 0; ; ++i) {
        write_ul_to_buffer(buffer, i);

        //send the whole buffer
        sendto(fd, buffer, BUFFER_LENGTH, 0, (struct sockaddr *)&address, sizeof(address));
        nanosleep(&pause, NULL);
    }
}
