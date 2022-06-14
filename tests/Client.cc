#include"Daw.h"
#include<vector>
#include<string>
#include<filesystem>
#include<iostream>
int main(){

	std::string file_path="../tests/text.txt";
	size_t file_size=std::filesystem::file_size(file_path);
	
	std::cout<<"client start run...\n";

	Daw::FiletsClient client(file_path);

	client.connect("127.0.0.1",8088);
	client.send();

	std::cout<<"client finish...\n";
	client.close();

}
