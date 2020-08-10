<?php

/*
@author = Donghyun Kang

This php script responds to android.
Handles log-in of user.
*/

require_once('config.php'); // includes Database config script

$localhost=mysql_connect(DB_HOST,DB_ROOT,DB_PW) // connect database
or
die(mysql_error()); // or die if error occurs

mysql_select_db(DB_NAME,$localhost); // select DB
mysql_query("SET NAMES 'utf8'"); // send query to set column names as UTF8 encoding

$phone = $_REQUEST['phone']; // get phone number from android
$pw = $_REQUEST['pw']; // get password of user, from android


$query_Usearch = "SELECT * FROM user WHERE phone = '".$phone."' AND pw = '".$pw. "'";
$query_Csearch = "SELECT * FROM usercar WHERE phone = '".$phone."'";
// Prepare queries, to get user's data and car's data from database

$query_exec = mysql_query($query_Usearch) or die(mysql_error());
$rows = mysql_num_rows($query_exec);
// send query to user table to get datas of user
// $rows contains user's data as array

$query_Cexec = mysql_query($query_Csearch) or die(mysql_error());
$crow = mysql_fetch_array($query_Cexec,MYSQL_ASSOC);
// send query to usercar table to get car's data
// $crow contains result of query as array

$query_statesearch = "SELECT * FROM carstate WHERE carnum = '".$crow["carnum"]."'";
// prepare query to get car's state datas

$Temprow=mysql_fetch_assoc($query_exec);
$query_Bupdate ="UPDATE board SET name='".$Temprow['name']."', carnum='".$crow['carnum']."', locstate='".'0'."', permit='".$crow['permit']."', login='".'1'."' WHERE '1'";
$query_Bexcec = mysql_query($query_Bupdate) or die(mysql_error());
// prepare and send query to update board table's login column
// where car's number is user's car number

$query_stateexec = mysql_query($query_statesearch) or die(mysql_error());
// send carstate search query and get's result

$Crows = mysql_num_rows($query_Cexec);
// save user related car data query's result to array

 if($rows == 0) { 
 echo "0"; 
// if requested user doesn't exist at DB, responds 0.
 }
 else {
 	$query_exec = mysql_query($query_Usearch) or die(mysql_error());
 	
 	while($row=mysql_fetch_assoc($query_exec)){
 		// Until no user has left
 		echo $row["name"];
 		echo "@";
 		// prints user's name and token '@'
 	}
 	while($Crows>0){
 		// while Car's number is bigger than 0
 		$query_Cexec = mysql_query($query_Csearch) or die(mysql_error());
 		// send Csearch query 1 more time to get data
 		$Cro=mysql_fetch_assoc($query_Cexec);
 		// get query's result as array
 		$query_stateexec = mysql_query($query_statesearch) or die(mysql_error());
		// send carstate search query and get's result
 		$Trow = mysql_fetch_assoc($query_stateexec);
 		// get car state search query's result as array

 		print $Cro["carnum"];
 		print "/";
 		print $Cro["carname"];
 		print "/";
 		print $Cro["permit"];
 		print "/";
 		print $Trow["st"];
 		print "/";
 		print $Trow["et"];
 		print "/";
 		print $Trow["lock"];
 		print "@";
 		// print car's number
 		// car's name
 		// permission level of current user
 		// car's start time
 		// car's end time
 		// car's lock state
 		// and '@' as token
 		$Crows--;
 		// $Crows is number of user related car
 	}	
}

mysql_close();
// close connection
?>
