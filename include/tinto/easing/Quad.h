#ifndef _PENNER_QUAD
#define _PENNER_QUAD

namespace tinto {
    namespace easing {
        class Quad {

        public:

            static float easeIn(float t, float b, float c, float d);

            static float easeOut(float t, float b, float c, float d);

            static float easeInOut(float t, float b, float c, float d);
        };
    }
}


#endif