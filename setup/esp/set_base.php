<?PHP
/*
    Nombre: set_base.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Configura las variables de acceso a la base de datos en config.onc.php
    Ver: 2.12
*/

session_start();
$path_phd="../../";

require($path_phd.'config.inc.php');

if (!isset($_SESSION['BASE']))

    {include('setup_head.inc');
     echo "<p class='danger'>LLAMADA INVALIDA</p>";
     exit();
    }

if (!is_writable($path_phd."config.inc.php"))
    {include('setup_head.inc');
     echo "<p class='danger'><b>IMPOSIBLE ESCRIBIR ARCHIVO {$path_phd}config.inc.php </b></p>
     <p class='ok'>Verifique que exista y que tenga permiso de escritura, e intente nuevamente.<br />
     El archivo config.inc.php se encuentra inicialmente en <b>/phd_2_00/include/.</b>
     </p>";
     exit();
    }

$a_phd = implode('', file($path_phd."config.inc.php"));

if (!isset($_POST[b_base]))
    {require('set_base.inc');
     exit();
    }

 if(!@mysql_connect($_POST[host],$_POST[usuario],$_POST[contrasena]) or !mysql_select_db($_POST[base]))
    {$mensaje="<p class='danger'>ERROR - No se estableci&oacute; la conexi&oacute;n con la base de datos. Ingrese nuevamente los valores.</p>";
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
