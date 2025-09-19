

#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_

#define GPIOA_BASE_ADRESS (0x40020000)
#define GPIOB_BASE_ADRESS (0x40020400)
#define GPIOC_BASE_ADRESS (0x40020800)

typedef struct
{
u32 MODER;
u32 OTYPER;
u32 OSPEEDER;
u32 PUPDR;
u32 IDR;
u32 ODR;
u32 BSRR;
u32 LCKR;
u32 AFRL;
u32 AFRH;
}GPIO_t;


#define GPIOA  ((volatile GPIO_t*)GPIOA_BASE_ADRESS)
#define GPIOB  ((volatile GPIO_t*)GPIOB_BASE_ADRESS)
#define GPIOC  ((volatile GPIO_t*)GPIOC_BASE_ADRESS)

#define GPIO_MUSK 3
#define ALT_FUNC_MUSK 15


#endif /* MGPIO_PRIVATE_H_ */
