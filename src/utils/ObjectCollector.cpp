//
// Created by Bruno Fortunato on 01/06/16.
//

#include "tinto/utils/ObjectCollector.h"

namespace tinto {

    ObjectCollector::ObjectCollector() {
        references = new std::vector<Collectable *>();
    }

    ObjectCollector::~ObjectCollector() {
        for (auto r : *references) {
            delete r;
        }

        delete references;
    }

}