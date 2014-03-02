#ifndef GPP_TEST_HPP
#define GPP_TEST_HPP
#include <string>
#include <fx.h>
class MainWindow : public FXMainWindow {
  public:
    FXDECLARE(MainWindow)
  public:
    MainWindow(FXApp *app);
    MainWindow(FXApp *app, const std::string &title);
    MainWindow(FXApp *app, unsigned short w, unsigned short h);
    MainWindow(FXApp *app, const std::string &title, unsigned short w,
               unsigned short h);
    virtual void create();
    virtual ~MainWindow();

  protected:
    MainWindow() {}
    int w_;
    int h_;
    FXPacker *label_packer;
    FXLabel *text_label;
};
#endif