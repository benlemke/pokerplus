  
#include "mainwin.h"
#include "chat_client.h"

using namespace std;

typedef std::deque<chat_message> chat_message_queue;

void Mainwin::toGui(std::string s, int participant, int balance, int pot, int val)
{
   	if(s == "updateButton")
	{
	updateButton();
	}else if(s == "grayOutButton")
	{
	grayOutButton();
	}else if(s == "shift")
	{
	shiftIndicator(participant);
	}else if(s == "updateFoldAction")
	{
	updateFoldAction(participant);
	}else if(s == "updateCheckAction")
	{
	updateCheckAction(participant);
	}else if(s == "updateCallAction")
	{
	updateCallAction(participant, val);
	}else if(s == "updateBetAction")
	{
	updateBetAction(participant, val);
	}else if(s == "updateRaiseAction")
	{
	updateRaiseAction(participant, val);
	}else if(s == "updateAllInAction")
	{
	updateAllInAction(participant);
	}else if(s == "startRound")
	{
	startRound();
	}else if(s == "updateBalances")
	{
	updateBalances(participant);
	}else if(s == "updateReadyBoxes")
	{
	updateReadyBoxes(participant);
	}else if(s == "updateCallRaiseButtons")
	{
	updateCallRaiseButtons(balance, val);
	}else if(s == "updateVals")
	{
	updateVals(participant, balance, pot);
	}else if(s == "skip")
	{
	skip();
	}
	
}
std::string big(int card)
{
    std::string sCard = "LargeCards/" + std::to_string(card) + ".jpg";
    return sCard;
}
std::string sml(int card)
{
    std::string sCard = "SmallCards/" + std::to_string(card) + ".jpg";
    return sCard;
}

