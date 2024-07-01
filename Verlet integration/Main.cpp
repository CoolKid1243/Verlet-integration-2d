#include "Application.h"
#include <memory>

int main() {
    std::unique_ptr<App> Application = std::make_unique<App>();
    Application->run();
   
    return 0;
}