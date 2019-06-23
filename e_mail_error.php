<?PHP
/*
    Nombre: e_mail_error.php
    Autor: Julio Tuozzo
    Función: Controlador del log de errores de envío de e-mail
    Function: Error send e-mail log controler
    Ver: 2.12

*/

session_start();
require('config.inc.php');
require($Include.'lang.inc');

if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<10)
          {require($Include.'login.inc');
           exit();
          }
## Me conecto con la base de datos
// Connect with the database

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## Depuro los GETs y POSTs
// GETs and POSTs sanitization

if (get_magic_quotes_gpc())
    { foreach($_GET as $clave => $valor)
      {$_GET[$clave]=stripslashes($_GET[$clave]);
      }
    }

foreach($_GET as $clave => $valor)
     {$_GET[$clave]=trim(htmlentities($_GET[$clave],ENT_QUOTES,"ISO-8859-1"));
     }

if (get_magic_quotes_gpc())
    { foreach($_POST as $clave => $valor)
      {$_POST[$clave]=stripslashes($_POST[$clave]);
      }
    }

foreach($_POST as $clave => $valor)
     {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
     }


// Llamó a Inicio
// Call Home

if (isset($_POST['inicio']))
    {header("Location: index.php");
    }

if (isset($_POST['eliminar']))
    {$query="DELETE FROM {$MyPHD}e_mail_error";
     $result=mysql_query($query) or die (mysql_error());
     unset($_GET);
    }

if (!isset($_GET['pagina']))
    {## cuento cuántos registros arroja la consulta
    // Count the rows of the query

    $query="SELECT COUNT(*) AS cuantos
            FROM {$MyPHD}e_mail_error";
    $result=mysql_query($query) or die (mysql_error());
    $row = mysql_fetch_array($result);
    $q_registros=$row['cuantos'];
    $pagina=1;
    $orden="insert_datetime";
    $sentido="DESC";

    }
else
    {$q_registros=$_GET['q_registros'];
     $pagina=$_GET['pagina'];
     $orden=$_GET['orden'];
     $sentido=$_GET['sentido'];
    }

## Calculo desde que registro muestro en función de la página
// Calculate since registry show based on the page.

$desde_reg=($pagina-1)*$_SESSION['PHD_MAX_LINES_SCREEN'];

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

$query="SELECT * FROM {$MyPHD}e_mail_error ORDER BY $orden $sentido LIMIT $desde_reg, {$_SESSION['PHD_MAX_LINES_SCREEN']}";

$result=mysql_query($query) or die (mysql_error());

require($Include.'e_mail_error_list.inc');
?>

