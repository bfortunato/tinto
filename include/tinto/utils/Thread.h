//
// Created by Bruno Fortunato on 06/06/16.
//

#ifndef TINTO_THREAD_H
#define TINTO_THREAD_H

#include <iostream>

#include <SDL_thread.h>

namespace tinto {

    typedef std::function<void(void *data)> ThreadAction;

    class Thread {
    public:
        Thread(const ThreadAction action);

        ~Thread();


        std::string name = "No name Thread";
        ThreadAction action;
        void *data;

        void run();

        static void init();

        static void checkMainThread();

        static void run(ThreadAction action);

    private:
        SDL_Thread *_thread;

        static SDL_threadID _mainThreadID;
    };

}

#endif //TINTO_THREAD_H
