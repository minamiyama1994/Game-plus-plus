#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

auto main(int argc, char **argv) -> int
{
	Fl_Window * window = new Fl_Window ( 340 , 180 ) ;
	Fl_Box * box = new Fl_Box ( 20 , 40 , 300 , 100 , "こんにちは世界" ) ;
	box->box ( FL_UP_BOX ) ;
	box->labelfont ( FL_BOLD + FL_ITALIC ) ;
	box->labelsize ( 36 ) ;
	box->labeltype ( FL_SHADOW_LABEL ) ;
	window->end ( ) ;
	window->show ( argc , argv ) ;
	return Fl::run ( ) ;
}