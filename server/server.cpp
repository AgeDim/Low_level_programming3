#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>
#include "../common/form.hxx"
#include "../common/request.hxx"
#include "../database/database.h"


response_t deleteNode(database *bd, view_t *form) {
    auto lvl = form->level();
    vector<string> p;
    if (lvl.front().any_id() == 1) {
        for (int i = lvl.size() - 1; i > 0; i--) {
            p.push_back(lvl[i].id());
        }
        auto parent_id = bd->meta_data.pos.at(path(p));
        auto children = bd->meta_data.child.at(parent_id);

        vector<node> nodes;
        for (auto &child: children) {
            auto path = bd->meta_data.path.at(child);
            bd->delete_node(to_vector(path));
        }
    } else {
        for (int i = lvl.size() - 1; i >= 0; i--) {
            p.push_back(lvl[i].id());
        }
        node nn = bd->find_node(p);
        bd->delete_node(p);
    }
    string request = "Delete done!";
    int status = 200;
    bool finished = true;
    response_t resp_res = response_t(status, request, finished);
    return resp_res;
}

response_t
insertNode(database *bd, view_t *form) {
    auto lvl = form->level();
    auto name = (std::string) lvl.front().id();
    vector<string> p;
    string operation;
    string right;
    string left;
    for (int i = lvl.size() - 1; i >= 1; i--) {
        p.push_back(lvl[i].id());
    }
    node n(name);
    auto filters = lvl.front().filter();
    for (auto &filter: filters) {
        for (auto &comparator: filter.comparator()) {
            operation = comparator.operation();
            left = comparator.operator1().operator_();
            right = comparator.operator2().operator_();
        }
        if (operation[0] == '=') {
            n.add(left, right.c_str());
        }
    }
    bd->add_node(p, n);
    node z = bd->find_node({"1", "2"});
    string request = "Insert done!";
    int status = 200;
    bool finished = true;
    response_t resp_res = response_t(status, request, finished);
    return resp_res;
}

response_t selectNode(database *bd, view_t *form) {
    string request;
    int status;
    bool finished;
    auto lvl = form->level();
    body_t body;
    vector<string> p;
    node res_node;
    if (lvl.front().any_id() == 1) {
        for (int i = lvl.size() - 1; i > 0; i--) {
            p.push_back(lvl[i].id());
        }
        auto parent_id = bd->meta_data.pos.at(path(p));
        auto children = bd->meta_data.child.at(parent_id);

        vector<node> nodes;
        vector<node> result_nodes;
        for (auto &child: children) {
            auto path = bd->meta_data.path.at(child);
            nodes.push_back(bd->find_node(to_vector(path)));
        }
        for (auto no: nodes) {
            vector<bool> filter;
            bool conditions = false;
            for (auto fil: lvl[0].filter()) {
                for (auto cond: fil.comparator()) {
                    auto left = cond.operator1().operator_();
                    auto right = cond.operator2().operator_();
                    auto operation = cond.operation();
                    switch (operation[0]) {
                        case '=':
                            if (no.getAttr()[left].get_value() == right) {
                                conditions = true;
                            }
                            break;
                        case '<':
                            if (no.getAttr()[left].get_value() < right) {
                                conditions = true;
                            }
                            break;
                        case '>':
                            if (no.getAttr()[left].get_value() > right) {
                                conditions = true;
                            }
                            break;
                    }
                    filter.push_back(conditions);
                }
            }
            if(!std::any_of(filter.begin(), filter.end(), [](bool b) { return !b; })){
                result_nodes.push_back(no);
            }
        }
        for (auto &nod: result_nodes) {
            node_t node = node_t(nod.name);
            unordered_map<string, attributes> attr = nod.getAttr();
            for (auto &pair: attr) {
                node.attr_value().push_back(pair.second.get_value());
                node.attr_name().push_back(pair.first);
            }
            body.nodes().push_back(node);
        }
    } else {
        for (int i = lvl.size() - 1; i >= 0; i--) {
            p.push_back(lvl[i].id());
        }
        node nd = bd->find_node(p);
        vector<bool> filter;
        bool conditions = false;
        for (auto fil: lvl[0].filter()) {
            for (auto cond: fil.comparator()) {
                auto left = cond.operator1().operator_();
                auto right = cond.operator2().operator_();
                auto operation = cond.operation();
                switch (operation[0]) {
                    case '=':
                        if (nd.getAttr()[left].get_value() == right) {
                            conditions = true;
                        }
                        break;
                    case '<':
                        if (nd.getAttr()[left].get_value() < right) {
                            conditions = true;
                        }
                        break;
                    case '>':
                        if (nd.getAttr()[left].get_value() > right) {
                            conditions = true;
                        }
                        break;
                }
                filter.push_back(conditions);
            }
        }
        if (!std::any_of(filter.begin(), filter.end(), [](bool b) { return !b; })) {
            unordered_map<string, attributes> attr = nd.getAttr();
            node_t node = node_t(nd.name);
            for (auto &pair: attr) {
                node.attr_value().push_back(pair.second.get_value());
                node.attr_name().push_back(pair.first);
            }
            body.nodes().push_back(node);
            request = "select done";
            status = 200;
            finished = true;
        } else {
            request = "select done, 0 matches";
            status = 200;
            finished = true;
        }
    }


    response_t resp_res = response_t(status, request, finished);
    resp_res.body(body);
    return resp_res;
}


int main(int argc, char *argv[]) {
    database database(argv[2]);
    database.create();
    if (argc != 3) {
        cerr << "Usage: port file_descriptor" << endl;
        exit(0);
    }
    int port = atoi(argv[1]);
    char msg[5000];
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
    int bytesRead = 0, bytesWritten = 0;
    while (true) {
        cout << "Awaiting client response..." << endl;
        memset(&msg, 0, sizeof(msg));
        bytesRead += read(newSd, msg, 5000);
        if (!strcmp(msg, "exit")) {
            cout << "Client has quit the session" << endl;
            break;
        }
        std::istringstream iss(msg);
        xml_schema::properties properties;
        properties.no_namespace_schema_location("../form.xsd");
        view_t result = *response(iss, 0, properties);
        std::string operation = result.operation();
        xml_schema::namespace_infomap map;
        map[""].name = "";
        map[""].schema = "request.xsd";
        std::ostringstream oss;

        if (operation[0] == '+') {
            response_t resp_res = insertNode(&database, &result);
            resp(oss, resp_res, map);
            bytesWritten += write(newSd, oss.str().c_str(), strlen(oss.str().c_str()));
            cout << "insert Done!";
        } else if (operation[0] == '-') {
            response_t resp_res = deleteNode(&database, &result);
            resp(oss, resp_res, map);
            bytesWritten += write(newSd, oss.str().c_str(), strlen(oss.str().c_str()));
            cout << "delete Done!";
        } else if (operation[0] == '?') {
            response_t resp_res = selectNode(&database, &result);
            resp(oss, resp_res, map);
            bytesWritten += write(newSd, oss.str().c_str(), strlen(oss.str().c_str()));
            cout << "select Done!";
        }
    }
    gettimeofday(&end1, nullptr);
    close(newSd);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec)
         << " secs" << endl;
    cout << "Connection closed..." << endl;
    database.save();
    return 0;
}