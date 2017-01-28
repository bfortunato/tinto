//
// Created by Bruno Fortunato on 01/06/16.
//

#include "tinto/utils/Observable.h"

namespace tinto {

    void Observable::on(std::string event, EventListener listener) {
        _listeners.push_back(_EventListenerData(event, listener));
    }

    void Observable::invoke(std::string event, void *data) {
        for (auto d : _listeners) {
            if (d.event == event) {
                d.listener(this, data);
            }
        }
    }

}