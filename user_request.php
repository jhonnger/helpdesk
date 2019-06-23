<?PHP
/*
    Nombre: user_request.php
    Autor: Julio Tuozzo
    Función: Ingreso de solicitud de soporte
    Function: Insert of support request.
    Ver: 2.12
*/

session_start();
## Me conecto con la base de datos.
// Connect with the data base.

require('config.inc.php');
require($Include.'lang.inc');


if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']!=4)
    {require($Include.'user_login.inc');
     exit();
    }

require($Include.'get_ip.inc');

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## Traigo las funciones PHP.
// Get PHP functions.

require('funciones.inc.php');

$text_max_attach=conv_bytes($_SESSION[PHD_MAX_ATTACH]);
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


## Inicializo las variables del formulario.
// Inicialized the variables of the form.

## Verfico que se haya ingresado por "submit"", si no es así muestro
## el formulario para ingresar la info de la solicitud.
// Verfy that has entered by “submit "", if it is not thus show
// the form to enter info of the request.

if(!isSet($_POST['guardar']))
     {require($Include.'user_request.inc');
	  exit();
	 }

$_SESSION['PHD_PISO']=$_POST['piso'];
$_SESSION['PHD_E_MAIL']=$_POST['e_mail'];
$_SESSION['PHD_TELEFONO']=$_POST['planta'];
$fecha=$_POST['fecha'];
$incidente=$_POST['incidente'];
$archivo = $_FILES["adjunto"]["tmp_name"];
$tamanio_adjunto = $_FILES["adjunto"]["size"];
$tipo_adjunto = $_FILES["adjunto"]["type"];
$nombre_adjunto = $_FILES["adjunto"]["name"];


## Sector de validaciones de los campos ingresados
// Sector of validations of the entered fields

if (strlen($_SESSION['PHD_E_MAIL'])>0 and !preg_match("#^.+@.+\\..+$#",$_SESSION['PHD_E_MAIL'])) ## Verifica el formato del e-mail
                                                         // verify the e-mail format
   	    {$mensaje.="<br /> $No_valid_e_mail";
	    }

if (strlen($incidente)==0) ## Verifico que haya ingresado el incidente
                           // Verify that the incident has entered
   {$mensaje.="<br> $No_incident";
   }

if($tamanio_adjunto>$_SESSION[PHD_MAX_ATTACH]) // verifico que el tamaño del archivo adjunto no sea mayor a $_SESSION[PHD_MAX_ATTACH].
    { $Big_attach=str_replace("%1%",$text_max_attach,$Big_attach );
      $mensaje.="<br> $Big_attach";
    }
elseif (strlen($nombre_adjunto)>1 and $tamanio_adjunto<1) // valido que exista el archivo
        {$No_attach=str_replace("%1%"," $nombre_adjunto ",$No_attach );
         $mensaje=$mensaje."<br> $No_attach";
        }

if (isSet($mensaje))  ## Hay errores, los muestro y no proceso la solicitud
                      // Error found, show the errors and doesn´t procces the request
   {$mensaje=$UPR_error_found.$mensaje;
    require($Include.'user_request.inc');
    exit();
   }
    

else  ## No hubo errores, guardo el registro
      // Not error found, store the registry
    
    { ## Paso las fechas a formato MySQL/GNU
      // Set the dates in MySQL/GNU format
     $fecha=fecha_mysql($fecha);

     $ip=get_ip();
     
     $planta=mysql_real_escape_string(html_entity_decode($_SESSION['PHD_TELEFONO'],ENT_QUOTES,"ISO-8859-1"));
     $ape_y_nom=mysql_real_escape_string(html_entity_decode($_SESSION['PHD_APE_Y_NOM'],ENT_QUOTES,"ISO-8859-1"));
     $incidente=mysql_real_escape_string(html_entity_decode($incidente,ENT_QUOTES,"ISO-8859-1"));
     
     ## verifico si hay adjunto y lo proceso
     // Check if there is a attach file and proccess it.

     if ( strlen($archivo)>1 )
            {$fp = fopen($archivo, "rb");
             $adjunto = fread($fp, $tamanio_adjunto);
             $adjunto = addslashes($adjunto);
             fclose($fp);
            }


     $query="INSERT INTO {$MyPHD}solicitud VALUES
             (NULL,
             '$fecha',
             '{$_SESSION['PHD_OPERADOR']}',
             '$ape_y_nom',
             '{$_SESSION['PHD_AREA_ID']}',
             '{$_SESSION['PHD_PISO']}',
             '{$_SESSION['PHD_E_MAIL']}',
             '{$_SESSION['PHD_TELEFONO']}',
             '$incidente',
             'PEN',
             null,
             '$ip',
             '$adjunto',
             '$tipo_adjunto',
             '$nombre_adjunto',
             '{$_SESSION['PHD_OPERADOR']}',
             NOW(),
             null,
             null)";

     $insert=mysql_query($query) or die (mysql_error());
     
      ## Levanto el número de solicitud para informarlo al usuario
     // Get the number of request to inform it to the user.

     $query="SELECT LAST_INSERT_ID() as seq_solicitud_id";
     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
     $_SESSION['PHD_SEQ_SOLICITUD_ID']=$row['seq_solicitud_id'];
    
     $send_alert_ur=send_alert_ur($row['seq_solicitud_id']);
     header("Location: $_SERVER[PHP_SELF]");
     //header("Location: user_request.php");
    }
?>
