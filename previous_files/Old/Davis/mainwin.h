#ifndef __MAINWIN_H
#define __MAINWIN_H

#include "ch_header.h"

#include <gtkmm.h>
//#include "shelter.h"
#include <fstream>
#include <iostream>
const std::string APP_TITLE{"POKER ++"};
const std::string APP_NAME{"edu.uta.cse1325.mass.v0_1_0"};
const std::string VERSION{"0.1.0"};
const std::string EXT = "mass";
const std::string COOKIE{"M⅍S1"};


class Mainwin : public Gtk::Window {
    public:
        Mainwin(chat_client*);
        virtual ~Mainwin();
    protected:
	void on_fold_click();
	void on_check_click();
	void on_bet_click();
	void on_call_click();
	void on_raise_click();
	void on_exchange_click();
	void on_HScale_value_changed();
	bool on_my_timeout();
        int seconds=30;
        bool reset=false;
	Gtk::VBox cvbox;
	Gtk::HBox hbox;
	Gtk::HBox actionHbox,balanceHbox,publicCardHbox,indicatorHbox, potHbox,privateCardHbox,cardSelectionHbox,exchangeHbox,playHbox;
	Gtk::Grid m_Grid;
	Gtk::Frame Frame_Horizontal, Frame_Vertical;
	Gtk::CheckButton RB1, RB2, RB3, RB4, RB5;
	Gtk::Separator sep1, sep2,sep3, sep4;
	Gtk::Scale HScale;
	Gtk::Grid m_grid,small_card_grid1,small_card_grid2,small_card_grid3,small_card_grid4,small_card_grid5;
/*	void on_new_game_click();*/
/*        void on_quit_click();              // Exit the application*/
/*        void on_about_click();              // new window displaying game rules and info*/
	void shiftIndicator();
	Gtk::Image *indicator =Gtk::manage(new Gtk::Image{"Icons/indicator.png"});

    private:
	int balance = 175;
	int potVal = 200;
        Gtk::Label p1,p2,p3,p4,p5;                  // Display player name
        Gtk::Label action1, action2, action3, action4, action5;                   // Action message display
	Gtk::Label balance1, balance2, balance3, balance4, balance5;		//Player's current balance, Available amount 
	Gtk::Label indicator1, indicator2, indicator3, indicator4, indicator5;   //Indicates whose turn.
	Gtk::Label pot;
	Gtk::Label timer;
	Gtk::Label image11, image12, image13, image14, image15;          //player1 hands
	Gtk::Label image21, image22, image23, image24, image25;	//player2 hands
	Gtk::Label image31, image32, image33, image34, image35;	//player3 hands
	Gtk::Label image41, image42, image43, image44, image45;	//player4 hands
	Gtk::Label image51, image52, image53, image54, image55;	//player5 hands

	Gtk::Label hand1, hand2, hand3, hand4, hand5;	//your hands, big picture
	
	Gtk::Button fold;//{"FOLD"};
	Gtk::Button check;//{"CHECK"};
	Gtk::Button bet;//{"BET $5"};
	Gtk::Button call;//{"CALL"};
	Gtk::Button raise;//{"RAISE $5"};
	Gtk::Button exchange{"EXCHANGE"};  

	Gtk::Image *bh1, *bh2, *bh3, *bh4, *bh5; //big cards
	Gtk::Image *h1, *h2, *h3, *h4, *h5,	 //sml cards
		   *h6, *h7, *h8, *h9, *h10,
		   *h11, *h12, *h13, *h14, *h15,
		   *h16, *h17, *h18, *h19, *h20,
		   *h21, *h22, *h23, *h24, *h25;

	int TESTVAL;
	int TESTTURN = 0;

   chat_client *c;
};
#endif 

