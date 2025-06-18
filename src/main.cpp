#include<../include/RedisServer.h>
#include<iostream>

int main(int argc, char *argv[]) {
    int port = 6379;
    if (argc >=2) port = std::stoi(argv[1]);

    RedisServer server(port);

    // Background persistance: dump the database to disk every 5 mins(300 seconds)

    std:: thread persistanceThread([&server]() {
        while (server.running) {
            std::this_thread::sleep_for(std::chrono::seconds(300));
            // Here you would call a method to persist the database
            // server.persistDatabase();
            std::cout << "Persisting database..." << std::endl;
        }
    });
    persistanceThread.detach();


    server.run();
    return 0;
}