#include <cstdlib>
#include "GPP_impl.hpp"
FXDEFMAP(MainWindow) MainWindowMap[] = {};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))
MainWindow::MainWindow(FXApp *app) : MainWindow{ app, "Game", 800, 600 } {}
MainWindow::MainWindow(FXApp *app, const std::string &title)
    : MainWindow{ app, title, 800, 600 } {}
MainWindow::MainWindow(FXApp *app, unsigned short w, unsigned short h)
    : MainWindow{ app, "Game", w, h } {}
MainWindow::MainWindow(FXApp *app, const std::string &title, unsigned short w,
                       unsigned short h)
    : FXMainWindow{ app, title.c_str(), nullptr, nullptr,
                    DECOR_ALL & ~DECOR_SHRINKABLE & ~DECOR_STRETCHABLE &
                        ~DECOR_MAXIMIZE,
                    0, 0, w, h , 0 , 0 , 0 , 0 , 0 , 0 },
      w_{ w }, h_{ h },
      image_packer_{ new FXPacker{ this, 0, 0, 0, w_, h_, 0, 0, 0, 0 } },
      image_icon_{ new FXBMPIcon{ app } },
      image_label_{ new FXLabel{
          image_packer_, "", image_icon_, JUSTIFY_LEFT | ICON_BEFORE_TEXT, 0, 0,
          w_,            h_, 0,           0,                               0, 0
      } },
      label_packer_{ new FXPacker{ image_packer_, 0,       0,       0,      w_,
                                   h_,   w_ / 10, w_ / 10, 0, h_ / 4 } },
      text_label_{ new FXLabel{ label_packer_, "こんにちは\n世界",
                                nullptr,       JUSTIFY_LEFT | ICON_BEFORE_TEXT,
                                0,             0,
                                4 * w_ / 5,    h_ / 4,
                                0,             0,
                                0,             0 } } {
    image_label_->setBackColor(FXRGB(0, 0, 0));
    FXFileStream stream{ "test/test.bmp", FXStreamLoad, 65536UL };
    image_icon_->loadPixels(stream);
    text_label_->setBackColor(FXRGB(255, 255, 255));
    text_label_->setPadRight(4 * w_ / 5 - text_label_->getWidthForHeight(0));
    text_label_->setPadBottom(h_ / 4 - text_label_->getHeightForWidth(0));
}
void MainWindow::create() {
    FXMainWindow::create();
    show();
}
MainWindow::~MainWindow() {}