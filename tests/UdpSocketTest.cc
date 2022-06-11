#include"Daw.h"
#include<vector>
#include<string>
#include<iostream>
using port_t=unsigned short;
int main(){

	std::string ip="127.0.0.1";
	port_t port=8089;
	Daw::UdpSocket sock("127.0.0.1",8088);
	sock.connect("127.0.0.1",8089);
	std::vector<uint8_t>buffer{0x55,0x56,0x57,0x58};

	sock.sendto(buffer,"127.0.0.1",8089);

/**
	std::vector<uint8_t>rec(20,0);
	sock.recvfrom(rec,ip,port);
**/	
	std::cout<<"end\n";
}
