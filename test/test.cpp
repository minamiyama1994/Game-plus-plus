#include<type_traits>
#include"boost/thread/thread.hpp"
#include"boost/chrono.hpp"
#include<FL/Fl.H>
#include<FL/Fl_Double_Window.H>
#include<FL/Fl_Box.H>
#include<FL/Fl_PNG_Image.H>
namespace
{
	Fl_Double_Window * window = nullptr ;
	Fl_Box * box = nullptr ;
	Fl_PNG_Image * image = nullptr ;
}
auto main(int argc, char **argv) -> int
{
	Fl::args ( argc , argv ) ;
	window = new Fl_Double_Window { 820 , 620 } ;
	box = new Fl_Box { 10 , 10 , 800 , 600 /*, "こんにちは世界" */ } ;
	image = new Fl_PNG_Image { "test000.png" } ;
	box->image ( image ) ;
	window->add ( box ) ;
	box->box ( FL_UP_BOX  ) ;
	window->end ( ) ;
	window->show ( ) ;
	Fl::wait ( 5 ) ;
	window->begin ( ) ;
	window->remove ( box ) ;
	//box = new Fl_Box { 10 , 10 , 800 , 600 /*, "こんにちは世界" */ } ;
	image = new Fl_PNG_Image { "test001.png" } ;
	box->image ( image ) ;
	window->add ( box ) ;
	box->box ( FL_UP_BOX  ) ;
	window->end ( ) ;
	window->show ( ) ;
	return Fl::run ( ) ;
}