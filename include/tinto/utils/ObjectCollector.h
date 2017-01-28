//
// Created by Bruno Fortunato on 01/06/16.
//

#ifndef TINTO_OBJECTCOLLECTOR_H
#define TINTO_OBJECTCOLLECTOR_H

#include <vector>
#include "Collectable.h"

namespace tinto {

    class ObjectCollector {
    public:

        ObjectCollector();

        ~ObjectCollector();

        template<class T>
        inline T collect(T reference) {
            references->push_back(reference);
            return reference;
        }

    private:
        std::vector<Collectable *> *references = nullptr;

    };

}

#endif //TINTO_OBJECTCOLLECTOR_H
