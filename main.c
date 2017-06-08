// main.c 
// 2ARC Project
// Corentin Postic, Aymeric Nosjean, Raphael Saladini, Romain 

#include "DEFINE.c"


void Get_Input (void); 

void main (void) {
	All_Off(); //Remet les variables d'affichage à 0
   									
	//Définit la position de base
    // du paddle et de la balle
    paddle_x = 0x7f;
	paddle_y = 0xc8;
	ball_x = 0x7f;		
	ball_y = 0x7f;       
    
    
	sprite1_x = 0x7f; 
	sprite1_y = 0x02;
	sprite2_x = 0xaa; // dernier sprite première ligne 
	sprite2_y = 0x02; // dernier sprite première ligne
	sprite3_x = 0x4f;
	sprite3_y = 0x02;
	sprite4_x = 0x24;
	sprite4_y = 0x02;
	sprite7_x = 0x39; //premier sprite deuxième ligne
	sprite7_y = 0x0e; //premier sprite deuxième ligne
	sprite6_x = 0x68; //deuxième sprite deuxième ligne
	sprite6_y = 0x0e; //deuxième sprite deuxième ligne
	sprite8_x = 0x96; //troisième sprite deuxième ligne
	sprite8_y = 0x0e; //troisième sprite deuxième ligne
	sprite9_x = 0xbe; //Quatrième sprite deuxième ligne
	sprite9_y = 0x0e; //Quatrième sprite deuxième ligne
	sprite10_x = 0x7f; 
	sprite10_y = 0x1a; 
	sprite11_x = 0xaa; 
	sprite11_y = 0x1a; 
	sprite12_x = 0x4f; 
	sprite12_y = 0x1a; 
	sprite13_x = 0x24; 
	sprite13_y = 0x1a; 
	sprite14_x = 0x96; 
	sprite14_y = 0x26; 
	sprite15_x = 0x68; 
	sprite15_y = 0x26; 
	/*sprite16_x = 0x96; 
	sprite16_y = 0x26; 
	sprite17_x = 0xbe; 
	sprite17_y = 0x26;*/ 

	vector_ball_y = 1; //Fait monter la balle
	Load_Palette();
	Reset_Scroll();
	All_On(); 		// Activation de l'écran
    game_status=1;
    while((joypad1 & A_BUTTON) == 0){Get_Input();}
    
	while (game_status == 1){
        if((joypad1 & START) != 0){
            while((joypad1 & A_BUTTON) == 0){
                Get_Input();
            }
        }
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
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite1_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite1_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite2_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite2_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite3_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite3_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite4_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite4_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite6_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite6_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite7_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite7_x; // relative x + master x
		++index4;
	}
		state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite8_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite8_x; // relative x + master x
		++index4;
	}
		state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite9_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite9_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite10_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite10_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite11_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite11_x; // relative x + master x
		++index4;
	}
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite12_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite12_x; // relative x + master x
		++index4;
	}
		state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite13_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite13_x; // relative x + master x
		++index4;
	}
	
	state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite14_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite14_x; // relative x + master x
		++index4;
	}
		state4 = sprite2 << 2; // same as state * 4
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + sprite15_y; // relative y + master y
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state4]; // tile numbers
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index]; // attributes, all zero here
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + sprite15_x; // relative x + master x
		++index4;
	}
}



void move_logic (void) {
    
    //Mise à jour de la position 
    //des tranches du paddle et de la balle
    tranche_gauche_balle = (ball_x / 2) - 3; 
	tranche_droite_balle = (ball_x / 2) + 3;
	tranche_gauche_paddle = (paddle_x / 2) - 8;
	tranche_droite_paddle = (paddle_x / 2) + 8 ; 

    //Mouvement du paddle
    //Ne dépasse pas les bords
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
    

    
    //Check la collision avec le bord du haut
	if (ball_y <= 0x01) {
		vector_ball_y=1; 
	}
    
    
    //Check la collision avec les côtés
    if (tranche_gauche_balle <= 0x00){
        vector_ball_x=2;// Haut
    }
    if (tranche_droite_balle >= 0x78){
        vector_ball_x=1;// Bas
    }

    //Check la collision avec le centre du paddle
	if (tranche_gauche_balle >= tranche_gauche_paddle+2 && tranche_droite_balle <= tranche_droite_paddle-2 && paddle_y-4 == ball_y) {
		vector_ball_y = 2;// Haut
        vector_ball_x = 0;//Position initiale -> rectiligne
        
	}
    
    //Check la collision avec la gauche du paddle
    if (tranche_gauche_balle >= tranche_gauche_paddle && tranche_gauche_balle <= tranche_gauche_paddle+2 && paddle_y-4 == ball_y) {
		vector_ball_y = 2;// Haut
        vector_ball_x = 1;//Gauche
	}
    
    //Check la collision avec la droite du paddle
    if (tranche_droite_balle >= tranche_droite_paddle-2 && tranche_droite_balle <= tranche_droite_paddle && paddle_y-4 == ball_y) {
		vector_ball_y = 2;// Haut
        vector_ball_x = 2;//Droite
	}
    
    if(ball_y > paddle_y){
        game_status=0;
    }

    
    
    //Fait monter/descendre la balle
    //en fonction de la valeur de vector_ball_y
	if (vector_ball_y == 1 ) {
		++ball_y; // la balle monte
	}    
	if (vector_ball_y == 2 ) {
		--ball_y; // la balle descend
	}
    
    //Bouge la balle à gauche et à droite
    //en fonction de la valeur de vector_ball_x
	if (vector_ball_x == 1 ) {
		--ball_x; //la balle va à gauche
	}
    
    
	if (vector_ball_x == 2 ) {
		++ball_x; //la balle va à droite
	}


}


