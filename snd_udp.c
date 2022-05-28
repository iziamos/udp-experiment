

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define PORT 10001
#define BUFFER_LENGTH 64

int
main (int argv, char ** argc) {

    int fd;
    struct sockaddr_in address;

    char buffer[BUFFER_LENGTH];
    char * blah = "bhal";

    if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("Failed to create socket\n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    // address.sin_addr.s_addr = inet_addr("239.193.4.0");
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    strcpy(buffer, "blah");

    for(;;) {
        sendto(fd, buffer, 5, 0, (struct sockaddr *)&address, sizeof(address));
    }
}
