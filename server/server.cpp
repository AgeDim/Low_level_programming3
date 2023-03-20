#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/time.h>
#include <sstream>
#include "../common/form.hxx"

using namespace std;

//Server side
int main(int argc, char *argv[]) {
    //for the server, we only need to specify a port number
    if (argc != 2) {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]);
    //buffer to send and receive messages with
    char msg[1500];

    //setup a socket and connection tools
    sockaddr_in servAddr{};
    bzero((char *) &servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0) {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    int bindStatus = bind(serverSd, (struct sockaddr *) &servAddr,
                          sizeof(servAddr));
    if (bindStatus < 0) {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    listen(serverSd, 5);
    sockaddr_in newSockAddr{};
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    int newSd = accept(serverSd, (sockaddr *) &newSockAddr, &newSockAddrSize);
    if (newSd < 0) {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }
    cout << "Connected with client!" << endl;
    struct timeval start1{}, end1{};
    gettimeofday(&start1, nullptr);
    int bytesRead, bytesWritten = 0;
    while (true) {
        cout << "Awaiting client response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(newSd, (char *) &msg, sizeof(msg), 0);
        if (!strcmp(msg, "exit")) {
            cout << "Client has quit the session" << endl;
            break;
        }
        std::istringstream iss(msg);
        xml_schema::properties properties;
        properties.no_namespace_schema_location("../form.xsd");
        response(iss, 0, properties);
        std::string res = iss.str();
        cout << "Client: " << res << endl;
        cout << ">";
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        if (data == "exit") {
            send(newSd, (char *) &msg, strlen(msg), 0);
            break;
        }
        bytesWritten += send(newSd, (char *) &msg, strlen(msg), 0);
    }
    gettimeofday(&end1, nullptr);
    close(newSd);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
         << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;
}