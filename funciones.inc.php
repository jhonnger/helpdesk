<?PHP
/*
    Nombre: funciones.inc.php
    Autor: Julio Tuozzo
    Función: Funciones de uso común en PHP.
    Function: Functions of use common in PHP.
    Ver: 2.12
    
*/
## fecha_mysql (fecha en formato dd/mm/yyyy hh:mm:ss)
## pasa la fecha en formato español al formato de MySQL/GNU
## yyyy-mm-dd hh:mm:ss

// fecha_mysql (date in format dd/mm/yyyy hh:mm:ss)
// passes the date in spanish format to the format of MySQL/GNU
// yyyy-mm-dd hh:mm:ss

function fecha_mysql ($fecha)
    {if (fecha_valida($fecha))
          {switch ($_SESSION['PHD_DATE_FORMAT'])
                {case "DMA":
                     $fecha=substr($fecha,6,4).'-'.substr($fecha,3,2).'-'.substr($fecha,0,2).substr($fecha,10);
                     break;

                 case "MDA":
                    $fecha=substr($fecha,6,4).'-'.substr($fecha,0,2).'-'.substr($fecha,3,2).substr($fecha,10);
                     break;

                 case "AMD":
                    $fecha=substr($fecha,0,4).'-'.substr($fecha,5,2).'-'.substr($fecha,8,2).substr($fecha,10);
                    break;

                 default:
                     $fecha=substr($fecha,6,4).'-'.substr($fecha,3,2).'-'.substr($fecha,0,2).substr($fecha,10);
                }

          }
     else
          {$fecha="";
          }
     return $fecha;
    }
    
## fecha_valida (fecha en formato dd/mm/yyyy hh:mm:ss)
## valida si la fecha y la hora (si existe) tienen un formato
## válido.
// fecha_valida (date in format dd/mm/yyyy hh:mm:ss)
// been worth if the date and the hour (if it exists) have a valid format.

function fecha_valida($fecha_hora)
    {list($fecha, $hora)=explode(" ",$fecha_hora); ## separo la fecha de la hora.
                                                 // separate the date of the hour.

     if(strlen(trim($fecha))>10) ## La fecha y la hora no estaban separadas por espacio
        {return false;           // The date and the hour were not separated of space
        }

## controlo si la fecha tiene un formato válido y separo día, mes y anio en variables identificables
// date valid format control and separate day, month and anio in identifiable variables


     switch ($_SESSION['PHD_DATE_FORMAT'])
                {case "DMA":
                     if(!preg_match('#([0-9]{2})/([0-9]{2})/([0-9]{4})#', $fecha, $array_fecha))
                        {return false;
                        }
                     list($fecha, $dia, $mes, $anio)=$array_fecha;
                     break;

                 case "MDA":
                     if(!preg_match('#([0-9]{2})/([0-9]{2})/([0-9]{4})#', $fecha, $array_fecha))
                        {return false;
                        }
                     list($fecha, $mes, $dia, $anio)=$array_fecha;
                 break;

                 case "AMD":
                     if(!preg_match('#([0-9]{4})/([0-9]{2})/([0-9]{2})#', $fecha, $array_fecha))
                        {return false;
                        }
                     list($fecha, $anio, $mes, $dia)=$array_fecha;
                 break;

                 default:
                     if(!preg_match('#([0-9]{2})/([0-9]{2})/([0-9]{4})#', $fecha, $array_fecha))
                        {return false;
                        }
                     list($fecha, $dia, $mes, $anio)=$array_fecha;
                }

     if($mes<1 or $mes>12) ## valido el mes
        {return false;     // check the month
        }

## Valido los días de Febrero
// Been worth the days of February
    if(anio_bisiesto($anio))
        {$febrero=29;
        }
    else
        {$febrero=28;
        }

    if (($mes==2) and (($dia<1) or ($dia>$febrero)))
        {return false;
        }

## Valido los meses de 30 días
// Been worth the 30 days months

    if ((($mes==4) or ($mes==6) or ($mes==9) or ($mes==11)) and (($dia<1) or ($dia>30)))
        {return false;
      }

## Valido los meses de 31 días
// Been worth the 31 days months

    if ((($mes==1) or ($mes==3) or ($mes==5) or ($mes==7) or ($mes==8) or ($mes==10) or ($mes==12)) and (($dia<1) or ($dia>31)))
        {return false;
        }

## Me fijo si hay hora y la valido
// Been worth the hour
    if (strlen(trim($hora))>0)
        {if(!preg_match('#([0-9]{2}):([0-9]{2}):([0-9]{2})#', $hora, $array_hora))  // veo si la hora tiene un formato válido
            { return false;
            }

        }
    list($hora, $hor, $min, $seg)=$array_hora;  // separo horas, minutos y segundos en variables identificables

    if($hor<0 or $hor>23)  // valido la hora
        { return false;
        }

    if($min<0 or $min>59)  // valido los minutos
        { return false;
        }

    if($seg<0 or $seg>59)  // valido los segundos
        {return false;
        }

    return true;
    }

