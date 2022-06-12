#include"Daw.h"
#include<iostream>
#include<sys/socket.h>

int main(){
	Daw::FiletsServer server("../tests/text.txt");
	
	server.listen("127.0.0.1",8088);
	auto request=server.wait();

	std::cout<<"recvived sender request:"<<"\n";
	std::cout<<"file name:"<<request.file_name<<"\n";
	std::cout<<"file size:"<<request.file_size<<"\n";
	std::cout<<"file id:"<<request.file_id<<"\n";

	server.decline();

	server.accept();
	return 0;
}
