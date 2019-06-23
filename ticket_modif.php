<?PHP
/*
    Nombre: ticket_modif.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Actualización de un ticket
    Function: Ticket update
    Ver: 2.12
*/

## Verifico que se encuentre validado el usuario, si no es asi lo
## dirijo a la pantalla de login.
// Verify that one is validated the user, if it is not therefore
// redirect to the screen of login.

session_start();
require('config.inc.php');
require($Include.'lang.inc');
require('funciones.inc.php');

if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<10)
    {include($Include.'login.inc');
     exit();
    }

## Me conecto con la base de datos
// Database connect

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());
$text_max_attach=conv_bytes($_SESSION[PHD_MAX_ATTACH]);

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

## Si esta seteada la variable $_POST['modificar'] o $_GET['modificar']
## busco los datos del ticket en la base.
// If is set the variables $_POST['modificar'] or $_GET['modificar']
// search for the data of the ticket in the database.

if (isSet($_POST['modificar']) or isSet($_GET['modificar']))
    {
    if(isSet($_POST['modificar']))
        {$seq_ticket_id=$_POST['modificar'];
        }
    else
        {$seq_ticket_id=$_GET['modificar'];
        }

    $query="SELECT {$MyPHD}ticket.*, {$MyPHD}operador.ape_y_nom as operador_ape_y_nom, NOW() as hora_leido,
                   {$MyPHD}area.nombre as nombre_area, COALESCE(seq_solicitud_id,0) as seq_solicitud_id
             FROM {$MyPHD}ticket
             INNER JOIN {$MyPHD}operador ON {$MyPHD}ticket.operador_id={$MyPHD}operador.operador_id
             LEFT JOIN {$MyPHD}area ON {$MyPHD}ticket.area_id={$MyPHD}area.area_id
             LEFT JOIN {$MyPHD}solicitud sol ON sol.seq_ticket_id={$MyPHD}ticket.seq_ticket_id
             WHERE {$MyPHD}ticket.seq_ticket_id=$seq_ticket_id AND $Filtro_ticket ";

     $result=mysql_query($query) or die (mysql_error());
     
     $row = mysql_fetch_array($result);

     ## Guardo en una variable global el número de ticket que estoy trabajando
     ## para que si se abre otra ventana con un ticket y se cambian los valores
     ## de los campos no me deje después guardar esta instancia, ya se me
     ## ocurrirá algo mejor para que trabajen las n ventanas.

     $_SESSION['ACT_PHD_SEQ_TICKET_ID']=$seq_ticket_id;

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
     
     ## Le doy forma al vector de los datos
     // Formating the data vector.

     foreach($row as $clave => $valor)
      {$row[$clave]=htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1");
      }

     ## inicializo las variables que voy a controlar si se modifican
     // Initializing the variables that going to control if there are changes.
     $piso=$_SESSION['PHD_PISO']=$row['piso'];
     $planta=$_SESSION['PHD_TELEFONO']=$row['planta'];
     $e_mail=$_SESSION['PHD_USER_E_MAIL']=$row['e_mail'];
     $proceso=$_SESSION['PHD_PROCESO']=$row['proceso'];
     $tipo=$_SESSION['PHD_TIPO']=$row['tipo'];
     $sub_tipo=$_SESSION['PHD_SUB_TIPO']=$row['sub_tipo'];
     $estado=$_SESSION['PHD_ESTADO']=$row['estado'];
     $prioridad=$_SESSION['PHD_PRIORIDAD']=$row['prioridad'];
     $asignado_a=$_SESSION['PHD_ASIGNADO_A']=$row['asignado_a'];
     $fecha_ultimo_estado=$_SESSION['PHD_FECHA_ULTIMO_ESTADO']=date("$Date_format H:i:s",strtotime($row['fecha_ultimo_estado']));
     $_SESSION['PHD_SEQ_SOLICITUD_ID']=$row['seq_solicitud_id'];
     
     if ($row[privado]=="S")
        {$privado=$_SESSION['PHD_PRIVADO']=$row[privado];
         $private_check="checked";
        }
     else
         {$privado=$_SESSION['PHD_PRIVADO']="N";
          $private_check="";
         }

     ## inicializo el resto de las variables
     // Initializing the rest of the variables.
     $seq_ticket_id=$row['seq_ticket_id'];
     $fecha=date("$Date_format H:i:s",strtotime($row['fecha']));
     $operador=$row['operador_id'];
     $nombre_area=$row['nombre_area'];
     $operador_ape_y_nom=$row['operador_ape_y_nom'];
     $operador_sector_id=$row['operador_sector_id'];
     $contacto=$row['contacto'];
     $usuario=$row['usuario_id'];
     $ape_y_nom=$row['ape_y_nom'];
     $area_id=$row['area_id'];
     $_SESSION['MOD_PHD_INCIDENTE']=str_replace(chr(10),"<br>",str_replace(chr(13),"",$row['incidente']));
     $nombre_adjunto=$row['nombre_adjunto'];
     $operador_ultimo_estado=$row['operador_ultimo_estado'];
    }

