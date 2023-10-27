create database songs_db
CREATE TABLE song_requests (     id serial PRIMARY KEY,     musicName varchar(256) NOT NULL,     artist varchar(128) NOT NULL,     listener varchar(64) NOT NULL,     msg varchar(1024) NOT NULL,     status integer NOT NULL DEFAULT 0,     timestamp integer DEFAULT EXTRACT(EPOCH FROM NOW()) );
