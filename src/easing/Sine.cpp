#include "tinto/easing/Sine.h"

namespace tinto {
    namespace easing {

        float Sine::easeIn(float t, float b, float c, float d) {
            return -c * cos(t / d * (PI / 2)) + c + b;
        }

        float Sine::easeOut(float t, float b, float c, float d) {
            return c * sin(t / d * (PI / 2)) + b;
        }

        float Sine::easeInOut(float t, float b, float c, float d) {
            return -c / 2 * (cos(PI * t / d) - 1) + b;
        }
    }
}