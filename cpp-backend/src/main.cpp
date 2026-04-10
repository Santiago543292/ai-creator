#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <thread>
#include <fstream>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

// Simple HTTP server
class WebServer {
private:
    SOCKET listenSocket;
    int port;

public:
    WebServer(int p = 8080) : port(p), listenSocket(INVALID_SOCKET) {}

    bool Start() {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            return false;
        }

        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET) {
            WSACleanup();
            return false;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serverAddr.sin_port = htons(port);

        if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            closesocket(listenSocket);
            WSACleanup();
            return false;
        }

        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
            closesocket(listenSocket);
            WSACleanup();
            return false;
        }

        return true;
    }

    void HandleRequests() {
        while (true) {
            sockaddr_in clientAddr;
            int clientAddrLen = sizeof(clientAddr);
            SOCKET clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &clientAddrLen);

            if (clientSocket == INVALID_SOCKET) {
                continue;
            }

            std::thread([this, clientSocket]() {
                HandleClient(clientSocket);
            }).detach();
        }
    }

private:
    void HandleClient(SOCKET clientSocket) {
        char buffer[4096];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';

            // Parse the request
            std::string request(buffer);
            std::string filename = "index.html";

            if (request.find("GET /") != std::string::npos) {
                size_t start = request.find("GET /") + 5;
                size_t end = request.find(" HTTP", start);
                if (end != std::string::npos) {
                    std::string path = request.substr(start, end - start);
                    if (path.empty() || path == "/") {
                        filename = "index.html";
                    } else {
                        filename = path;
                    }
                }
            }

            // Get executable directory
            char exePath[MAX_PATH];
            GetModuleFileNameA(nullptr, exePath, MAX_PATH);
            char* lastSlash = strrchr(exePath, '\\');
            if (lastSlash) {
                *lastSlash = '\0';
            }

            // Build full file path
            std::string fullPath = std::string(exePath) + "\\web\\" + filename;

            // Read and send file
            std::ifstream file(fullPath, std::ios::binary);
            if (file.is_open()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                std::string content = buffer.str();

                // Determine content type
                std::string contentType = "text/html";
                if (filename.find(".css") != std::string::npos) {
                    contentType = "text/css";
                } else if (filename.find(".js") != std::string::npos) {
                    contentType = "application/javascript";
                } else if (filename.find(".png") != std::string::npos) {
                    contentType = "image/png";
                } else if (filename.find(".jpg") != std::string::npos || filename.find(".jpeg") != std::string::npos) {
                    contentType = "image/jpeg";
                }

                // Send HTTP response
                std::string response = "HTTP/1.1 200 OK\r\n";
                response += "Content-Type: " + contentType + "\r\n";
                response += "Content-Length: " + std::to_string(content.length()) + "\r\n";
                response += "Connection: close\r\n";
                response += "\r\n";
                response += content;

                send(clientSocket, response.c_str(), response.length(), 0);
                file.close();
            } else {
                // Send 404
                std::string notFound = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
                send(clientSocket, notFound.c_str(), notFound.length(), 0);
            }
        }

        closesocket(clientSocket);
    }

    void Stop() {
        if (listenSocket != INVALID_SOCKET) {
            closesocket(listenSocket);
            WSACleanup();
        }
    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Start web server
    WebServer server(8080);
    if (!server.Start()) {
        MessageBoxA(nullptr, "Failed to start web server", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Start server in background thread
    std::thread serverThread([&server]() {
        server.HandleRequests();
    }).detach();

    // Give server a moment to start
    Sleep(500);

    // Open browser
    ShellExecuteA(nullptr, "open", "http://localhost:8080", nullptr, nullptr, SW_SHOW);

    // Keep running
    Sleep(INFINITE);

    return 0;
}
