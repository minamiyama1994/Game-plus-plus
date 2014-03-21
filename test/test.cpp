#include "GPP/GPP.hpp"
int main(int argc, char *argv[]) {
    return gpp::game(argc,argv)
    (gpp::text { "Hello!" } + gpp::image{ "hello.jpg" })
    (gpp::text { "For example, you can play the BGM As you can see." } + gpp::bgm { "test.mp3" } + gpp::pause {} + gpp::text { "and you can display the image as you can see." } + gpp::image{ "test.jpg" })
    (gpp::text { "I end the introduction of \"Game++\" in this." })();
}
