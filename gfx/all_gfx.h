//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
    typedef struct{
    void *Map;
    int MapSize;
    void *Tiles;
    int TileSize;
    void *Palette;
    int *Info;
} PAGfx_struct;
#endif


// Sprite files : 
extern const unsigned char spr_menu_button_Sprite[6144] __attribute__ ((aligned (4))) ;  // Pal : palMenu_Pal
extern const unsigned char spr_menu_icons_Sprite[5120] __attribute__ ((aligned (4))) ;  // Pal : palMenu_Pal
extern const unsigned char spr_perso_Sprite[12288] __attribute__ ((aligned (4))) ;  // Pal : palPerso_Pal
extern const unsigned char spr_game_icons_Sprite[6144] __attribute__ ((aligned (4))) ;  // Pal : palGame_Pal

// Background files : 
extern const int bg_splash_top_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_splash_top_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_splash_top_Pal
extern const unsigned char bg_splash_top_Tiles[49088] __attribute__ ((aligned (4))) ;  // Pal : bg_splash_top_Pal
extern PAGfx_struct bg_splash_top; // background pointer

extern const int bg_splash_loading_top_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_splash_loading_top_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_splash_loading_top_Pal
extern const unsigned char bg_splash_loading_top_Tiles[46784] __attribute__ ((aligned (4))) ;  // Pal : bg_splash_loading_top_Pal
extern PAGfx_struct bg_splash_loading_top; // background pointer

extern const int bg_splash_bottom_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_splash_bottom_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_splash_bottom_Pal
extern const unsigned char bg_splash_bottom_Tiles[49152] __attribute__ ((aligned (4))) ;  // Pal : bg_splash_bottom_Pal
extern PAGfx_struct bg_splash_bottom; // background pointer

extern const int bg_menu_top_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_menu_top_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_top_Pal
extern const unsigned char bg_menu_top_Tiles[49088] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_top_Pal
extern PAGfx_struct bg_menu_top; // background pointer

extern const int bg_menu_bottom_01_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_menu_bottom_01_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_01_Pal
extern const unsigned char bg_menu_bottom_01_Tiles[45120] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_01_Pal
extern PAGfx_struct bg_menu_bottom_01; // background pointer

extern const int bg_menu_bottom_02_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_menu_bottom_02_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_02_Pal
extern const unsigned char bg_menu_bottom_02_Tiles[41088] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_02_Pal
extern PAGfx_struct bg_menu_bottom_02; // background pointer

extern const int bg_menu_bottom_03_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_menu_bottom_03_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_03_Pal
extern const unsigned char bg_menu_bottom_03_Tiles[36800] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_03_Pal
extern PAGfx_struct bg_menu_bottom_03; // background pointer

extern const int bg_menu_bottom_04_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_menu_bottom_04_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_04_Pal
extern const unsigned char bg_menu_bottom_04_Tiles[32576] __attribute__ ((aligned (4))) ;  // Pal : bg_menu_bottom_04_Pal
extern PAGfx_struct bg_menu_bottom_04; // background pointer

extern const int bg_newchar_top_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_newchar_top_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_newchar_top_Pal
extern const unsigned char bg_newchar_top_Tiles[46784] __attribute__ ((aligned (4))) ;  // Pal : bg_newchar_top_Pal
extern PAGfx_struct bg_newchar_top; // background pointer

extern const int bg_newchar_bottom_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_newchar_bottom_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_newchar_bottom_Pal
extern const unsigned char bg_newchar_bottom_Tiles[45248] __attribute__ ((aligned (4))) ;  // Pal : bg_newchar_bottom_Pal
extern PAGfx_struct bg_newchar_bottom; // background pointer

extern const char bg_font_menu_Height;
extern const char bg_font_menu_Sizes[256];
extern const int bg_font_menu_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_font_menu_Map[1024] __attribute__ ((aligned (4))) ;  // Pal : bg_font_menu_Pal
extern const unsigned char bg_font_menu_Tiles[11392] __attribute__ ((aligned (4))) ;  // Pal : bg_font_menu_Pal
extern PAGfx_struct bg_font_menu; // background pointer

extern const int bg_game_tiles_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_game_tiles_Map[16384] __attribute__ ((aligned (4))) ;  // Pal : bg_game_tiles_Pal
extern const unsigned char bg_game_tiles_Tiles[27072] __attribute__ ((aligned (4))) ;  // Pal : bg_game_tiles_Pal
extern PAGfx_struct bg_game_tiles; // background pointer

extern const int bg_game_bottom_Info[3]; // BgMode, Width, Height
extern const unsigned short bg_game_bottom_Map[768] __attribute__ ((aligned (4))) ;  // Pal : bg_game_bottom_Pal
extern const unsigned char bg_game_bottom_Tiles[49024] __attribute__ ((aligned (4))) ;  // Pal : bg_game_bottom_Pal
extern PAGfx_struct bg_game_bottom; // background pointer


// Palette files : 
extern const unsigned short palMenu_Pal[115] __attribute__ ((aligned (4))) ;
extern const unsigned short palPerso_Pal[51] __attribute__ ((aligned (4))) ;
extern const unsigned short palGame_Pal[252] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_splash_top_Pal[236] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_splash_loading_top_Pal[166] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_splash_bottom_Pal[219] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_menu_top_Pal[236] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_menu_bottom_01_Pal[256] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_menu_bottom_02_Pal[256] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_menu_bottom_03_Pal[256] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_menu_bottom_04_Pal[255] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_newchar_top_Pal[166] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_newchar_bottom_Pal[173] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_font_menu_Pal[69] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_game_tiles_Pal[105] __attribute__ ((aligned (4))) ;
extern const unsigned short bg_game_bottom_Pal[159] __attribute__ ((aligned (4))) ;


#endif

