<?php
/*
@author = Donghyun Kang

This php script responds to android.
Handles log-in of user, with usercar database.
*/
require_once('config.php');

$localhost = mysql_connect(DB_HOST,DB_ROOT,DB_PW)
or
trigger_error(mysql_error(),E_USER_ERROR);

mysql_select_db(DB_NAME,$localhost);
mysql_query("SET NAMES 'utf8'");
// database connection

$carnum = $_REQUEST['carnum'];
// gets car's number from user(android) and save as $carnum

$query_cars = "SELECT * FROM usercar WHERE carnum = '".$carnum."'";
$query_exec = mysql_query($query_cars) or die(mysql_error());
$rows = mysql_num_rows($query_exec);
// searches for data from usercar table, where carnum equals $carnum 
// $rows == number of rows, matched with $carnum
if($rows == 0){
	echo "0";
}
// no user found

else{
	// if user found, prints car's number
	print $carnum;
	print "@";
	// '@' is token
	while($rows>0){
		// and prints user's name, phone number, and permit level
		$row=mysql_fetch_assoc($query_exec);
		print $row["name"];
		print "/";
		print $row["phone"];
		print "/";
		print $row["permit"];

		// 			'/'is token
		print "@";
		$rows--;


	}	

}

?>