<?php
/*
@author = Donghyun Kang

This php script responds to android.
Handles duplication check while user signs up to system.
*/

require_once('config.php');

$localhost = mysql_connect(DB_HOST,DB_ROOT,DB_PW)
or
trigger_error(mysql_error(),E_USER_ERROR);
 
mysql_select_db(DB_NAME, $localhost);

mysql_query("set names utf8");

// database connection

 
$phone = $_REQUEST['phone'];
$carnum = $_REQUEST['carnum'];
// gets user's phone number and car's number
// and save as $phone, $car_num

$query_search = "SELECT * FROM user WHERE phone = '".$phone."'";
$query_exec = mysql_query($query_search) or die(mysql_error());
$rows = mysql_num_rows($query_exec);
// $rows == number of rows, matched with given phone number($phone) in user table

 if($rows == 0) {
 echo "No Such User Found"; 
 }
 else  {
    echo "User Found"; 
}
// 

mysql_close();
// close database connection

?>