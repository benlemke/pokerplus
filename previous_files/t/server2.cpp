//
// chat_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2018 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "dealer.h"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include "asio.hpp"
#include "chat_message.hpp"
#include "json.hpp"
#include <string>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using asio::ip::tcp;

dealer Dealer;
//Dealer.createDeck();
//vector<int>Deck = Dealer.getDeck();
int card1, card2, card3, card4, card5, card6, card7, card8, card9, card10;;
//int hand1[5], hand2[5], hand3[5], hand4[5], hand5[5];
int hand[6][5];
int ehand[6][5];
int rankHand[6][6];
//----------------------------------------------------------------------

typedef std::deque<chat_message> chat_message_queue;

//----------------------------------------------------------------------

class player
{
public:
    virtual ~player() {}
    virtual void deliver(const chat_message& msg) = 0;
    string uuid;
    //int turn;
    int playerNo;
    bool ready = false;
    int balance = 195;
    int skipStatus = false;
    string actionTaken;
};

typedef std::shared_ptr<player> player_ptr;

//----------------------------------------------------------------------
int turn=0;
int playerNumber=0;
int start;
string action;
int pot = 0;
int bid = 0;
int raise_by = 0;
int bidChange = 0;
int totalPlayers;
bool skip1=false;
bool skip2=false;
bool skip3=false;
bool skip4=false;
bool skip5=false;
class poker_table
{
public:
	poker_table()
	{
	Dealer.createDeck();
	Deck = Dealer.getDeck();
	}
    void join(player_ptr participant)
    {
	playerNumber++;
        cout<<"New Player has joined the room"<<endl;
        
        /*participant->playerNo=playerNum;
	participant->turn=player_turn;                          //gives turn # to each player
        player_turn++;
        playerNum++;*/
	participant->playerNo = playerNumber;
	cout<< "***************" << participant->playerNo << "***************" << endl;
	    card1 = Deck.back();
            Deck.pop_back();
	    card2 = Deck.back();
	    Deck.pop_back();
            card3 = Deck.back();
	    Deck.pop_back();
            card4 = Deck.back();
	    Deck.pop_back();
            card5 = Deck.back();
	    Deck.pop_back();
	    card6 = Deck.back();
            Deck.pop_back();
	    card7 = Deck.back();
	    Deck.pop_back();
            card8 = Deck.back();
	    Deck.pop_back();
            card9 = Deck.back();
	    Deck.pop_back();
            card10 = Deck.back();
	    Deck.pop_back();
	    /*
		hand1[0] =card1;
		hand1[1] =card2;
		hand1[2] =card3;
		hand1[3] =card4;
		hand1[4] =card5;
		*/
		
		hand[participant->playerNo][0] =card1;
		hand[participant->playerNo][1] =card2;
		hand[participant->playerNo][2] =card3;
		hand[participant->playerNo][3] =card4;
		hand[participant->playerNo][4] =card5;
		
		ehand[participant->playerNo][0] =card6;
		ehand[participant->playerNo][1] =card7;
		ehand[participant->playerNo][2] =card8;
		ehand[participant->playerNo][3] =card9;
		ehand[participant->playerNo][4] =card10;
		
	    boost::uuids::basic_random_generator<boost::mt19937> g;
            boost::uuids::uuid u=g();
	    //Dealer.organizeAndRank(hand1,rankHand1);
	    Dealer.organizeAndRank(hand[participant->playerNo],rankHand[participant->playerNo]);
            string playerID;
            stringstream ss;
            ss<<u;
            playerID=ss.str();
            participant->uuid = playerID;
//            participant->turn = player_turn;
            cout << "Player number " << participant->playerNo << "uuid is " << participant->uuid << endl;
	    cout << "cards are "<< card1 <<", " << card2 <<", " << card3 <<", " << card4 << ", "<<card5<<endl;
            participants_.insert(participant);
            
	    //send client their uuid and turn
            nlohmann::json to_player;
                    to_player["playerNo"] = participant->playerNo;
                    to_player["uuid"] = participant->uuid;
		    to_player["hand["+ to_string(participant->playerNo) +"][0]"]=hand[participant->playerNo][0];
                    to_player["hand["+ to_string(participant->playerNo) +"][1]"]=hand[participant->playerNo][1];
                    to_player["hand["+ to_string(participant->playerNo) +"][2]"]=hand[participant->playerNo][2];
                    to_player["hand["+ to_string(participant->playerNo) +"][3]"]=hand[participant->playerNo][3];
                    to_player["hand["+ to_string(participant->playerNo) +"][4]"]=hand[participant->playerNo][4];

		    to_player["ehand["+ to_string(participant->playerNo) +"][0]"]=ehand[participant->playerNo][0];
                    to_player["ehand["+ to_string(participant->playerNo) +"][1]"]=ehand[participant->playerNo][1];
                    to_player["ehand["+ to_string(participant->playerNo) +"][2]"]=ehand[participant->playerNo][2];
                    to_player["ehand["+ to_string(participant->playerNo) +"][3]"]=ehand[participant->playerNo][3];
                    to_player["ehand["+ to_string(participant->playerNo) +"][4]"]=ehand[participant->playerNo][4];
                    string t = to_player.dump();
                    chat_message sending;
                    if (t.size() < chat_message::max_body_length)
                    {
                        memcpy( sending.body(), t.c_str(), t.size() );
                                sending.body_length(t.size());
                                sending.encode_header();
                        participant->deliver(sending);
                    }

        

        participants_.insert(participant);
        for (auto msg: recent_msgs_)                    //CSE3310 (server)  previous chat messages are sent to a client
        {
            participant->deliver(msg);
            //cout<<"poker_table join() for loop"<<endl;
        }
        //cout<<"poker_table join() done printing"<<endl;
    }
    
