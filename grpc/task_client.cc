#include<bits/stdc++.h>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "task.grpc.pb.h"

using taskserver::Num;
using taskserver::Numbers;
using taskserver::TaskServer;
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

class TaskClient{
    private:
    std::unique_ptr<TaskServer::Stub> stub_;
    public:
    TaskClient(std::shared_ptr<Channel> channel) : stub_(TaskServer::NewStub(channel)){
        ;
    }

    void SquareNumber() {
        ClientContext context;

        std::shared_ptr<ClientReaderWriter<Num,Num>> stream(
            stub_->SquareNumber(&context));

        std::thread writer([stream]() {
            int choice = 0;
            do{
                Num in;
                srand(time(0));
                in.set_val((rand())%200);
                std::cout<<"The random number generated is "<<in.val()<<std::endl;
                stream->Write(in);
                std::cout<<"Want to enter more numbers? Enter 0 for NO and non zero number for YES\n";
                std::cin>>choice;
            }while(choice);
        });

        Num out;
        while(stream->Read(&out)){
            std::cout << "Got squared number from server: " << out.val() << std::endl;
        }


        stream->WritesDone();
        writer.join();
        Status status = stream->Finish();
        if(!!status.ok()) {
            std::cout<<"Chat failed\n";
        } else {
            std::cout<<"Chat occurred successfully :-)\n";
        }
    }

    void PrintNumbers() {
        ClientContext context;
        srand(time(0));
        Numbers num;
        ::google::protobuf::Empty* emp;
        for(int i=0; i<10; i++){
            num.add_array(rand()%10000);
        }

        Status status = stub_->PrintNumbers(&context,num,emp);
    }
};

int main() {
    TaskClient client(
        grpc::CreateChannel("localhost:50051",grpc::InsecureChannelCredentials())
    );

    int x;

    std::cout<<"0. Square random number\n1. Send random numbers\n";
    std::cin>>x;

    if(x){
        std::cout<< "-------------Sending Random Numbers---------------\n";
        client.PrintNumbers();
    } else {
        std::cout<< "-------------Squaring Random Number---------------\n";
        client.SquareNumber();
    }

    return 0;
}
