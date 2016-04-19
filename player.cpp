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

bool player::getPlayMode() const{
	return this->playClip;
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
				int delay = 1000 / frameRate;//delay = 1000 / frame_rate;
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
			int delay = 1000 / frameRate;

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
	}
	else
	{
		int start = -1;
		int end = -1;
		int delay = -1;
		int size = clips.size();
		cliplabel *item;

		for (int i = clipIndex; !stop && i < size; i++)
		{
			item = clips[i];
			isEdited orginMode = item->getEditedMode();
			if (item->getCutType() != -1 && orginMode != isDeleted && orginMode != isSelectedDeleted)
			{
				//item->setEditedMode(isViewed);
				//ui->scrollArea_1->horizontalScrollBar()->setSliderPosition(item->pos().x());
				//frame_slider->setValue(i);
				start = item->getRange().at(0);
				end = item->getRange().at(1);
				vector<int> cutRanges = item->getCuts();
				emit setCurrentClipIndex(i);

				if (!cutRanges.empty())
				{
					int size = cutRanges.size();
					delay = 1000 / frameRate;
					for (int j = 0; !stop && j < size; j += 2)
					{
						int cut_start = cutRanges.at(j);
						int cut_end = cutRanges.at(j + 1);
						for (int k = cut_start; !stop && k <= cut_end; k++)
						{
							emit display(k);
							Sleep(delay);
						}
					}
				}
				else if (item->getCutType() == 2)
				{
					delay = 1000 / frameRate;
					for (int j = start; !stop && j <= end; j++)
					{
						emit display(j);
						Sleep(delay);
					}
				}
				else
				{
					delay = 1000;
					emit display((start + end) / 2);
					Sleep(delay);
				}
				//item->setEditedMode(orginMode);
			}
		}
	}

	if (!stop)
	{
		startFrameIndex = -1;
		stop = true;
		if (playClip)	
			emit setPlayButtonIcon(true);
		else
			emit setPlayButtonIcon(false);
	}
}