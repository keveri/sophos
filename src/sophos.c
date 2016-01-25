#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "options.c"
#include "wisdoms.c"

static void log_and_exit(const char *error) {
    perror(error);
    exit(1);
}

static void bind_and_listen_to_port(const uint32_t sock,
                                    const struct sockaddr_in server) {
    if (bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) < 0) {
        log_and_exit("Failed to bind the server socket");
    }
    if (listen(sock, 1) < 0) {
        log_and_exit("Failed to listen on the server socket");
    }
}

static struct sockaddr_in create_server(const uint32_t port) {
    struct sockaddr_in server = {0};
    server.sin_family         = AF_INET;
    server.sin_addr.s_addr    = htonl(INADDR_ANY);
    server.sin_port           = htons(port);
    return server;
}

static void process_connections(const uint32_t sock, socklen_t socksize,
                                const warray wisdoms) {
    struct sockaddr_in client;
    int32_t conn_sock = accept(sock, (struct sockaddr *)&client, &socksize);
    char *msg;

    while(conn_sock) {
        msg = pick_a_wisdom(wisdoms);
        printf("Connection from: %s\n", inet_ntoa(client.sin_addr));
        send(conn_sock, msg, strlen(msg), 0);
        close(conn_sock);
        conn_sock = accept(sock, (struct sockaddr *)&client, &socksize);
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    const options opt               = parse_options(argc, argv);
    const struct sockaddr_in server = create_server(opt.port);
    const socklen_t socksize        = sizeof(struct sockaddr_in);
    const uint32_t sock             = socket(AF_INET, SOCK_STREAM, 0);
    const warray wisdoms            = read_wisdoms(opt.input);

    bind_and_listen_to_port(sock, server);
    process_connections(sock, socksize, wisdoms);

    clean_wisdoms(wisdoms);
    close(sock);
    return 0;
}
