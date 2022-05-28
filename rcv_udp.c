

#include <arpa/inet.h>
#include <stdio.h>

#define PORT 10001
#define BUFFER_LENGTH 64

unsigned long
read_ul_from_buffer(unsigned char * buffer) {

    unsigned long ret = 0l;

    ret |= (buffer[0] << 24) ;
    ret |= (buffer[1] << 16) ;
    ret |= (buffer[2] <<  8) ;
    ret |= (buffer[3]) ;

    return ret;
}

int
assert_seq_in_order(unsigned long previous, unsigned long current) {
    return (current == 0l) || (previous == -1) || ((previous + 1) == current);
}

int
main (int argv, char ** argc) {

    int fd, n;
    struct sockaddr_in address;
    char buffer[BUFFER_LENGTH];

    unsigned long previous = -1l;

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

    int faults = 0;

    for(;;) {
        n = recv(fd, buffer, BUFFER_LENGTH, MSG_DONTWAIT);
        if (n > 0) {
            buffer[n] = '\0';
            unsigned long seq = read_ul_from_buffer(buffer);
            printf("Seq number: '%ul'\n", seq);

            if (assert_seq_in_order(previous, seq))
            {
                previous = seq;
                continue;
            }

            printf("Expected sequence %ul but got %ul this is the %d fault!\n", previous + 1, seq, faults);
            previous = seq;
            faults++;

            if (faults > 10) {
                return -1;
            }
        }

    }
}