Mainwin::Mainwin(chat_client *c_)
{	
    c=c_;
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);
    
    //    vbox->override_background_color(Gdk::RGBA{"green"}); //changes background color of the vbox
    
    //hbox.pack_start(vbox);
    //action1.set_text("Calls $175");
    //vbox.pack_start(hbox);
    //vbox.pack_start(action1);
    
    p1.set_markup("<span size='16000' color ='black' weight='bold'>Player 1 </span>");
    p2.set_markup("<span size='16000' color ='black' weight='bold'>Player 2 </span>");
    p3.set_markup("<span size='16000' color ='black' weight='bold'>Player 3 </span>");
    p4.set_markup("<span size='16000' color ='black' weight='bold'>Player 4 </span>");
    p5.set_markup("<span size='16000' color ='black' weight='bold'>Player 5 </span>");
    	if(c->playerNo == 1)
	{
	p1.set_markup("<span size='16000' color ='black' weight='bold'>You</span>");
	}
	else if(c->playerNo == 2)
	{
	p2.set_markup("<span size='16000' color ='black' weight='bold'>You</span>");
	}
	else if(c->playerNo == 3)
	{
	p3.set_markup("<span size='16000' color ='black' weight='bold'>You</span>");
	}
	else if(c->playerNo == 4)
	{
	p4.set_markup("<span size='16000' color ='black' weight='bold'>You</span>");
	}
	else if(c->playerNo == 5)
	{
	p5.set_markup("<span size='16000' color ='black' weight='bold'>You</span>");
	}
    p1.override_background_color(Gdk::RGBA{"white"});
    p2.override_background_color(Gdk::RGBA{"white"});
    p3.override_background_color(Gdk::RGBA{"white"});
    p4.override_background_color(Gdk::RGBA{"white"});
    p5.override_background_color(Gdk::RGBA{"white"});
    
    vbox->pack_start(m_Grid, Gtk::PACK_SHRINK, 10);
    m_Grid.set_row_homogeneous(true);
    m_Grid.set_column_homogeneous(true);
    m_Grid.attach(p1, 0, 0, 1, 1);
    m_Grid.attach(p2, 1, 0, 1, 1);
    m_Grid.attach(p3, 2, 0, 1, 1);
    m_Grid.attach(p4, 3, 0, 1, 1);
    m_Grid.attach(p5, 4, 0, 1, 1);
    
    action1.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action2.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action3.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action4.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action5.set_markup("<span size='16000' color ='black' >Waiting </span>");
    
    action1.override_background_color(Gdk::RGBA{"white"});
    action2.override_background_color(Gdk::RGBA{"white"});
    action3.override_background_color(Gdk::RGBA{"white"});
    action4.override_background_color(Gdk::RGBA{"white"});
    action5.override_background_color(Gdk::RGBA{"white"});
    
    m_Grid.attach(action1, 0, 1, 1, 1);
    m_Grid.attach(action2, 1, 1, 1, 1);
    m_Grid.attach(action3, 2, 1, 1, 1);
    m_Grid.attach(action4, 3, 1, 1, 1);
    m_Grid.attach(action5, 4, 1, 1, 1);
    
    balance1.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(bal1) + "</span>");
    balance2.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(bal2) + "</span>");
    balance3.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(bal3) + "</span>");
    balance4.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(bal4) + "</span>");
    balance5.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(bal5) + "</span>");
    
    balance1.override_background_color(Gdk::RGBA{"white"});
    balance2.override_background_color(Gdk::RGBA{"white"});
    balance3.override_background_color(Gdk::RGBA{"white"});
    balance4.override_background_color(Gdk::RGBA{"white"});
    balance5.override_background_color(Gdk::RGBA{"white"});
    
    //add(balanceHbox);
    m_Grid.attach(balance1, 0, 2, 1, 1);
    m_Grid.attach(balance2, 1, 2, 1, 1);
    m_Grid.attach(balance3, 2, 2, 1, 1);
    m_Grid.attach(balance4, 3, 2, 1, 1);
    m_Grid.attach(balance5, 4, 2, 1, 1);
    
    image11.set_text(" | ");
    image12.set_text(" | ");
    image13.set_text(" | ");
    image14.set_text(" | ");
    
    
    //    cvbox.pack_start(publicCardHbox);
    //    publicCardHbox.pack_start(image11, Gtk::PACK_END, 0);
    //    publicCardHbox.pack_start(image12, Gtk::PACK_END, 0);
    //    publicCardHbox.pack_start(image13, Gtk::PACK_END, 0);
    //    publicCardHbox.pack_start(image14,Gtk::PACK_END, 0);
    //    publicCardHbox.pack_start(image15,Gtk::PACK_END, 0);
    /*
    h1 =Gtk::manage(new Gtk::Image{sml(11)});
    h2 =Gtk::manage(new Gtk::Image{sml(11)});
    h3 =Gtk::manage(new Gtk::Image{sml(11)});
    h4 =Gtk::manage(new Gtk::Image{sml(11)});
    h5 =Gtk::manage(new Gtk::Image{sml(11)});
    
    h6 =Gtk::manage(new Gtk::Image{sml(11)});
    h7 =Gtk::manage(new Gtk::Image{sml(11)});
    h8 =Gtk::manage(new Gtk::Image{sml(11)});
    h9 =Gtk::manage(new Gtk::Image{sml(11)});
    h10 =Gtk::manage(new Gtk::Image{sml(11)});
    
    h11 =Gtk::manage(new Gtk::Image{sml(11)});
    h12 =Gtk::manage(new Gtk::Image{sml(11)});
    h13 =Gtk::manage(new Gtk::Image{sml(11)});
    h14 =Gtk::manage(new Gtk::Image{sml(11)});
    h15 =Gtk::manage(new Gtk::Image{sml(11)});
    
    h16 =Gtk::manage(new Gtk::Image{sml(11)});
    h17 =Gtk::manage(new Gtk::Image{sml(11)});
    h18 =Gtk::manage(new Gtk::Image{sml(11)});
    h19 =Gtk::manage(new Gtk::Image{sml(11)});
    h20 =Gtk::manage(new Gtk::Image{sml(11)});
    
    h21 =Gtk::manage(new Gtk::Image{sml(11)});
    h22 =Gtk::manage(new Gtk::Image{sml(11)});
    h23 =Gtk::manage(new Gtk::Image{sml(11)});
    h24 =Gtk::manage(new Gtk::Image{sml(11)});
    h25 =Gtk::manage(new Gtk::Image{sml(11)});
    
    
    small_card_grid1.attach(*h1, 0, 0, 1, 1);
    small_card_grid1.attach(*h2, 1, 0, 1, 1);
    small_card_grid1.attach(*h3, 2, 0, 1, 1);
    small_card_grid1.attach(*h4, 3, 0, 1, 1);
    small_card_grid1.attach(*h5, 4, 0, 1, 1);
    
    small_card_grid2.attach(*h6, 0, 0, 1, 1);
    small_card_grid2.attach(*h7, 1, 0, 1, 1);
    small_card_grid2.attach(*h8, 2, 0, 1, 1);
    small_card_grid2.attach(*h9, 3, 0, 1, 1);
    small_card_grid2.attach(*h10, 4, 0, 1, 1);
    
    small_card_grid3.attach(*h11, 0, 0, 1, 1);
    small_card_grid3.attach(*h12, 1, 0, 1, 1);
    small_card_grid3.attach(*h13, 2, 0, 1, 1);
    small_card_grid3.attach(*h14, 3, 0, 1, 1);
    small_card_grid3.attach(*h15, 4, 0, 1, 1);
    
    small_card_grid4.attach(*h16, 0, 0, 1, 1);
    small_card_grid4.attach(*h17, 1, 0, 1, 1);
    small_card_grid4.attach(*h18, 2, 0, 1, 1);
    small_card_grid4.attach(*h19, 3, 0, 1, 1);
    small_card_grid4.attach(*h20, 4, 0, 1, 1);
    
    small_card_grid5.attach(*h21, 0, 0, 1, 1);
    small_card_grid5.attach(*h22, 1, 0, 1, 1);
    small_card_grid5.attach(*h23, 2, 0, 1, 1);
    small_card_grid5.attach(*h24, 3, 0, 1, 1);
    small_card_grid5.attach(*h25, 4, 0, 1, 1);
    
    m_Grid.attach(small_card_grid1, 0, 3, 1, 1);
    m_Grid.attach(small_card_grid2, 1, 3, 1, 1);
    m_Grid.attach(small_card_grid3, 2, 3, 1, 1);
    m_Grid.attach(small_card_grid4, 3, 3, 1, 1);
    m_Grid.attach(small_card_grid5, 4, 3, 1, 1);
*/
    shiftIndicator(1);
 
    
    //pot.set_text("\nPOT: $" +std::to_string(potVal));
    potLabel.set_markup("<span size='20000' color ='red' weight='bold'>  </span>");
    //pot.override_foreground_color(Gdk::RGBA{"gold"});
    m_Grid.attach(potLabel, 2, 5, 1, 1);
    

    
    
    bh1 =Gtk::manage(new Gtk::Image{big(1111)});
    bh2 =Gtk::manage(new Gtk::Image{big(2222)});
    bh3 =Gtk::manage(new Gtk::Image{big(3333)});
    bh4 =Gtk::manage(new Gtk::Image{big(4444)});
    bh5 =Gtk::manage(new Gtk::Image{big(5555)});
    
    
    //image21.override_background_color(Gdk::RGBA{"black"});
    vbox->pack_start(sep2);
    vbox->pack_start(privateCardHbox);
    //image21.set_text(" \n");
    //privateCardHbox.pack_start(image21);
    privateCardHbox.pack_start(*bh1);
    privateCardHbox.pack_start(*bh2);
    privateCardHbox.pack_start(*bh3);
    privateCardHbox.pack_start(*bh4);
    privateCardHbox.pack_start(*bh5);
    
    vbox->pack_start(cardSelectionHbox);
    cardSelectionHbox.pack_start(RB1,Gtk::PACK_END, 0);
    cardSelectionHbox.pack_start(RB2,Gtk::PACK_END, 0);
    cardSelectionHbox.pack_start(RB3,Gtk::PACK_END, 0);
    cardSelectionHbox.pack_start(RB4,Gtk::PACK_END, 0);
    cardSelectionHbox.pack_start(RB5,Gtk::PACK_END, 0);
    
    vbox->pack_start(exchangeHbox);

    
    exchangeHbox.pack_start(ready ,Gtk::PACK_END, 0);
    ready.signal_clicked().connect([this] {this->on_ready_click();});
    ready.show();
    
    fold.set_sensitive(false);
    check.set_sensitive(false);
    bet.set_sensitive(false);

    vbox->pack_start(sep3);
    image21.set_text(" \n");
    vbox->pack_start(image21);
    
    HScale.set_digits(1);
    HScale.set_value_pos(Gtk::POS_TOP);
    HScale.set_draw_value();
    
    //cvbox.pack_start(image21);
    vbox->pack_start(playHbox);
    playHbox.pack_start(fold ,Gtk::PACK_END, 0);
    playHbox.pack_start(check ,Gtk::PACK_END, 0);
    playHbox.pack_start(bet ,Gtk::PACK_END, 0);
    
    fold.set_size_request(30,30);
    fold.show();
    Gtk::Image* folding = Gtk::manage(new Gtk::Image{"Icons/fold.jpg"});
    fold.set_image(*folding);
    folding->show();
    
    check.set_size_request(30,30);
    Gtk::Image* checking = Gtk::manage(new Gtk::Image{"Icons/check.jpg"});
    check.set_image(*checking);
    checking->show();
    
    bet.set_size_request(30,30);
    Gtk::Image* beting = Gtk::manage(new Gtk::Image{"Icons/bet.jpg"});
    bet.set_image(*beting);
    beting->show();
    
    call.set_size_request(30,30);
    raise.set_size_request(30,30);

    fold.signal_clicked().connect([this] {this->on_fold_click();});
    check.signal_clicked().connect([this] {this->on_check_click();});
    bet.signal_clicked().connect([this] {this->on_bet_click();});
    
    bet.show();
    check.show();
    
    //playHbox.pack_start(sep4);
    playHbox.pack_end(HScale);
    
    HScale.set_increments(1, 1);
    HScale.signal_value_changed().connect([this] {this->on_HScale_value_changed();});
    //vbox->pack_start(image21);
    image22.set_text(" \n");
    vbox->pack_start(image22);
    //RB1.set_active();
    //RB2.set_active();
    //nhbox.show_all();
    //hbox.show_all();
    add(hbox);
    
    vbox->show_all();
    
    show_all_children();
    
    set_title(APP_TITLE);    //Application Title
    set_default_size(800, 600);   //default size of application window
    m_Grid.set_column_spacing(20);   
}

