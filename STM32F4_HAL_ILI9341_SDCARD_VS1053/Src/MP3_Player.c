#include "MP3_Player.h"
#include "fatfs.h"

#define BYTES_2_WRITE 	32
#define BUFFER_SIZE 	512

uint8_t mp3Buffer[BUFFER_SIZE];

uint32_t fileSize, readBytes;
uint16_t cnt = 0;

FATFS fs;
FIL fil;

/* Set Volume */
bool MP3_SetVolume(uint8_t volumeLeft, uint8_t volumeRight)
{
    uint16_t volume;
    volume = ( volumeLeft << 8 ) + volumeRight;

    if(!VS1053_CmdWrite(_VS1053_VOL_ADDR, volume)) return false;

    return true;
}

/* Initialize VS1053 & Open a file */
bool MP3_Init()
{
    VS1053_Init();
    VS1053_Reset();

    // MP3 configuration
    if(!VS1053_CmdWrite(_VS1053_MODE_ADDR, 0x0800)) return false;
    if(!VS1053_CmdWrite(_VS1053_BASS_ADDR, 0x7A00)) return false;
    if(!VS1053_CmdWrite(_VS1053_CLOCKF_ADDR, 0x2000)) return false;

    // MP3 set volume, maximum volume is 0x00 and total silence is 0xFE.
    if(!MP3_SetVolume( 0x2F, 0x2F )) return false;

    /* Mount SD Card */
    if(f_mount(&fs, "", 0) != FR_OK) return false;

    return true;
}

bool MP3_Play(const char *filename)
{
	/* Open file to read */
	if(f_open(&fil, filename, FA_READ) != FR_OK) return false;

	/* Get the file size */
	fileSize = f_size(&fil);

    while (fileSize > BUFFER_SIZE)
    {
    	/* Fill the buffer */
    	if(f_read(&fil, mp3Buffer, BUFFER_SIZE, (UINT*)&readBytes) != FR_OK) return false;

    	/* SPI Tx buffer */
        for (cnt = 0; cnt < BUFFER_SIZE / BYTES_2_WRITE; cnt++)
        {
            while(!VS1053_DataWrite32( mp3Buffer + cnt * BYTES_2_WRITE ));
        }

        /* Left bytes to send */
        fileSize -= BUFFER_SIZE;
    }

    /* If left bytes are smaller than buffer */
    if(f_read(&fil, mp3Buffer, fileSize, (UINT*)&readBytes) != FR_OK) return false;

    /* SPI Tx buffer */
    for (cnt = 0; cnt < fileSize; cnt++)
    {
        while(!VS1053_DataWrite(*(mp3Buffer + cnt)));
    }

    /* Delay 100ms */
    HAL_Delay(100);

    return true;
}
