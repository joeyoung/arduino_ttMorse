// cosTab.h = lookup table for rise/fall wave shape

// created: April 16/13 - G. D. (Joe) Young <jyoung@islandnet.com>

// this table is cosine waveshape cosTab. For other waveshapes, 
// replace this table's values, but call the table luTab

#ifndef LUTAB_H
#define LUTAB_H

const unsigned char luTab[ ] = {
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	1,	1,	1,	1,	2,
	2,	2,	3,	3,	3,	4,	4,	5,
	5,	5,	6,	6,	7,	8,	8,	9,
	9,	10,	10,	11,	12,	12,	13,	14,
	15,	15,	16,	17,	18,	19,	19,	20,
	21,	22,	23,	24,	25,	26,	27,	28,
	29,	30,	31,	32,	33,	34,	35,	36,
	37,	38,	39,	40,	42,	43,	44,	45,
	46,	48,	49,	50,	51,	53,	54,	55,
	56,	58,	59,	60,	62,	63,	64,	66,
	67,	69,	70,	71,	73,	74,	76,	77,
	79,	80,	81,	83,	84,	86,	87,	89,
	90,	92,	93,	95,	96,	98,	99,	101,
	103,	104,	106,	107,	109,	110,	112,	113,
	115,	117,	118,	120,	121,	123,	124,	126,
	128,	129,	131,	132,	134,	135,	137,	138,
	140,	142,	143,	145,	146,	148,	149,	151,
	152,	154,	156,	157,	159,	160,	162,	163,
	165,	166,	168,	169,	171,	172,	174,	175,
	176,	178,	179,	181,	182,	184,	185,	186,
	188,	189,	191,	192,	193,	195,	196,	197,
	199,	200,	201,	202,	204,	205,	206,	207,
	209,	210,	211,	212,	213,	215,	216,	217,
	218,	219,	220,	221,	222,	223,	224,	225,
	226,	227,	228,	229,	230,	231,	232,	233,
	234,	235,	236,	236,	237,	238,	239,	240,
	240,	241,	242,	243,	243,	244,	245,	245,
	246,	246,	247,	247,	248,	249,	249,	250,
	250,	250,	251,	251,	252,	252,	252,	253,
	253,	253,	254,	254,	254,	254,	255,	255,
	255,	255,	255,	255,	255,	255,	255,	255  }
;

#endif

	