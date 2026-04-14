#include <bsp_api.h>
#include <r_ioport.h>
#include "Arduino_LED_Matrix.h"


ArduinoLEDMatrix matrix;

byte frame[8][12] = {
    {0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
    {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
int main() {
    matrix.begin();
    while (true) {
        matrix.renderBitmap(frame, 8, 12);
    }
    return 0;
}
