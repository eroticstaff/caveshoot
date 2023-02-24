#ifndef CAVESHOOT_NETWORK_H
#define CAVESHOOT_NETWORK_H

#include <SFML/Network.hpp>
#include <iostream>

#define LOG(x) std::cout << "[LOG]: " <<x << std::endl

class Network {
public:
    bool isConnected() {
        return status == sf::Socket::Done;
    }

    bool isOk() {
        return (currentStatus == sf::Socket::Done) and isConnected();
    }

    template<class T, class ...Args>
    void send(T first, Args... args) {
        currentPacket << first;
        send(args...);
    }

    template<class T>
    void send(T last) {
        currentPacket << last;
        currentStatus = socket.send(currentPacket);
        currentPacket.clear();
        if (not isOk()) {
            LOG("error sending data");
        }
    }

    [[nodiscard]] const std::string &get_result() const {
        return result;
    }

    void recieve() {
        sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) {
            packet >> result;
        }
    }

    void connect() {
        LOG("connecting");
        status = socket.connect("127.0.0.1", 53000);
        if (not isConnected()) {
            LOG("error connecting");
        } else {
            socket.setBlocking(false);
        }
    }

private:
    sf::Packet currentPacket;
    sf::Socket::Status currentStatus = sf::Socket::Disconnected;
    sf::TcpSocket socket;
    sf::Socket::Status status = sf::Socket::Disconnected;
    std::string result;
};


#endif //CAVESHOOT_NETWORK_H
