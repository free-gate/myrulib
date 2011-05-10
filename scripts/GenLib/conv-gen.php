<?php

require_once '../Common/datafile.php';
require_once '../Common/strutils.php';

function InitDatabase($mysql)
{
	$mysql->query("DROP TABLE auth");
	$mysql->query("CREATE TABLE auth(aid integer primary key AUTO_INCREMENT, name VARCHAR(300)) DEFAULT CHARACTER SET utf8");
	$mysql->query("CREATE INDEX auth_name ON auth(name)");

	$mysql->query("DROP TABLE book");
	$mysql->query("CREATE TABLE book(bid integer PRIMARY KEY, aid integer)");
}

function GetAuthId($mysql, $name)
{
	if (strlen($name) == 0) return 0; 

	$stmt1 = $mysql->stmt_init();
	$stmt1->prepare("SELECT aid FROM auth WHERE name=?");
	$stmt1->bind_param("s", $param1);
	$param1 = $name;
	$stmt1->execute();
	$stmt1->bind_result($code1);
	if ($stmt1->fetch()) {
		$code = $code1;
		$stmt1->close();
		return $code;
	}
	$stmt1->close();

	$stmt2 = $mysql->stmt_init();
	$stmt2->prepare("INSERT INTO auth(name) VALUES(?)");
	$stmt2->bind_param("s", $param2);
	$param2 = $name;
	$stmt2->execute();
	
	return $mysql->insert_id;
}

function AppendBook($mysql, $aid, $bid)
{
	$stmt = $mysql->stmt_init();
	$stmt->prepare("INSERT INTO book(aid, bid) VALUES(?,?)");
	$stmt->bind_param("ii", $param_aid, $param_bid);
	$param_aid = $aid;
	$param_bid = $bid;
	$stmt->execute();
	$stmt->close();
}

function GetDescr($mysql, $md5sum)
{
	$descr = NULL;
	$stmt = $mysql->stmt_init();
	$stmt->prepare("SELECT descr FROM description WHERE md5=?");
	$stmt->bind_param("s", $param_md5);
	$param_md5 = $md5sum;
	$stmt->execute();
	$stmt->bind_result($res_descr);
	if ($stmt->fetch()) {
		$descr = $res_descr;
		return $descr;
	}
	return NULL;
}

function convert_books($mysql_db, $sqlite_db)
{
  $mysql_db->query("begin transaction");
  $sqlite_db->query("begin transaction");

  $sqlite_db->query("DELETE FROM books");
  $sqlite_db->query("DELETE FROM authors");

  $mysql_db->real_query("DELETE FROM authors");

  $sqltest = "
	SELECT Id, Title, VolumeInfo, Series, Periodical, Author, Language, Topic, Filesize, Extension, DATE_FORMAT(TimeLastModified,'%y%m%d') As Time, identifier, md5, coverurl
	FROM updated
	ORDER BY Id 
  ";

  $auth = 0;
  $name = "";

  $stmt_book = $mysql_db->stmt_init();
  $stmt_book->prepare("INSERT INTO book(aid, bid) VALUES(?,?)");
  $stmt_book->bind_param("ii", $param_aid, $param_bid);

  $query = $mysql_db->query($sqltest);
  while ($row = $query->fetch_array()) {

	$book = $row['Id'];

	$title = trim($row['Title'])." ".trim($row['VolumeInfo']);
	$title = trim($title);
	if (strlen($title) == 0) $title = trim($row['Periodical']);
	if (strlen($title) == 0) $title = trim($row['Series']);

    echo $row['Time']." - ".$book." - ".$row['Extension']." - ".$row['Author']." - ".$title."\n";
	$next = trim($row['Author']);
	if ($name != $next) {
	  $auth = GetAuthId($mysql_db, $next);
	  $name = $next;
	}

	$file_type = trim($row['Extension']);
	$file_type = trim($file_type, ".");
	$file_type = strtolower($file_type);
	$time = $row['Time'];
	if ($time < 20) $time = 0;

	$descr = GetDescr($mysql_db, $row['md5']);
	$md5sum = strtolower($row['md5']);
        
	$sql = "INSERT INTO books (id, id_author, title, file_size, file_type, created, lang, md5sum, description) VALUES(?,?,?,?,?,?,?,?,?)";
	$insert = $sqlite_db->prepare($sql);
	$err= $insert->execute(array($book, $auth, $title, $row['Filesize'], $file_type, $time, $row['Language'], $md5sum, $descr));
	$insert->closeCursor();

	$param_aid = $auth;
	$param_bid = $book;
	$stmt_book->execute();
  }

  $stmt_book->close();

  $sqlite_db->query("INSERT OR REPLACE INTO dates(id, lib_num) (select created, count(id) from books group by created)");

  $sqlite_db->query("commit");
  $mysql_db->query("commit");
}

