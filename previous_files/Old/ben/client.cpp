#include "client.h"

Mainwin *win = nullptr;
using asio::ip::tcp;
using namespace std;
typedef std::deque<chat_message> chat_message_queue;

chat_client::chat_client(asio::io_context& io_context, const tcp::resolver::results_type& endpoints) : io_context_(io_context), socket_(io_context)
    {
        do_connect(endpoints);
    }
    
    void chat_client::write(const chat_message& msg)
    {
        asio::post(io_context_,
                   [this, msg]()
                   {
            
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(msg);
            if (!write_in_progress)
            {
                
                do_write();
            }
        });
    }
    
    void chat_client::close()
    {
        asio::post(io_context_, [this]() { socket_.close(); });
    }
    void chat_client::do_connect(const tcp::resolver::results_type& endpoints)
    {
        
        // CSE3310 connection is established with the server
        asio::async_connect(socket_, endpoints,
                            [this](std::error_code ec, tcp::endpoint)
                            {
            if (!ec)
            {
                do_read_header();
            }
        });
    }
    void chat_client::do_read_header()
    {
        asio::async_read(socket_,
                         asio::buffer(read_msg_.data(), chat_message::header_length),
                         [this](std::error_code ec, std::size_t /*length*/)
                         {
            if (!ec && read_msg_.decode_header())
            {
                do_read_body();
            }
            else
            {
                socket_.close();
            }
        });
    }
    void chat_client::do_read_body()
    {
        //CSE 3310 message body is received from the server
        asio::async_read(socket_,
                         asio::buffer(read_msg_.body(), read_msg_.body_length()),
                         [this](std::error_code ec, std::size_t /*length*/)
                         {
            if (!ec)
            {
              
		std::cout.write(read_msg_.body(), read_msg_.body_length());//	
		std::cout << "\n";
		assert(win);
		win->process_data_from_dealer(std::string(read_msg_.body()));
                do_read_header();
            }
            else
            {
                socket_.close();
            }
        });
    }
    void chat_client::do_write()
    {
        //cout<<"at do_write"<<endl<<endl;
        //CSE 3310 message is sent to the chat server.
        asio::async_write(socket_,
                          asio::buffer(write_msgs_.front().data(),
                                       write_msgs_.front().length()),
                          [this](std::error_code ec, std::size_t /*length*/)
                          {
            //cout<<"do_write inside async_write"<<endl<<endl;
            
            if (!ec)
            {
                write_msgs_.pop_front();
                //cout<<"do_write->async_write->if brace"<<std::endl;
                if (!write_msgs_.empty())
                {
                    do_write();
                }
            }
            else
            {
                
                socket_.close();
            }
        });
    }


