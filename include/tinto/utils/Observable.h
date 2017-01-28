//
// Created by Bruno Fortunato on 01/06/16.
//

#ifndef TINTO_OBSERVABLE_H
#define TINTO_OBSERVABLE_H

#include <vector>
#include <string>
#include <functional>

namespace tinto {

    class Observable;

    typedef std::function<void(Observable *, void *)> EventListener;

    class _EventListenerData {
    public:
        _EventListenerData(const std::string &event, const EventListener &listener) : event(event),
                                                                                      listener(listener) { }

        std::string event;
        EventListener listener;
    };

    class Observable {
    public:
        void invoke(std::string event, void *data = nullptr);

        void on(std::string event, EventListener listener);

    private:
        std::vector<_EventListenerData> _listeners;
    };

}


#endif //TINTO_OBSERVABLE_H
