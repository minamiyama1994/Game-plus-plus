#ifndef GPP_GPP_HPP
#define GPP_GPP_HPP
#include <tuple>
#include <string>
#include <memory>
#include <vector>
#include <functional>
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
template <typename D> class command_base;
template <typename... T> class command_tuple : public std::tuple<T...> {
    template <std::size_t... N, typename T_>
    auto expand_command_tuple(ftmp::list<ftmp::integral<std::size_t, N>...>,
                              const command_base<T_> &t)
        const -> command_tuple<T..., T_> {
        return command_tuple<T..., T_>{ std::get<N>(*this)...,
                                        static_cast<const T_ &>(t) };
    }
    template <std::size_t... N1, std::size_t... N2, typename... T_>
    auto expand_command_tuple(ftmp::list<ftmp::integral<std::size_t, N1>...>,
                              ftmp::list<ftmp::integral<std::size_t, N2>...>,
                              const command_tuple<T_...> &t)
        const -> command_tuple<T..., T_...> {
        return command_tuple<T..., T_...>{ std::get<N1>(*this)...,
                                           std::get<N2>(t)... };
    }
    template <std::size_t... N>
    auto expand_operator_call(ftmp::list<ftmp::integral<std::size_t, N>...>,
                              game &g) const -> game &;

  public:
    using std::tuple<T...>::tuple;
    command_tuple() = default;
    command_tuple(const command_tuple &) = default;
    command_tuple(command_tuple &&) = default;
    auto operator=(const command_tuple &) -> command_tuple & = default;
    auto operator=(command_tuple &&) -> command_tuple & = default;
    ~command_tuple() = default;
    template <typename T_>
    auto add(const command_base<T_> &t) const -> command_tuple<T..., T_> {
        return expand_command_tuple(
            typename ftmp::make_integer_sequence<
                ftmp::integral<std::size_t, 0>,
                ftmp::integral<std::size_t, sizeof...(T)> >::type{},
            t);
    }
    template <typename... T_>
    auto add(const command_tuple<T...> &t) const -> command_tuple<T..., T_...> {
        return expand_command_tuple(
            typename ftmp::make_integer_sequence<
                ftmp::integral<std::size_t, 0>,
                ftmp::integral<std::size_t, sizeof...(T)> >::type{},
            typename ftmp::make_integer_sequence<
                ftmp::integral<std::size_t, 0>,
                ftmp::integral<std::size_t, sizeof...(T_)> >::type{},
            t);
    }
    template <typename U>
    auto operator+(const U &u) const -> decltype(this -> add(u)) {
        return this->add(u);
    }
    auto operator()(game &g) const -> game &;
};
template <typename... T>
auto expand_operator_call_impl(
    game &g, std::vector<std::function<game &(game &)> >::const_iterator begin,
    std::vector<std::function<game &(game &)> >::const_iterator end) -> game &{
    if (begin == end) {
        return g;
    }
    return expand_operator_call_impl((*begin)(g), begin + 1, end);
}
template <typename... T>
template <std::size_t... N>
auto command_tuple<T...>::expand_operator_call(
    ftmp::list<ftmp::integral<std::size_t, N>...>, game &g) const -> game &{
    std::vector<std::function<game &(game &)> > fs{ std::get<N>(*this)... };
    return expand_operator_call_impl(g, fs.begin(), fs.end());
}
template <typename... T>
auto command_tuple<T...>::operator()(game &g) const -> game &{
    return expand_operator_call(
        typename ftmp::make_integer_sequence<
            ftmp::integral<std::size_t, 0>,
            ftmp::integral<std::size_t, sizeof...(T)> >::type{},
        g);
}
template <typename D> class command_base {
    template <std::size_t... N, typename... T>
    auto expand_command_tuple(ftmp::list<ftmp::integral<std::size_t, N>...>,
                              const command_tuple<T...> &t)
        const -> command_tuple<D, T...> {
        return command_tuple<D, T...>{ static_cast<const D &>(*this),
                                       std::get<N>(t)... };
    }

  public:
    command_base() = default;
    command_base(const command_base &) = default;
    command_base(command_base &&) = default;
    auto operator=(const command_base &) -> command_base & = default;
    auto operator=(command_base &&) -> command_base & = default;
    ~command_base() = default;
    template <typename T>
    auto add(const command_base<T> &t) const -> command_tuple<D, T> {
        return command_tuple<D, T>{ static_cast<const D &>(*this),
                                    static_cast<const T &>(t) };
    }
    template <typename... T>
    auto add(const command_tuple<T...> &t) const -> command_tuple<D, T...> {
        return expand_command_tuple(
            typename ftmp::make_integer_sequence<
                ftmp::integral<std::size_t, 0>,
                ftmp::integral<std::size_t, sizeof...(T)> >::type{},
            t);
    }
    template <typename U>
    auto operator+(const U &u) const -> decltype(this -> add(u)) {
        return this->add(u);
    }
};
class text : public command_base<text> {
  public:
    class Impl;

