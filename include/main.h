#ifndef MALLOW_PAINT_MAIN_H
#define MALLOW_PAINT_MAIN_H

#include <snes.h>

/* Application configurations and constants */
#define SCREEN_MODE BG_MODE1

/* Background music track IDs (mapped to res/soundbank.h) */
#define MUSIC_MALLOW_TITLE  0   /* Custom Mallow Paint title theme (res/mallow_title.it) */
#define MUSIC_POLLEN8       1   /* Bundled PVSnesLib sample track (res/pollen8.it) */

/* Default startup track; override or toggle at runtime between both sources */
#ifndef MUSIC_BACKGROUND
#define MUSIC_BACKGROUND    MUSIC_MALLOW_TITLE
#endif

/* Background Music (SPC700 / SNESMod) interface implemented in src/bgm.c */
void initMusic(void);
void playMusic(u16 trackId);
void updateMusic(void);
u16  getCurrentMusic(void);

#endif /* MALLOW_PAINT_MAIN_H */
