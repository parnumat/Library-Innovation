<!DOCTYPE html>
<html>
<head>
	<title></title>
	<link rel="stylesheet" type="text/css" href="past2.css">
</head>
<body>
	<div class="php1">
		<div class="php2">Your data
			<p class="data">First name: 
				<?php echo $_GET["fname"]; ?><br><br>
				Last name:<?php echo $_GET["lname"]; ?><br><br>
      	  		Student number:<?php echo $_GET["id_code"]; ?><br><br>
        		Sex:<?php echo $_GET["gender"]; ?>
			</p>
				
		</div>
	</div>
</body>
</html>