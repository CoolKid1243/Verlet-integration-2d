#include "Application.h"
#include <memory>

// From dev to dev, log how many days have been waisted on this system here: 5

int main() {
    std::unique_ptr<App> Application = std::make_unique<App>();
    Application->run();
   
    return 0;
}