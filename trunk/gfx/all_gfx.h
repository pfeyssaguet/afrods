// Graphics converted using PAGfx by Mollusk.

#pragma once

#ifdef __cplusplus
extern "C"{
#endif

// Sprites:
extern const unsigned char spr_menu_Sprite[6144] __attribute__((aligned (4))); // Palette: palMenu_Pal
extern const unsigned char spr_menu_icons_Sprite[6144] __attribute__((aligned (4))); // Palette: palMenu_Pal
extern const unsigned char spr_perso_Sprite[12288] __attribute__((aligned (4))); // Palette: palPerso_Pal

// Backgrounds:
extern const int bg_splash_top_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg_splash_top_Map[768] __attribute__((aligned (4))); // Palette: bg_splash_top_Pal
extern const unsigned char bg_splash_top_Tiles[48960] __attribute__((aligned (4))); // Palette: bg_splash_top_Pal

extern const int bg_splash_bottom_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg_splash_bottom_Map[768] __attribute__((aligned (4))); // Palette: bg_splash_bottom_Pal
extern const unsigned char bg_splash_bottom_Tiles[49152] __attribute__((aligned (4))); // Palette: bg_splash_bottom_Pal

extern const int bg_menu_top_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg_menu_top_Map[768] __attribute__((aligned (4))); // Palette: bg_menu_top_Pal
extern const unsigned char bg_menu_top_Tiles[48960] __attribute__((aligned (4))); // Palette: bg_menu_top_Pal

extern const int bg_menu_bottom_01_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg_menu_bottom_01_Map[768] __attribute__((aligned (4))); // Palette: bg_menu_bottom_01_Pal
extern const unsigned char bg_menu_bottom_01_Tiles[45248] __attribute__((aligned (4))); // Palette: bg_menu_bottom_01_Pal

extern const int bg_menu_bottom_02_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg_menu_bottom_02_Map[768] __attribute__((aligned (4))); // Palette: bg_menu_bottom_02_Pal
extern const unsigned char bg_menu_bottom_02_Tiles[41408] __attribute__((aligned (4))); // Palette: bg_menu_bottom_02_Pal

extern const int bg_menu_bottom_03_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg_menu_bottom_03_Map[768] __attribute__((aligned (4))); // Palette: bg_menu_bottom_03_Pal
extern const unsigned char bg_menu_bottom_03_Tiles[37568] __attribute__((aligned (4))); // Palette: bg_menu_bottom_03_Pal

extern const int bg_menu_bottom_04_Info[3] __attribute__((aligned (4))); // BgMode, Width, Height
extern const unsigned int bg_menu_bottom_04_Map[768] __attribute__((aligned (4))); // Palette: bg_menu_bottom_04_Pal
extern const unsigned char bg_menu_bottom_04_Tiles[33728] __attribute__((aligned (4))); // Palette: bg_menu_bottom_04_Pal


// Palettes:
extern const unsigned short palMenu_Pal[256] __attribute__((aligned (4)));
extern const unsigned short palPerso_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg_splash_top_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg_splash_bottom_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg_menu_top_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg_menu_bottom_01_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg_menu_bottom_02_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg_menu_bottom_03_Pal[256] __attribute__((aligned (4)));
extern const unsigned short bg_menu_bottom_04_Pal[256] __attribute__((aligned (4)));

#ifdef __cplusplus
}
#endif
