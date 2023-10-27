
#ifndef SONGREQUESTCONTROLLER_H
#define SONGREQUESTCONTROLLER_H

#include<pqxx/pqxx>

class SongRequestController {
private:
	std::shared_ptr<pqxx::connection> hcon;
public:
	SongRequestController();
	~SongRequestController();
	bool insertSong(SongRequest* sg);
	bool updateSong(SongRequest* sg);
	bool deleteSong(uint32 id);
	bool getSongById(uint32 id, SongRequest* sg);
	bool getSongs(std::vector<std::shared_ptr<SongRequest>>& songs);
};
#endif
