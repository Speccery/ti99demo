*********************************************************************
* Filename: ROUTINES.INC
* Date:     05/04/2016
* Author:   orbitaldecay
*
* This file provides the addresses of routines in the control bank
* that are loaded at the start of the demo. These routines may be useful
* for various demo screen code.
*********************************************************************

*********************************************************************
* Draw Bitmap
* Switches to graphics mode II and draws a full screen bitmap.
* R1: Bank / file index containing pattern table
* R2: Bank / file index containing color table
*
* DO NOT CALL THIS UNLESS YOU'VE SET LWPI >8300!!
*
* Example:
*
*      LI   R1, 1
*      LI   R2, 2
*      BL   @BITMAP
*
*********************************************************************
BITMAP  EQU     >201A

*********************************************************************
* Load To CPU RAM
*
* If we're building a cartridge, this function switches to the bank
* specified in Register 1 (0=BANK0, 1=BANK1) and copies R2 bytes to
* the RAM at the address specified in Register 0. If we're loading
* from disk, it copies the entire file specified in Register 1
* (0=DEMOA, 1=DEMOB) to the RAM address in Register 0.
*
* 1. NOTICE THAT THIS TRASHES THE DATA IN THE VDP!!!
* 2. DO NOT CALL THIS UNLESS YOU'VE SET LWPI >8300
*
* Example:
*       LI  R0, 1       ; Bank 1
*       LI  R1, >A000   ; To RAM address >A000
*       LI  R2, >1800   ; Copy >1800 bytes
*       BL  @LDTOVDP
*
*********************************************************************
LDTORAM EQU     BITMAP+4

*********************************************************************
* Load To VDP RAM
*
* If we're building a cartridge, this function switches to the bank
* specified in Register 1 (0=BANK0, 1=BANK1) and copies R2 bytes to
* the VDP at the address specified in Register 0. If we're loading
* from disk, it copies the entire file specified in Register 1
* (0=DEMOA, 1=DEMOB) to the VDP address in Register 0.
*
* DO NOT CALL THIS UNLESS YOU'VE SET LWPI >8300!!
*
* Example:
*       LI  R0, 1       ; Bank 1
*       LI  R1, >2000   ; To VDP address >2000
*       LI  R2, >1800   ; Copy >1800 bytes
*       BL  @LDTOVDP
*
*********************************************************************
LDTOVDP EQU     LDTORAM+4

*********************************************************************
* Play Song
*
* Plays the currently loaded song in a loop. Will only play when the
* VDP interrupt has been triggered. On return @VDPINT will be -1 if
* an interrupt has occurred and 0 if an interrupt has not occurred.
* ATTEN is used to set the attenuation of the music player
* (in MSB, >0000 - >0F00)
*********************************************************************
PLAYSNG EQU     LDTOVDP+4
VDPINT  EQU     PLAYSNG+4
ATTEN   EQU     >20A0
