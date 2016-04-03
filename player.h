#ifndef PLAYER_H
#define PLAYER_H

#define NOMINMAX

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include <windows.h>
#include "cliplabel.h"

class player : public QThread
{
	Q_OBJECT

public:
	player(QObject *parent = 0);
    ~player();
	void loadVideo(std::string filename, int framerate, std::vector<cliplabel*> fileClips);
	void playVideo(int index, bool singleClip = true);
	void stopVideo();
	bool isStopped() const;
	bool getPlayMode() const;

protected:
	void run();

signals:
	void display(int frameIndex);
	void setCurrentClipIndex(int clipIndex);

private:
	bool stop;
	QMutex mutex;
	QWaitCondition condition;
	int frameRate;
	int clipIndex;
	int startFrameIndex;
	bool playClip;
	std::string fileName;
	std::vector<cliplabel*> clips;

};

#endif // PLAYER_H
