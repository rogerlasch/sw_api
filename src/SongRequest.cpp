
#include<crow.h>
#include"../gpp_utils.h"
#include "SongRequest.h"

using namespace std;

// Construtor padrão
SongRequest::SongRequest() {
	id = 0;
	status = SG_DEFAULT;
	timestamp = 0;
	musicName = "";
	artist = "";
	listener = "";
	msg = "";
}

// Construtor com parâmetros
SongRequest::SongRequest(uint32 id, uint32 status, int64 timestamp, const string& musicName, const string& artist, const string& listener, const string& msg) {
	this->id = id;
	this->status = status;
	this->timestamp = timestamp;
	this->musicName = musicName;
	this->artist = artist;
	this->listener = listener;
	this->msg = msg;
}

// Construtor de cópia
SongRequest::SongRequest(const SongRequest& sg) {
	*this = sg;
}

// Destrutor
SongRequest::~SongRequest() {}

// Operador de atribuição
SongRequest& SongRequest::operator=(const SongRequest& sg) {
	if (this == &sg) {
		return *this;
	}
	id = sg.id;
	status = sg.status;
	timestamp = sg.timestamp;
	musicName = sg.musicName;
	artist = sg.artist;
	listener = sg.listener;
	msg = sg.msg;
	return *this;
}

// Converte o objeto para uma representação de string
string SongRequest::toString() const {
	stringstream ss;
	ss << fixed;
	ss << "ID:" << id << ", Music Name: " << musicName << ", Artist: " << artist << ", Listener: " << listener << ", Msg: " << msg << ", Timestamp: " << timestamp << ", Status: " << status << endl;
	return ss.str();
}

// Limpa os membros da classe
void SongRequest::clear() {
	id = 0;
	status = SG_DEFAULT;
	timestamp = 0;
	musicName.clear();
	artist.clear();
	listener.clear();
	msg.clear();
}
#include <crow/json.h>

string SongRequest::toJson() const {
	crow::json::wvalue json;
	json["id"] = id;
	json["status"] = status;
	json["timestamp"] = timestamp;
	json["musicName"] = musicName;
	json["artist"] = artist;
	json["listener"] = listener;
	json["msg"] = msg;
	return json.dump();
}

bool SongRequest::fromJson(const string& s) {
	crow::json::rvalue json = crow::json::load(s);
	if (!json)return false;
	if (json.has("id")) {
		id = json["id"].u();
	}
	if (json.has("status")) {
		status = json["status"].u();
	}
	if (json.has("timestamp")) {
		timestamp = json["timestamp"].i();
	}
	if (json.has("musicName")) {
		musicName = json["musicName"].s();
	}
	if (json.has("artist")) {
		artist = json["artist"].s();
	}
	if (json.has("listener")) {
		listener = json["listener"].s();
	}
	if (json.has("msg")) {
		msg = json["msg"].s();
	}
	return true;
}
