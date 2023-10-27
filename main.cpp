
#include"gpp_utils.h"
#include <crow.h>
#include"src/SongRequest.h"
#include"src/SongRequestController.h"

using namespace std;
using namespace gpp;

string getJsonMsg(uint32 code, const string& msg);
int main() {
	gpp_starter gst;
	try {
		crow::SimpleApp app;
		SongRequestController controller;

		// Rota para obter pedidos
		CROW_ROUTE(app, "/pedidos")
			.methods(crow::HTTPMethod::Get)
			([&controller] {
			vector<shared_ptr<SongRequest>> songs;
			if (controller.getSongs(songs)) {
				stringstream ss;
				ss << "[";
				uint32 size = songs.size();
				for (uint32 i = 0; i < size; i++) {
					ss << songs[i]->toJson();
					if (i < size - 1) ss << ",";
				}
				ss << "]";
				return crow::response(200, ss.str());
			}
			return crow::response(500, getJsonMsg(500, "Problemas internos com o servidor. Tente mais tarde."));
				});

		// Rota para criar um novo pedido
		CROW_ROUTE(app, "/pedido/create")
			.methods(crow::HTTPMethod::Post)
			([&controller](const crow::request& req) {
			SongRequest ms;
			if (!ms.fromJson(req.body)) {
				return crow::response(400, getJsonMsg(400, "O json fornecido está vazio, ou corrompido."));
			}
			if (controller.insertSong(&ms)) {
				return crow::response(200, ms.toJson());
			}
			return crow::response(500, getJsonMsg(500, "Erro ao gravar os dados."));
				});

		// Rota para atualizar um pedido existente
		CROW_ROUTE(app, "/pedido/update")
			.methods(crow::HTTPMethod::Put)
			([&controller](const crow::request& req, crow::response& res)->void {
			SongRequest sg;
			if (!sg.fromJson(req.body)) {
				res.code = 400;
				res.body = getJsonMsg(400, "O json está vazio, ou chegou corrompido.");
				res.end();
			}
			if (controller.updateSong(&sg)) {
				res.code = 200;
				res.body = req.body;
				res.end();
			}
			else {
				res.code = 500;
				res.body = getJsonMsg(500, "Erro ao atualizar o registro...");
				res.end();
			}
				});

		// Rota para excluir um pedido
		CROW_ROUTE(app, "/pedido/delete/<uint>")
			.methods(crow::HTTPMethod::Delete)
			([&controller](const crow::request& req, crow::response& res, uint32  id) {
			if (controller.deleteSong(id)) {
				res.code = 200;
				res.body = getJsonMsg(200, "Registro excluído com sucesso!");
				res.end();
			}
			else {
				res.code = 500;
				res.body = getJsonMsg(500, "Erro ao excluir o registro, talvez ele não exista mais.");
				res.end();
			}
				});
		// Inicie o servidor Crow
		app.port(3000).multithreaded().run();
	}
	catch (const exception& e) {
		_GERROR("{}", e.what());
	}
	return 0;
}

string getJsonMsg(uint32 code, const string& msg) {
	crow::json::wvalue json;
	json["server_message"] = msg;
	return json.dump();
}