#### anio_bisiesto(año)
#### valida si un año es bisiesto o no

function anio_bisiesto($anio)
    {
    if ($anio % 4 != 0)
        {return false;
      }
    else
        {if ($anio % 100 == 0)
            {if ($anio % 400 == 0)
                {return true;
                }
              else
                    {return false;
                    }
            }
        else
            {return true;
            }
        }
    }

## conv_bytes($bytes)
## Convierte cantidad de bytes en Kb. o Mb.
// Convert amount of bytes in Kb. or Mb.

function conv_bytes($bytes)
    {if ($bytes>1000000)
          {$aux_bytes=intval($bytes/1000000);
           $text_bytes="$aux_bytes Mb.";
          }
      elseif ($bytes>1000)
          {$aux_bytes=intval($bytes/1000);
           $text_bytes="$aux_bytes Kb.";
          }
      else
          {$text_bytes="$bytes bytes";
          }
      return $text_bytes;
    }

## Variable con la condición para que los registros de la tabla 'ticket'
## se vean si no son privados o el operador es del sector
// Variable with the condition for the records of the table 'ticket' are
// visible when the ticket does not private or the operator belong
// to the sector of it.

$Filtro_ticket=" ({$MyPHD}ticket.privado='N' or {$MyPHD}ticket.operador_sector_id='$_SESSION[PHD_SECTOR_ID]') ";

## send_ticket ($operador, $seq_ticket_id, $filtro)
## Envia un correo con el ticket $seq_ticket_id a $operador.
// Send an e-mail with the $seq_ticket_id ticket to $operador