Mainwin::~Mainwin() { }

void Mainwin::on_fold_click() {
    reset=true;
    std::cout << "Player Folded!" << std::endl;
    bh1->set(big(1111));
    bh2->set(big(2222));
    bh3->set(big(3333));
    bh4->set(big(4444));
    bh5->set(big(5555));
    chat_message msg;
    nlohmann::json to_dealer;
    to_dealer["action"] = "folded";    
    std::string t = to_dealer.dump();
    msg.body_length(t.size());
    std::memcpy(msg.body(), t.c_str() , msg.body_length());
    msg.encode_header();   
    assert ( c );
    c->write(msg);    
}

void Mainwin::on_check_click() {
    reset=true;
    //action1.set_text("\nChecked");
    std::cout << "Player Checked!" << std::endl;
    //shiftIndicator();

    //send dealer player checked
    chat_message msg;
    nlohmann::json to_dealer;
    to_dealer["action"] = "checked";
    to_dealer["ammount"] = 0;
    std::string t = to_dealer.dump();
    msg.body_length(t.size());
    std::memcpy(msg.body(), t.c_str() , msg.body_length());
    msg.encode_header();    
    assert ( c );
    c->write(msg);
}

void Mainwin::on_bet_click() {
    reset=true;
    int sp = HScale.get_value();
    TESTVAL = sp;
    std::string to_call_button = "$" + std::to_string(TESTVAL);
    call.set_label(to_call_button);
    
    //action1.set_text("\nBet $" + std::to_string(sp));

    std::cout << "Player Bet $" + std::to_string(sp) + "!"<< std::endl;
    
    
    
    potVal = potVal + TESTVAL;

    //send dealer player bet, amount bet, player's balance and pot value after betting 
    chat_message msg;
    nlohmann::json to_dealer;
    to_dealer["action"] = "bet";
    c->balance=c->balance-sp;
    to_dealer["bid"] = sp;
    to_dealer["balance"]=c->balance;
    std::string t = to_dealer.dump();
    msg.body_length(t.size());
    std::memcpy(msg.body(), t.c_str() , msg.body_length());
    msg.encode_header();  
    assert ( c );
    c->write(msg);
}

