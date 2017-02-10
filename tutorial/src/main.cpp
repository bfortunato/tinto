//
// Created by bruno fortunato on 28/01/2017.
//

#include <tinto/tinto.h>

using namespace tinto;

class MyScene: public Scene {
public:
    MyScene(GameEngine *engine):Scene(engine) {}

    virtual void init() override {
        Scene::init();

        auto rectangle = collector->collect(new Rectangle(engine));
        rectangle->rect = GRect(
                engine->metrics->rect.getCenter().x,
                engine->metrics->rect.getCenter().y,
                1,
                1
        );
        rectangle->backgroundColor = Color(0x00FF00FF);
        rectangle->init();

        rectangle->animate(AnimationProperty::ROTATION, 0, 90, 1000, AnimationEase::EASE_IN_OUT, true);

        addChild(rectangle);
    }

};

int main(int argc, char * argv[]) {
    auto engine = tinto::GameEngine();
    engine.init(800, 600);

    engine.sceneManager->setRoot(new MyScene(&engine));

    engine.run();
    engine.destroy();

    return 0;
}