#include"FiletsServer.h"
#include<filesystem>
#include<stdexcept>
#include<string.h>
#include"RequestPayload.h"
#include"Recvresponse.h"
#include"DataPayload.h"
#include<vector>
#include<fstream>

namespace Daw{
	FiletsServer::FiletsServer(const std::string& path){
		this->out_=new std::ofstream;
		this->file_path_=path;
		out_->open(file_path_,std::ios::out | std::ios::binary | std::ios::trunc);

		if(!out_->is_open()){
			std::string msg=std::string("Could not open this file:")+strerror(errno);
			throw std::exception();
		}

		this->buffer_=new WriteBuffer(this->out_);
	}

	void FiletsServer::listen(const std::string& host,const port_t port){
		this->socket_.bind(host,port);
	}

	//拿到接收数据
	RequestPayload FiletsServer::wait(){
		auto packet=socket_.recvfrom();
		this->socket_.connect(packet.host,packet.port);

		auto request=Frame::deserialize(packet.payload);
		this->file_size_=reinterpret_cast<RequestPayload*>(request.payload)->file_size;
		return *dynamic_cast<RequestPayload*>(request.payload);
	}

	void FiletsServer::close(){
		this->socket_.close();
		///todo:文件指针
	}

	void FiletsServer::write(const std::function<bool(TransferProcess)>&callback){
		auto& status=this->status_;
		
		status_.total_size=this->file_size_;
		status_.completed_size=0;
		
		while(status_.completed_size<status_.total_size){
			auto buffer=this->socket_.recvfrom();
			auto frame=Frame::deserialize(buffer.payload);
			auto content=((DataPayload*)frame.payload)->content;

			this->buffer_->write(content);
			status_.completed_size+=content.size();

			if(!callback(status))throw std::exception();
		}
		this->buffer_->flush();
	}

	void FiletsServer::accept(){
		Frame data_frame(0,0,FrameType::RecvResponse);
		auto *payload=new RecvResponse();

		payload->response=true;
		data_frame.put(payload);
		
		auto buffer=data_frame.serialize();
		this->socket_.send(buffer);
	}

	void FiletsServer::decline(){
		Frame data_frame(0,0,FrameType::RecvResponse);
		auto *payload=new RecvResponse();

		payload->response=false;
		data_frame.put(payload);

		auto buffer=data_frame.serialize();
		this->socket_.send(buffer);
	}


}