void Mainwin::on_call_click() {
    reset=true;
    //action1.set_text("\nCalled $" + std::to_string(TESTVAL));
    std::string to_call_button = "$" + std::to_string(TESTVAL);
    call.set_label(to_call_button);
    Gtk::Image* calling = Gtk::manage(new Gtk::Image{"Icons/call.jpg"});
    call.set_image(*calling);
    calling->show();
    

    std::cout << "Player Called $" + std::to_string(TESTVAL) + "!"<< std::endl;
    //balance1.set_text("\n$" + std::to_string(balance));
    balance1.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
    balance1.override_background_color(Gdk::RGBA{"white"});
    
    potVal = potVal + TESTVAL;
    potLabel.set_text("\nPOT: $" +std::to_string(potVal));
	
    //send dealer player called, amount called, player's balance and pot value after calling 
    chat_message msg;
    nlohmann::json to_dealer;
    to_dealer["action"] = "called";
    to_dealer["amount"] = TESTVAL;
    to_dealer["balance"] = c->balance;
    to_dealer["pot"] = potVal;
    std::string t = to_dealer.dump();
    msg.body_length(t.size());
    std::memcpy(msg.body(), t.c_str() , msg.body_length());
    msg.encode_header();  
    assert ( c );
    c->write(msg);
}

void Mainwin::on_raise_click() {
    reset=true;
    int sp = HScale.get_value();
    //action1.set_text("\nRaised $" + std::to_string(sp));

    std::cout << "Player Raised $" + std::to_string(sp) + "!"<< std::endl;
    TESTVAL += sp;
    std::string to_call_button = "$" + std::to_string(TESTVAL);
    call.set_label(to_call_button);
    Gtk::Image* calling = Gtk::manage(new Gtk::Image{"Icons/call.jpg"});
    call.set_image(*calling);
    calling->show();
    
    //balance1.set_text("\n$" + std::to_string(balance));
 
    potVal = potVal + TESTVAL;
    potLabel.set_text("\nPOT: $" +std::to_string(potVal));
	
    //send dealer player raised, by how much, total amount after raised, player's balance and pot value after raising 
    chat_message msg;
    nlohmann::json to_dealer;
    to_dealer["action"] = "raised";
    to_dealer["raise_by"] = sp;
    to_dealer["balance"] = c->balance;
    to_dealer["pot"] = potVal;
    std::string t = to_dealer.dump();
    msg.body_length(t.size());
    std::memcpy(msg.body(), t.c_str() , msg.body_length());
    msg.encode_header();  
    assert ( c );
    c->write(msg);
}

