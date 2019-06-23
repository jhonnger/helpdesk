<?PHP
/*
    Name: set_base.php
    Author: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Function: Configure the access variables of phd.inc
    Ver: 2.12
*/

session_start();
$path_phd="../../";

require($path_phd.'config.inc.php');


if (!isset($_SESSION['BASE']))

    {include('setup_head.inc');
     echo "<p class='danger'>INVALID CALL</p>";
     exit();
    }

if (!is_writable($path_phd."config.inc.php"))
    {include('setup_head.inc');
     echo "<p class='danger'><b>ERROR - IMPOSSIBLE TO WRITE THE FILE {$path_phd}config.inc.php </b></p>
     <p class='ok'>Verify if the file exists and the access permission and try again.<br />
      The config.inc.php file is placed in <b>/phd_2_12/.</b>
     </p>";
     exit();
    }

$a_phd = implode('', file($path_phd."config.inc.php"));

if (!isset($_POST[b_base]))
    {require('set_base.inc');
     exit();
    }

 if(!@mysql_connect($_POST[host],$_POST[usuario],$_POST[contrasena]) or !mysql_select_db($_POST[base]))
    {$mensaje="<p class='danger'>ERROR - Did not connect with the data base. Enter the values again.</p>";
     require('set_base.inc');
     exit();
    }

$a_phd=str_replace("\$Host = '$Host'","\$Host = '$_POST[host]'",$a_phd);
$a_phd=str_replace("\$Usuario = '$Usuario'","\$Usuario = '$_POST[usuario]'",$a_phd);
$a_phd=str_replace("\$Contrasena = '$Contrasena'","\$Contrasena = '$_POST[contrasena]'",$a_phd);
$a_phd=str_replace("\$Base = '$Base'","\$Base = '$_POST[base]'",$a_phd);
$fp = fopen ($path_phd."config.inc.php", "w+");
fwrite($fp,$a_phd);
fclose($fp);

session_destroy();
header("Location: index.php");
?>
