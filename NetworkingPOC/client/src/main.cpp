/*
 * main.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: raphael
 */

#include <chrono>
#include <thread>
#include <iostream>

#include "SFML/Network.hpp"

int main()
{
    std::cout<<"networking poc\n";

    sf::TcpSocket socket;
    sf::Socket::Status status;

    //std::string ip = "192.168.0.5";
    std::string ip = "0.0.0.0";
    int port = 53001;


    do
    {
        std::cout<<"try connect to " << ip<<":"<<port<<"\n";
        status = socket.connect(ip, port);

        if(status != sf::Socket::Done)
        {
            std::cout<<"connected!\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    while (status != sf::Socket::Done);

    int i = 0;
    while(true)
    {
        std::cout<<"Client is connected... ";
        std::string data;
        std::cin >> data;

        if(socket.send(data.c_str(), data.size()) != sf::Socket::Done)
        {
            std::cout<<"Error sending data\n";
        }
        else
        {
            std::cout<<"successfully sent data '"<<data<<"'\n";
        }
    }
}

