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
    command_tuple() = default;
    command_tuple(const command_tuple &) = default;
    command_tuple(command_tuple &&) = default ;
	auto operator = ( const command_tuple & ) -> command_tuple & = default ;
	auto operator = ( command_tuple && ) -> command_tuple & = default ;
    ~ command_tuple() = default;
    command_tuple(const T1 &o1, const T &... o);
    command_tuple(T1 &&o1, T &&... o);
    template <typename T_>
    auto add(const T_ &t_)const -> command_tuple<T1, T..., T_> {
        return head_ + (tail_ + t_);
    }
    auto operator()(game &g)const -> game &{ return tail_(head_(g)); }
	template <typename U>
	auto operator+(const U &u)const -> decltype(this->add(u)) {
		return this->add(u);
	}
};
template <typename T> class command_tuple<T> {
    T head_;

  public:
    command_tuple() = default;
    command_tuple(const command_tuple &) = default;
    command_tuple(command_tuple &&) = default ;
	auto operator = ( const command_tuple & ) -> command_tuple & = default ;
	auto operator = ( command_tuple && ) -> command_tuple & = default ;
    ~ command_tuple() = default;
    command_tuple(const T &o);
    command_tuple(T &&o);
    template <typename T_> auto add(const T_ &t_)const -> command_tuple<T, T_> {
        return command_tuple<T, T_>{ head_, t_ };
    }
    auto operator()(game &g)const -> game &{ return head_(g); }
	template <typename U>
	auto operator+(const U &u)const -> decltype(this->add(u)) {
		return this->add(u);
	}
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
                              const command_tuple<T...> &t)const
        -> command_tuple<D, T...> {
        return command_tuple<D, T...>{ static_cast<D &>(*this),
                                       std::get<N>(t)... };
    }

  public:
    command_base() = default;
    command_base(const command_base &) = default;
    command_base(command_base &&) = default ;
	auto operator = ( const command_base & ) -> command_base & = default ;
	auto operator = ( command_base && ) -> command_base & = default ;
    ~ command_base() = default;
    template <typename T> auto add(const T &t) -> command_tuple<D, T> {
        return command_tuple<D, T>{ static_cast<D &>(*this), t };
    }
    template <typename... T>
    auto add(const command_tuple<T...> &t)const -> command_tuple<D, T...> {
        return expand_command_tuple(
            typename ftmp::make_integer_sequence<
                ftmp::integral<std::size_t, 0>,
                ftmp::integral<std::size_t, sizeof...(T)> >::type{},
            t);
    }
    auto operator()(game &g)const -> game &{ return static_cast<D &>(*this)(g); }
	template <typename U>
	auto operator+(const U &u)const -> decltype(this->add(u)) {
		return this->add(u);
	}
};
class text : public command_base<text> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    text() = delete;
    text(const text &) = default;
    text(text &&) = default ;
	auto operator = ( const text & ) -> text & = default ;
	auto operator = ( text && ) -> text & = default ;
    text(const std::string &t);
    ~text();
    auto operator()(game &g)const -> game &;
};
class image : public command_base<image> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    image() = delete;
    image(const image &) = default;
    image(image &&) = default ;
	auto operator = ( const image & ) -> image & = default ;
	auto operator = ( image && ) -> image & = default ;
    image(const std::string &path);
    ~image();
    auto operator()(game &g)const -> game &;
};
class bgm : public command_base<bgm> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    bgm() = delete;
    bgm(const bgm &) = default;
    bgm(bgm &&) = default ;
	auto operator = ( const bgm & ) -> bgm & = default ;
	auto operator = ( bgm && ) -> bgm & = default ;
    bgm(const std::string &path);
    ~bgm();
    auto operator()(game &g)const -> game &;
};
class pause : public command_base<pause> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    pause(const pause &) = default;
    pause(pause &&) = default ;
	auto operator = ( const pause & ) -> pause & = default ;
	auto operator = ( pause && ) -> pause & = default ;
    pause();
    ~pause();
    auto operator()(game &g)const -> game &;
};
class clear : public command_base<clear> {
  public:
    class Impl;

  private:
    std::unique_ptr<Impl> impl_;

  public:
    clear(const clear &) = default;
    clear(clear &&) = default ;
	auto operator = ( const clear & ) -> clear & = default ;
	auto operator = ( clear && ) -> clear & = default ;
    clear();
    ~clear();
    auto operator()(game &g)const -> game &;
};
class game {
  public:
    class Impl;

  private:
    friend text::Impl;
    friend image::Impl;
    friend bgm::Impl;
    friend pause::Impl;
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
    auto operator()(const commannd_type &cmd)const -> game &{
        (cmd + pause {} + clear{})(*this);
    }
    auto operator()()const -> int { return 0; }
};
}
#endif