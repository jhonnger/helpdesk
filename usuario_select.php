<?PHP
/*
    Nombre: usuario_select.php
    Autor: Julio Tuozzo
    Función: Devuelve los datos del usuario en formato XML
    Function: Returns the user's data in XML format.
    Versión: 2.12
*/


## Verifico que se encuentre validado el operador, si no es asi no devuelve nada
// Verify that one is validated the user, if it is not return nothing.

session_start();
if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<6)
    {exit();
    }

require('config.inc.php');
require('funciones.inc.php');
require($Include.'lang.inc');

## Me conecto con la base de datos para poder buscar
## al usuario
// Connect with the database to search the user´s data.



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

$usuario=$_POST['usuario']; 
## Veo si el post de usuario tiene valor, si es así busco el apellido y nombre y área.
// If post of user has value search the last name and names and area.

if (isSet($_POST['usuario']) )
    {$query="SELECT u.*, a.nombre as nombre_area
             FROM {$MyPHD}usuario u, {$MyPHD}area a
             WHERE usuario_id='$usuario' AND
             a.area_id=u.area_id AND
             u.activo='S' AND
             a.activo='S'";

     $result=mysql_query($query) or die (mysql_error());
     $q_filas=mysql_num_rows($result);

     if ($q_filas>0)
        {$row = mysql_fetch_array($result); 
         $ape_y_nom=$row['ape_y_nom'];
         $area_id=$row['area_id'];
         $piso=$row['piso'];
         $planta=$row['planta'];
         $e_mail=$row['e_mail'];
         $nombre_area=$row['nombre_area'];

         if (strlen($_SESSION['PHD_STATE_ALERT'])>0)
                {$_SESSION['PHD_CONDICION']="WHERE estado='$_SESSION[PHD_STATE_ALERT]' AND usuario_id='$usuario'
                                             AND $Filtro_ticket";
                 $_SESSION['PHD_TITULO']="Filtro= <b>$State:</b> $_SESSION[PHD_STATE_ALERT], <b>$User:</b> $usuario ";
                 $query="SELECT usuario_id
                         FROM {$MyPHD}ticket ".$_SESSION['PHD_CONDICION'];
                 $result=mysql_query($query) or die (mysql_error()."<br> $query");
                 $alertas=mysql_num_rows($result);
                }


         ## Envío la respuesta XML
         // The XML response
         
         header('Content-Type: text/xml');
         header("Cache-Control: no-cache, must-revalidate");
         header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");

         echo "<?xml version='1.0' encoding='ISO-8859-1'?>
               <usuario>
                  <ape_y_nom>$ape_y_nom </ape_y_nom>
                  <area_id>$area_id </area_id>
                  <piso>$piso </piso>
                  <planta>$planta </planta>
                  <e_mail>$e_mail </e_mail>
                  <nombre_area>$nombre_area </nombre_area>
                  <alertas>$alertas </alertas>
               </usuario>";
        }

    }

?>