  private:
    std::shared_ptr<Impl> impl_;

  public:
    text() = delete;
    text(const text &) = default;
    text(text &&) = default;
    auto operator=(const text &) -> text & = default;
    auto operator=(text &&) -> text & = default;
    text(const std::string &t);
    ~text();
    auto operator()(game &g) const -> game &;
};
class image : public command_base<image> {
  public:
    class Impl;

  private:
    std::shared_ptr<Impl> impl_;

  public:
    image() = delete;
    image(const image &) = default;
    image(image &&) = default;
    auto operator=(const image &) -> image & = default;
    auto operator=(image &&) -> image & = default;
    image(const std::string &path);
    ~image();
    auto operator()(game &g) const -> game &;
};
class bgm : public command_base<bgm> {
  public:
    class Impl;

  private:
    std::shared_ptr<Impl> impl_;

  public:
    bgm() = delete;
    bgm(const bgm &) = default;
    bgm(bgm &&) = default;
    auto operator=(const bgm &) -> bgm & = default;
    auto operator=(bgm &&) -> bgm & = default;
    bgm(const std::string &path);
    ~bgm();
    auto operator()(game &g) const -> game &;
};
class pause : public command_base<pause> {
  public:
    class Impl;

  private:
    std::shared_ptr<Impl> impl_;

  public:
    pause(const pause &) = default;
    pause(pause &&) = default;
    auto operator=(const pause &) -> pause & = default;
    auto operator=(pause &&) -> pause & = default;
    pause();
    ~pause();
    auto operator()(game &g) const -> game &;
};
class clear : public command_base<clear> {
  public:
    class Impl;

  private:
    std::shared_ptr<Impl> impl_;

  public:
    clear(const clear &) = default;
    clear(clear &&) = default;
    auto operator=(const clear &) -> clear & = default;
    auto operator=(clear &&) -> clear & = default;
    clear();
    ~clear();
    auto operator()(game &g) const -> game &;
};
class game {
  public:
    class Impl;

  private:
    friend text::Impl;
    friend image::Impl;
    friend bgm::Impl;
    friend pause::Impl;
    std::shared_ptr<Impl> impl_;

  public:
    game();
    game(int argc, char **argv);
    game(int argc, char **argv, const std::string &title);
    game(int argc, char **argv, unsigned short w, unsigned short h);
    game(int argc, char **argv, const std::string &title, unsigned short w,
         unsigned short h);
    ~game();
    auto title(const std::string &) -> game &;
    auto size(unsigned short w, unsigned short h) -> game &;
    template <typename commannd_type>
    auto operator()(const commannd_type &cmd) -> game &{
        (cmd + pause {} + clear{})(*this);
    }
    auto operator()() const -> int { return 0; }
};
}
#endif