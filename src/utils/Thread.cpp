//
// Created by Bruno Fortunato on 06/06/16.
//

#include <SDL_log.h>

#include "tinto/utils/Thread.h"

namespace tinto {

    Thread::Thread(const ThreadAction action) : action(action) {

    }

    Thread::~Thread() {
        _thread = nullptr;
    }

    static int __doRun(void *data) {
        Thread *thread = static_cast<Thread *>(data);
        thread->action(thread->data);
        delete thread;
        return 0;
    }

    void Thread::run() {
        _thread = SDL_CreateThread(__doRun, name.c_str(), this);
    }

    void Thread::run(ThreadAction action) {
        //Thread *t = new Thread(action);
        //t->run();

        action(nullptr);
    }

    void Thread::init() {
        _mainThreadID = SDL_GetThreadID(NULL);
    }


    void Thread::checkMainThread() {
        auto currentId = SDL_GetThreadID(NULL);
        if (_mainThreadID != currentId) {
            SDL_Log("Can be called only in main thread");
            throw std::exception();
        }
    }

    SDL_threadID Thread::_mainThreadID = 0;

}




