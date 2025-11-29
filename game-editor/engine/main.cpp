#include <emscripten/bind.h>
#include <string>

std::string test() 
{
    return "hello world!";
}

EMSCRIPTEN_BINDINGS(my_module) 
{
    emscripten::function("test", &test);
}