<?PHP
/*
    Nombre: consulta.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Controlador de la consulta avanzada
    Function: Advanced query controller.
    Ver: 2.12
*/


# Primero verifico si ya esta sesionado, si no es así
# pide usuario y contraseña antes de seguir.
// First I verify if already this in session, if it is not thus
// requests usuary and password before following.

session_start();
require('config.inc.php');
require($Include.'lang.inc');
## Traigo las funciones PHP
// Get PHP functions

require('funciones.inc.php');


if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<10)
    {require($Include.'login.inc');
     exit();
    }

## Me conecto con la base de datos para poder seleccionar
## las distintas opciones de los atributos, usuarios, etc.
// Connect with the data base to be able to select
// the different options from the attributes, users, etc.


$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

$opcion=$Advanced_query;

if (count($_POST)==0 and count($_GET)==0 )
    {require($Include.'consulta_param.inc');
     exit();
    }
elseif(count($_POST)!=0)
    {require($Include.'consulta_condition.inc');
    }
elseif(count($_GET)!=0)
    {$condicion=$_SESSION['PHD_CONDICION'];
     $q_registros=$_GET[q_registros];
     $pagina=$_GET[pagina];
     $orden=$_GET[orden];
     $sentido=$_GET['sentido'];
     $menu=$_GET['menu'];
     $titulo=$_SESSION['PHD_TITULO'];
    }

if ($q_registros==0)
    {$query="SELECT COUNT(*) AS cuantos
             FROM {$MyPHD}ticket $condicion";
     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
     $q_registros=$row['cuantos'];
    }


if (isset($_POST[buscar])  or isset($_GET[pagina]))
    {include($Include.'c_screen.inc');
    }
elseif (isset($_POST['exportar']))
    {include($Include.'c_export.inc');
    }
else
    {$mensaje="<div class='error'>consulta.php call error</div>";
     require($Include.'consulta_param.inc');
    }