void Mainwin::on_HScale_value_changed() {
    int sp = HScale.get_value();
    std::string to_bet_button = "$" + std::to_string(sp);
    std::string to_raise_button = "$" + std::to_string(sp);
    if (sp == 175)
    {
        to_bet_button = "ALL IN $" + std::to_string(sp) + "!";
        to_raise_button = "ALL IN $" + std::to_string(sp) + "!";
    }
    raise.set_label(to_raise_button);
    bet.set_label(to_bet_button);
    
    Gtk::Image* beting = Gtk::manage(new Gtk::Image{"Icons/bet.jpg"});
    bet.set_image(*beting);
    beting->show();
    
    Gtk::Image* raising = Gtk::manage(new Gtk::Image{"Icons/raise.jpg"});
    raise.set_image(*raising);
    raising->show();
}

void Mainwin::on_exchange_click(){
    if(RB1.get_active())
    {
        bh1->set(big(142));
        //h1->set(sml(142));
        RB1.set_sensitive(false);
    }
    if(RB2.get_active())
    {
        bh2->set(big(94));
        //h2->set(sml(94));
        RB2.set_sensitive(false);
    }
    if(RB3.get_active())
    {
        bh3->set(big(41));
        //h3->set(sml(41));
        RB3.set_sensitive(false);
    }
    if(RB4.get_active())
    {
        bh4->set(big(111));
        //h4->set(sml(111));
        RB4.set_sensitive(false);
    }
    if(RB5.get_active())
    {
        bh5->set(big(22));
       //h5->set(sml(22));
        RB5.set_sensitive(false);
    }
    RB1.set_active(false);
    RB2.set_active(false);
    RB3.set_active(false);
    RB4.set_active(false);
    RB5.set_active(false);
}

void Mainwin::on_ready_click()
{
    ready.set_sensitive(false);
    exchangeHbox.pack_start(exchange ,Gtk::PACK_END, 0);
    exchange.signal_clicked().connect([this] {this->on_exchange_click();});
    
   

        //set small images
	
   
       chat_message msg;
       nlohmann::json to_dealer;
       to_dealer["ready"] = true;
       //to_dealer["p"+ to_string(c->playerNo)+" ready"] = true;

       std::string t = to_dealer.dump();
       msg.body_length(t.size());
       std::memcpy(msg.body(), t.c_str() , msg.body_length());
       

       msg.encode_header();
       
       assert ( c );
       c->write(msg);
}

void Mainwin::shiftIndicator(int participant){
    //if (TESTTURN>=1)
	//TESTTURN = c->turn-1;
    //reset=false;
    //seconds=30;
	
	
    m_Grid.remove(*indicator);
    m_Grid.attach(*indicator, participant-1, 4, 1, 1);
   // TESTTURN += 1;
    //if (TESTTURN == 5) TESTTURN = 0;
		
}



void Mainwin::updateButton()
{
     HScale.set_range(5, 175);
     fold.set_sensitive(true);
     check.set_sensitive(true);
     bet.set_sensitive(true);
     
}

void Mainwin::grayOutButton()
{
     fold.set_sensitive(false);
     check.set_sensitive(false);
     bet.set_sensitive(false);
     call.set_sensitive(false);
     raise.set_sensitive(false);
}

void Mainwin::updateReadyBoxes(int participant)
{
	if (participant==1)
	{
	   action1.set_markup("<span size='16000' color ='white' weight='bold'>Ready! </span>");
           action1.override_background_color(Gdk::RGBA{"green"});
	   p1.override_background_color(Gdk::RGBA{"white"});
	}

        if (participant==2)
        {
           action2.set_markup("<span size='16000' color ='white' weight='bold'>Ready! </span>");
           action2.override_background_color(Gdk::RGBA{"green"});
           p2.override_background_color(Gdk::RGBA{"white"});
        }

	if (participant==3)
        {
           action3.set_markup("<span size='16000' color ='white' weight='bold'>Ready! </span>");
           action3.override_background_color(Gdk::RGBA{"green"});
           p3.override_background_color(Gdk::RGBA{"white"});
        }

        if (participant==4)
        {
           action4.set_markup("<span size='16000' color ='white' weight='bold'>Ready! </span>");
           action4.override_background_color(Gdk::RGBA{"green"});
           p4.override_background_color(Gdk::RGBA{"white"});
        }

        if (participant==5)
        {
           action5.set_markup("<span size='16000' color ='white' weight='bold'>Ready! </span>");
           action5.override_background_color(Gdk::RGBA{"green"});
           p5.override_background_color(Gdk::RGBA{"white"});
        }
}

