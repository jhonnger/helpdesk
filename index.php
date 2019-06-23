<?php
/*
    Nombre: index.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Ingreso al sistema, menú principal.
    Function: Home page of the system, main menu.
    Ver: 2.12
*/

phpinfo();
# Primero verifico si ya esta sesionado, si no es así
# pide usuario y contraseña antes de seguir.
// First I verify if already this in session, if it is not thus
// requests usuary and password before following.

session_start();
require('config.inc.php');
require($Include.'lang.inc');
if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<10)
    {require($Include.'login.inc');
     exit();
    }

## Traigo las funciones PHP
// Get PHP functions

require('funciones.inc.php');


## Me conecto con la base de datos para poder seleccionar
## las distintas opciones de los atributos, usuarios, etc.
// Connect with the data base to be able to select
// the different options from the attributes, users, etc.


$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## inicializo la variable de $frames del head para que haga un refresh de la página.

$frames="<meta http-equiv='refresh' content='300' />";

## Armo las condiciones de los tickets que muestro en la página principal

if (isset($_POST['buscar']) or !isset($_GET['pagina']))
    {unset($_SESSION['PHD_MAIN_CONS']);
      if(!isset($_POST['buscar']))
        {$_SESSION['PHD_MAIN_CONS']['asignado_a']=$asignado_a=strip_tags(trim($_SESSION['PHD_OPERADOR']));
         $_SESSION['PHD_MAIN_CONS']['estado']=$estado=trim($_SESSION['PHD_MAIN_SCREEN_STATE']);
        }
     else
        {$_SESSION['PHD_MAIN_CONS']['operador_id']=$operador=strip_tags(trim($_POST[operador]));
         $_SESSION['PHD_MAIN_CONS']['sector_id']=$operador_sector_id=strip_tags(trim($_POST[operador_sector_id]));
         $_SESSION['PHD_MAIN_CONS']['estado']=$estado=trim($_POST[estado]);
         $_SESSION['PHD_MAIN_CONS']['asignado_a']=$asignado_a=strip_tags(trim($_POST[asignado_a]));
         $_SESSION['PHD_MAIN_CONS']['asignado_a_sector']=$asignado_a_sector=strip_tags(trim($_POST[asignado_a_sector]));
    
        }

    ## Armo el query con las condiciones que se pusieron en pantalla.
    // Make the query with the conditions


    if (strlen($operador)>0)
        {$condicion.="operador_id='$operador' AND ";
        }

    if (strlen($operador_sector_id)>0)
        {$condicion.="operador_sector_id='$operador_sector_id' AND ";
        }


    if (strlen($asignado_a)>0)
        {$condicion.="asignado_a='$asignado_a' AND ";
        }

    if (strlen($asignado_a_sector)>0)
        {$condicion.="asignado_a_sector='$asignado_a_sector' AND ";
        }

    if (strlen($estado)>0)
        {$condicion.="estado='$estado' AND ";
        }


    ## Armo el WHERE de la consulta
    // make the WHERE of the query

    $condicion=" WHERE $Filtro_ticket AND ".$condicion;
    ## Saco el último AND de la cadena $condicion y armo la consulta
    $_SESSION['PHD_CONDICION']=$condicion=substr($condicion,0,(strlen($condicion)-5));

    ## cuento cuántos registros arroja la consulta
    // Count the rows of the query

    $query="SELECT COUNT(*) AS cuantos
            FROM {$MyPHD}ticket $condicion";
    $result=mysql_query($query) or die (mysql_error());
    $row = mysql_fetch_array($result);
    $q_registros=$row['cuantos'];
    $pagina=1;
    $orden="seq_ticket_id";
    $sentido="ASC";
    }
else
    {$condicion=$_SESSION['PHD_CONDICION'];
     $q_registros=$_GET[q_registros];
     $pagina=$_GET[pagina];
     $orden=$_GET[orden];
     $sentido=$_GET['sentido'];
    }
if ($q_registros==0)
    {$query="SELECT COUNT(*) AS cuantos
             FROM {$MyPHD}ticket $condicion";
     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
     $q_registros=$row['cuantos'];
    }

$desde_reg=($pagina-1)*$_SESSION[PHD_MAX_LINES_SCREEN];


## Hago la consulta
// make query

$query="SELECT seq_ticket_id, fecha, usuario_id, ape_y_nom, area_id, incidente,
        estado, fecha_ultimo_estado, prioridad
        FROM {$MyPHD}ticket
        $condicion ORDER BY $orden $sentido LIMIT $desde_reg, $_SESSION[PHD_MAX_LINES_SCREEN]";

$result=mysql_query($query) or die (mysql_error());

require($Include.'index.inc');
?>