elseif (isset($_POST['adjunto'])) ## Veo si abre el adjunto
                                  // Check if open the attach
    {$query = "SELECT * FROM {$MyPHD}ticket WHERE seq_ticket_id=$_POST[seq_ticket_id]";
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
else ## inicializo las variables con lo que viene del formulario
     // Initializing the variables with the form data.
    { ## Verifico si esta seteado magic_quotes_gpt para sacar la barra invertida (\)
      // Check if magic_quotes_gpt is setting On for delete the slash (\)

     if (get_magic_quotes_gpc())
        { foreach($_POST as $clave => $valor)
            {$_POST[$clave]=stripslashes($_POST[$clave]);
            }
        }
     foreach($_POST as $clave => $valor)
         {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
         }

     $seq_ticket_id=$_POST['seq_ticket_id'];
     $fecha=$_POST['fecha'];
     $fecha_sigo=$_POST['fecha_sigo'];
     $operador=$_POST['operador'];
     $operador_ape_y_nom=$_POST['operador_ape_y_nom'];
     $operador_sector_id=$_POST['operador_sector_id'];
     $contacto=$_POST['contacto'];
     $ape_y_nom=$_POST['ape_y_nom'];
     $area_id=$_POST['area_id'];
     $piso=$_POST['piso'];
     $planta=$_POST['planta'];
     $e_mail=$_POST['e_mail'];
     $incidente=$_POST['incidente'];
     $comentario=$_POST['comentario'];
     $visible=$_POST['visible'];
     $prioridad=$_POST['prioridad'];
     $asignado_a=$_POST['asignado_a'];
     $proceso=$_POST['proceso'];
     $tipo=$_POST['tipo'];
     $nombre_adjunto=$_POST['nombre_adjunto'];
     $sub_tipo=$_POST['sub_tipo'];
     $estado=$_POST['estado'];
     $fecha_ultimo_estado=$_POST['fecha_ultimo_estado'];
     $operador_ultimo_estado=$_POST['operador_ultimo_estado'];
     $usuario=$_POST['usuario'];

     if ($_POST[privado]=="S")
          {$privado=$_POST[privado];
           $private_check="checked='checked'";
          }
     else
          {$privado="N";
           $private_check="";
          }

     if ($_POST[visible]=="S" and strlen($comentario)>0)
          {$visible=$_POST[visible];
           $visible_check="checked='checked'";
          }
     else
          {$visible="N";
           $visible_check="";
          }

     $s_archivo = $_FILES["sigo_adjunto"]["tmp_name"];
     $s_tamanio_adjunto = $_FILES["sigo_adjunto"]["size"];
     $s_tipo_adjunto = $_FILES["sigo_adjunto"]["type"];
     $s_nombre_adjunto = $_FILES["sigo_adjunto"]["name"];

     }

## Verfico que se haya ingresado por "guardar", si no es así muestro
## el formulario para ingresar la info del ticket.
// Verify that has been post 'guardar', if it is not thus  show
// the form to enter info of the ticket

if(!isSet($_POST['guardar']))
     {include($Include.'ticket_modif.inc');
	  exit();
	}

## Sector de validaciones de los campos ingresados
// validation of the inputs fields

if (strlen($e_mail)>0 and !preg_match('#^.+@.+\\..+$#',$e_mail)) ## Verifica el formato del e-mail
                                                         // verify the e-mail format
   	    {$mensaje.="<br /> $No_valid_e_mail";
	    }

if($s_tamanio_adjunto>$_SESSION[PHD_MAX_ATTACH]) // verifico que el tamaño del archivo adjunto no sea mayor a $_SESSION[PHD_MAX_ATTACH].
    { $Big_attach=str_replace("%1%",$text_max_attach,$Big_attach );
      $mensaje.="<br> $Big_attach";
    }
elseif (strlen($s_nombre_adjunto)>1 and $s_tamanio_adjunto<1) // valido que exista el archivo
        {$No_attach=str_replace("%1%"," $s_nombre_adjunto ",$No_attach );
         $mensaje=$mensaje."<br> $No_attach";
        }

if (strlen($asignado_a)==0 and $_SESSION['PHD_ASSIGN_TICKET']=="S")
       { $mensaje.="<br /> $No_assign";
       }


if (!fecha_valida($fecha_ultimo_estado))  ## Verfico que el formato de la fecha de ultimo estado sea válido
                                          // Verify the format of the last state date
    {$mensaje.="<br /> $No_valid_format_lsd";
    }

    elseif (strtotime(fecha_mysql($fecha))>strtotime(fecha_mysql($fecha_ultimo_estado)))
        {$mensaje=$mensaje."<br> $Lsd_lower_date";
        }

if (strlen($proceso)<1)
    {$mensaje.="<br /> $No_process ";
    }

if (strlen($tipo)<1)
    {$mensaje.="<br /> $No_type ";
    }

if ($privado=="S" and strlen($asignado_a)>0) ## Si es privado verifico que no se haya asignado a un operador de otro sector
                   // If is private verify that doesn't assigned to other sector operator.

     {$query="SELECT *
              FROM {$MyPHD}operador
              WHERE operador_id='$asignado_a'";

      $result=mysql_query($query) or die (mysql_error());
      $row = mysql_fetch_array($result);
      $aux_operador_sector_id=$row['sector_id'];
      
      if ($aux_operador_sector_id!=$_SESSION[PHD_SECTOR_ID])
            { $mensaje.="<br /> $Cant_assign_private";
            }
     }

## Valido que todavía sigan en $_SESSION los atributos del actual registro

if ($_SESSION['ACT_PHD_SEQ_TICKET_ID']!=$seq_ticket_id)
        {$Other_win_open=str_replace("%1%",$_SESSION['ACT_PHD_SEQ_TICKET_ID'],$Other_win_open );
          $mensaje="<br /> $Other_win_open";
        }
if (isSet($mensaje))  ## Hay errores, los muestro y no proceso el ticket
                      // There are errors, show it and don't proccess the ticket.
   {$mensaje="$UPR_error_found".$mensaje;
    include($Include.'ticket_modif.inc');
    exit();
   }
    

else  ## No hubo errores, verifico que no se haya actualizado el ticket mientras estuvo
      ## en pantalla.
      // were no errors, verify that the ticket has not been updated while it was in screen

     {$query="SELECT {$MyPHD}ticket.update_datetime, {$MyPHD}ticket.update_oper, {$MyPHD}operador.ape_y_nom
              FROM {$MyPHD}ticket, {$MyPHD}operador
              WHERE seq_ticket_id=$seq_ticket_id AND
              {$MyPHD}ticket.update_oper={$MyPHD}operador.operador_id";

      $result=mysql_query($query) or die (mysql_error());

      $row = mysql_fetch_array($result);
      $update_datetime=$row['update_datetime'];
      
      if ($_SESSION['PHD_HORA_LEIDO']<=$update_datetime) ## El registro se actualizó desde que lo
                                                         ## leí, no se puede guardar la actualización
                                                         // The record was updated after there was read,
                                                         // its not possible update it.

            {$mensaje="$Was_updated_1 {$row['update_oper']} - {$row['ape_y_nom']}, $Was_updated_2";
             include($Include.'ticket_modif.inc');
             exit();
            }


      ## verifico si hubo cambios y hago el update del ticket y guardo los datos para el seguimiento.
      // verify that were changes and do the update to the follow up of the ticket.

     ## Veo si hay adjunto y lo proceso
     // Check if has attach and proccess it.

     if ( strlen($s_archivo)>1 )
            {$fp = fopen($s_archivo, "rb");
             $s_adjunto = fread($fp, $s_tamanio_adjunto);
             $s_adjunto = addslashes($s_adjunto);
             fclose($fp);
            }

     $comentario=mysql_real_escape_string(html_entity_decode($comentario,ENT_QUOTES,"ISO-8859-1"));
     $fecha_sigo=fecha_mysql($fecha_sigo);
     $update="UPDATE {$MyPHD}ticket SET ";
     $result=mysql_query("START TRANSACTION") or die (mysql_error());

     if ($piso!=$_SESSION['PHD_PISO'])
        {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Floor',
                 '$_SESSION[PHD_PISO]',
                 '$piso',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
          $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
          $update.="piso='$piso', "; // agrego la línea para el update de ticket
        }

    if ($planta!=$_SESSION['PHD_TELEFONO'])
        { $planta=mysql_real_escape_string(html_entity_decode($planta,ENT_QUOTES,"ISO-8859-1"));
          $query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Phone',
                 '$_SESSION[PHD_TELEFONO]',
                 '$planta',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
          $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
          $update.="planta='$planta', "; // agrego la línea para el update de ticket
        }

    if ($e_mail!=$_SESSION['PHD_USER_E_MAIL'])
        { $e_mail=mysql_real_escape_string(html_entity_decode($e_mail,ENT_QUOTES,"ISO-8859-1"));
          $query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Elec_mail',
                 '$_SESSION[PHD_USER_E_MAIL]',
                 '$e_mail',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
          $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
          $update.="e_mail='$e_mail', "; // agrego la línea para el update de ticket
        }

    if ($prioridad!=$_SESSION['PHD_PRIORIDAD'])
        {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Priority',
                 '$_SESSION[PHD_PRIORIDAD]',
                 '$prioridad',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
          $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
          $update.="prioridad='$prioridad', "; // agrego la línea para el update de ticket
        }

    if ($asignado_a!=$_SESSION['PHD_ASIGNADO_A'])
        {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Assigned_to',
                 '$_SESSION[PHD_ASIGNADO_A]',
                 '$asignado_a',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
          $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
          $update.="asignado_a='$asignado_a', "; // agrego la línea para el update de ticket
          
          send_ticket($asignado_a,$seq_ticket_id,$Filtro_ticket,$e_mail,$ape_y_nom);

          ## Busco el sector asignado
          // Search the assigned sector

         $query="SELECT sector_id
                 FROM {$MyPHD}operador
                 WHERE operador_id='$asignado_a'";
         $result=mysql_query($query) or die (mysql_error());
         $row = mysql_fetch_array($result);
         $asignado_a_sector=$row['sector_id'];
         $update.="asignado_a_sector='$asignado_a_sector', "; // agrego la línea para el update de ticket
        }
        
    if ($privado!=$_SESSION['PHD_PRIVADO'])
        {if ($privado=="S")
            {$new_privado=$Yes;
             $old_privado=$No;
            }
         else
            {$new_privado=$No;
             $old_privado=$Yes;
            }

          $query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Private',
                 '$old_privado',
                 '$new_privado',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
          $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
          $update.="privado='$privado', "; // agrego la línea para el update de ticket
        }

    if ($proceso!=$_SESSION['PHD_PROCESO'])
        {if (strlen($_SESSION['PHD_PROCESO'])>0)
            {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Process',
                 '$_SESSION[PHD_PROCESO]',
                 '$proceso',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

              $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
              $insert=mysql_query($query) or die (mysql_error());
              $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
             }
         $update.="proceso='$proceso', "; // agrego la línea para el update de ticket
        }

    if ($tipo!=$_SESSION['PHD_TIPO'] )
        {if(strlen($_SESSION['PHD_TIPO'])>0)
            {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Type',
                 '$_SESSION[PHD_TIPO]',
                 '$tipo',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

             $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
             $insert=mysql_query($query) or die (mysql_error());
             $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
            }
         $update.="tipo='$tipo', "; // agrego la línea para el update de ticket
        }

    if ($sub_tipo!=$_SESSION['PHD_SUB_TIPO'])
        {if(strlen($_SESSION['PHD_TIPO'])>0)
            {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$Subtype',
                 '$_SESSION[PHD_SUB_TIPO]',
                 '$sub_tipo',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

              $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
              $insert=mysql_query($query) or die (mysql_error());
              $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
            }
           $update.="sub_tipo='$sub_tipo', "; // agrego la línea para el update de ticket
        }

    if ($estado!=$_SESSION['PHD_ESTADO'])
        {
          switch ($estado) {
              
              case 'Procesado':
              $estado_ = 'PAS';
              break;
              case 'Cancelado':
              $estado_ = 'CAN';
              break;
              case 'Pendiente':
              $estado_ = 'PEN';
              break;
              case 'Atendido':
              $estado_ = 'ATE';
              break;
          	}

          $update_="UPDATE {$MyPHD}solicitud SET estado='$estado_' WHERE seq_ticket_id=$seq_ticket_id;";
          $actualizo_=mysql_query($update_) or die (mysql_error());

          $query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 '$State',
                 '$_SESSION[PHD_ESTADO]',
                 '$estado',
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
          $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.
          $update.="estado='$estado', "; // agrego la línea para el update de ticket
          // Paso la fechas a formato MySQL/GNU
          $fecha_ultimo_estado=fecha_mysql($fecha_ultimo_estado);
          $update.="fecha_ultimo_estado='$fecha_ultimo_estado', "; // agrego la línea para el update de ticket

          $operador_ultimo_estado=$_SESSION[PHD_OPERADOR];

          $update.="operador_ultimo_estado='$operador_ultimo_estado', "; // agrego la línea para el update de ticket
        }

        elseif ($fecha_ultimo_estado!=$_SESSION['PHD_FECHA_ULTIMO_ESTADO'])
            {$query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                    (NULL,
                     $seq_ticket_id,
                     '$fecha_sigo',
                     '$_SESSION[PHD_OPERADOR]',
                     null,
                     '$Last_state_date',
                     '$_SESSION[PHD_FECHA_ULTIMO_ESTADO]',
                     '$fecha_ultimo_estado',
                     '$comentario',
                     '$visible',
                     '$s_adjunto',
                     '$s_tipo_adjunto',
                     '$s_nombre_adjunto',
                     '$_SESSION[PHD_OPERADOR]',
                     null,
                     NOW())";

              $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
              $insert=mysql_query($query) or die (mysql_error());
              $s_adjunto=$s_tipo_adjunto=$s_nombre_adjunto=$comentario='';  // Vacío el comentario y el adjunto para que no lo grabe varias veces.

              // Paso la fechas a formato MySQL/GNU
              $fecha_ultimo_estado=fecha_mysql($fecha_ultimo_estado);
              $update.="fecha_ultimo_estado='$fecha_ultimo_estado', "; // agrego la línea para el update de ticket
            }

// Verifico si comentario o el adjunto tienen contenido, si es así, los guardo

    if (strlen($comentario)>0 or strlen($s_nombre_adjunto)>0)
        { $query="INSERT INTO {$MyPHD}sigo_ticket VALUES
                (NULL,
                 $seq_ticket_id,
                 '$fecha_sigo',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 'Comentario',
                 null,
                 null,
                 '$comentario',
                 '$visible',
                 '$s_adjunto',
                 '$s_tipo_adjunto',
                 '$s_nombre_adjunto',
                 '$_SESSION[PHD_OPERADOR]',
                 null,
                 NOW())";

          $query=str_replace("''","null",$query);  // coloco null en los campos vacíos
          $insert=mysql_query($query) or die (mysql_error());
        }

// Verifico que se haya cambiado algún campo de "ticket" para hacer el update
// me doy cuenta porque aparece una coma en la variable $update

    $donde_hay_coma=strrpos($update,",");
    if ($donde_hay_coma>0)
        {$update.=" update_oper='$_SESSION[PHD_OPERADOR]', update_datetime=NOW() WHERE seq_ticket_id=$seq_ticket_id";
         $actualizo=mysql_query($update) or die (mysql_error());

        }
    $result=mysql_query("COMMIT") or die (mysql_error());
    if($visible=='S')
            {send_comment($seq_ticket_id,$Filtro_ticket);
            }
echo "<script language='JavaScript'>window.close();</script>";
   }


?>
