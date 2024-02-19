#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>

int main()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {
        AF_INET,    // for ipv4
        0x901f,     // hex value of 8080, opposite order due to socket api
        0          // ip address
    };
    bind(s, &addr, sizeof(addr));

    listen(s, 10);

    int client_fd = accept(s, 0, 0);

    char buffer[256] = {0}
    recv(client_fd, buffer, 256, 0);

    // only upporting GET requests
    // GET /file.html ....

    char* f = buffer + 5;
    strchr(f, ' ') = 0;

    // open fxn, comes from fcntl.h
    int opened_fd = open(f, O_RDONLY);

    sendfile(client_fd, opened_fd, 0, 256);

    // close files & socket
    close(opened_fd);
    close(client_fd);
    close(s);
}
