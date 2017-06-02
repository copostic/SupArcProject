// main.c 
// 2ARC Project
// Corentin Postic, Aymeric Nosjean, Raphael Saladini, Romain 
.



#include "DEFINE.c"


void Get_Input (void); 


void main (void) {
	All_Off();
	tranche_gauche_balle = ball_x / 2-3; 
	tranche_droite_balle = ball_x / 2+3;
	tranche_gauche_paddle =  paddle_x / 2-8;
	tranche_droite_paddle = paddle_x / 2+8;    									
	paddle_x = 0x7f;		//Start position paddle x
	paddle_y = 0xc8;		//Start position paddle y
	ball_x = 0x7f; 			//Start position ball x
	ball_y = 0x7f;			//Start position ball y
	sprtie1x = 0x01; 
	sprite1y = 0x01; 
	vector_ball_y = 1; 
	Load_Palette();
	Reset_Scroll();
	All_On(); 		// Screen on
	while (1){ 	
		while (NMI_flag == 0); 
		
		Get_Input();
		move_logic();
		update_Sprites();
		
		NMI_flag = 0;
	}
}
	
	
void All_Off (void) {
	PPU_CTRL = 0;
	PPU_MASK = 0; 
}
	
	
void All_On (void) {
	PPU_CTRL = 0x90; // screen is on, NMI on
	PPU_MASK = 0x1e; 
}
	
	
void Reset_Scroll (void) {
	PPU_ADDRESS = 0;
	PPU_ADDRESS = 0;
	SCROLL = 0;
	SCROLL = 0;
}
	
	
void Load_Palette (void) {
	PPU_ADDRESS = 0x3f;
	PPU_ADDRESS = 0x00;
	for( index = 0; index < sizeof(PALETTE); ++index ){
		PPU_DATA = PALETTE[index];
	}
}


void update_Sprites (void) {
	state4 = paddle << 2; // same as state * 4
	index4 = 0;
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + paddle_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + paddle_x; // relative x + master x
		++index4;
	}
	state4 = ball << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + ball_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + ball_x; // relative x + master x
		++index4;
	}
	state4 = sprite1 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite1y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprtie1x; // relative x + master x
		++index4;
	}
}



void move_logic (void) {
	if (paddle_x <= 0xea){
		if ((joypad1 & RIGHT) != 0){
			state = paddle;
			paddle_x=paddle_x+3;
		
	}}
	if (paddle_x >= 0x02 ){
		if ((joypad1 & LEFT) != 0){
			state = paddle;
			paddle_x=paddle_x-3;
		
	}}
	if (ball_y <= 0x01) {
		vector_ball_y=1; 
	}
	if (tranche_gauche_balle >= tranche_gauche_paddle && tranche_droite_balle <= tranche_droite_paddle) {
		vector_ball_y = 2;
	}
	if (vector_ball_y == 1 ) {
		++ball_y; // la balle monte
	}
	if (vector_ball_y == 2 ) {
		--ball_y; // la balle descend
	}
	if (vector_ball_x == 1 ) {
		++ball_x; 
	}
	if (vector_ball_x == 2 ) {
		--ball_x; 
	}
}


