#include "player.h"

using namespace std;

player::player(QObject *parent)
	: QThread(parent)
{
	stop = true;
	startFrameIndex = -1;
}

player::~player()
{
	mutex.lock();
	stop = true;
	condition.wakeOne();
	mutex.unlock();
	wait();
}

void player::loadVideo(string filename, int framerate, vector<cliplabel*> fileClips)
{
	fileName = filename;
	frameRate = framerate;
	clips = fileClips;
}

void player::playVideo(int index, bool singleClip)
{
	if (!isRunning()) {
		if (isStopped()){
			stop = false;
		}
		clipIndex = index;
		playClip = singleClip;
		start(LowPriority);
	}
}

void player::stopVideo()
{
	stop = true;
}

bool player::isStopped() const{
	return this->stop;
}

void player::run()
{
	if (playClip)
	{
		cliplabel* current_clip = clips[clipIndex];
		vector<int> cutRanges = current_clip->getCuts();
		if (cutRanges.empty())
		{
			int start;
			if (startFrameIndex == -1) start = current_clip->getRange().at(0);
			else start = startFrameIndex;
			int end = current_clip->getRange().at(1);

			if (current_clip->getCutType() == 2)
			{
				int delay = 500 / frameRate;//delay = 1000 / frame_rate;
				for (int j = start; !stop && j <= end; j++)
				{
					emit display(j);
					startFrameIndex = j;
					Sleep(delay);
				}
			}
			else
				emit display((start + end) / 2);
		}
		else
		{
			int start, end;
			int size = cutRanges.size();
			int delay = 500 / frameRate;

			for (int i = 0; !stop && i < size; i += 2)
			{
				start = cutRanges.at(i);
				end = cutRanges.at(i + 1);
				if (startFrameIndex > end) continue;
				else if (startFrameIndex >= start && startFrameIndex <= end)
					start = startFrameIndex;
				for (int j = start; !stop && j <= end; j++)
				{
					emit display(j);
					startFrameIndex = j;
					Sleep(delay);
				}
			}
		}
		if (!stop)
		{
			startFrameIndex = -1;
			stop = true;
		}
	}
}