void Mainwin::updateFoldAction(int participant)
{
	if (participant==1)
	{
	   action1.set_markup("<span size='16000' color ='white' weight='bold'>Folded </span>");
    	   action1.override_background_color(Gdk::RGBA{"black"});
	   if (c->playerNo==participant)
		p1.set_markup("<span size='16000' color ='white' weight='bold'>You </span>");
	   else
	   	p1.set_markup("<span size='16000' color ='white' weight='bold'>Player 1 </span>");
	   p1.override_background_color(Gdk::RGBA{"black"});
	   balance1.set_markup("<span size='14000' color ='white' >$  "
                       +  std::to_string(c->balance) + "</span>");
	   balance1.override_background_color(Gdk::RGBA{"black"});
	}
        if (participant==2)
        {
           action2.set_markup("<span size='16000' color ='white' weight='bold'>Folded </span>");
           action2.override_background_color(Gdk::RGBA{"black"});
           if (c->playerNo==participant)
                p2.set_markup("<span size='16000' color ='white' weight='bold'>You </span>");
           else
	   	p2.set_markup("<span size='16000' color ='white' weight='bold'>Player 2 </span>");
           p2.override_background_color(Gdk::RGBA{"black"});
           balance2.set_markup("<span size='14000' color ='white' >$  "
                       +  std::to_string(c->balance) + "</span>");
           balance2.override_background_color(Gdk::RGBA{"black"});
        }
	if (participant==3)
        {
           action3.set_markup("<span size='16000' color ='white' weight='bold'>Folded </span>");
           action3.override_background_color(Gdk::RGBA{"black"});
           if (c->playerNo==participant)
                p3.set_markup("<span size='16000' color ='white' weight='bold'>You </span>");
	   else
	        p3.set_markup("<span size='16000' color ='white' weight='bold'>Player 3 </span>");
           p3.override_background_color(Gdk::RGBA{"black"});
           balance3.set_markup("<span size='14000' color ='white' >$  "
                       +  std::to_string(c->balance) + "</span>");
           balance3.override_background_color(Gdk::RGBA{"black"});
        }
        if (participant==4)
        {
           action4.set_markup("<span size='16000' color ='white' weight='bold'>Folded </span>");
           action4.override_background_color(Gdk::RGBA{"black"});
           if (c->playerNo==participant)
                p4.set_markup("<span size='16000' color ='white' weight='bold'>You </span>");           
	   else
      	        p4.set_markup("<span size='16000' color ='white' weight='bold'>Player 4 </span>");
           p4.override_background_color(Gdk::RGBA{"black"});
           balance4.set_markup("<span size='14000' color ='white' >$  "
                       +  std::to_string(c->balance) + "</span>");
           balance4.override_background_color(Gdk::RGBA{"black"});
        }
        if (participant==5)
        {
           action5.set_markup("<span size='16000' color ='white' weight='bold'>Folded </span>");
           action5.override_background_color(Gdk::RGBA{"black"});
           if (c->playerNo==participant)
                p5.set_markup("<span size='16000' color ='white' weight='bold'>You </span>");           
	   else
        	p5.set_markup("<span size='16000' color ='white' weight='bold'>Player 5 </span>");
           p5.override_background_color(Gdk::RGBA{"black"});
           balance5.set_markup("<span size='14000' color ='white' >$  "
                       +  std::to_string(c->balance) + "</span>");
           balance5.override_background_color(Gdk::RGBA{"black"});
        }
}

void Mainwin::updateCheckAction(int participant)
{
	if (participant==1)
	{
	   action1.set_markup("<span size='16000' color ='black' weight='bold'>Checked </span>");
    	   action1.override_background_color(Gdk::RGBA{"yellow"});
	}
        if (participant==2)
        {
           action2.set_markup("<span size='16000' color ='black' weight='bold'>Checked </span>");
    	   action2.override_background_color(Gdk::RGBA{"yellow"});
        }
	if (participant==3)
        {
           action3.set_markup("<span size='16000' color ='black' weight='bold'>Checked </span>");
    	   action3.override_background_color(Gdk::RGBA{"yellow"});
        }
        if (participant==4)
        {
           action4.set_markup("<span size='16000' color ='black' weight='bold'>Checked </span>");
    	   action4.override_background_color(Gdk::RGBA{"yellow"});
        }
        if (participant==5)
        {
           action5.set_markup("<span size='16000' color ='black' weight='bold'>Checked </span>");
    	   action5.override_background_color(Gdk::RGBA{"yellow"});
	}
}

void Mainwin::updateCallAction(int participant, int val)
{
	if (participant==1)
	{
	   action1.set_markup("<span size='16000' color ='black' weight='bold'>Called $" +to_string(val)+"</span>");
    	   action1.override_background_color(Gdk::RGBA{"yellow"});
	}
        if (participant==2)
        {
           action2.set_markup("<span size='16000' color ='black' weight='bold'>Called $" +to_string(val)+"</span>");
    	   action2.override_background_color(Gdk::RGBA{"yellow"});
        }
	if (participant==3)
        {
           action3.set_markup("<span size='16000' color ='black' weight='bold'>Called $" +to_string(val)+"</span>");
    	   action3.override_background_color(Gdk::RGBA{"yellow"});
        }
        if (participant==4)
        {
           action4.set_markup("<span size='16000' color ='black' weight='bold'>Called $" +to_string(val)+"</span>");
    	   action4.override_background_color(Gdk::RGBA{"yellow"});
        }
        if (participant==5)
        {
           action5.set_markup("<span size='16000' color ='black' weight='bold'>Called $" +to_string(val)+"</span>");
    	   action5.override_background_color(Gdk::RGBA{"yellow"});
	}
}


