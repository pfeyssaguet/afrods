// Graphics converted using PAGfx by Mollusk.

#pragma once

#ifdef __cplusplus
extern "C"{
#endif

// Sprites:
extern const unsigned char perso_Sprite[12288] __attribute__((aligned (4))); // Palette: perso_Pal

// Backgrounds:
extern const int bg0_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg0_Map[768] __attribute__((aligned (4))); // Palette: bg0_Pal
extern const unsigned char bg0_Tiles[12352] __attribute__((aligned (4))); // Palette: bg0_Pal


// Palettes:
extern const unsigned short perso_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg0_Pal[256] __attribute__((aligned (4)));

#ifdef __cplusplus
}
#endif
