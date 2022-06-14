#include"FiletsClient.h"
#include"RequestPayload.h"
#include"Recvresponse.h"
#include"DataPayload.h"
#include<stdexcept>
#include<filesystem>
#include<string.h>

namespace Daw{
	FiletsClient::FiletsClient(const std::string& path){
		this->in_=new std::ifstream;
		this->file_path_=path;
		this->in_->open(path,std::ios::in | std::ios::binary);

		if(!this->in_->is_open()){
			std::string msg=std::string("could not open this file:")+strerror(errno);
			throw std::exception();
		}

		this->buffer_.open(this->in_);
	}

	void FiletsClient::connect(const std::string& host,const port_t port){
		this->socket_.connect(host,port);
	}

	bool FiletsClient::try_send(){
		Frame r_frame(0,0,FrameType::SendRequest);
		RequestPayload* payload=this->prepare_send_request();
		r_frame.mount(payload);
		auto buffer=r_frame.get();
		delete payload;
		payload=nullptr;

		this->socket_.send(buffer);
		auto r_packet=this->socket_.recvfrom();

		Frame response=Frame::put(r_packet.payload);
		auto* resp=dynamic_cast<RecvResponse*>(response.payload);
		auto ack=resp->response;
		delete resp;
		return ack;
	}


	void FiletsClient::close(){
		this->socket_.close();
	}

	std::string_view FiletsClient::parse_file_name(const std::string& file){
		int size=file.size();
		///这里简单的从后向前拿到'/'
		int index=0;
		for(int i=size-1;i>=0;i--){
			if(file[i]=='/'){
				index=i+1;
				break;
			}
		}
		std::string_view file_name(file.substr(index));
		return file_name;
	}

	RequestPayload * FiletsClient::prepare_send_request(){
		std::error_code err;
		this->file_size_=std::filesystem::file_size(this->file_path_,err);
		if(err.value()!=0)throw std::exception();

		auto file_name=parse_file_name(this->file_path_);
		auto* payload=new RequestPayload();
		payload->client_name="client";//todo:利用socket进行
		payload->file_name=file_name;
		payload->file_size=this->file_size_;
		return payload;
	}

	//void FiletsClient::send(const std::function<bool(TransferProcess&)>&callback){
	void FiletsClient::send(){
		auto& status=this->status_;
		
		status.total_size=this->file_size_;
		status.completed_size=0;

		while(status.completed_size<status.total_size){
			auto disk_buffer=this->buffer_.read(1024);
			DataPayload* payload=new DataPayload();
			payload->content=disk_buffer;

			Frame frame(0,0,FrameType::Data);
			frame.mount(payload);
			auto net_buffer=frame.get();

			this->socket_.send(net_buffer);
			status.completed_size+=net_buffer.size();

	//		if(!callback(status))throw std::exception();
		}
	}
}
