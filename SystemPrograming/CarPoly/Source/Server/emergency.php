<?php
/*
@author = Donghyun Kang

This php script shows accident reports.
This script gets data from database and shows which accident has occured, with page refresh, by every 3 seconds.

When an accident occurs, Android updates emergency table.
Then this shows accident with different condition of that accident.( Crush while driving or Crush while stopped )

*/

$url=$_SERVER['REQUEST_URI'];
header("Refresh: 3; URL=$url"); // for synchronization with server's accident data, this page refreshes, every 3 seconds
?>


<!DOCTYPE html>
<html>
<head>
<title>Emergency Report Center</title>
<style type="text/css">
h1 {
	color: red;
}
h2 {
	color: blue;
}
</style>
</head>
<body>

<?php

require_once('config.php');

$localhost = mysql_connect(DB_HOST,DB_ROOT,DB_PW)
or
die(mysql_error());
// connect database

mysql_select_db(DB_NAME,$localhost);
mysql_query("SET NAMES 'utf8'");


$query_Isearch = "SELECT * FROM emergency";

$query_exec = mysql_query($query_Isearch) or die(mysql_error());
$rows = mysql_num_rows($query_exec);
// get all emergency datas from database

if($rows==0){
	echo "<h2>There's no accident</h2>";
}
else{
	while($row=mysql_fetch_assoc($query_exec)){
		// prints User's name and Car's number
		echo "<h1>";
		echo $row["name"];
		print " got accident, with car number ";
		echo $row["carnum"];

		// prints differently by accident state
		// 2 == DRIVING STATE
		// 1 == STOPPED STATE
		if($row["eme"]==2){
			echo " while driving.";
		}
		else{
			echo " while stopped state";
		}
		echo "<br />";
		echo "</h1>";
		
	}
}

mysql_close();
// close database connection
?>

</body>
</html>