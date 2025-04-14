#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/HelloThere.h"
#include "scenes/Assignment2.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = {new TestScene(), new HelloThere(),
                                  new Assignment2(),
    };
    Application app(scenes);
    return app.Run();

}
