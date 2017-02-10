//
// Created by bruno fortunato on 28/01/2017.
//

#include <tinto/tinto.h>
#include <android/log.h>

#define APPNAME "tintotutorial"

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
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "1");

    auto engine = tinto::GameEngine();
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "2");

    engine.init(800, 600);
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "3");

    engine.sceneManager->setRoot(new MyScene(&engine));
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "4");
    engine.run();
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "5");
    engine.destroy();
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "6");
    return 0;
}