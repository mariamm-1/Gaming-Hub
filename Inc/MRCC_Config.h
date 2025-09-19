#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_

/*Choose between:
 * 1-HSI_CLOCK
 * 2-HSE_CLOCK
 * 3-PLL
 */


#define SYSTEM_CLOCK   HSI_CLOCK

/*Choose between:
 * 1-MECHANICAL_CLOCK
 * 2-RC_CLOCK
 */

#define HSE_OSC       RC_CLOCK

#endif
