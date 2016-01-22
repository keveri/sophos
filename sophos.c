#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdint.h>

#define PORT 4444

struct sockaddr_in create_server(uint16_t port) {
    struct sockaddr_in server = {0};
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port        = htons(port);
    return server;
}

const char* pick_message() {
    // TODO: pick a random msg from predefined list.
    const char* msg = "Hello\n";
    return msg;
}

void process_connections(uint32_t sock, socklen_t socksize) {
    struct sockaddr_in client;
    int32_t conn_sock = accept(sock, (struct sockaddr *)&client, &socksize);
    const char* msg = pick_message();

    while(conn_sock)
    {
        printf("Connection from: %s\n", inet_ntoa(client.sin_addr));
        send(conn_sock, msg, strlen(msg), 0); 
        close(conn_sock);
        conn_sock = accept(sock, (struct sockaddr *)&client, &socksize);
    }

}

int main() {
    struct sockaddr_in server = create_server(PORT);
    const socklen_t socksize = sizeof(struct sockaddr_in);
    const uint32_t sock = socket(AF_INET, SOCK_STREAM, 0);

    bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr));
    listen(sock, 1);

    process_connections(sock, socksize);

    close(sock);
    return 0;
}
