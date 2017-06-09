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
    game_status = 1;
	vector_ball_y = 1; //Fait monter la balle
	Load_Palette();
	Reset_Scroll();
	All_On(); 		// Activation de l'écran

    while((joypad1 & A_BUTTON) == 0 && game_status == 1 ){Get_Input();}
    while(1){
        if (game_status == 0){
            while((joypad1 & A_BUTTON) == 0){Get_Input();}
            reset();
            game_status = 1;
        }
        
        if (game_status == 1){
            if((joypad1 & START) != 0){
                while((joypad1 & A_BUTTON) == 0){Get_Input();}
            }
            Get_Input();
            move_logic();
            check_collision();
		    update_Sprites();
            NMI_flag = 0;
        }
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
	state = paddle << 2;
	index4 = 0;
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + paddle_y;
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state];
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index];
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + paddle_x;
		++index4;
	}
	state = ball << 2;
	for (index = 0; index < 4; ++index ){
		SPRITES[index4] = MetaSprite_Y[index] + ball_y;
		++index4;
		SPRITES[index4] = MetaSprite_Tile[index + state];
		++index4;
		SPRITES[index4] = MetaSprite_Attrib[index];
		++index4;
		SPRITES[index4] = MetaSprite_X[index] + ball_x;
		++index4;
	}

    for (sprite_number = 0; sprite_number < 12; sprite_number++){
        state = sprite_brick << 2;
        for (index = 0; index < 4; ++index ){
            SPRITES[index4] = MetaSprite_Y[index] + sprite_y[sprite_number];
            ++index4;
            SPRITES[index4] = MetaSprite_Tile[index + state];
            ++index4;
            SPRITES[index4] = MetaSprite_Attrib[index];
            ++index4;
            SPRITES[index4] = MetaSprite_X[index] + sprite_x[sprite_number];
            ++index4;
        }
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
			paddle_x=paddle_x+1;
	}}
	if (paddle_x >= 0x02 ){
		if ((joypad1 & LEFT) != 0){
			state = paddle;
			paddle_x=paddle_x-1;
	}}
    
    //Fait monter/descendre la balle
    //en fonction de la valeur de vector_ball_y
	if (vector_ball_y == 1 ) {
		++ball_y; // la balle descend
	}    
	if (vector_ball_y == 2 ) {
		--ball_y; // la balle monte
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

void check_collision(void){
    //Check la collision avec le bord du haut
	if (ball_y <= 0x01) {
		vector_ball_y=1; 
	}
    
    
    //Check la collision avec les côtés
    if (tranche_gauche_balle <= 0x00){
        vector_ball_x=2;// Droite
    }
    if (tranche_droite_balle >= 0x78){
        vector_ball_x=1;// Gauche
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
    
    //Check la collision avec les blocs
    if(ball_y < 0x36){
        for(i = 0; i < 13; i++){
            if(tranche_gauche_balle >= (sprite_x[i] / 2)-8 && tranche_droite_balle <= (sprite_x[i]/2)+8 && (ball_y == sprite_y[i]+8 || ball_y == sprite_y[i]-8) ){
                sprite_x[i] = 0;
                sprite_y[i] = 0xc8;
                if (vector_ball_y == 2){
                vector_ball_y = 1;
                    }
                else{
                    vector_ball_y = 2;
                }
                count+=sprite_x[i];
                if(i == 1 && count == 0){game_status = 0;}
               }
        }
    }
}

void reset(void){
    paddle_x = 0x7f;
	paddle_y = 0xc8;
	ball_x = 0x7f;		
	ball_y = 0x7f;
    vector_ball_x = 0;
    vector_ball_y = 1;
    for (i=0; i <13; i++){
        sprite_x[i]=sprite_x_temp[i];
        sprite_y[i]=sprite_y_temp[i];
    }
}