#include"Daw.h"
#include<vector>
#include<string>
#include<iostream>
using port_t=unsigned short;
int main(){

	std::string ip="127.0.0.1";
	Daw::UdpSocket udps1,udps2;
	byte_t buf[]={"hello world"};
	std::vector<byte_t>msg(buf,buf+sizeof(buf));

	udps1.bind(ip,8088);
	udps2.bind(ip,8089);
	
	udps1.connect(ip,8089);
	udps1.send(msg);

	auto packet=udps2.recvfrom();
	std::cout<<packet.host<<"\n";
	std::cout<<packet.port<<"\n";
	auto vec=packet.payload;
	for(auto ch:vec)std::cout<<ch<<"";

	udps1.close();
	udps2.close();
}
