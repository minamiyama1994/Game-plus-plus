#ifndef GPP_TEST_HPP
#define GPP_TEST_HPP
class MainWindow : public FXMainWindow {
  public:
    FXDECLARE(MainWindow)
  public:
    MainWindow(FXApp *app);
    virtual void create();
    virtual ~MainWindow();

  protected:
    MainWindow() {}
};
#endif