void Mainwin::updateBetAction(int participant, int val)
{
	if (participant==1)
	{
	   action1.set_markup("<span size='16000' color ='black' weight='bold'>Bet $" +to_string(val)+"</span>");
    	   action1.override_background_color(Gdk::RGBA{"green"});
	}
        if (participant==2)
        {
           action2.set_markup("<span size='16000' color ='black' weight='bold'>Bet $" +to_string(val)+"</span>");
    	   action2.override_background_color(Gdk::RGBA{"green"});
        }
	if (participant==3)
        {
           action3.set_markup("<span size='16000' color ='black' weight='bold'>Bet $" +to_string(val)+"</span>");
    	   action3.override_background_color(Gdk::RGBA{"green"});
        }
        if (participant==4)
        {
           action4.set_markup("<span size='16000' color ='black' weight='bold'>Bet $" +to_string(val)+"</span>");
    	   action4.override_background_color(Gdk::RGBA{"green"});
        }
        if (participant==5)
        {
           action5.set_markup("<span size='16000' color ='black' weight='bold'>Bet $" +to_string(val)+"</span>");
    	   action5.override_background_color(Gdk::RGBA{"green"});
	}
}
	void Mainwin::updateRaiseAction(int participant, int val)
{
	if (participant==1)
	{
	   action1.set_markup("<span size='16000' color ='black' weight='bold'>Raised $" +to_string(val)+"</span>");
    	   action1.override_background_color(Gdk::RGBA{"green"});
	}
        if (participant==2)
        {
           action2.set_markup("<span size='16000' color ='black' weight='bold'>Raised $" +to_string(val)+"</span>");
    	   action2.override_background_color(Gdk::RGBA{"green"});
        }
	if (participant==3)
        {
           action3.set_markup("<span size='16000' color ='black' weight='bold'>Raised $" +to_string(val)+"</span>");
    	   action3.override_background_color(Gdk::RGBA{"green"});
        }
        if (participant==4)
        {
           action4.set_markup("<span size='16000' color ='black' weight='bold'>Raised $" +to_string(val)+"</span>");
    	   action4.override_background_color(Gdk::RGBA{"green"});
        }
        if (participant==5)
        {
           action5.set_markup("<span size='16000' color ='black' weight='bold'>Raised $" +to_string(val)+"</span>");
    	   action5.override_background_color(Gdk::RGBA{"green"});
	}
}
	void Mainwin::updateBalances(int participant)
{	
	potLabel.set_markup("<span size='20000' color ='red' weight='bold'> </span>");
	if (participant==1)
	{
	balance1.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
	}
        if (participant==2)
        {
	 balance2.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
        }
	if (participant==3)
        {
	balance3.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
        }
        if (participant==4)
        {
	balance4.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
        }
        if (participant==5)
        {
	balance5.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
	}
}
	void Mainwin::updateAllInAction(int participant)
{
	if (participant==1)
	{
	balance1.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
	   action1.set_markup("<span size='16000' color ='black' weight='bold'>All In! #</span>");
    	   action1.override_background_color(Gdk::RGBA{"green"});
	}
        if (participant==2)
        {
	 balance2.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
           action2.set_markup("<span size='16000' color ='black' weight='bold'>All In! #</span>");
    	   action2.override_background_color(Gdk::RGBA{"green"});
        }
	if (participant==3)
        {
	balance3.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
           action3.set_markup("<span size='16000' color ='black' weight='bold'>All In! #</span>");
    	   action3.override_background_color(Gdk::RGBA{"green"});
        }
        if (participant==4)
        {
	balance4.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
           action4.set_markup("<span size='16000' color ='black' weight='bold'>All In! #</span>");
    	   action4.override_background_color(Gdk::RGBA{"green"});
        }
        if (participant==5)
        {
	balance5.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(c->balance) + "</span>");
           action5.set_markup("<span size='16000' color ='black' weight='bold'>All In! #</span>");
    	   action5.override_background_color(Gdk::RGBA{"green"});
	}
	
    
    
    
    
}
void Mainwin::startRound()
{
    ready.hide();
    exchange.show();
    exchange.set_sensitive(false);
    action1.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action2.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action3.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action4.set_markup("<span size='16000' color ='black' >Waiting </span>");
    action5.set_markup("<span size='16000' color ='black' >Waiting </span>");
   
            if (c->size==4)
        {
                action5.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance5.set_markup("<span size='14000' color ='black' >$ N/A </span>");
        }

        if (c->size==3)
        {
                action5.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance5.set_markup("<span size='14000' color ='black' >$ N/A </span>");
                action4.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance4.set_markup("<span size='14000' color ='black' >$ N/A </span>");
        }
        if (c->size==2)
        {
                action5.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance5.set_markup("<span size='14000' color ='black' >$ N/A </span>");
                action4.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance4.set_markup("<span size='14000' color ='black' >$ N/A </span>");
                action3.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance3.set_markup("<span size='14000' color ='black' >$ N/A </span>");
        }

    action1.override_background_color(Gdk::RGBA{"white"});
    action2.override_background_color(Gdk::RGBA{"white"});
    action3.override_background_color(Gdk::RGBA{"white"});
    action4.override_background_color(Gdk::RGBA{"white"});
    action5.override_background_color(Gdk::RGBA{"white"});
	/*
	if(c->playerNo == 1)
	{
	h1->set(sml(c->getHand(0)));
    	h2->set(sml(c->getHand(1)));
	h3->set(sml(c->getHand(2)));
	h4->set(sml(c->getHand(3)));
	h5->set(sml(c->getHand(4)));
	}
	else if (c->playerNo == 2)
	{
	h6->set(sml(c->getHand(0)));
    	h7->set(sml(c->getHand(1)));
	h8->set(sml(c->getHand(2)));
	h9->set(sml(c->getHand(3)));
	h10->set(sml(c->getHand(4)));
	}
	else if (c->playerNo == 3)
	{
	h11->set(sml(c->getHand(0)));
    	h12->set(sml(c->getHand(1)));
	h13->set(sml(c->getHand(2)));
	h14->set(sml(c->getHand(3)));
	h15->set(sml(c->getHand(4)));
	}
	else if (c->playerNo == 4)
	{
	h16->set(sml(c->getHand(0)));
    	h17->set(sml(c->getHand(1)));
	h18->set(sml(c->getHand(2)));
	h19->set(sml(c->getHand(3)));
	h20->set(sml(c->getHand(4)));
	}
	else if (c->playerNo == 5)
	{
	h21->set(sml(c->getHand(0)));
    	h22->set(sml(c->getHand(1)));
	h23->set(sml(c->getHand(2)));
	h24->set(sml(c->getHand(3)));
	h25->set(sml(c->getHand(4)));
	}
    	*/
	//set big images
	bh1->set(big(c->getHand(0)));
	bh2->set(big(c->getHand(1)));
	bh3->set(big(c->getHand(2)));
	bh4->set(big(c->getHand(3)));
	bh5->set(big(c->getHand(4)));
}