function send_ticket($operador,$seq_ticket_id,$filtro,$e_mail,$cc_nombre)

    {## Busco el registro del que le asignaron el ticket para ver si hay que
     ## avisarle por correo y levantar la dirección de e_mail
     // Search the assigned ticket to see if it's must to send the e-mail

    require('config.inc.php');
    require($Include.'lang.inc');

    $query="SELECT * from {$MyPHD}operador
             WHERE operador_id='$operador'
             AND avisar_asignado='S'";

    $result=mysql_query($query) or die (mysql_error());
    $q_filas=mysql_num_rows($result);

    if($q_filas!=1)
        {return false;
        }
    $row = mysql_fetch_array($result);
    $para=$row[e_mail];
    $copia = $e_mail;


    $ape_y_nom=$row['ape_y_nom'];

    $Alert_assign_head=str_replace("%1%", $seq_ticket_id,$Alert_assign_head );
    $Alert_assign_head=str_replace("%2%", $operador,$Alert_assign_head );
    $Alert_assign_head=str_replace("%3%", $row[ape_y_nom],$Alert_assign_head );

    $asunto=$Alert_assign_head;


    ## Busco el ticket
    // Search the ticket
    
    $query="SELECT * from {$MyPHD}ticket
             WHERE seq_ticket_id=$seq_ticket_id
             AND $filtro";
             

    $result=mysql_query($query) or die (mysql_error());
    $q_filas=mysql_num_rows($result);

    if($q_filas!=1)
        {return false;
        }

    $row = mysql_fetch_array($result);
    $fecha=date('d/m/Y H:i:s',strtotime($row['fecha']));

    ## Cuerpo del mensaje en HTML
    // HTML body message

    if (get_magic_quotes_gpc())
        { foreach($row as $clave => $valor)
            {$row[$clave]=stripslashes($row[$clave]);
            }
        }

    foreach($row as $clave => $valor)
        {$row[$clave]=trim(str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1"))));
        }

    $e_mensaje_html.="<p style=\"font-family: Helvetica, Arial, Sans-Serif; font-size:10pt; font-style:normal\">";
    $e_mensaje_html.="<b>$Ticket:</b> #$row[seq_ticket_id] &nbsp; &nbsp;  <b>$Date:</b> $fecha  &nbsp; &nbsp;  <b>$Area:</b> $row[area_id] &nbsp; &nbsp;  <b>$Floor:</b> $row[piso] <br />";
    $e_mensaje_html.="<b>$User:</b> ($row[usuario_id]) - $row[ape_y_nom] &nbsp; &nbsp;  <b>$Phone:</b> $row[planta] <br /> <br />";
    $e_mensaje_html.="<b>$Incident:</b> $row[incidente] <br /><br />";
    $e_mensaje_html.="<b><b><b>Su $Ticket:</b> #$row[seq_ticket_id] a sido asignado al Operador <br />" ;
    $e_mensaje_html.="<b>($operador)</b> - $ape_y_nom <br /><br />" ;

    ## Busco si hay cometarios en el ticket
    // Search if there are comments in the ticket

    /*$query_0="SELECT fecha, st.operador_id, o.ape_y_nom,usuario_id, comentario
              FROM {$MyPHD}sigo_ticket st inner join {$MyPHD}operador o on st.operador_id=o.operador_id
              WHERE seq_ticket_id=$seq_ticket_id
              ORDER BY seq_sigo_ticket_id";

    $result_0=mysql_query($query_0) or die (mysql_error());
    while ($row_0 = mysql_fetch_array($result_0))
            {//if (strlen($row_0[comentario])>0)
                //{ 
                    $b_fecha=date('d/m/Y H:i',strtotime($row_0['fecha']));
                    if (get_magic_quotes_gpc())
                        { foreach($row_0 as $clave => $valor)
                            {$row_0[$clave]=stripslashes($row_0[$clave]);
                            }
                        }

                    foreach($row_0 as $clave => $valor)
                        {$row_0[$clave]=trim(str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row_0[$clave],ENT_QUOTES,"ISO-8859-1"))));
                        }

                    //$e_mensaje_html.=wordwrap("<b>$b_fecha  - ($row_0[operador_id])</b> - $row_0[comentario] <br /><br />");
                    $e_mensaje_html.=wordwrap("<b>($row_0[operador_id])</b> - $row_0[ape_y_nom] <br /><br />");  
               // }
            }
*/
    // Envío el correo

    return send_e_mail($_SESSION['PHD_APE_Y_NOM'],$_SESSION['PHD_FROM_USER_REQUEST'],$ape_y_nom,$para,$asunto,$e_mensaje_html,$copia,$cc_nombre);
    
    
   }

## send_alert_ur($seq_solicitud_id, $seq_ticket_id=0)

## Envía un correo con los datos de la solicitud que se ha insertado a los
## operadores que tienen 'S' en aviso_solicitud
// Send an e-mail with the user request information to the operators that
// have the aviso_solitud field set on 'S'

function send_alert_ur($seq_solicitud_id, $seq_ticket_id=0)
    { require('config.inc.php');
      require($Include.'lang.inc');

     $query="SELECT * from {$MyPHD}operador
             WHERE nivel>0
             AND avisar_solicitud='S'";

    $result=mysql_query($query) or die (mysql_error());
    $q_filas=mysql_num_rows($result);

    if($q_filas<1)
        {return false;
        }

     $query="SELECT * from {$MyPHD}solicitud
             WHERE seq_solicitud_id=$seq_solicitud_id";

    $result_0=mysql_query($query) or die (mysql_error());
    $q_filas=mysql_num_rows($result_0);

    if($q_filas!=1)
        {return false;
        }

    if($seq_ticket_id>0)
            {$Alert_ticket_comment_subjet=str_replace("%1%", $_SESSION[PHD_OPERADOR],$Alert_ticket_comment_subjet);
             $Alert_ticket_comment_subjet=str_replace("%2%", $_SESSION[PHD_APE_Y_NOM],$Alert_ticket_comment_subjet);
             $subjet=str_replace("%3%", $seq_ticket_id,$Alert_ticket_comment_subjet);
            }
    else
            {$subjet=str_replace("%1%", $seq_solicitud_id,$Alert_user_request_subjet);
            }

    $row_0 = mysql_fetch_array($result_0);

    $fecha=date('d/m/Y H:i:s',strtotime($row_0['fecha']));

    foreach($row_0 as $clave => $valor)
        {$row_0[$clave]=trim(htmlentities($valor,ENT_QUOTES,"ISO-8859-1"));
        }
	$e_mensaje_html.="<p style=\"font-family: Helvetica, Arial, Sans-Serif; font-size:10pt; font-style:normal\">";
    $e_mensaje_html.="$Support_request: <strong>#$row_0[seq_solicitud_id]</strong>  <br /> $Date: <strong>$fecha</strong>  <br />
    $Area: <strong>$row_0[area]</strong>   $Floor: <strong>$row_0[piso]</strong> <br />";
    $e_mensaje_html.="$User: <strong>($row_0[usuario_id]) $row_0[ape_y_nom]</strong>    $Phone: <strong>$row_0[planta]</strong><br /><br />";
    $e_mensaje_html.="<strong>$Detail:</strong> $row_0[incidente] <br /><br /> </p>";

    ## Busco si hay cometarios en el ticket
    // Search if there are comments in the ticket


    $query_0="SELECT fecha, operador_id, usuario_id, comentario
              FROM {$MyPHD}sigo_ticket
              WHERE seq_ticket_id=$seq_ticket_id
              AND visible='S'
              ORDER BY seq_sigo_ticket_id";

    $result_0=mysql_query($query_0) or die (mysql_error());
    while ($row_0 = mysql_fetch_array($result_0))
            {if (strlen($row_0[comentario])>0)
                { $b_fecha=date('d/m/Y H:i',strtotime($row_0['fecha']));
                    if (get_magic_quotes_gpc())
                        { foreach($row_0 as $clave => $valor)
                            {$row_0[$clave]=stripslashes($row_0[$clave]);
                            }
                        }

                    foreach($row_0 as $clave => $valor)
                        {$row_0[$clave]=trim(str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row_0[$clave],ENT_QUOTES,"ISO-8859-1"))));
                        }

                    $e_mensaje_html.=wordwrap("<b>$b_fecha  - ({$row_0['operador_id']}{$row_0['usuario_id']})</b> - $row_0[comentario] <br /><br />");
                }
            }

    // Send mail
    // Envió el correo

    while ($row = mysql_fetch_array($result))
            {$mandar_mail=send_e_mail("Help Desk Grupo Carita Feliz",$_SESSION['PHD_FROM_USER_REQUEST'],$row['ape_y_nom'],$row['e_mail'],$subjet,$e_mensaje_html,'','');
            }
    return $mandar_mail;   }

