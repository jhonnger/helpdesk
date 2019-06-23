<?PHP
/*
    Nombre: solic_modif.php
    Autor: Julio Tuozzo 
    Función: Controlador de actualización de una solicitud de soporte
    Function: Support request update controller
    Ver: 2.12
*/

## Verifico que se encuentre validado el usuario, si no es asi lo
## dirijo a la pantalla de login.
// Verify that one is validated the user, if it is not therefore
// redirect to the screen of login.

session_start();
require('config.inc.php');
require($Include.'lang.inc');


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

if($_GET['op']=="user")
      {if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']!=4)
                {require($Include.'user_login.inc');
                 exit();
                }
       else
            {$op="?op=user";
            }
      }
elseif (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<10)
    {include($Include.'login.inc');
     exit();
    }


## Me conecto con la base de datos
// Database connect

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## Traigo las funciones PHP

require('funciones.inc.php');

$mensaje="";

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

## Busco los datos de la solicitud en la base.
// Search for the data of the request in the database.

if (isSet($_POST['modificar']))
    {$seq_solicitud_id=$_POST['modificar'];
     $query="SELECT s.*, a.nombre as nombre_area, NOW() as hora_leido
             FROM {$MyPHD}solicitud s
             LEFT JOIN {$MyPHD}area a ON s.area=a.area_id
             WHERE seq_solicitud_id=$seq_solicitud_id";

     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);

     ## Como la base de datos no maneja los lockeos para hacer el update,
     ## guardo el momento de lectura del registro y si al hacer el update
     ## esta hora es menor a la de update_datetime del registro quiere
     ## decir que hubo un cambio y no guarda las modificaciones de esta
     ## sesión.
     // As the data base does not handle the registry locks for update,
     // keep the date and time from reading of the registry and when doing
     // update his hour is smaller to the one of update_datetime of the registry
     // means that there was a change and does not keep the modifications from this session.

     $_SESSION['PHD_HORA_LEIDO']=$row['hora_leido'];
    }

elseif (isset($_POST['adjunto'])) ## Veo si abre el adjunto
                                  // Check if open the attach
    {$query = "SELECT * FROM {$MyPHD}solicitud WHERE seq_solicitud_id=$_POST[seq_solicitud_id]";
     $result = mysql_query($query);
     $row = mysql_fetch_array($result);
     $tipo_adjunto = $row['tipo_adjunto'];
     $adjunto = $row['adjunto'];
     $nombre_adjunto = $row['nombre_adjunto'];

     header("Content-type: $tipo_adjunto");
     header("Content-Disposition: attachment; filename=\"$nombre_adjunto\"");
     echo $adjunto;
     exit();

    }

else
    {$seq_solicitud_id=$_POST['seq_solicitud_id']; 
     $query="SELECT *
             FROM {$MyPHD}solicitud
             WHERE seq_solicitud_id=$seq_solicitud_id";
     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
    }

## inicializo las variables.
// Initializing the variables.

