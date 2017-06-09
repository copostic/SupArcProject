// let's define some things

#define PPU_CTRL		*((unsigned char*)0x2000)
#define PPU_MASK		*((unsigned char*)0x2001)
#define PPU_STATUS		*((unsigned char*)0x2002)
#define OAM_ADDRESS		*((unsigned char*)0x2003)
#define SCROLL			*((unsigned char*)0x2005)
#define PPU_ADDRESS		*((unsigned char*)0x2006)
#define PPU_DATA		*((unsigned char*)0x2007)
#define OAM_DMA			*((unsigned char*)0x4014)


#define RIGHT		0x01
#define LEFT		0x02
#define DOWN		0x04
#define UP			0x08
#define START		0x10
#define SELECT		0x20
#define B_BUTTON	0x40
#define A_BUTTON	0x80


// Globals
// our startup code initialized all values to zero
#pragma bss-name(push, "ZEROPAGE")
unsigned char NMI_flag;
unsigned char Frame_Count;
unsigned char index;
unsigned char index4;
unsigned char paddle_x;
unsigned char paddle_y;
unsigned char ball_x; 
unsigned char ball_y; 
unsigned char state;
unsigned char joypad1;
unsigned char joypad1old;
unsigned char joypad1test; 
unsigned char joypad2; 
unsigned char joypad2old;
unsigned char joypad2test;
unsigned char ball_x; 
unsigned char ball_y; 
unsigned char vector_ball_x; 
unsigned char vector_ball_y;
unsigned char tranche_gauche_balle;
unsigned char tranche_droite_balle; 
unsigned char tranche_droite_paddle; 
unsigned char tranche_gauche_paddle;
unsigned char game_status;
unsigned char i;
unsigned char count;
unsigned char sprite_x []    = {0x24,0x68,0x96,0xaa,0x38,0x5f,0x48,0x64,0x86,0x24,0x7f,0xaa};
unsigned char sprite_y []    = {0x02,0x02,0x02,0x0e,0x0e,0x0e,0x1a,0x1a,0x1a,0x26,0x26,0x26}; 
unsigned char sprite_number; 


#pragma bss-name(push, "OAM")
unsigned char SPRITES[256];
// OAM equals ram addresses 200-2ff




const unsigned char PALETTE[]={
0x00, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
0x00, 0x37, 0x24, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0}; // 0x28 : couleur gris

const unsigned char MetaSprite_Y[] = {0, 0, 8, 8}; // relative y coordinates

const unsigned char MetaSprite_Tile[] = { // tile numbers
    0, 1, 0x10, 0x11, // paddle
	2, 3, 0x12, 0x13, // balle
	4, 5, 0x14, 0x15, //sprite_brick
	6, 7, 0x16, 0x17}; // sprite_grey
enum {paddle, ball, sprite_brick, sprite_grey};


const unsigned char MetaSprite_Attrib[] = {0, 0, 0, 0}; 
// attributes = flipping, palette
//the reason I didn't just hardcode 0 below, is we still have the flexibility to use multiple palettes
//and or sprite flipping on the same metasprite

const unsigned char MetaSprite_X[] = {0, 8, 0, 8}; //relative x coordinates
//we are using 4 sprites, each one has a relative position from the top left sprite



// Prototypes
void All_Off (void);
void All_On (void);
void Reset_Scroll (void);
void Load_Palette (void);
void update_Sprites (void);
void move_logic (void);
void check_collision(void);

