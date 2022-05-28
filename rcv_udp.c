

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define PORT 10001
#define BUFFER_LENGTH 512

int
main (int argv, char ** argc) {

    int fd, n;
    struct sockaddr_in address;

    char buffer[BUFFER_LENGTH];

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Failed to create socket");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    printf("%d",fd);
    if (bind(fd, (struct sockaddr*) &address, sizeof(address)) < 0 ) {
        printf("Failed to bind.\n");
        return -1;
    }

    for(;;) {
        n = recv(fd, buffer, BUFFER_LENGTH, MSG_WAITFORONE);
        if (n > 0) {
            buffer[n] = '\0';
        }
        printf("%s", buffer);
    }
}
