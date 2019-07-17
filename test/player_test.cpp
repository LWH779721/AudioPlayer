#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern "C"{
#include "Interface.h"
}

void *mPlayer = NULL;
	
static void playerMsgCallback(int msg, int id, int ext1, int ext2)
{
    printf("callback msg:[%d] id:[%d] ext1:[%d] ext2:[%d]\n", msg, id, ext1, ext2);
    switch (msg)
    {
        case MEDIA_PLAYBACK_COMPLETE:
			//player_deinit(mPlayer);	
            break;
        case MEDIA_ERROR:
            break;
        case MEDIA_PREPARED:
			off64_t us;
			getDuration(mPlayer, &us);
			printf("%llu\n", us / 1000);
			start(mPlayer);
            break;
        case MEDIA_SETSRC_DONE:
            break;
        default:
            break;
    }
}

int main(int argc, char **args)
{
	AudioFormat outputFormat = {0};
	int i4Ret, i = 0;
	
    mPlayer = player_init();
    if (!mPlayer) {
        printf("player init failed!\n");
        return -1;
    }

    outputFormat.mChannelLayout = AV_CH_LAYOUT_STEREO;
    outputFormat.mSampleFmt = AV_SAMPLE_FMT_S16;
    outputFormat.mSampleRate = 44100;
    outputFormat.mChannels = 2;
	
    memcpy(outputFormat.mDeviceName, args[1], strlen(args[1]));
    setPlaybackSettings(mPlayer, &outputFormat);

    registerCallback(mPlayer, playerMsgCallback);
	
	char cmd;
	while (1)
	{	
		cmd = fgetc(stdin);
		if (cmd == 'c')
		{
			break;
		}
		else if (cmd == 'r')
		{
			if (i > 0)
			{
				printf("reset!\n");
				reset(mPlayer);
			}
			
			i4Ret = setDataSource_url(mPlayer, args[2], i++);

			i4Ret = prepareAsync(mPlayer);	
		}
		else if (cmd == 'p')
		{
			i4Ret = pause_l(mPlayer);		
		}
		
		sleep(1);
	}
	
deinit:
	player_deinit(mPlayer);	
	return 0;
}