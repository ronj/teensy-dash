#include "Bitmaps.h"

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#else
#define PROGMEM
#endif

namespace PeripheralLayer
{
	namespace Bitmaps
	{
		namespace internal
		{
			const uint8_t WaterTemperatureData[] =
			{
				0x00, 0x00, 0x40, 0x00, 0x00, //                  #                 
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xFF, 0xE0, 0x00, //                 ###########        
				0x00, 0x00, 0xFF, 0xE0, 0x00, //                 ###########        
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xFF, 0xE0, 0x00, //                 ###########        
				0x00, 0x00, 0xFF, 0xE0, 0x00, //                 ###########        
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xFF, 0xE0, 0x00, //                 ###########        
				0x00, 0x00, 0xFF, 0xE0, 0x00, //                 ###########        
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x01, 0xF0, 0x00, 0x00, //                #####               
				0xFF, 0x03, 0xF8, 0x1F, 0xE0, // ########      #######      ########
				0xFF, 0xE3, 0xF8, 0xFF, 0xE0, // ###########   #######   ###########
				0xC3, 0xE3, 0xF8, 0xF8, 0x60, // ##    #####   #######   #####    ##
				0x00, 0x01, 0xF0, 0x00, 0x00, //                #####               
				0x00, 0x00, 0xE0, 0x00, 0x00, //                 ###                
				0x00, 0x00, 0x00, 0x00, 0x00, //                                    
				0x00, 0x00, 0x00, 0x00, 0x00, //                                    
				0x3E, 0x3F, 0x1F, 0x8F, 0x80, //   #####   ######   ######   #####  
				0x3F, 0xFF, 0xFF, 0xFF, 0x80, //   ###############################  
				0x03, 0xE1, 0xF0, 0xF8, 0x00, //       #####    #####    #####      
			};

			const uint8_t TripDistanceData[] PROGMEM =
			{
				0x00, 0x00, 0x00, 0xF0, //                         ####  
				0x00, 0x00, 0x01, 0x08, //                        #    # 
				0x00, 0x00, 0x02, 0xF4, //                       # #### #
				0x03, 0x80, 0x02, 0x94, //       ###             # #  # #
				0x1F, 0xE0, 0x02, 0x94, //    ########           # #  # #
				0x38, 0x38, 0x02, 0xF4, //   ###     ###         # #### #
				0x77, 0xDC, 0x03, 0x0C, //  ### ##### ###        ##    ##
				0x6F, 0xEC, 0x01, 0x98, //  ## ####### ##         ##  ## 
				0xEC, 0x6C, 0x01, 0x98, // ### ##   ## ##         ##  ## 
				0xD8, 0x26, 0x00, 0xF0, // ## ##     #  ##         ####  
				0xD8, 0x26, 0x00, 0x60, // ## ##     #  ##          ##   
				0xCC, 0x66, 0x01, 0xE0, // ##  ##   ##  ##        ####   
				0xCF, 0xEC, 0x0F, 0x00, // ##  ####### ##      ####      
				0x67, 0xCC, 0x78, 0x00, //  ##  #####  ##   ####         
				0x60, 0x1C, 0xE0, 0x00, //  ##        ###  ###           
				0x30, 0x18, 0xF0, 0x00, //   ##       ##   ####          
				0x30, 0x38, 0x3C, 0x00, //   ##      ###     ####        
				0x18, 0x30, 0x18, 0x00, //    ##     ##       ##         
				0x1C, 0x70, 0x70, 0x00, //    ###   ###     ###          
				0x0C, 0xE3, 0xC0, 0x00, //     ##  ###   ####            
				0x06, 0xCF, 0x00, 0x00, //      ## ##  ####              
				0x07, 0xF8, 0x00, 0x00, //      ########                 
				0x03, 0xE0, 0x00, 0x00, //       #####                   
				0x01, 0x00, 0x00, 0x00, //        #           
			};

