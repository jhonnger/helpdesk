<?PHP
/*
    Nombre: area_select.php
    Autor: Julio Tuozzo
    Función: Devuelve los datos del área en formato XML
    Function: Returns the area's data in XML format.
    Versión: 2.12
*/


## Verifico que se encuentre validado el operador, si no es asi no devuelve nada
// Verify that one is validated the user, if it is not return nothing.

session_start();
if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<6)
    {exit();
    }

## Me conecto con la base de datos para poder buscar
## el área
// Connect with the database to search the area´s data.


require('config.inc.php');
$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## Verifico si esta seteado magic_quotes_gpt para sacar la barra invertida (\)
// Check if magic_quotes_gpt is setting On for delete the slash (\)

if (get_magic_quotes_gpc())
    { foreach($_POST as $clave => $valor)
      {$_POST[$clave]=stripslashes($_POST[$clave]);
      }
    }

foreach($_POST as $clave => $valor)
     {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
     }

$area_id=$_POST['area_id'];
## Veo si el post de usuario tiene valor, si es así busco la descripción del área
// If post of user has value search the area description.

if (isSet($_POST['area_id']) )
    {$query="SELECT *
             FROM {$MyPHD}area
             WHERE area_id='$area_id' AND
             activo='S'";

     $result=mysql_query($query) or die (mysql_error());
     $q_filas=mysql_num_rows($result);

     if ($q_filas>0)
        {$row = mysql_fetch_array($result);

         $nombre_area=$row['nombre'];

         ## Envío la respuesta XML
         // The XML response
         
         header('Content-Type: text/xml');
         header("Cache-Control: no-cache, must-revalidate");
         header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");

         echo "<?xml version='1.0' encoding='ISO-8859-1'?>
               <area>
                  <nombre_area>$nombre_area </nombre_area>
               </area>";

        }
     else
        {## Envío la respuesta XML
         // The XML response

         header('Content-Type: text/xml');
         header("Cache-Control: no-cache, must-revalidate");
         header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");

         echo "<?xml version='1.0' encoding='ISO-8859-1'?>
               <area>
                  <nombre_area> </nombre_area>
               </area>";

        }
    }


?>
