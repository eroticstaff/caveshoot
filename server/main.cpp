#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include <string>
#include "Shell.h"


#define LOG(x) std::cout << x << std::endl


sf::TcpListener listener;

int main() {
    std::cout << "starting server" << std::endl;

    listener.setBlocking(false);

    std::set_terminate([]() {
        listener.close();
    });
    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done) {
        LOG("error binding to port");
        std::terminate();
    }

    // accept a new connection
    std::vector<sf::TcpSocket *> clients;
    sf::SocketSelector selector;

    selector.add(listener);
    auto shell = new Shell;
//    shell.exec("cd ..;\nls;\n");
//    shell.exec("echo 123127463298756975623475\n");
//    shell.exec("ping google.com -c 2");
//    return 0;
    while (true) {
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                auto *socket = new sf::TcpSocket;
                listener.accept(*socket);
                clients.push_back(socket);
                selector.add(*socket);
                LOG("connected new client");
            } else {
                for (auto &client: clients) {
                    if (selector.isReady(*client)) {
                        sf::Packet packet;
                        if (client->receive(packet) == sf::Socket::Done) {
                            LOG("recieved data");
                            std::string data;
                            packet >> data;
                            auto result = shell->exec(data, std::chrono::seconds(3));
                            LOG(data);
                            packet.clear();
                            packet << result;
                            client->send(packet);
                            if (not shell->isSuccess()) {
                                LOG("recreating shell");
                                delete shell;
                                shell = new Shell;
                            }
                        }
                    }
                }
            }
        }
    }


    return 0;
}