    void leave(player_ptr participant)
    {
        //cout<<"poker_table leave()"<<endl;
        
        participants_.erase(participant);
    }
    
    void deliver(const chat_message& msg)
    {      //cout<<"poker_table deliver()"<<endl;
        
        recent_msgs_.push_back(msg);
        while (recent_msgs_.size() > max_recent_msgs)
            recent_msgs_.pop_front();
        
        for (auto participant: participants_)       //CSE3310 (server)  messages are sent to all connected clients
        {
            participant->deliver(msg);
            //cout<<"sending to all the clients"<<endl;
        }
    }
    
    
    
    void deliver_to(const chat_message& msg,int deli_to)
    {      //cout<<"poker_table deliver()"<<endl;
        
        recent_msgs_.push_back(msg);
        while (recent_msgs_.size() > max_recent_msgs)
            recent_msgs_.pop_front();
        
        for (auto participant: participants_)       //CSE3310 (server)  messages are sent to all connected clients
        {

            if(participant->playerNo==deli_to)
                participant->deliver(msg);
            //cout<<"sending to individual clients"<<endl;
        }
    }
    void set_ready(bool status,int deli_to)
    {
        for (auto participant: participants_)       //CSE3310 (server)  messages are sent to all connected clients
        {

            if(participant->playerNo==deli_to)
            {
		
		nlohmann::json to_player;
		//to_player["p"+to_string(participant->playerNo)+" ready"];
                participant->ready=status;
                cout<<"This is the set_ready function\nplayer: "<<deli_to<<" status: "<<status<<endl;
            }
        }
    }
    bool allReady()                                 //checks if all the player in the servers are ready for the game
    {
        bool all_ready = true;
        for (auto participant: participants_)       //set all_ready to false if all players aren't ready
        {
            
            if(participant->ready==false)
            {
                all_ready=false;
            }
        }
        return all_ready;
    }
    int getSize()
    {
	    return participants_.size();
    }
private:
	vector<int>Deck;
    std::set<player_ptr> participants_;
    enum { max_recent_msgs = 100 };           //CSE3310 (server) maximum number of messages are stored
    chat_message_queue recent_msgs_;
};

