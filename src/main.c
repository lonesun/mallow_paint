/*---------------------------------------------------------------------------------
    Mallow Paint - SNES Application
---------------------------------------------------------------------------------*/
#include <snes.h>
#include "main.h"

int main(void)
{
    // Initialize default text engine on Background 0
    // Default Map is 0x6800, Gfx font is at 0x3000
    consoleInitDefaultText(0);

    // Set background graphics and map pointers
    bgSetGfxPtr(0, 0x3000);
    bgSetMapPtr(0, 0x6800, SC_32x32);

    // Set video mode 1 (16 colors per BG layer) and enable only BG0
    setMode(SCREEN_MODE, 0);
    bgSetDisable(1);
    bgSetDisable(2);

    // Draw welcome screen text
    consoleDrawText(8, 8,  "=== MALLOW PAINT ===");
    consoleDrawText(6, 12, "SNES ENGINE INITIALIZED");
    consoleDrawText(6, 16, "READY FOR PIXEL MAGIC!");

    // Turn screen brightness on (full intensity)
    setScreenOn();

    // Main game / event loop
    while (1)
    {
        // Sync with the vertical blank interrupt (60 FPS on NTSC)
        WaitForVBlank();
    }

    return 0;
}
