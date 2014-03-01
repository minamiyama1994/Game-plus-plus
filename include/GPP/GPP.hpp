#ifndef GPP_GPP_HPP
#define GPP_GPP_HPP
#include <tuple>
#include <string>
#include <memory>
#include "FTMP/list.hpp"
#include "FTMP/integral.hpp"
#include "FTMP/make_integer_sequence.hpp"
namespace gpp {
class text;
class image;
class bgm;
class pause;
class clear;
class game;
template <typename... T> class command_tuple;
template <typename T1, typename... T> class command_tuple<T1, T...> {
    T1 head_;
    command_tuple<T...> tail_;

  public:
    command_tuple(const T1 &o1, const T &... o);
    command_tuple(T1 &&o1, T &&... o);
    template <typename T_>
    auto add(const T_ &t_) -> command_tuple<T1, T..., T_> {
        return head_ + (tail_ + t_);
    }
    auto operator()(game &g) -> game &{ return tail_(head_(g)); }
};
template <typename T> class command_tuple<T> {
    T head_;

  public:
    command_tuple(const T &o);
    command_tuple(T &&o);
    template <typename T_> auto add(const T_ &t_) -> command_tuple<T, T_> {
        return command_tuple<T, T_>{ head_, t_ };
    }
    auto operator()(game &g) -> game &{ return head_(g); }
};
template <typename T1, typename... T>
command_tuple<T1, T...>::command_tuple(const T1 &o1, const T &... o)
    : head_{ o1 }, tail_{ o... } {}
template <typename T1, typename... T>
command_tuple<T1, T...>::command_tuple(T1 &&o1, T &&... o)
    : head_{ std::move(o1) }, tail_{ std::move(o)... } {}
template <typename T>
command_tuple<T>::command_tuple(const T &o)
    : head_{ o } {}
template <typename T>
command_tuple<T>::command_tuple(T &&o)
    : head_{ std::move(o) } {}
template <typename D> class command_base {
    template <std::size_t... N, typename... T>
    auto expand_command_tuple(ftmp::list<ftmp::integral<std::size_t, N>...>,
                              const command_tuple<T...> &t)
        -> command_tuple<D, T...> {
        return command_tuple<D, T...>{ static_cast<D &>(*this),
                                       std::get<N>(t)... };
    }

  public:
    template <typename T> auto add(const T &t) -> command_tuple<D, T> {
        return command_tuple<D, T>{ static_cast<D &>(*this), t };
    }
    template <typename... T>
    auto add(const command_tuple<T...> &t) -> command_tuple<D, T...> {
        return expand_command_tuple(
            typename ftmp::make_integer_sequence<
                ftmp::integral<std::size_t, 0>,
                ftmp::integral<std::size_t, sizeof...(T)> >::type{},
            t);
    }
    auto operator()(game &g) -> game &{ return static_cast<D &>(*this)(g); }
};
template <typename T, typename U>
constexpr auto operator+(const T &t, const U &u) -> decltype(t.add(u)) {
    return t.add(u);
}
class text : public command_base<text> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    text(const std::string &t);
    ~text();
    auto operator()(game &g) -> game &;
};
class image : public command_base<image> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    image(const std::string &path);
    ~image();
    auto operator()(game &g) -> game &;
};
class bgm : public command_base<bgm> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    bgm(const std::string &path);
    ~bgm();
    auto operator()(game &g) -> game &;
};
class pause : public command_base<pause> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    pause();
    ~pause();
    auto operator()(game &g) -> game &;
};
class clear : public command_base<clear> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    clear();
    ~clear();
    auto operator()(game &g) -> game &;
};
class game {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    game();
    game(int argc, char **argv);
    game(int argc, char **argv, const std::string &title);
    game(int argc, char **argv, unsigned short w, unsigned short h);
    game(int argc, char **argv, const std::string &title, unsigned short w,
         unsigned short h);
    ~game();
    auto title(const std::string) -> game &;
    auto size(unsigned short w, unsigned short h) -> game &;
    template <typename commannd_type>
    auto operator()(const commannd_type &cmd) -> game &{
        (cmd + pause{} + clear { })(*this);
    }
    auto operator()() -> int { return 0; }
};
int show_window(int argc, char **argv);
}
#endif