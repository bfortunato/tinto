//
// Created by Bruno Fortunato on 01/06/16.
//

#ifndef TINTO_FPSTEXT_H
#define TINTO_FPSTEXT_H


#include "Text.h"

namespace tinto {

    class FpsText : public Text {
    public:
        virtual void update(GameTime *gameTime) override;

        FpsText(GameEngine *engine) : Text(engine) { }

    private:
        Uint32 _elapsedTime = 0;
    };

}

#endif //TINTO_FPSTEXT_H
