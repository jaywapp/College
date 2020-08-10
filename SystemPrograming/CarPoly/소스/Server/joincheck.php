<?php
/*
@author = Donghyun Kang

This php script responds to android.
Handles sign up of user.
*/
require_once('config.php');

$localhost = mysql_connect(DB_HOST,DB_ROOT,DB_PW)
or
trigger_error(mysql_error(),E_USER_ERROR);

mysql_select_db(DB_NAME, $localhost);
mysql_query("SET NAMES 'utf8'");

// database connection

$phone = $_REQUEST['phone']; // gets phone number of user
$pw = $_REQUEST['pw']; // gets password of user
$name = $_REQUEST['name']; // gets name of user
$carnum = $_REQUEST['carnum']; // gets car number of user
$carname = $_REQUEST['carname']; //gets car name of user
$insu = $_REQUEST['insu']; // gets insuarance of user
$permit = $_REQUEST['permit']; // gets permit level of user
$power = 0; // power of car, initializing with 0
$lock = 0; // lock state of car, initializing with 0


$check = mysql_query("select * from user where phone='".$phone."'") or die(mysql_error());
$rows = mysql_num_rows($check);

// gets user's data from user table with given $phone (phone number)

$checkQuery = "SELECT * from usercar WHERE carnum='".$carnum."'";
$check = mysql_query($checkQuery) or die(mysql_error());
$rowc = mysql_num_rows($check);

// gets car datas from usercar table with given $carnum (car number)

if($rows == 0){

$query_joinU = "INSERT into user(name,pw,phone) values('$name','$pw','$phone')";
$query_joinC = "INSERT into usercar(phone,carname,carnum,permit) values('$phone','$carname','$carnum','$permit')";

$query_joinCS = "INSERT into carstate(carnum,carname,power,locstate,insu,st,et) values('$carnum','$carname','$power','$lock','$insu','1','2')";

// if user exist, send queries

$result1 = mysql_query($query_joinU) or die(mysql_error());

$result2 = mysql_query($query_joinC) or die(mysql_error());

// save result as xml file

if($rowc == 0){
	$result3 = mysql_query($query_joinCS) or die(mysql_error());
}


$xmlcode = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
$xmlcode .= "<result>$result1</result>\n";

$dir = "C:\APM_Setup\htdocs";

$filename = $dir."\insertresult.xml";

file_put_contents($filename, $xmlcode);
}
//xml prining
else {
	exit();
	// if user not exist, end this script
}

mysql_close();
// close database connection
?>
