<?PHP
/*
    Nombre: ticket_insert.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Ingreso de ticket en la base de datos
    Function: Insert ticket in the data base.
    Ver: 2.12
*/

## Verifico que se encuentre validado el usuario, si no es asi lo
## dirijo a la pantalla de login.
// Verify that one is validated the user, if it is not therefore
// redirect to the screen of login.

session_start();
require('config.inc.php');
require($Include.'lang.inc');
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

## Traigo las funciones PHP.
// Get PHP functions.

require('funciones.inc.php');

## Inicializo las variables del formulario.
// Inicialized the variables of the form.

$text_max_attach=conv_bytes($_SESSION[PHD_MAX_ATTACH]);

$operador=$_SESSION['PHD_OPERADOR'];
$operador_ape_y_nom=$_SESSION['PHD_APE_Y_NOM'];

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

if(!isset($_POST['contacto']))
    {$contacto=$_SESSION['PHD_CONTACT_DEFAULT'];
    }
else
    {$contacto=$_POST['contacto'];
    }
$fecha=$_POST['fecha'];
$usuario=$_POST['usuario'];
$ape_y_nom=$_POST['ape_y_nom'];
$area_id=$_POST['area_id'];
$piso=$_POST['piso'];
$e_mail=$_POST['e_mail'];
$planta=$_POST['planta'];
$incidente=$_POST['incidente'];
$comentario=$_POST['comentario'];
$asignado_a=$_POST['asignado_a'];

if (!isSet($_POST['proceso']))
    {$proceso=$_SESSION['PHD_PROCESS_DEFAULT'];
    }
else
    {$proceso=$_POST['proceso'];
    }

$tipo=$_POST['tipo'];
$sub_tipo=$_POST['sub_tipo'];

if (!isSet($_POST['prioridad']))
    {$prioridad=3;
     $private_check="checked"; // Aquí detecto que el formulario esta en blanco e inicializo el ticket como privado
    }
else
    {$prioridad=$_POST['prioridad'];}


if ($_POST[privado]=="S")
     {$privado=$_POST[privado];
      $private_check="checked";
     }
elseif (!isset($private_check))
     {$privado="N";
      $private_check="";
     }


if (!isSet($_POST['estado']))
    {$estado=$_SESSION['PHD_STATE_DEFAULT'];}
else
    {$estado=$_POST['estado'];}


$fecha_ultimo_estado=$_POST['fecha_ultimo_estado'];
$operador_ultimo_estado=$operador;
$archivo = $_FILES["adjunto"]["tmp_name"];
$tamanio_adjunto = $_FILES["adjunto"]["size"];
$tipo_adjunto = $_FILES["adjunto"]["type"];
$nombre_adjunto = $_FILES["adjunto"]["name"];

## Verfico que se haya ingresado por "submit"", si no es así muestro
## el formulario para ingresar la info del ticket.
// Verfy that has entered by “submit "", if it is not thus show
// the form to enter info of the ticket.

if(!isSet($_POST['guardar']))
     {require($Include.'ticket_insert.inc');
	  exit();
	 }

//echo "olvidÃ© contraseÃ±a";
//echo $incidente;
//echo "olvidó";
//exit();

## Sector de validaciones de los campos ingresados
// Sector of validations of the entered fields

if (strlen($contacto)==0) ## Verifico que haya ingresado la forma de contacto
                         // Verify that the contact way was entered
   {$mensaje.="<br> $No_contact";
   }


if (strlen($usuario)==0) ## Verifico que haya ingresado el usuario
                         // Verify that the user has entered
   {$mensaje.="<br> $No_user";
   }

if (strlen($ape_y_nom)==0) ## Verifico que haya ingresado el apellido y nombre
                           // Verify that the last name and name has entered
   {$mensaje.="<br> $No_last_name";
   }

if (strlen($area_id)==0) ## Verifico que haya ingresado el area
                      // Verify that the area has entered
   {$mensaje.="<br> $No_area";
   }

if (strlen($e_mail)>0 and !preg_match('#^.+@.+\\..+$#',$e_mail)) ## Verifico el formato del e-mail
                                                         // verify the e-mail format
   	    {$mensaje.="<br /> $No_valid_e_mail";
	    }

if (strlen($incidente)==0) ## Verifico que haya ingresado el incidente
                           // Verify that the incident has entered
   {$mensaje.="<br> $No_incident";
   }

if($tamanio_adjunto>$_SESSION['PHD_MAX_ATTACH']) // verifico que el tamaño del archivo adjunto no sea mayor a $_SESSION[PHD_MAX_ATTACH].
    { $Big_attach=str_replace("%1%",$text_max_attach,$Big_attach );
      $mensaje.="<br> $Big_attach";
    }
elseif (strlen($nombre_adjunto)>1 and $tamanio_adjunto<1) // valido que exista el archivo
        {$No_attach=str_replace("%1%"," $nombre_adjunto ",$No_attach );
         $mensaje=$mensaje."<br> $No_attach";
        }

if (strlen($asignado_a)==0 and $_SESSION['PHD_ASSIGN_TICKET']=="S")
       { $mensaje.="<br /> $No_assign";
       }


if ($privado=="S" and strlen($asignado_a)>0) ## Si es privado verifico que no se haya asignado a un operador de otro sector
                   // If is private verify that doesn't assigned to other sector operator.

     {$query="SELECT *
              FROM {$MyPHD}operador
              WHERE operador_id='$asignado_a'";

      $result=mysql_query($query) or die (mysql_error());
      $row = mysql_fetch_array($result);
      $operador_sector_id=$row['sector_id'];

      if ($operador_sector_id!=$_SESSION[PHD_SECTOR_ID])
            { $mensaje.="<br /> $Cant_assign_private";
            }
     }
     