			const uint8_t BatteryData[] PROGMEM =
			{
				0x03, 0xE0, 0x00, 0xF8, 0x00, //       #####             #####      
				0x03, 0xE0, 0x00, 0xF8, 0x00, //       #####             #####      
				0x03, 0xE0, 0x00, 0xF8, 0x00, //       #####             #####      
				0xFF, 0xFF, 0xFF, 0xFF, 0xE0, // ###################################
				0xFF, 0xFF, 0xFF, 0xFF, 0xE0, // ###################################
				0xFF, 0xFF, 0xFF, 0xFF, 0xE0, // ###################################
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xE0, 0x00, 0x00, 0x30, 0xE0, // ###                       ##    ###
				0xE0, 0x00, 0x00, 0x30, 0xE0, // ###                       ##    ###
				0xE7, 0xE0, 0x00, 0xFC, 0xE0, // ###  ######             ######  ###
				0xE7, 0xE0, 0x00, 0xFC, 0xE0, // ###  ######             ######  ###
				0xE0, 0x00, 0x00, 0x30, 0xE0, // ###                       ##    ###
				0xE0, 0x00, 0x00, 0x30, 0xE0, // ###                       ##    ###
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xE0, 0x00, 0x00, 0x00, 0xE0, // ###                             ###
				0xFF, 0xFF, 0xFF, 0xFF, 0xE0, // ###################################
				0xFF, 0xFF, 0xFF, 0xFF, 0xE0, // ###################################
				0xFF, 0xFF, 0xFF, 0xFF, 0xE0, // ###################################
			};

			const uint8_t FuelPumpData[] PROGMEM =
			{
				0x3F, 0xFE, 0x00, 0x00, //   #############           
				0x7F, 0xFF, 0x00, 0x00, //  ###############          
				0x7F, 0xFF, 0x18, 0x00, //  ###############   ##     
				0x60, 0x03, 0x0C, 0x00, //  ##           ##    ##    
				0x60, 0x03, 0x06, 0x00, //  ##           ##     ##   
				0x60, 0x03, 0x06, 0x00, //  ##           ##     ##   
				0x60, 0x03, 0x07, 0x00, //  ##           ##     ###  
				0x60, 0x03, 0x03, 0x00, //  ##           ##      ##  
				0x60, 0x03, 0x02, 0x00, //  ##           ##      #   
				0x60, 0x03, 0xC2, 0x00, //  ##           ####    #   
				0x7F, 0xFF, 0x62, 0x00, //  ############### ##   #   
				0x7F, 0xFF, 0x23, 0x00, //  ###############  #   ##  
				0x7F, 0xFF, 0x21, 0x00, //  ###############  #    #  
				0x7F, 0xFF, 0x21, 0x00, //  ###############  #    #  
				0x7F, 0xFF, 0x21, 0x80, //  ###############  #    ## 
				0x7F, 0xFF, 0x20, 0x80, //  ###############  #     # 
				0x7F, 0xFF, 0x20, 0x80, //  ###############  #     # 
				0x7F, 0xFF, 0x20, 0xC0, //  ###############  #     ##
				0x7F, 0xFF, 0x20, 0x40, //  ###############  #      #
				0x7F, 0xFF, 0x20, 0x40, //  ###############  #      #
				0x7F, 0xFF, 0x20, 0x40, //  ###############  #      #
				0x7F, 0xFF, 0x20, 0x40, //  ###############  #      #
				0x7F, 0xFF, 0x10, 0x40, //  ###############   #     #
				0x7F, 0xFF, 0x1F, 0x80, //  ###############   ###### 
				0x7F, 0xFF, 0x07, 0x00, //  ###############     ###  
				0xFF, 0xFF, 0x80, 0x00, // #################         
			};

			const uint8_t OilCanData[] PROGMEM =
			{
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x18, 0xFC, 0x00, 0x00, 0x38, 0xFC, 0x00, 0x00, 0x70, 0x30, 0x00, 0x00,
				0xFF, 0xFF, 0xE0, 0x18, 0xDF, 0xFF, 0xF0, 0x3C, 0x18, 0x00, 0x38, 0x76, 0x18, 0x00, 0x1F, 0xE2,
				0x18, 0x00, 0x0E, 0x60, 0x18, 0x00, 0x04, 0xE2, 0x18, 0x00, 0x01, 0xC5, 0x18, 0x00, 0x03, 0x85,
				0x18, 0x00, 0x07, 0x02, 0x1F, 0xFF, 0xFE, 0x00, 0x1F, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};
		}
	}
}
