/*---------------------------------------------------------------------------------
    Mallow Paint - SNES Application
---------------------------------------------------------------------------------*/
#include <snes.h>
#include "main.h"

static void drawTrackLabel(u16 trackId)
{
    if (trackId == MUSIC_POLLEN8)
    {
        consoleDrawText(4, 20, "BGM: POLLEN8 (SAMPLE)   ");
    }
    else
    {
        consoleDrawText(4, 20, "BGM: MALLOW TITLE THEME ");
    }
    consoleDrawText(4, 22, "[SELECT] SWITCH BGM     ");
}

int main(void)
{
    u16 pad0;
    u16 prevSelect = 0;
    u16 selectHeld;

    // Boot the SPC700 sound driver first (Book I Appendix D / Sound Caution #9)
    initMusic();

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
    drawTrackLabel(MUSIC_BACKGROUND);

    // Turn screen brightness on (full intensity)
    setScreenOn();

    // Play background music (defaults to MUSIC_MALLOW_TITLE; supports MUSIC_POLLEN8)
    playMusic(MUSIC_BACKGROUND);

    // Main game / event loop
    while (1)
    {
        // Process SPC700 music stream messages each frame
        updateMusic();

        // Sync with the vertical blank interrupt (60 FPS on NTSC)
        WaitForVBlank();

        // Allow toggling between the generated Mallow Title Theme and Pollen8 with SELECT
        // (Edge detection per Book I System Caution #16)
        pad0 = padsCurrent(0);
        selectHeld = (pad0 & KEY_SELECT);
        if (selectHeld && !prevSelect)
        {
            if (getCurrentMusic() == MUSIC_MALLOW_TITLE)
            {
                playMusic(MUSIC_POLLEN8);
            }
            else
            {
                playMusic(MUSIC_MALLOW_TITLE);
            }
            drawTrackLabel(getCurrentMusic());
        }
        prevSelect = selectHeld;
    }

    return 0;
}
