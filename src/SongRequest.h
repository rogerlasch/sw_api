


#ifndef SONGREQUEST_H
#define SONGREQUEST_H

enum SONG_STATUS {
	SG_DEFAULT = 0,
	SG_QUEUE,
	SG_FILED
};

class SongRequest {
public:
	uint32 id;
	uint32 status;
	int64 timestamp;
	std::string musicName;
	std::string artist;
	std::string listener;
	std::string msg;
	SongRequest();
	SongRequest(uint32 id, uint32 status, int64 timestamp, const std::string& musicName, const std::string& artist, const std::string& listener, const std::string& msg);
	SongRequest(const SongRequest& sg);
	~SongRequest();
	SongRequest& operator=(const SongRequest& sg);
	std::string toString()const;
	void clear();
	std::string toJson()const;
	bool fromJson(const std::string& s);
};
#endif
