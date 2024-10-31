

#include <sys_init.h>
#include <cm4.h>
#include <kmain.h>
#include <stdint.h>
#include <sys_usart.h>
#include <kstdio.h>
#include <sys_rtc.h>
#include <kstring.h>
//include -> common-defines.h 
#include<stdint.h>
#include<stdbool.h>

//#include<libopencm3/stm32/memorymap.h>

#ifndef DEBUG
#define DEBUG 1
#endif

//bootloader.c file 

//flase base = FLASH(RX): ORIGIN = 0x08000000, LENGTH = 32K

#define BOATLOADER_SIZE (0x10000U) //64kB
//#define Main_APP_START_ADDRESS (0X08008000)
// Bootloader   0800_0000
#define Main_APP_START_ADDRESS (0X08010000U) //duos 

#define VERSION_ADDR ((volatile uint32_t *)0x2000FFFC)


//const uint32_t data[0x8000]={0};

static void jump_to_main(void){

        typedef void(*void_fn)(void);
        //second entry -> reset vector 
        uint32_t *reset_vector_entry = (uint32_t *)(Main_APP_START_ADDRESS + 4U);
        uint32_t *reset_vector= (uint32_t *)(*reset_vector_entry);

        void_fn jump_fn= (void_fn)reset_vector;

        jump_fn();

}

void kmain(void)
{
  //  __sys_init();
   *VERSION_ADDR = 150; // Example version
   
  jump_to_main();
    
}


// Bootloader   Main frame 
// Bootloader   64 kiB  64-34=30KiB  30KiB padding 