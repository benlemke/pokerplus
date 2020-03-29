#include <iostream>
#include <sstream>
#include <fstream>
#include "MainWindow.h"
MainWindow::MainWindow()
{
    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(800, 600);
    set_title(APP_TITLE);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);   
}

void MainWindow::Refresh()
{
    
}
void MainWindow::Display_Player_Hand()
{
    
}
void MainWindow::Balance_Visibility()
{
    
}
void MainWindow::Player_Status()
{
    
}
void MainWindow::Fold_Button_Pressed()
{
    
}
void MainWindow::Match_Button_Color()
{
    
}
void MainWindow::Match_Button_Label()
{
    
}
void MainWindow::Match_Button_Pressed()
{
    
}
void MainWindow::Add_Button_Pressed()
{
    
}
void MainWindow::Exchange_Button_Label()
{
    
}
void MainWindow::Exchange_Button_Pressed()
{
    
}
void MainWindow::Status_Label()
{
    
}
void MainWindow::Status_Color()
{
    
}
void MainWindow::Status_Opacity()
{
    
}
void MainWindow::Slider_()
{
    
}
void MainWindow::SliderStatus() //or Widget
{
    
}
void MainWindow::MinAdd()
{
    
}
void MainWindow::MaxAdd()
{
    
}
void MainWindow::Balance_Opacity()
{
    
}

void MainWindow::Reveal_Cards()
{
    
}
void MainWindow::SelectionBoxStatus()
{
    
}
void MainWindow::TurnPosition()
{
    
}
void MainWindow::PlayerCards()
{
    
}
void MainWindow::Pot(int potValue)
{
    
}
void MainWindow::Timer()
{
    
}
void MainWindow::Id_Opacity()
{
    
}
MainWindow::~MainWindow()
{
}
int main()
{
    return 0;
}