function convert_auth($mysql_db, $sqlite_db)
{

  $char_list = 'А Б В Г Д Е Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ы Э Ю Я A B C D E F G H I J K L M N O P Q R S T U V W X Y Z';

  if (strpos($char_list, $letter) === false) { $letter = "#"; };

  $sqlite_db->query("begin transaction");

  $sqltest = "SELECT auth.aid, auth.name, book.num FROM auth INNER JOIN (SELECT aid, COUNT(bid) AS num FROM book GROUP BY aid) AS book ON book.aid=auth.aid";

  $query = $mysql_db->query($sqltest);
  while ($row = $query->fetch_array()) {
    echo $row['aid']." - ".$row['name']."\n";
    $full_name = trim($row['name']);
    $search_name = strtolowerEx($full_name);
    $letter = utf8_substr($full_name,0,1);
    $letter = strtoupperEx($letter,0,1);
    $sql = "INSERT INTO authors (id, number, letter, full_name, last_name, search_name) VALUES(?,?,?,?,?,?)";
    $insert = $sqlite_db->prepare($sql);
    $insert->execute(array($row['aid'], $row['num'], $letter, $full_name, $full_name, $search_name));
    $insert->closeCursor();
  }
  $query->close(); 

  $sqlite_db->query("commit");
}  

function convert_dates($mysql_db, $sqlite_db)
{
  $sqlite_db->query("begin transaction;");

  $sqlite_db->query("DELETE FROM dates");

  $sqltest = "
    SELECT DATE_FORMAT(TimeLastModified,'%y%m%d') as Time, MAX(id) as Max, MIN(id) as Min, COUNT(id) AS Num
	FROM updated
	GROUP BY DATE_FORMAT(TimeLastModified,'%y%m%d') 
  ";

  $query = $mysql_db->query($sqltest);
  while ($row = $query->fetch_array()) {
	echo $row['Time']." - ".$row['Max']." - ".$row['Min']."\n";
    $sql = "INSERT INTO dates (id, lib_max, lib_min, lib_num) VALUES(?,?,?,?)";
    $insert = $sqlite_db->prepare($sql);
    $err= $insert->execute(array($row['Time'], $row['Max'], $row['Min'], $row['Num']));
    $insert->closeCursor();
  }
  $sqlite_db->query("commit");
}  

function setup_params($sqlite_db, $date, $type)
{
  $sqlite_db->query("begin transaction;");
  
  $sqlite_db->query("DELETE FROM params;");
  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (1,  'Genesis library');");
  $sqlite_db->query("INSERT INTO params(id,value) VALUES (2,  1);");
  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (3,  'GENESIS');");
  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (11, 'gen.lib.rus.ec');");
#  $sqlite_db->query("INSERT INTO params(id,value) VALUES (20, $date);");
#  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (21, '$type');");
  
  $sqlite_db->query("commit;");
}

function FullImport($mysql_db, $file, $date)
{
  $sqlite_db = new PDO('sqlite:./'.$file);
  
  create_tables($sqlite_db);
  setup_params($sqlite_db, $date, "FULL");
  
  convert_books($mysql_db, $sqlite_db);
  convert_auth($mysql_db, $sqlite_db);
  convert_dates($mysql_db, $sqlite_db);
  
  create_indexes($sqlite_db);
}

$mysql_srvr = 'localhost';
$mysql_user = 'root';
$mysql_pass = '11111111';
$mysql_base = 'bookwarrior';
$sqlitefile = 'myrulib.db';

include('settings.php');

$sqlite_db = new PDO('sqlite:./myrulib.db');
$mysql_db = new mysqli($mysql_srvr, $mysql_user, $mysql_pass, $mysql_base);
$mysql_db->query("SET NAMES utf8");

$date = date('Ymd');
echo "Today: ".$date."\n";

InitDatabase($mysql_db);
FullImport($mysql_db, $sqlitefile, $date);
system("zip genesis.db.zip $sqlitefile");
  
?>
