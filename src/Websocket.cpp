#include <string>
#include <chrono>
#include <iostream>
#include "websocket.h"

WebSocketServer::WebSocketServer() {
    // WebSocket 서버 생성자
}

WebSocketServer::~WebSocketServer() {
    stop();
}

void WebSocketServer::start() {
    running = true;
    serverThread = std::thread([this]() {
        uWS::App().ws<nullptr>("/*", {
            .open = [](auto* ws) {
                std::cout << "Client connected!" << std::endl;
            },
            .message = [](auto* ws, std::string message, uWS::OpCode opCode) {  // std::string 사용
                std::cout << "Received message from client: " << message << std::endl;
            },
            .close = [](auto* ws, int /*code*/, std::string /*message*/) {  // std::string 사용
                std::cout << "Client disconnected!" << std::endl;
            }
        }).listen(9001, [](auto* token) {
            if (token) {
                std::cout << "Server started and listening on port 9001" << std::endl;
            } else {
                std::cerr << "Failed to start server" << std::endl;
            }
        }).run();
    });
}

void WebSocketServer::stop() {
    if (running) {
        running = false;
        if (serverThread.joinable()) {
            serverThread.join();
        }
    }
}

void WebSocketServer::sendSimulationData(const std::string& data) {
    // 이 함수에서 실제 WebSocket 연결을 통해 데이터를 보내는 로직을 구현합니다.
    // ws->send(data, uWS::OpCode::TEXT);
    std::cout << "Sending: " << data << std::endl;
}
