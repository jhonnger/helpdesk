<?PHP
/*
    Nombre: set_mail.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Configura las variables para el envío del correo electrónico
    Ver: 2.12
*/

session_start();
require('../../config.inc.php');

if (!isset($_SESSION['MAIL']))

    {include('setup_head.inc');
     echo "<p class='danger'>LLAMADA INVALIDA</p>";
     exit();
    }

$a_phd = implode('', file("../../config.inc.php"));

if (!isset($_POST[b_mail]))
    {require('set_mail.inc');
     exit();
    }


if (get_magic_quotes_gpc())
    { foreach($_POST as $clave => $valor)
      {$_POST[$clave]=stripslashes($_POST[$clave]);
      }
    }

foreach($_POST as $clave => $valor)
     {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
     }

$a_phd=str_replace("\$Mail_host = '$Mail_host'","\$Mail_host = '$_POST[host]'",$a_phd);
$a_phd=str_replace("\$Mail_usuario = '$Mail_usuario'","\$Mail_usuario = '$_POST[usuario]'",$a_phd);
$a_phd=str_replace("\$Mail_clave = '$Mail_clave'","\$Mail_clave = '$_POST[clave]'",$a_phd);
$a_phd=str_replace("\$Mail_port = $Mail_port","\$Mail_port = $_POST[port]",$a_phd);
$fp = fopen ("../../config.inc.php", "w+");
fwrite($fp,$a_phd);
fclose($fp);

session_destroy();
header("Location: index.php");
?>