## send_comment($seq_ticket_id)

## Envía un correo al usuario con el comentario que haya agregado el operador
// Send an e-mail to the user with the operator comment added


function send_comment($seq_ticket_id,$filtro)

    { require('config.inc.php');
      require($Include.'lang.inc');

    $query_="SELECT * from {$MyPHD}ticket
             WHERE seq_ticket_id=$seq_ticket_id
             AND $filtro";

    $result_=mysql_query($query_) or die (mysql_error());
    
    $row_ = mysql_fetch_array($result_);
    
        $fecha=date('d/m/Y H:i:s',strtotime($row_['fecha']));
        /*$e_mensaje_html="<html>
                        <head>
                          <meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1'>
                        </head>";*/
       	$e_mensaje_html.="<p style=\"font-family: Helvetica, Arial, Sans-Serif; font-size:10pt; font-style:normal\">";
        $e_mensaje_html="<b>$Ticket:</b> #$row_[seq_ticket_id] &nbsp; &nbsp;  <b>$Date:</b> $fecha  &nbsp; &nbsp;  <b>$Area:</b> $row_[area_id] &nbsp; &nbsp;  <b>$Floor:</b> $row_[piso] <br />";
        $e_mensaje_html.="<b>$User:</b> ($row_[usuario_id]) - $row_[ape_y_nom] &nbsp; &nbsp;  <b>$Phone:</b> $row_[planta] <br/>";


        $query_ = "SELECT * FROM {$MyPHD}solicitud WHERE seq_ticket_id=$row_[seq_ticket_id]";
	    $result_=mysql_query($query_) or die (mysql_error());
	    $row_1 = mysql_fetch_array($result_);
	    
	    $fecha_update=date("$Date_format H:i:s",strtotime($row_1[update_datetime]));
		$fecha_insert=date("$Date_format H:i:s",strtotime($row_1[insert_datetime]));
		$estado = $row_1[estado];

		if ($estado!="PAS")
		{
		        switch($estado)
		        {
		          case "PEN":
		                 $e_mensaje_html.= "<strong>$State:  {$_SESSION[PHD_PEN]} $By ({$row_1[update_oper]}) - $fecha_insert</strong><br /><br />";
		                 break;
		         case "CAN":
		                  $e_mensaje_html.= "<strong>$State:  {$_SESSION[PHD_CAN]} $By ({$row_1[update_oper]}) - $fecha_update</strong><br /><br />";
		                  break;
		         case "ATE":
		                  $query__="SELECT *
		                       FROM {$MyPHD}ticket
		                       WHERE seq_ticket_id=$row_[seq_ticket_id]";

		               $result__=mysql_query($query__) or die (mysql_error());

		               $row_1___ = mysql_fetch_array($result__);
		               $fecha_ultimo_estado=date("$Date_format H:i:s",strtotime($row_1___[fecha_ultimo_estado]));
		               $e_mensaje_html.= "<strong>$State:  {$_SESSION[PHD_ATE]} $By ({$row_1___[update_oper]}) - $fecha_update</strong><br/><br/>";
		                  break;
		        }
		}
		else//procesado
		{
	         $query___="SELECT *
	                   FROM {$MyPHD}ticket
	                   WHERE seq_ticket_id=$row_[seq_ticket_id]";

	           $result___=mysql_query($query___) or die (mysql_error());

	           $row_1__ = mysql_fetch_array($result___);
	           $fecha_ultimo_estado=date("$Date_format H:i:s",strtotime($row_1__[fecha_ultimo_estado]));
	           $e_mensaje_html.= "<strong>$State: {$row_1__[estado]} $By ({$row_1__[operador_ultimo_estado]}) - $fecha_ultimo_estado</strong><br /><br />";
		 }


        $e_mensaje_html.="<br /><b>$Incident:</b> $row_[incidente] <br /><br />";
        /*$e_mensaje_html.= "<b></b> <hr> <br/><br />"; */
    
//st.*, op.ape_y_nom, op.e_mail as op_email 
     $query_="SELECT st.operador_id as operador_id, st.fecha as fecha_, st.comentario as comentario, op.ape_y_nom as ape_y_nom, op.e_mail as op_email 
             FROM {$MyPHD}sigo_ticket st
             INNER JOIN {$MyPHD}operador op ON op.operador_id=st.operador_id
             WHERE st.visible='S'
             AND LENGTH(st.comentario)>1
             AND st.seq_ticket_id=$seq_ticket_id";
             
    $result_=mysql_query($query_) or die (mysql_error());
    $q_filas_=mysql_num_rows($result_);

    if($q_filas_<1)
        {return false;
        }

        $comentario_html="<br />$e_mensaje_html";

    while ($row_ = mysql_fetch_array($result_))
            {
                $operador_id_ = $row_['operador_id'];
                $ape_y_nom_ = $row_['ape_y_nom'];
                $fecha_ = $row_['fecha_'];

             /*$Comment_added_by=str_replace("%1%","({$row['operador_id']}) {$row['ape_y_nom']}", $Comment_added_by);
             $Comment_added_by=str_replace("%2%",date('d/m/Y',strtotime($row['fecha'])), $Comment_added_by);
             $Comment_added_by=str_replace("%3%",date('H:i',strtotime($row['fecha'])), $Comment_added_by);*/

             //$Comment_added_by = "Comentario agregado por ($row['operador_id']) $row['ape_y_nom'], el $row['fecha'] :");

             $comentario_html_=trim(str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row_['comentario'],ENT_QUOTES,"ISO-8859-1"))));
             $comentario_html.="<strong>Comentario agregado por ($operador_id_) $ape_y_nom_, el ".date('d/m/Y',strtotime($fecha_))." a las ".date('H:i',strtotime($fecha_))." : </strong><br /> $comentario_html_<br /> ";

             $e_mail_from=$row_['op_email'];
             $from_ape_y_nom=$row_['ape_y_nom'];
            }


     $query="SELECT tk.*, sol.seq_solicitud_id 
	 		 FROM {$MyPHD}solicitud sol
	 		 JOIN {$MyPHD}ticket tk ON tk.seq_ticket_id=sol.seq_ticket_id
             WHERE tk.seq_ticket_id=$seq_ticket_id";

     $result=mysql_query($query) or die (mysql_error());
     $q_filas=mysql_num_rows($result);

     $row = mysql_fetch_array($result);

     if($q_filas!=1 or !preg_match('#^.+@.+\\..+$#',$row['e_mail']))
         {return false;
         }

    $Alert_comment_subject=str_replace("%1%", $row['seq_solicitud_id'],$Alert_comment_subjet);

    //$comentario_html. = "</HTML>";
    return send_e_mail($from_ape_y_nom,$_SESSION['PHD_FROM_USER_REQUEST'],$row['ape_y_nom'],$row['e_mail'], $Alert_comment_subject,$comentario_html,'','');
        
    }


