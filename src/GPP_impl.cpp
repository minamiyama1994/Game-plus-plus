#include "GPP_impl.hpp"
FXDEFMAP(MainWindow) MainWindowMap[] = {};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))
MainWindow::MainWindow(FXApp *app)
    : MainWindow{ app, "MainWindow", 800, 600 } {}
MainWindow::MainWindow(FXApp *app, const std::string &title)
    : MainWindow{ app, title, 800, 600 } {}
MainWindow::MainWindow(FXApp *app, unsigned short w, unsigned short h)
    : MainWindow{ app, "Game", w, h } {}
MainWindow::MainWindow(FXApp *app, const std::string &title, unsigned short w,
                       unsigned short h)
    : FXMainWindow{ app, title.c_str(), nullptr, nullptr,
                    DECOR_ALL & ~DECOR_SHRINKABLE & ~DECOR_STRETCHABLE &
                        ~DECOR_MAXIMIZE,
                    0, 0, w, h },
      w_{ w }, h_{ h },
      label_packer{ new FXPacker{ this, 0,       0,       0,      w_,
                                  h_,   w_ / 10, w_ / 10, h_ / 2, h_ / 4 } },
      text_label{ new FXLabel{ label_packer, "こんにちは世界",
                               nullptr,
                               LABEL_NORMAL, 0, 0, 4 * w_ / 5, h_ / 4 , 0 , 0 , 0 , 0 } } {}
void MainWindow::create() {
	text_label->setBackColor ( FXRGB ( 255,255,255 ) ) ;
    FXMainWindow::create();
    show(PLACEMENT_SCREEN);
}
MainWindow::~MainWindow() {}