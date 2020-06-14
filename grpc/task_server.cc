#include <bits/stdc++.h>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "task.grpc.pb.h"

using taskserver::Num;
using taskserver::Numbers;
using grpc::Status;

class TaskServerImpl final : public taskserver::TaskServer::Service {
    public:
        Status SquareNumber(grpc::ServerContext* context, grpc::ServerReaderWriter<Num,Num>* stream) override {
            Num in,out;
            while(stream->Read(&in)) {
                out.set_val(in.val()*in.val());
                stream->Write(out);
            }

            return Status::OK;
        }

        Status PrintNumbers(grpc::ServerContext* context, const Numbers* arr,::google::protobuf::Empty* response) override {
            std::cout<<"Recieved numbers\n";
            for(int num:arr->array()){
                std::cout<<num<<std::endl;
            }

            return Status::OK;
        }
};

int main() {
    std::string server_address("0.0.0.0:50051");
    TaskServerImpl service;    

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout <<"Server listening on " << server_address << std::endl;
    server->Wait();

    return 0;
}