function send_e_mail($from_ape_y_nom,$from_e_mail,$to_ape_y_nom,$to_e_mail, $subject,$body,$copia,$cc_nombre)

    { require('config.inc.php');
    require_once('class.phpmailer.php');
      /*if(!class_exists("PHPMailer"))
	  		{require('class.phpmailer.php');
	  		}*/
	//$body="<div style='text-align:left'><img style='text-align:left' src='/images/phd_400_55.gif' alt='GRUPO CARITA FELIZ' border=0 /></div><br /><br />".$body;

    // Send mail

    $mail = new PHPMailer();
    $mail->IsSMTP();
    $mail->IsHTML(true);
    $mail->SMTPDebug = 0;
    $mail->SMTPAuth = true;
    $mail->SMTPSecure = "ssl";
    $mail->Host = $Mail_host;
    $mail->Port = $Mail_port;
    $mail->Username = $Mail_usuario;
    $mail->Password = $Mail_clave;
    $mail->SetFrom($from_e_mail, 'Help Desk Grupo Carita Feliz');
    //$mail->AddReplyTo($to_e_mail, $to_ape_y_nom);
    $mail->Subject = $subject;
    //$mail->MsgHTML($body);.
    $mail->Body= $body;
    //$address = $to_e_mail;
    $mail->AddAddress($to_e_mail, $to_ape_y_nom);
    $mail->AddCC($copia, $cc_nombre);

    if ($mail->Send())
        {return "";
        }
    else
        { ## Guardo el error de envío de correo
          // Save the e-mail send error
          
          $body=mysql_real_escape_string(html_entity_decode($body,ENT_QUOTES,"ISO-8859-1"));
          $error=mysql_real_escape_string(html_entity_decode($mail->ErrorInfo,ENT_QUOTES,"ISO-8859-1"));
          $query="INSERT INTO e_mail_error VALUES
                  (NOW(),
                   '$from_ape_y_nom',
                   '$from_e_mail',
                   '$to_ape_y_nom',
                   '$to_e_mail',
                   '$subject',
                   '$body',
                   '$error')";
                   
          $insert=mysql_query($query) or die (mysql_error());
          return $mail->ErrorInfo;
        }

    
    }


## Función que genera las contraseñas
// Function that generates the passwords

function generapwd($largo=8)

    {## inicializo variables
     $caracteres = "123456789123456789abcdefghijklmnopqrstuvwxyz";
     $contrasenia = "";

     ## Inicializo para rand
     srand ((double) microtime() * 1000000);

     ## Genero la contraseña
     while ( $largo )
        {$contrasenia .= substr( $caracteres, rand( 0, strlen( $caracteres )), 1);
         $largo--;
        }

        return( $contrasenia );
        }


?>
