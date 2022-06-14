#include"Daw.h"
#include<vector>
#include<string>
#include<sys/socket.h>
#include<iostream>

int main(){
	Daw::FiletsServer server("../recvfile/recvfile.buf");
	
	server.listen("127.0.0.1",8088);

	std::cout<<"start listen....\n";

	while(true){
		auto request=server.wait();

		std::cout<<"recv information:\n";
		std::cout<<"file name:"<<request.file_name<<"\n";
		std::cout<<"file size:"<<request.file_size<<"\n";
		std::cout<<"file id:"<<request.file_id<<"\n";
		server.accept();
		server.write();
		std::cout<<"finish...prepare for next one\n";
	}
	
	server.close();
	return 0;
}
