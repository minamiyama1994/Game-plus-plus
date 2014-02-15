#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>

auto main(int argc, char **argv) -> int
{
	Fl_Window * window = new Fl_Window { 820 , 620 } ;
	Fl_Box * box = new Fl_Box { 10 , 10 , 800 , 600 /*, "こんにちは世界" */} ;
	box->image ( new Fl_PNG_Image { "test.png" } ) ;
	window->end ( ) ;
	window->show ( argc , argv ) ;
	return Fl::run ( ) ;
}