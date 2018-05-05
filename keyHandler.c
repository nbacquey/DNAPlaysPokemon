
#include "keyHandler.h"



const char* BTN[] = {"Up", "Down", "A", "B", "Left", "Right", "S", "E"};
//													    	Select & Start

const int BTN_CORRESPONDANCE[] = {
			   // idx en base 10 ; correspondance en base 4 ; correspondance en base d'ADN
	btn_Up,    // 00; 00; AA
	btn_Up,    // 01; 01; AT
	btn_Down,  // 02; 02; AC
	btn_Down,  // 03; 03; AG
	btn_A,     // 04; 10; TA
	btn_A,     // 05; 11; TT
	btn_B,     // 06; 12; TC
	btn_B,     // 07; 13; TG
	btn_Left,  // 08; 20; CA
	btn_Left,  // 09; 21; CT
	btn_Right, // 10; 22; CC
	btn_Right, // 11; 23; CG
	btn_Select,// 12; 30; GA
	btn_Select,// 14; 31; GT
	btn_Start, // 15; 32; CC
	btn_Start  // 15; 33; CG
};

int get_next_btn(DNAWrapper* wrapper){

	int base1 = nextBase(wrapper);
	int base2 = nextBase(wrapper);

	if (base1 == -1 || base2 == -1) return -1 ; // no more duplet
	
	int index_in_BTN_CORRESPONDANCE = base1 * 4 + base2; 

	return BTN_CORRESPONDANCE[index_in_BTN_CORRESPONDANCE];
}

