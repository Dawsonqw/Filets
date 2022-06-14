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
	//ps:ofstream:文件写操作 内存到硬盘 ifstream:文件读操作 硬盘到内存
	FiletsServer::FiletsServer(const std::string& path){
		this->file_stream_=new std::ofstream;
		this->file_path_=path;
		file_stream_->open(file_path_,std::ios::out | std::ios::binary | std::ios::trunc);

		if(!file_stream_->is_open()){
			std::string msg=std::string("Could not open this file:")+strerror(errno);
			throw std::exception();
		}

		this->buffer_=new WriteBuffer(this->file_stream_);
	}

	void FiletsServer::listen(const std::string& host,const port_t port){
		this->socket_.bind(host,port);
	}

	//拿到接收数据
	RequestPayload FiletsServer::wait(){
		auto packet=socket_.recvfrom();
		this->socket_.connect(packet.host,packet.port);
		
		Frame request=Frame::put(packet.payload);
		this->file_size_=reinterpret_cast<RequestPayload*>(request.payload)->file_size;
		return *dynamic_cast<RequestPayload*>(request.payload);
	}

	void FiletsServer::close(){
		this->socket_.close();
		///todo:文件指针
	}

	//void FiletsServer::write(const std::function<bool(TransferProcess)>&callback){
	void FiletsServer::write(){
		///这里的写针对写入磁盘或者说写到指定路径
		auto& status=this->status_;
		
		status_.total_size=this->file_size_;
		status_.completed_size=0;
		
		while(status_.completed_size<status_.total_size){
			auto buffer=this->socket_.recvfrom();
			auto frame=Frame::put(buffer.payload);
			auto content=((DataPayload*)frame.payload)->content;

			this->buffer_->write(content);
			status_.completed_size+=content.size();

			//(!callback(status))throw std::exception();
		}
		this->buffer_->flush();
	}

	void FiletsServer::accept(){
		///ack seq
		Frame data_frame(0,0,FrameType::RecvResponse);
		auto *payload=new RecvResponse();

		payload->response=true;
		data_frame.mount(payload);
		
		auto buffer=data_frame.get();
		///回复一个数组 表示确认收到
		this->socket_.send(buffer);
	}

	void FiletsServer::decline(){
		Frame data_frame(0,0,FrameType::RecvResponse);
		auto *payload=new RecvResponse();

		payload->response=false;
		data_frame.mount(payload);
		//表示未收到
		auto buffer=data_frame.get();
		this->socket_.send(buffer);
	}


}

