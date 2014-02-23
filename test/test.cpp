#include <fx.h>
#include "test.hpp"

FXDEFMAP(MainWindow) MainWindowMap[] = {};

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

// 250x250のメインウインドウの大きさ
MainWindow::MainWindow(FXApp *app)
    : FXMainWindow(app, "MainWindow", NULL, NULL, DECOR_ALL, 0, 0, 250, 250) {}

void MainWindow::create() {
  FXMainWindow::create();
  show(PLACEMENT_SCREEN); // PLACEMENT_SCREENで画面中央に表示
}

MainWindow::~MainWindow() {}
int main(int argc, char *argv[]) {
  FXApp application("MainWindow", "MainWindow");
  application.init(argc, argv);
  new MainWindow(&application);
  application.create();
  return application.run();
}