<?php
/*
@author = Donghyun Kang

This php script responds to android.
Handles log out of user.
*/

require_once('config.php');

$localhost=mysql_connect(DB_HOST,DB_ROOT,DB_PW)
or
die(mysql_error());

// database connection

mysql_select_db(DB_NAME,$localhost);
mysql_query("SET NAMES 'utf8'");

$login = $_REQUEST['login'];
$carnum = $_REQUEST['carnum'];

$query_Lupdate = "UPDATE board SET name='0', carnum='0', locstate='0', permit='0', login='".$login."' WHERE 1";

// updates board table with log out's datas


$query_exec = mysql_query($query_Lupdate) or die(mysql_error());
// send query to database

if($query_exec){
	echo "1";
}

// if success, print 1 to android

mysql_close();

?>