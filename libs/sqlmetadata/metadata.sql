CREATE TABLE if not exists %1 (Artist varchar(100), TrackTitle  varchar(100), AlbumTitle  varchar(100), TrackNumber    varchar(10), Genre varchar(20), Comment  varchar(200), Rating int, FileName  varchar(255) PRIMARY KEY, INDEX(Genre) );


CREATE TABLE IF NOT EXISTS MetaData (TrackTitle  text, Artist text, AlbumTitle  text, TrackTime integer, TrackNumber integer, Genre varchar(30),  Preference integer, Comment  text, FileName  varchar(255) PRIMARY KEY) DEFAULT CHARSET utf8;

INSERT INTO MetaData (Artist, TrackTitle, AlbumTitle, TrackNumber, TrackTime, Genre, Rating, FileName) VALUES ("Orbital2", "Mission Impossible3", "Official Soundtrack4", "5", "3:26", "Techno7", 9, "/home/ezust/workspace/oopdocbook/trunk/docs/solution/mp3player/mission.mp3") ON DUPLICATE KEY UPDATE Rating=VALUES(Rating), Genre=VALUES(Genre), AlbumTitle=VALUES(AlbumTitle), TrackTitle=VALUES(TrackTitle), TrackNumber=VALUES(TrackNumber), Artist=VALUES(Artist) ;

QString("select %2.pid, %1.TrackTitle, %1.Artist, %1.AlbumTitle, %1.TrackNumber, %1.TrackTime, %1.Genre, %1.Rating, %1.FileName from %1, %2 where %2.FileName = %1.FileName order by %2.pid") .arg("MetaData").arg("dbplaylist_test1");

select urls.rpath, genres.name urls,tags,genres where urls.id = tags.url and tags.genre = genres.id

SQLite3:
CREATE TABLE IF NOT EXISTS MetaData (TrackTitle  text, Artist text, AlbumTitle  text, TrackTime integer, TrackNumber integer, Genre varchar(30),  Preference integer, Comment  text, FileName  varchar(255) PRIMARY KEY) ;

MySQL:
CREATE TABLE IF NOT EXISTS MetaData (TrackTitle  text, Artist text, AlbumTitle  text, TrackTime integer, TrackNumber integer, Genre varchar(30),  Preference integer, Comment  text, FileName  varchar(255) PRIMARY KEY, INDEX(Genre)) DEFAULT CHARSET utf8;

playlists:
create table if not exists dbplaylist_test (pid INT AUTO_INCREMENT PRIMARY KEY, FileName text);