if (strlen($proceso)==0) ## Verifico que haya ingresado el proceso
                      // Verify that the process has entered
   {$mensaje.="<br> $No_process";
   }

if (strlen($tipo)==0) ## Verifico que haya ingresado el tipo
                      // Verify that the type has entered
   {$mensaje.="<br> $No_type";
   }

if (strlen($estado)==0) ## Verifico que haya ingresado estado
                      // Verify that the state has entered
   {$mensaje.="<br> $No_state";
   }


if (!fecha_valida($fecha_ultimo_estado))  ## Verfico que el formato de la fecha de ultimo estado sea válido
                                          // Verify that the last state date format is valid.
    {$mensaje.="<br> $No_valid_format_lsd";
    }

elseif (strtotime(fecha_mysql($fecha))>strtotime(fecha_mysql($fecha_ultimo_estado)))
    {$mensaje.="<br> $Lsd_lower_date";
    }

if (isSet($mensaje))  ## Hay errores, los muestro y no proceso el ticket
                      // Error found, show the errors and doesn´t procces the ticket
   {$mensaje=$UPR_error_found.$mensaje;
    require($Include.'ticket_insert.inc');
    exit();
   }
    

else  ## No hubo errores, guardo el registro
      // Not error found, store the registry
    
    { ## Paso las fechas a formato MySQL/GNU
      // Set the dates in MySQL/GNU format
     $fecha=fecha_mysql($fecha);
     $fecha_ultimo_estado=fecha_mysql($fecha_ultimo_estado);

     ## paso las entidades html a caracter
     // Convert the html entities to character
     
     $planta=mysql_real_escape_string(html_entity_decode($planta,ENT_QUOTES,"ISO-8859-1"));
     $ape_y_nom=mysql_real_escape_string(html_entity_decode($ape_y_nom,ENT_QUOTES,"ISO-8859-1"));
     $incidente=mysql_real_escape_string(html_entity_decode($incidente,ENT_QUOTES,"ISO-8859-1"));
     $comentario=mysql_real_escape_string(html_entity_decode($comentario,ENT_QUOTES,"ISO-8859-1"));
     
     ## Busco el sector asignado
     // Search the assigned sector
     
     if (strlen($asignado_a)>0)
        {$query="SELECT sector_id
                FROM {$MyPHD}operador
                WHERE operador_id='$asignado_a'";
        $result=mysql_query($query) or die (mysql_error());
        $row = mysql_fetch_array($result);
        $asignado_a_sector=$row['sector_id'];
        }

     ## verifico si hay adjunto y lo proceso
     // Check if there is a attach file and proccess it.

     if ( strlen($archivo)>1 )
            {$fp = fopen($archivo, "rb");
             $adjunto = fread($fp, $tamanio_adjunto);
             $adjunto = addslashes($adjunto);
             fclose($fp);
            }

     $result=mysql_query("START TRANSACTION") or die (mysql_error());
     
     $query="INSERT INTO {$MyPHD}ticket VALUES
             (NULL,
             '$fecha',
             '$privado',
             '$operador',
             '$_SESSION[PHD_SECTOR_ID]',
             '$contacto',
             '$usuario',
             '$ape_y_nom',
             '$area_id',
             '$piso',
             '$planta',
             '$e_mail',
             '$asignado_a',
             '$asignado_a_sector',
             '$prioridad',
             '$incidente',
             '$proceso',
             '$tipo',
             '$sub_tipo',
             '$estado',
             '$fecha_ultimo_estado',
             '$operador_ultimo_estado',
             '$adjunto',
             '$tipo_adjunto',
             '$nombre_adjunto',
             '$operador',
             NOW(),
             '$operador',
             NOW())";

     $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
     $insert=mysql_query($query) or die (mysql_error());

     ## Levanto el número de ticket para informarlo al operador.
     // Get the number of ticket to inform it to the operator.

     $query="SELECT LAST_INSERT_ID() as seq_ticket_id";
     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
     $_SESSION['PHD_SEQ_TICKET_ID']=$seq_ticket_id=$row['seq_ticket_id'];
     
     if (strlen($comentario)>1) ## Hay un comentario, se abre el seguimiento
                                // There is a comment, it's open a follow up

        {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 NOW(),
                 '$operador',
                 null,
                 NULL,
                 NULL,
                 NULL,
                 '$comentario',
                 '$visible',
                 NULL,
                 NULL,
                 NULL,
                 '$operador',
                 null,
                 NOW())";
         $insert=mysql_query($query) or die (mysql_error());
        }

     $result=mysql_query("COMMIT") or die (mysql_error());
           
     $query="INSERT INTO {$MyPHD}solicitud VALUES
             (NULL,
             '$fecha',
             '$usuario',
             '$ape_y_nom',
             '$area_id',
             '$piso',
             '$e_mail',
             '$planta',
             '$incidente',
             'PEN',
             '$seq_ticket_id',
             '',
             '$adjunto',
             '$tipo_adjunto',
             '$nombre_adjunto',
             '$operador',
             NOW(),
             '$operador',
             NOW())";

     $insert=mysql_query($query) or die (mysql_error());

     send_ticket($asignado_a,$seq_ticket_id,$Filtro_ticket,$e_mail,$ape_y_nom);

     ## Verifico si el ticket esta asignado para mandar aviso a quien se lo asignaron.
     // Check if the ticket was assined to send an e-mail to the assigned operator.
     
     /*if (strlen($asignado_a)>0)
        { send_ticket($asignado_a,$seq_ticket_id,$Filtro_ticket);
        }*/

        header("Location: ticket_insert.php");
    }
?>
