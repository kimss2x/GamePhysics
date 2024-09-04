#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <uwebsockets/App.h>
#include <thread>
#include <string>

class WebSocketServer {
public:
    WebSocketServer();
    ~WebSocketServer();

    void start();
    void stop();
    void sendSimulationData(const std::string& data);

private:
    std::thread serverThread;
    std::atomic<bool> running{false};
};

#endif // WEBSOCKET_H
