#include"Daw.h"
#include<iostream>
#include<filesystem>
int main(){
	std::string file_path="../tests/text.txt";
	size_t file_size=std::filesystem::file_size(file_path);
	std::cout<<"file_size:"<<file_size<<"\n";

	Daw::FiletsClient client(file_path);

	client.connect("127.0.0.1",8088);
	client.try_send();

	std::cout<<"end..\n";
	client.close();
	return 0;
}
