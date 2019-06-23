<?PHP
/*
    Nombre: usuario_list.php
    Autor: Julio Tuozzo
    Función: Lista de usuarios de los casos
    Function: Ticket's users list.
    Ver: 2.12
*/

session_start();
require('config.inc.php');
require($Include.'lang.inc');

if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<20)
    {require($Include.'login.inc');
     exit();
    }

## Me conecto con la base de datos
// Connect with the database


$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## Depuro los GETs
// GETs sanitization

if (get_magic_quotes_gpc())
    { foreach($_GET as $clave => $valor)
      {$_GET[$clave]=stripslashes($_GET[$clave]);
      }
    }

foreach($_GET as $clave => $valor)
     {$_GET[$clave]=trim(htmlentities($_GET[$clave],ENT_QUOTES,"ISO-8859-1"));
     }

## Verifico si existe filtro
// Verify that filter exists

if (isset($_POST[filtrar]))

    {## inicializo las variables
     // inicializig variables
     if (get_magic_quotes_gpc())
        { foreach($_POST as $clave => $valor)
             {$_POST[$clave]=stripslashes($_POST[$clave]);
             }
        }
     foreach($_POST as $clave => $valor)
            {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
            }

    $_SESSION[USUARIO][usuario_id]=$_POST[usuario_id];
    $_SESSION[USUARIO][area_id]=$_POST[area_id];
    $_SESSION[USUARIO][ape_y_nom]=$_POST[ape_y_nom];
    $_SESSION[USUARIO][activo]=$_POST[activo];
    }

if (isset($_SESSION[USUARIO]))
    {$condicion="";

    if (strlen($_SESSION[USUARIO][usuario_id])>0)
        {$condicion.="usuario_id like '%{$_SESSION[USUARIO][usuario_id]}%' AND ";
        }

    if (strlen($_SESSION[USUARIO][area_id])>0)
        {$condicion.="area_id='{$_SESSION[USUARIO][area_id]}' AND ";
        }

    if (strlen($_SESSION[USUARIO][ape_y_nom])>0)
        {$condicion.="ape_y_nom like '%{$_SESSION[USUARIO][ape_y_nom]}%' AND ";
        }

    if (strlen($_SESSION[USUARIO][activo])>0)
        {$condicion.="activo='{$_SESSION[USUARIO][activo]}' AND ";
        }

    ## Armo el WHERE de la consulta
    // make the WHERE of the query

    $condicion=" WHERE ".$condicion;
    ## Saco el último AND de la cadena $condicion y armo la consulta
    $condicion=substr($condicion,0,(strlen($condicion)-5));
    }


if ($_GET[pagina]<1)
    {## cuento cuántos registros arroja la consulta
    // Count the rows of the query

    $query="SELECT COUNT(*) AS cuantos
            FROM {$MyPHD}usuario $condicion";
    $result=mysql_query($query) or die (mysql_error());
    $row = mysql_fetch_array($result);
    $q_registros=$row['cuantos'];
    $pagina=1;
    $orden="usuario_id";
    
    }
else
    {$q_registros=$_GET[q_registros];
     $pagina=$_GET[pagina];
     $orden=$_GET[orden];
     $sentido=$_GET['sentido'];
    }

## Calculo desde que registro muestro en función de la página
// Calculate since registry show based on the page.

$desde_reg=($pagina-1)*$_SESSION[PHD_MAX_LINES_SCREEN];

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

require($Include.'usuario_list.inc');
?>

