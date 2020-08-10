<?php

/*
@author = Donghyun Kang

This php script responds to android.
Handles database of car's lock state, in server.
*/

require_once('config.php'); // includes Database config script

$localhost = mysql_connect(DB_HOST,DB_ROOT,DB_PW) // connect database
or
trigger_error(mysql_error(),E_USER_ERROR); // or die if error occurs

mysql_select_db(DB_NAME,$localhost); // select DB
mysql_query("SET NAMES 'utf8'"); // send query to set column names as UTF8 encoding

$lock = $_REQUEST['lock']; // get lock value from android
$carnum = $_REQUEST['carnum']; // get car number value from android

$query = "UPDATE carstate SET locstate='".$lock."'WHERE carnum='".$carnum."'";
$query_exec = mysql_query($query) or die(mysql_error());
// send query to locstate table to update lock value

$query = "UPDATE board SET locstate='".$lock."' WHERE carnum='".$carnum."'";
$query_exec = mysql_query($query) or die(mysql_error());
// send query to board table to update lock value

echo $lock; // returns current lock value to android

mysql_close(); // close database connection

?>
