
#include "keyHandler.h"



const char* BTN[] = {"Up", "Down", "A", "B", "Left", "Right", "S", "E"};
//													    	Select & Start

const int BTN_CORRESPONDANCE_2B[] = {
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
	btn_Select,// 13; 31; GT
	btn_Start, // 14; 32; CC
	btn_Start  // 15; 33; CG
};

const int BTN_CORRESPONDANCE_3B[] = {
  btn_Up,     // 00; 000; AAA
  btn_Up,     // 01; 001; AAT
  btn_Up,     // 02; 002; AAC
  btn_Up,     // 03; 003; AAG
  btn_Up,     // 04; 010; ATA
  btn_Up,     // 05; 011; ATT
  btn_Up,     // 06; 012; ATC
  btn_Up,     // 07; 013; ATG
  btn_Up,     // 08; 020; ACA
  btn_Up,     // 09; 021; ACT
  btn_Down,   // 10; 022; ACC
  btn_Down,   // 11; 023; ACG
  btn_Down,   // 12; 030; AGA
  btn_Down,   // 13; 031; AGT
  btn_Down,   // 14; 032; AGC
  btn_Down,   // 15; 033; AGG
  
  btn_Down,   // 16; 100; TAA
  btn_Down,   // 17; 101; TAT
  btn_Left,     // 18; 102; TAC
  btn_Left,     // 19; 103; TAG
  btn_Left,     // 20; 110; TTA
  btn_Left,     // 21; 111; TTT
  btn_Left,     // 22; 112; TTC
  btn_Left,     // 23; 113; TTG
  btn_Right,     // 24; 120; TCA
  btn_Right,     // 25; 121; TCT
  btn_Right,     // 26; 122; TCC
  btn_Right,     // 27; 123; TCG
  btn_Right,     // 28; 130; TGA
  btn_Right,     // 29; 131; TGT
  btn_Right,     // 30; 132; TGC
  btn_Right,     // 31; 133; TGG
  
  btn_A,     // 32; 200; CAA
  btn_A,     // 33; 201; CAT
  btn_A,     // 34; 202; CAC
  btn_A,     // 35; 203; CAG
  btn_A,     // 36; 210; CTA
  btn_A,     // 37; 211; CTT
  btn_A,     // 38; 212; CTC
  btn_A,     // 39; 213; CTG
  btn_A,     // 40; 220; CCA
  btn_A,     // 41; 221; CCT
  btn_A,     // 42; 222; CCC
  btn_A,     // 43; 223; CCG
  btn_A,     // 44; 230; CGA
  btn_A,     // 45; 231; CGT
  btn_A,     // 46; 232; CGC
  btn_A,     // 47; 233; CGG
  
  btn_A,     // 48; 300; GAA
  btn_A,     // 49; 301; GAT
  btn_A,     // 50; 302; GAC
  btn_A,     // 51; 303; GAG
  btn_B,     // 52; 310; GTA
  btn_B,     // 53; 311; GTT
  btn_B,     // 54; 312; GTC
  btn_B,     // 55; 313; GTG
  btn_B,     // 56; 320; GCA
  btn_B,     // 57; 321; GCT
  btn_B,     // 58; 322; GCC
  btn_B,     // 59; 323; GCG
  btn_Start,     // 60; 330; GGA
  btn_Start,     // 61; 331; GGT
  btn_Start,     // 62; 332; GGC
  btn_Start      // 63; 333; GGG
};

int get_next_btn_2B(DNAWrapper* wrapper){

	int base1 = nextBase(wrapper);
	int base2 = nextBase(wrapper);

	if (base1 == -1 || base2 == -1) return -1 ; // no more duplet
	
	int index_in_BTN_CORRESPONDANCE = (base1 << 2) + base2; 

	return BTN_CORRESPONDANCE_2B[index_in_BTN_CORRESPONDANCE];
}

int get_next_btn_3B(DNAWrapper* wrapper){

	int base1 = nextBase(wrapper);
	int base2 = nextBase(wrapper);
        int base3 = nextBase(wrapper);

	if (base1 == -1 || base2 == -1 || base3 == -1) return -1 ; // no more duplet
	
	int index_in_BTN_CORRESPONDANCE = (base1 << 4) + (base2 << 2) + base3; 

	return BTN_CORRESPONDANCE_3B[index_in_BTN_CORRESPONDANCE];
}