//----------------------------------------------------------------------

class poker_player
: public player,
public std::enable_shared_from_this<poker_player>
{
public:
    poker_player(tcp::socket socket, poker_table& room)
    : socket_(std::move(socket)),
    room_(room)
    {
        //cout<<"poker_player constructor"<<endl;
        
    }
    
    void start()
    {
        //cout<<"poker_player start()"<<endl;
        
        room_.join(shared_from_this());
        do_read_header();
    }
    
    void deliver(const chat_message& msg)
    {
        //cout<<"poker_player deliver()"<<endl;
        
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress)
        {
            do_write();
            
        }
    }
    
private:
    void do_read_header()
    {
      auto self(shared_from_this());
      asio::async_read(socket_,
          asio::buffer(read_msg_.data(), chat_message::header_length),
          [this, self](std::error_code ec, std::size_t /*length*/)
          {
            if (!ec && read_msg_.decode_header())
            {
            // clear out the old buffer from the last read
            // a '\0' is a good value to make sure a string
            // is terminated
            for (unsigned int i=0;i<chat_message::max_body_length;i++)
            {
                read_msg_.body() [i] = '\0';
            }
	    	do_read_body();
            }
            else
            {
              room_.leave(shared_from_this());
            }
          });
    }

    void do_read_body()
    {
      auto self(shared_from_this());
      asio::async_read(socket_,
          asio::buffer(read_msg_.body(), read_msg_.body_length()),
          [this, self](std::error_code ec, std::size_t /*length*/)
          {
            if (!ec)
            {
                /*
                 json Davis example stuff was here
                 */
		if (turn==0)
		{	
		   nlohmann::json to_dealer = nlohmann::json::parse(std::string(read_msg_.body()));
		   nlohmann::json from_player = nlohmann::json::parse(std::string(read_msg_.body()));
		   room_.set_ready(to_dealer["ready"],shared_from_this()->playerNo);
		   totalPlayers=room_.getSize();
	           //send out ready status to all players
		   if (shared_from_this()->ready==true)
		   {
			nlohmann::json to_player;
	     		to_player["participant"]=shared_from_this()->playerNo;
			to_player["ready"]=true;
			to_player["pot"]=pot;
			to_player["balance"]=shared_from_this()->balance;
			to_player["size"] = totalPlayers;
                        string t=to_player.dump();
                        chat_message sending;
                        if (t.size() < chat_message::max_body_length)
                        {
                           memcpy( sending.body(), t.c_str(), t.size() );
                           sending.body_length(t.size());
                           sending.encode_header();
                           room_.deliver(sending);
                        }
		   }	

		   if (room_.allReady()==false)
		   {
			cout<<"cant start game"<<endl;
			nlohmann::json to_player1;
			to_player1["start"]=false;
			pot=(playerNumber) * 5;
			to_player1["pot"]=pot;
			to_player1["balance"]=shared_from_this()->balance;
                        string t=to_player1.dump();
                        chat_message sending;
                        if (t.size() < chat_message::max_body_length)
                        {
                           memcpy( sending.body(), t.c_str(), t.size() );
                           sending.body_length(t.size());
                           sending.encode_header();
                           room_.deliver(sending);
                        }
		   }
                   else
                   {	
			bidChange = playerNumber;
			turn++;
			nlohmann::json to_player2;
			to_player2["start"]=true;
			to_player2["participant"]=shared_from_this()->playerNo;
			to_player2["turn"]=turn;
			to_player2["bid"]=bid;
			to_player2["pot"]=pot;
			to_player2["balance"]=shared_from_this()->balance;
                        string t=to_player2.dump();
                        chat_message sending;
                        if (t.size() < chat_message::max_body_length)
                        {
                            memcpy( sending.body(), t.c_str(), t.size() );
                            sending.body_length(t.size());
                            sending.encode_header();
                            room_.deliver(sending);
                        }
		   }
		
		}
	  
		//if turn not 0
		else
		{
			turn++;
			if (turn== (room_.getSize()+1))
				turn=1;
			if (skip1==true && turn==1)
			       turn++;
			if (skip2==true && turn==2)                
                               turn++;
			if (skip3==true && turn==3)                
                               turn++;
			if (skip4==true && turn==4)                
                               turn++;
			if (skip5==true && turn==5)                
                        turn++;

			if (turn==(room_.getSize()+1))turn=1;
			//read json from player getting their action
                        nlohmann::json from_player = nlohmann::json::parse(std::string(read_msg_.body()));
			
		                if (from_player["action"].empty()==false)
				{
					shared_from_this()->actionTaken = from_player["action"];
					action = from_player["action"];
					if(action == "bet")
					{
					bidChange = playerNumber;
					bid = from_player["bid"];
					pot = pot + bid;
					cout << "pot = " <<pot<<endl;
					shared_from_this()->balance=from_player["balance"];
					}
					if(action == "raised")
					{
					bidChange = playerNumber;
					raise_by = from_player["raise_by"];
					pot = pot + raise_by + bid;
					cout << "pot = " <<pot<<endl;
					int temp = from_player["balance"];
					shared_from_this()->balance=temp-(raise_by+bid);
					bid = bid + raise_by;
					}
					if(action == "called")
					{
					int temp = from_player["balance"];
					shared_from_this()->balance=temp-bid;
					pot = pot + bid;
					cout << "pot = " <<pot<<endl;
					}
					if(action == "allin")
					{
					bidChange = playerNumber;
					
						if(from_player["raise_by"].empty() == false)
						{
						raise_by = from_player["raise_by"];
						pot = pot + raise_by + bid;
						cout << "pot = " <<pot<<endl;
						int temp = from_player["balance"];
						shared_from_this()->balance=temp-raise_by-bid;
						bid = bid + raise_by;
						}
						if(from_player["bid"].empty() == false)
						{
						bid = from_player["bid"];
						pot = pot + bid;
						cout << "pot = " <<pot<<endl;
						shared_from_this()->balance=from_player["balance"];
						}
					}
					if(action == "folded")
					{
					if (shared_from_this()->playerNo==1)
						skip1=true;
					if (shared_from_this()->playerNo==2)
                                                skip2=true;
					if (shared_from_this()->playerNo==3)
                                                skip3=true;
					if (shared_from_this()->playerNo==4)
                                                skip4=true;
					if (shared_from_this()->playerNo==5)
                                                skip5=true;
					shared_from_this()->skipStatus=true;
					bidChange =bidChange - 1;
					}
				}
				if (from_player["hand["+ to_string(shared_from_this()->playerNo) +"][0]"].empty() == false)
					hand[shared_from_this()->playerNo][0] = from_player["hand["+ to_string(playerNo) +"][0]"];
				if (from_player["hand["+ to_string(shared_from_this()->playerNo) +"][1]"].empty() == false)
				        hand[shared_from_this()->playerNo][1] = from_player["hand["+ to_string(playerNo) +"][1]"];
				if (from_player["hand["+ to_string(shared_from_this()->playerNo) +"][2]"].empty() == false)
				        hand[shared_from_this()->playerNo][2] = from_player["hand["+ to_string(playerNo) +"][2]"];
				if (from_player["hand["+ to_string(shared_from_this()->playerNo) +"][3]"].empty() == false)
				        hand[shared_from_this()->playerNo][3] = from_player["hand["+ to_string(playerNo) +"][3]"];
				if (from_player["hand["+ to_string(shared_from_this()->playerNo) +"][4]"].empty() == false)
				        hand[shared_from_this()->playerNo][4] = from_player["hand["+ to_string(playerNo) +"][4]"];
					
			 	if (from_player["gimmieCards"].empty() == false)
				{
					nlohmann::json to_player;
					Dealer.organizeAndRank(hand[shared_from_this()->playerNo],rankHand[shared_from_this()->playerNo]);
				    	
					to_player["turn"]=turn;
					to_player["participant"]=shared_from_this()->playerNo;
					to_player["balance"]=shared_from_this()->balance;
					to_player["pot"]=pot;
					to_player["hand["+ to_string(shared_from_this()->playerNo) +"][0]"]=hand[shared_from_this()->playerNo][0];
					to_player["hand["+ to_string(shared_from_this()->playerNo) +"][1]"]=hand[shared_from_this()->playerNo][1];
					to_player["hand["+ to_string(shared_from_this()->playerNo) +"][2]"]=hand[shared_from_this()->playerNo][2];
				 	to_player["hand["+ to_string(shared_from_this()->playerNo) +"][3]"]=hand[shared_from_this()->playerNo][3];
					to_player["hand["+ to_string(shared_from_this()->playerNo) +"][4]"]=hand[shared_from_this()->playerNo][4];
					string t=to_player.dump();
		                        chat_message sending;
		                        if (t.size() < chat_message::max_body_length)
		                        {
		                                memcpy( sending.body(), t.c_str(), t.size() );
		                                sending.body_length(t.size());
		                                sending.encode_header();
		                                room_.deliver(sending);
		                        }
				}
				
				nlohmann::json to_player2;
				if(bidChange == 0)
				{	
				cout<<"POT SETTLED"<<endl;
				to_player2["potSettled"]=true;
				to_player2["exchangePhase"]=true;
				turn = 1;
				if (skip1==true && turn==1)
                               		turn++;
				}
				bidChange=bidChange-1;
				//send turn to all players
		                to_player2["participant"]=shared_from_this()->playerNo;
				to_player2["action"]=action;
				to_player2["turn"]=turn;
				to_player2["raise_by"]=raise_by;
				to_player2["pot"]=pot;	
				to_player2["bid"]=bid;
				to_player2["balance"]=shared_from_this()->balance;
                                string t=to_player2.dump();
                                chat_message sending;
                                if (t.size() < chat_message::max_body_length)
                                {
                                        memcpy( sending.body(), t.c_str(), t.size() );
                                        sending.body_length(t.size());
                                        sending.encode_header();
                                        room_.deliver(sending);
                                }
			
		}	
	    do_read_header();
            }
            else
            {
                room_.leave(shared_from_this());
            }
        });
    }
    
    void do_write()
    {
      auto self(shared_from_this());
      asio::async_write(socket_,
          asio::buffer(write_msgs_.front().data(),
            write_msgs_.front().length()),
          [this, self](std::error_code ec, std::size_t /*length*/)
          {
            if (!ec)
            {
              write_msgs_.pop_front();
              if (!write_msgs_.empty())
              {
                do_write();
              }
            }
            else
            {
              room_.leave(shared_from_this());
            }
          });
    }
    
    tcp::socket socket_;
    poker_table& room_;
    chat_message read_msg_;
    chat_message_queue write_msgs_;
};

//----------------------------------------------------------------------

class poker_game
{
public:
    poker_game(asio::io_context& io_context,
               const tcp::endpoint& endpoint)
    : acceptor_(io_context, endpoint)
    {
        //cout<<"Poker game started"<<endl;
        
        do_accept();
    }
    
private:
    void do_accept()
    {
        
        
        acceptor_.async_accept(
                               [this](std::error_code ec, tcp::socket socket)
                               {
            if (!ec)
            {
                std::make_shared<poker_player>(std::move(socket), room_)->start();
            }
            
            do_accept();
        });
    }
    
    tcp::acceptor acceptor_;
    poker_table room_;
};

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: dealer <port> [<port> ...]\n";
            return 1;
        }
        
        asio::io_context io_context;
        
        std::list<poker_game> servers;
        for (int i = 1; i < argc; ++i)
        {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_context, endpoint);
        }
        
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}

