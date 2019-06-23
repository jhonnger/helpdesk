<?PHP
/*
    Nombre: abro_adjunto.php
    Autor: Julio Tuozzo
    Función: Abrir el adjunto de sigo_ticket
    Function: Open the attached file of sigo_ticket
    Ver: 2.12
*/

## Verifico que se encuentre validado el usuario, si no es asi lo
## dirijo a la pantalla de login.
// Verify that one is validated the user, if it is not therefore
// redirect to the screen of login.

session_start();

require('config.inc.php');
require($Include.'lang.inc');


## Me conecto con la base de datos
// Connect with the data base

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


## Verifico que tenga algún valor $_GET['file'], si no es un error.
// Verify if $_GET['file'] has any value, else is an error


if (isSet($_GET['file']))

    {$query="SELECT *
             FROM {$MyPHD}sigo_ticket
             WHERE seq_sigo_ticket_id={$_GET['file']} ";
             
     $result=mysql_query($query) or die (mysql_error());
     
     $row = mysql_fetch_array($result);

     $tipo_adjunto = $row['tipo_adjunto'];
     $adjunto = $row['adjunto'];
     $nombre_adjunto = $row['nombre_adjunto'];

     if(strlen($nombre_adjunto)>1)
        {header("Content-type: $tipo_adjunto");
         header("Content-Disposition: attachment; filename=\"$nombre_adjunto\"");
         echo $adjunto;
        }
     else
        {require('head.inc');
         echo "<div class='error'>INVALID CALL </div>";
        }
    }
else 
    { require('head.inc');
      echo "<div class='error'>INVALID CALL </div>";

    }


?>
