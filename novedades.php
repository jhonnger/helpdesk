<?PHP
/*
    Nombre: novedades.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Controlador del listado de novedades
    Function: News list controller.
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

$opcion=$News;

if (count($_POST)==0 and count($_GET)==0 )
    {$fecha_desde=$fecha_hasta=date($Date_format);
	 require($Include.'novedades_param.inc');
     exit();
    }
elseif(count($_POST)!=0)
    {require($Include.'novedades_condition.inc');
    }
elseif(count($_GET)!=0)
    {$q_registros=$_GET[q_registros];
     $pagina=$_GET[pagina];
     $orden=$_GET[orden];
     $sentido=$_GET['sentido'];
     $titulo=$_SESSION['PHD_NEWS_TITULO'];
    }

if($sentido=="DESC")
    {$_aux_var="arr_$orden";
     $$_aux_var="&nbsp; &#9660;";
     $_aux_var="sen_$orden";
     $$_aux_var="ASC";
    }
else
    {$_aux_var="arr_$orden";
     $$_aux_var="&nbsp; &#9650;";
     $_aux_var="sen_$orden";
     $$_aux_var="DESC";
    }


if (isset($_POST['buscar'])  or isset($_GET['pagina']))
    {require($Include.'novedades_list.inc');
    }
else
    {$mensaje="<div class='error'>novedades.php call error</div>";
     require($Include.'novedades_param.inc');
    }



