// luTab.h = lookup table for rise/fall wave shape

// created: April 13/13 - G. D. (Joe) Young <jyoung@islandnet.com>

// this table is exponential waveshape expTab. For other waveshapes, 
// replace this table's values, but call the table luTab

#ifndef LUTAB_H
#define LUTAB_H

const unsigned char luTab[ ] = {
	255,	251,	247,	243,	239,	235,	232,	228,
	224,	221,	217,	214,	211,	207,	204,	201,
	198,	195,	192,	189,	186,	183,	180,	177,
	175,	172,	169,	166,	164,	161,	159,	156,
	154,	151,	149,	147,	144,	142,	140,	138,
	136,	134,	131,	129,	127,	125,	123,	121,
	120,	118,	116,	114,	112,	111,	109,	107,
	105,	104,	102,	101,	99,		97,		96,		94,
	93,		91,		90,		89,		87,		86,		85,		83,
	82,		81,		79,		78,		77,		76,		75,		73,
	72,		71,		70,		69,		68,		67,		66,		65,
	64,		63,		62,		61,		60,		59,		58,		57,
	56,		55,		54,		53,		53,		52,		51,		50,
	49,		49,		48,		47,		46,		46,		45,		44,
	44,		43,		42,		41,		41,		40,		40,		39,
	38,		38,		37,		37,		36,		35,		35,		34,
	34,		33,		33,		32,		32,		31,		31,		30,
	30,		29,		29,		28,		28,		27,		27,		27,
	26,		26,		25,		25,		25,		24,		24,		23,
	23,		23,		22,		22,		22,		21,		21,		21,
	20,		20,		20,		19,		19,		19,		18,		18,
	18,		17,		17,		17,		17,		16,		16,		16,
	16,		15,		15,		15,		15,		14,		14,		14,
	14,		14,		13,		13,		13,		13,		12,		12,
	12,		12,		12,		11,		11,		11,		11,		11,
	11,		10,		10,		10,		10,		10,		10,		9,
	9,		9,		9,		9,		9,		9,		8,		8,
	8,		8,		8,		8,		8,		7,		7,		7,
	7,		7,		7,		7,		7,		7,		6,		6,
	6,		6,		6,		6,		6,		6,		6,		6,
	5,		5,		5,		5,		5,		5,		5,		5,
	5,		5,		5,		4,		4,		4,		4,		4  };

#endif