void Mainwin::updateCallRaiseButtons(int balance, int bid){

    check.hide();
    bet.hide();
    playHbox.pack_start(call ,Gtk::PACK_END, 0);
    playHbox.pack_start(raise ,Gtk::PACK_END, 0);
    HScale.set_value(5);
    call.set_label("$"+to_string(bid));
    HScale.set_range(5, balance-bid);
    Gtk::Image* calling = Gtk::manage(new Gtk::Image{"Icons/call.jpg"});
    call.set_image(*calling);
    calling->show();
    call.signal_clicked().connect([this] {this->on_call_click();});
    call.show();
    
    Gtk::Image* raising = Gtk::manage(new Gtk::Image{"Icons/raise.jpg"});
    raise.set_image(*raising);
    raising->show();
    raise.signal_clicked().connect([this] {this->on_raise_click();});
    raise.show();
    fold.set_sensitive(true);
    call.set_sensitive(true);
    raise.set_sensitive(true);
}
void Mainwin::updateVals(int participant,int balance,int pot)
{
	potLabel.set_markup("<span size='20000' color ='red' weight='bold'>$"+std::to_string(pot)+"  </span>");
	if (participant==1)
	{
	balance1.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(balance) + "</span>");
	}
        if (participant==2)
        {
	 balance2.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(balance) + "</span>");
        }
	if (participant==3)
        {
	balance3.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(balance) + "</span>");
        }
        if (participant==4)
        {
	balance4.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(balance) + "</span>");
        }
        if (participant==5)
        {
	balance5.set_markup("<span size='14000' color ='black' >$  "
                        +  std::to_string(balance) + "</span>");
	}
}

void Mainwin::skip()
{
	Mainwin::on_fold_click();
}

void Mainwin::hidePlayers(int size)
{
	if (size==4)
	{
		action5.set_markup("<span size='16000' color ='black' > N/A </span>");

		balance5.set_markup("<span size='14000' color ='black' >$ N/A </span>");
	}

	if (size==3)
        {
                action5.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance5.set_markup("<span size='14000' color ='black' >$ N/A </span>");
                action4.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance4.set_markup("<span size='14000' color ='black' >$ N/A </span>");
	}
	if (size==2)
	{
                action5.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance5.set_markup("<span size='14000' color ='black' >$ N/A </span>");
                action4.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance4.set_markup("<span size='14000' color ='black' >$ N/A </span>");
                action3.set_markup("<span size='16000' color ='black' > N/A </span>");

                balance3.set_markup("<span size='14000' color ='black' >$ N/A </span>");
	}
}



