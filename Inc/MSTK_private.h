
#ifndef MSTK_PRIVATE_H_
#define MSTK_PRIVATE_H_

#define MSTK_BASE_ADRESS (0xE000E010)

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}MSTK_t;

#define STK ((volatile MSTK_t*)MSTK_BASE_ADRESS)


#define Countflag   16
#define ClockSource 2
#define TICKINT     1
#define STK_Enable      0

#define STK_AHB   0
#define STK_AHB_8 1


#endif /* MSTK_PRIVATE_H_ */
