#include <string>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;


class Video;
class MP4Video;
class MOVVideo;
class MKVVideo;
class M4VVideo;
class AVIVideo;

class MediaPlayer {

public:
	virtual void PlayMP4Video(MP4Video*);
	virtual void PlayMOVVideo(MOVVideo*);
	virtual void PlayMKVVideo(MKVVideo*);
	virtual void PlayM4VVideo(M4VVideo*);
	virtual void PlayAVIVideo(AVIVideo*);
};

class ApplicationManager {

public:

	virtual void runVideo(string videoName);

	virtual void addVideo(Video* video);

	virtual void removeVideo(Video* video);

	virtual void setMediaPlayer(MediaPlayer* mediaPlayer);

private:
	list<Video*> videos;
	MediaPlayer* mediaPlayer;
};



class Video {

public:
	string name;
	string type;
	int secondsDuration;

	Video(string name, int secondsDuration) {
		this->name = name;
		this->secondsDuration = secondsDuration;
		this->type = "Not defined";
	}

	virtual void Play(MediaPlayer&) = 0;
};

class MP4Video : public Video {

public:
	
	int resolution;

	MP4Video(string name, int secondsDuration) : Video(name, secondsDuration) {
		type = "MP4";
		resolution = 1080;
	}

	void Play(MediaPlayer& mediaPlayer) {
		mediaPlayer.PlayMP4Video(this);
	}
};

class MOVVideo : public Video {

public:

	int dataFrameCount;

	MOVVideo(string name, int secondsDuration) : Video(name, secondsDuration) {
		type = "MOV";
		dataFrameCount = 100;
	}

	void Play(MediaPlayer& mediaPlayer) {
		mediaPlayer.PlayMOVVideo(this);
	}
};

class MKVVideo : public Video {

public:

	string mkvDecodingAlgorithm;

	MKVVideo(string name, int secondsDuration) : Video(name, secondsDuration) {
		type = "MKV";
		mkvDecodingAlgorithm = "Dynamic Decoding";
	}

	void Play(MediaPlayer& mediaPlayer) {
		mediaPlayer.PlayMKVVideo(this);
	}
};

class M4VVideo : public Video {

public:

	int m4vFrameCount;

	M4VVideo(string name, int secondsDuration) : Video(name, secondsDuration) {
		type = "M4V";
		m4vFrameCount = 32;
	}

	void Play(MediaPlayer& mediaPlayer) {
		mediaPlayer.PlayM4VVideo(this);
	}
};

class AVIVideo : public Video {

public:

	string aviVersion;

	AVIVideo(string name, int secondsDuration) : Video(name, secondsDuration) {
		type = "AVI";
		aviVersion = "3.0";
	}

	void Play(MediaPlayer& mediaPlayer) {
		mediaPlayer.PlayAVIVideo(this);
	}
};



void MediaPlayer::PlayMP4Video(MP4Video* mp4Video) {
	cout << "Video with type: " + mp4Video->type + " and name: " + mp4Video->name + " is playing now with resolution: " + to_string(mp4Video->resolution) + "\n";
	cout << "The length of this video is: " + to_string(mp4Video->secondsDuration) + " seconds";
	cout << "***********************************************\n";
}

void MediaPlayer::PlayMOVVideo(MOVVideo* movVideo) {
	cout << "Video with type: " + movVideo->type + " and name: " + movVideo->name + " is playing now with data frame count: " + to_string(movVideo->dataFrameCount) + "\n";
	cout << "The length of this video is: " + to_string(movVideo->secondsDuration) + " seconds";
	cout << "***********************************************\n";
}

void MediaPlayer::PlayMKVVideo(MKVVideo* mkvVideo) {
	cout << "Video with type: " + mkvVideo->type + " and name: " + mkvVideo->name + " is playing now with resolution: " + mkvVideo->mkvDecodingAlgorithm + "\n";
	cout << "The length of this video is: " + to_string(mkvVideo->secondsDuration) + " seconds";
	cout << "***********************************************\n";
}

void MediaPlayer::PlayM4VVideo(M4VVideo* m4vVideo) {
	cout << "Video with type: " + m4vVideo->type + " and name: " + m4vVideo->name + " is playing now with M4V frame count: " + to_string(m4vVideo->m4vFrameCount) + "\n";
	cout << "The length of this video is: " + to_string(m4vVideo->secondsDuration) + " seconds";
	cout << "***********************************************\n";
}

void MediaPlayer::PlayAVIVideo(AVIVideo* aviVideo) {
	cout << "Video with type: " + aviVideo->type + " and name: " + aviVideo->name + " is playing now with AVI version: " + aviVideo->aviVersion + "\n";
	cout << "The length of this video is: " + to_string(aviVideo->secondsDuration) + " seconds";
	cout << "***********************************************\n";
}

class VideoPlayer : public MediaPlayer {
	// this class can override play methods, but in this case it use default versions.
};

class anotherVideoPlayer : public MediaPlayer {
	// this video player uses different algorithms for display MOV and M4V videos.

	void PlayMOVVideo(MOVVideo* movVideo) {
		cout << "This video player uses different algorithm for display MOV videos \n";
		cout << "MOV videos are smoother in this video player \n";
		cout << "***********************************************\n";
	}

	void PlayM4VVideo(M4VVideo* m4vVideo) {
		cout << "This video player uses different algorithm for display M4V videos \n";
		cout << "M4V videos are smoother in this video player \n";
		cout << "***********************************************\n";
	}
};

void ApplicationManager::runVideo(string videoName) {
	list<Video*>::iterator it;
	for (it = videos.begin(); it != videos.end(); ++it)
		if ((*it)->name == videoName)
			(*it)->Play(*mediaPlayer);

}

void ApplicationManager::addVideo(Video* video) {

	videos.push_back(video);
}

void ApplicationManager::removeVideo(Video* video) {

	videos.remove(video);
}


void ApplicationManager::setMediaPlayer(MediaPlayer* mediaPlayer) {

	this->mediaPlayer = mediaPlayer;
}



int main() {

	ApplicationManager* applicationManager = new ApplicationManager();

	MediaPlayer* videoPlayer = new VideoPlayer();

	Video* mp4Video = new MP4Video("Matrix.mp4", 12432);
	Video* movVideo = new MOVVideo("Godfather.mov", 15000);
	Video* mkvVideo = new MKVVideo("Sample.mkv", 11560);
	Video* m4vVideo = new M4VVideo("Iron_Man.m4v", 12428);
	Video* aviVideo = new AVIVideo("Avengers.avi", 18000);

	applicationManager->setMediaPlayer(videoPlayer);
	applicationManager->addVideo(mp4Video);
	applicationManager->addVideo(movVideo);
	applicationManager->addVideo(mkvVideo);
	applicationManager->addVideo(m4vVideo);
	applicationManager->addVideo(aviVideo);

	applicationManager->runVideo("Matrix.mp4");
	applicationManager->runVideo("Godfather.mov");
	applicationManager->runVideo("Sample.mkv");
	applicationManager->runVideo("Iron_Man.m4v");
	applicationManager->runVideo("Avengers.avi");

}

