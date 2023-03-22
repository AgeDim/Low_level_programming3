#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <sys/time.h>

#include "../parse_module/XPathparser.h"
#include "../common/form.hxx"
#include "../common/request.hxx"
#include "response_filling.h"

using namespace std;

//Client side
int main(int argc, char *argv[]) {
    //we need 2 things: ip address and port number, in that order
    if (argc != 3) {
        cerr << "Usage: ip_address port" << endl;
        exit(0);
    } //grab the IP address and port number
    char *serverIp = argv[1];
    int port = atoi(argv[2]);
    //create a message buffer
    char msg[100000];
    //setup a socket and connection tools
    struct hostent *host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr;
    bzero((char *) &sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
            inet_addr(inet_ntoa(*(struct in_addr *) *host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                         (sockaddr *) &sendSockAddr, sizeof(sendSockAddr));
    if (status < 0) {
        cout << "Error connecting to socket!" << endl;
        return -1;
    }
    cout << "Connected to the server!" << endl;
    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, nullptr);
    while (1) {
        form *tree = parse();
        view_t result = fill_response(tree);
        xml_schema::namespace_infomap map;
        map[""].name = "";
        map[""].schema = "form.xsd";
        std::ostringstream oss;
        response(oss, result, map);
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, oss.str().c_str());
        bytesWritten += send(clientSd, (char *) &msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(clientSd, (char *) &msg, sizeof(msg), 0);
        std::istringstream iss(msg);
        xml_schema::properties properties;
        properties.no_namespace_schema_location("../request.xsd");
        response_t recieve = *resp(iss, 0, properties);
        cout << recieve.message() << endl;
        if (recieve.body().present()) {
            auto nodes = recieve.body().get().nodes();
            for (auto &node: nodes) {
                cout << "Node name:" << node.name() << endl;
                for (int i = 0; i < node.attr_name().size(); i++) {
                    cout << "---Attribute " << i << " name:" << node.attr_name()[i] << " ----value:" << node.attr_value()[i] << endl;
                }
            }
        }
        if (!strcmp(msg, "exit")) {
            cout << "Server has quit the session" << endl;
            break;
        }
    }
    gettimeofday(&end1, nullptr);
    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten <<
         " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
         << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;
}
