
#include <pqxx/pqxx>
#include"../gpp_utils.h"
#include"SongRequest.h"
#include "SongRequestController.h"

using namespace std;

// Construtor
SongRequestController::SongRequestController() {
	string connectionStr = "dbname = songs_db user = postgres password = postgres hostaddr = 127.0.0.1 port = 5432";
	try {
		hcon = make_shared<pqxx::connection>(connectionStr);
		if (hcon->is_open()) {
			// A conexão foi estabelecida com sucesso
			// Você pode armazenar a conexão em um membro de dados da classe, se necessário
		}
		else {
			// Lida com erros de conexão
			_GCRITICAL("Erro ao se conectar com o Postgresql");
		}
	}
	catch (const exception& e) {
		_GEXCEPT(e.what());
	}
}

// Destrutor
SongRequestController::~SongRequestController() {
	hcon.reset();
}

// Método para inserir um pedido de música no PostgreSQL
bool SongRequestController::insertSong(SongRequest* sg) {
	try {
		pqxx::work txn(*hcon);
		string sql = "insert into song_requests(musicName, artist, listener, msg, status) values($1, $2, $3, $4, $5) returning id, timestamp";
		pqxx::result result = txn.exec_params(sql, sg->musicName, sg->artist, sg->listener, sg->msg, sg->status);
		txn.commit();
		if (!result.empty()) {
			sg->id = result[0][0].as<uint32>();
			sg->timestamp = result[0][1].as<int64>();
			return true;
		}
	}
	catch (const exception& e) {
		_GERROR("{}", _GEXCEPT(e.what()).what());
		return false;
	}
	return false;
}

// Método para atualizar um pedido de música no PostgreSQL
bool SongRequestController::updateSong(SongRequest* sg) {
	try {
		pqxx::work txn(*hcon);
		string sql = "update song_requests set musicName = $1, artist = $2, listener = $3, msg = $4, status = $5 where id= $6";
		pqxx::result result = txn.exec_params(sql, sg->musicName, sg->artist, sg->listener, sg->msg, sg->status, sg->id);
		txn.commit();
		return true;
	}
	catch (const exception& e) {
		_GERROR("{}", _GEXCEPT(e.what()).what());
		return false;
	}
	return false;
}

// Método para excluir um pedido de música no PostgreSQL
bool SongRequestController::deleteSong(uint32 id) {
	try {
		pqxx::work txn(*hcon);
		string sql = "delete from song_requests where id = $1";
		pqxx::result result = txn.exec_params(sql, id);
		txn.commit();
		return true;
	}
	catch (const exception& e) {
		_GERROR("{}", _GEXCEPT(e.what()).what());
		return false;
	}
	return false;
}

// Método para obter um pedido de música por ID do PostgreSQL
bool SongRequestController::getSongById(uint32 id, SongRequest* sg) {
	try {
		pqxx::work txn(*hcon);
		string sql = "select id, musicName, artist, listener, msg, status, timestamp from song_requests where id = $1";
		pqxx::result result = txn.exec_params(sql, id);
		txn.commit();
		if (result.size() > 0) {
			sg->id = id;
			sg->musicName = result[0][1].as<string>();
			sg->artist = result[0][2].as<string>();
			sg->listener = result[0][3].as<string>();
			sg->msg = result[0][4].as<string>();
			sg->status = result[0][5].as<uint32>();
			sg->timestamp = result[0][6].as<uint32>();
			return true;
		}
	}
	catch (const exception& e) {
		_GERROR("{}", _GEXCEPT(e.what()).what());
		return false;
	}
	return false;
}

// Método para obter todos os pedidos de música do PostgreSQL
bool SongRequestController::getSongs(vector<shared_ptr<SongRequest>>& songs) {
	try {
		pqxx::work txn(*hcon);
		string sql = "select id, musicName, artist, listener, msg, status, timestamp from song_requests";
		pqxx::result results = txn.exec_params(sql);
		txn.commit();
		if (results.size() > 0) {
			songs.clear();
			uint32 size = results.size();
			for (uint32 i = 0; i < size; i++) {
				shared_ptr<SongRequest> sg = make_shared<SongRequest>();
				sg->id = results[i][0].as<uint32>();
				sg->musicName = results[i][1].as<string>();
				sg->artist = results[i][2].as<string>();
				sg->listener = results[i][3].as<string>();
				sg->msg = results[i][4].as<string>();
				sg->status = results[i][5].as<uint32>();
				sg->timestamp = results[i][6].as<uint32>();
				songs.push_back(sg);
			}
		}
		return true;
	}
	catch (const exception& e) {
		_GERROR("{}", _GEXCEPT(e.what()).what());
		return false;
	}
	return false;
}
