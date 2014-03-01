#include "GPP_impl.hpp"
FXDEFMAP(MainWindow) MainWindowMap[] = {};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))
// 250x250のメインウインドウの大きさ
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
      text_label{ new FXLabel{ this, "こんにちは世界" } } {}
void MainWindow::create() {
    FXMainWindow::create();
    show(PLACEMENT_SCREEN); // PLACEMENT_SCREENで画面中央に表示
}
MainWindow::~MainWindow() {}