foreach($row as $clave => $valor)
     {$row[$clave]=trim(htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1"));
     }
$fecha=date("$Date_format H:i:s",strtotime($row['fecha']));
$usuario=$row['usuario_id'];
$ape_y_nom=$row['ape_y_nom'];
$area=$row['area'];
$nombre_area=$row['nombre_area'];
$incidente=$row['incidente'];
$e_mail=$row['e_mail'];
$piso=$row['piso'];
$planta=$row['planta'];
$estado=$row['estado'];
$seq_ticket_id=$row['seq_ticket_id'];
$insert_ip=$row['insert_ip'];
$adjunto = $row['adjunto'];
$tipo_adjunto = $row['tipo_adjunto'];
$nombre_adjunto = $row['nombre_adjunto'];

## Verfico que se haya ingresado por "actualizar", si no es así muestro
## el formulario con los datos de la solicitud.
// Verify that has been post 'actualizar', if it is not thus  show
// the form with the info of the request

if(!isSet($_POST['actualizar']) and !isSet($_POST['guardar']))
     {include($Include.'solic_modif.inc');
	  exit();
	}

## Verifico que no se haya actualizado el ticket mientras estuvo en pantalla.
// Verify that the ticket has not been updated while it was in screen

$query="SELECT sol.update_datetime, sol.update_oper, oper.ape_y_nom
         FROM {$MyPHD}solicitud sol, {$MyPHD}operador oper
         WHERE seq_solicitud_id=$seq_solicitud_id AND
         sol.update_oper=oper.operador_id";

$result=mysql_query($query) or die (mysql_error());

$row = mysql_fetch_array($result);
$update_datetime=$row['update_datetime'];
      
if ($_SESSION['PHD_HORA_LEIDO']<=$update_datetime) ## El registro se actualizó desde que lo
                                                         ## leí, no se puede guardar la actualización
                                                         // The record was updated after there was read,
                                                         // its not possible update it.

     {$mensaje="$Was_updated_1 {$row['update_user']} - {$row['ape_y_nom']}, $Was_updated_2";
      include($Include.'solic_modif.inc');
      exit();
     }

switch ($_POST['actualizar'])
    {case $Open_ticket:
        $estado="PAS";
        break;
     case "$Cancel $Request":
        $estado="CAN";
        break;
    }
    
//estado='$estado',
$update="UPDATE {$MyPHD}solicitud SET
              update_oper='$_SESSION[PHD_OPERADOR]',
              update_datetime=NOW()
              WHERE seq_solicitud_id=$seq_solicitud_id";

$actualizo=mysql_query($update) or die (mysql_error());

// Si la solicitud se pasa doy de alta el ticket y abro la ventana para
// modificarlo y poder hacer el seguimiento.


if (isSet($_POST['guardar']) and strlen($_POST['comentario'])>0)
        {$fecha=fecha_mysql(date("$Date_format H:i:s"));
         $comentario=mysql_real_escape_string(html_entity_decode($_POST['comentario'],ENT_QUOTES,"ISO-8859-1"));
         $query="INSERT INTO {$MyPHD}sigo_ticket VALUES
             (NULL,
              $seq_ticket_id,
             '$fecha',
             null,
             '$usuario',
             null,
             null,
             null,
             '$comentario',
             'S',
             null,
             null,
             null,
             null,
             '$usuario',
             NOW())";

        $insert=mysql_query($query) or die (mysql_error());
        $send_mail=send_alert_ur($seq_solicitud_id, $seq_ticket_id);
        $alert_mensaje="window.alert('$Comment_added');";
        }

elseif ($estado=="PAS")
     {$fecha=fecha_mysql(date("$Date_format H:i:s"));
      $operador=$_SESSION['PHD_OPERADOR'];
      $adjunto = mysql_real_escape_string(html_entity_decode($adjunto,ENT_QUOTES,"ISO-8859-1"));
      $planta=mysql_real_escape_string(html_entity_decode($planta,ENT_QUOTES,"ISO-8859-1"));
      $ape_y_nom=mysql_real_escape_string(html_entity_decode($ape_y_nom,ENT_QUOTES,"ISO-8859-1"));
      $incidente=mysql_real_escape_string(html_entity_decode($incidente,ENT_QUOTES,"ISO-8859-1"));

      $query="INSERT INTO {$MyPHD}ticket VALUES
             (NULL,
             '$fecha',
             'S',
             '$operador',
             '$_SESSION[PHD_SECTOR_ID]',
             'Web',
             '$usuario',
             '$ape_y_nom',
             '$area',
             '$piso',
             '$planta',
             '$e_mail',
             NULL,
             NULL,
             3,
             '$incidente',
             '$_SESSION[PHD_PROCESS_DEFAULT]',
             '',
             NULL,
             '$_SESSION[PHD_STATE_DEFAULT]',
             '$fecha',
             '$operador',
             '$adjunto',
             '$tipo_adjunto',
             '$nombre_adjunto',
             '$operador',
             DATE_SUB(NOW(), INTERVAL 1 SECOND),
             '$operador',
             DATE_SUB(NOW(), INTERVAL 1 SECOND))";

     $insert=mysql_query($query) or die (mysql_error());
     
     ## Levanto el número de ticket para guardarlo en la solicitud.
     // Get the number of ticket to store in the request.

     $query="SELECT LAST_INSERT_ID() as seq_ticket_id";
     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
     $seq_ticket_id=$row['seq_ticket_id'];

     $query="UPDATE {$MyPHD}solicitud
            SET seq_ticket_id=$seq_ticket_id
            WHERE seq_solicitud_id=$seq_solicitud_id";

     $update=mysql_query($query) or die (mysql_error());

     header("Location: ticket_modif.php?modificar=$seq_ticket_id");


    }

elseif ($estado=="CAN")
     {$fecha=fecha_mysql(date("$Date_format H:i:s"));
      $operador=$_SESSION['PHD_OPERADOR'];
      $adjunto = mysql_real_escape_string(html_entity_decode($adjunto,ENT_QUOTES,"ISO-8859-1"));
      $planta=mysql_real_escape_string(html_entity_decode($planta,ENT_QUOTES,"ISO-8859-1"));
      $ape_y_nom=mysql_real_escape_string(html_entity_decode($ape_y_nom,ENT_QUOTES,"ISO-8859-1"));
      $incidente=mysql_real_escape_string(html_entity_decode($incidente,ENT_QUOTES,"ISO-8859-1"));

      $query="INSERT INTO {$MyPHD}ticket VALUES
             (NULL,
             '$fecha',
             'S',
             '$operador',
             '$_SESSION[PHD_SECTOR_ID]',
             'Web',
             '$usuario',
             '$ape_y_nom',
             '$area',
             '$piso',
             '$planta',
             '$e_mail',
             NULL,
             NULL,
             3,
             '$incidente',
             '$_SESSION[PHD_PROCESS_DEFAULT]',
             '',
             NULL,
             'Cancelado',
             '$fecha',
             '$operador',
             '$adjunto',
             '$tipo_adjunto',
             '$nombre_adjunto',
             '$operador',
             DATE_SUB(NOW(), INTERVAL 1 SECOND),
             '$operador',
             DATE_SUB(NOW(), INTERVAL 1 SECOND))";

     $insert=mysql_query($query) or die (mysql_error());
     
     ## Levanto el número de ticket para guardarlo en la solicitud.
     // Get the number of ticket to store in the request.
/*
     $query="SELECT LAST_INSERT_ID() as seq_ticket_id";
     $result=mysql_query($query) or die (mysql_error());
     $row = mysql_fetch_array($result);
     $seq_ticket_id=$row['seq_ticket_id'];*/

     $query="UPDATE {$MyPHD}solicitud
            SET estado='$estado'
            WHERE seq_solicitud_id=$seq_solicitud_id";

     $update=mysql_query($query) or die (mysql_error());

     //header("Location: solic_list.php?pagina=1&q_registros=0&orden=seq_solicitud_id&sentido=ASC");


    }    

$control= "<script language='JavaScript'>
      $alert_mensaje
      window.close();</script>";

require($Include.'solic_modif.inc');

?>
