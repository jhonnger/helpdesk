<?PHP
/*
    Nombre: solic_modif.inc
    Autor: Julio Tuozzo
    Función: Vista de actualización / consulta de una solicitud de soporte
    Function: Support request update / consult view
    Ver: 2.00
*/


$ancho_guardar=26+(strlen($Save)*7);
$ancho_abrir=26+(strlen($Open_ticket)*7);
$ancho_cancelar=26+(strlen($Cancel." ".$Request)*7);
$ancho_cerrar=26+(strlen($Close)*7);
$ancho_agregar=26+(strlen($Add_comment)*7);

include('head.inc');

#Formateo el campo del incidente
// Formating the incident field

$disp_incidente=str_replace(chr(10),"<br>",str_replace(chr(13),"",$incidente));


## Inicio el formulario de solicitudes
// Start the request form.
echo
"<body>
    <a href='http://www.p-hd.com.ar'><img src='./images/phd_150_20.gif' border='0' alt='PHD Help Desk' /></a>
    <form name='solicitud' method='post' action='$_SERVER[PHP_SELF]$op'>
    <input type='hidden' name='seq_solicitud_id' value='$seq_solicitud_id'>
    <div style='margin:10px 0 10px 30px'>
    <h3>$Support_request: # $seq_solicitud_id</h3>
    <br />
    $Date: <b>$fecha</b>
    </div>
    <center class=error>$mensaje</center>

    <table class=borde_fino width='95%' cellpadding='2' cellspacing='1' align='center' >
     <tr>
      <td colspan='3'><b> $User_information </b></td>
     </tr>
     <tr>
      <td>
      $User: <b>$usuario</b> 
      </td>
      <td> $Last_and_first_name: <b>$ape_y_nom</b> </td>
      <td>$Area: <b>$area - $nombre_area</b></td>
     </tr>

     <tr>
          <td> $Floor: <b>$piso</b> </td>
          <td >$Phone: <b>$planta</b></td>
     </tr>
     <tr>
        <td colspan='2'>
        $Elec_mail: <b>$e_mail</b>
        </td>
        <td> IP: <b>$insert_ip</b>
        </td>
       </tr>
    </table>
    <br />

    <div style='margin:10px 30px 10px 30px'>
 
     <strong> $Reason_request: </strong> <br />
     <div style='padding:10px' class='caja_texto'> $disp_incidente </div> <br />";

     if (strlen($nombre_adjunto)>0)
             { echo "$Attached_file: &nbsp <strong>$nombre_adjunto</strong> &nbsp
               <input class='boton_bold' type='submit' value='$Download' name='adjunto'>
               <input type='hidden' name='nombre_adjunto' value='$nombre_adjunto'> <br /> <br />";
             }

$fecha_update=date("$Date_format H:i:s",strtotime($row['update_datetime']));
$fecha_insert=date("$Date_format H:i:s",strtotime($row['insert_datetime']));

      $query___="SELECT seq_sigo_ticket_id,nombre_adjunto FROM {$MyPHD}sigo_ticket WHERE seq_ticket_id=$seq_ticket_id order by seq_sigo_ticket_id desc";
      $result___=mysql_query($query___);
      $row___ = mysql_fetch_array($result___);
      $sigo_ticket_____=$row___['seq_sigo_ticket_id'];
      $sigo_ticket____=$row___['nombre_adjunto'];




if ($estado!="PAS")
{
     switch($estado)
            {case "PEN":
                     echo "$State: <p> <strong>{$_SESSION['PHD_PEN']} $By ({$row['insert_user']}) - $fecha_insert</strong>"; 
                     if (strlen($sigo_ticket____)>1)
                     {
                     echo " <input class='boton' type='button' name='s_adjunto' value='{$sigo_ticket____}' onClick='window.location=\"abro_adjunto.php?file={$sigo_ticket_____}\"' /></p>";
                     }
                     break;
             case "CAN":
                      echo "$State: <p> <strong>{$_SESSION['PHD_CAN']} $By ({$row['update_oper']}) - $fecha_update</strong>";
                      if (strlen($sigo_ticket____)>1)
                     {echo " <input class='boton' type='button' name='s_adjunto' value='{$sigo_ticket____}' onClick='window.location=\"abro_adjunto.php?file={$sigo_ticket_____}\"' /></p>";
                     }
                      break;
             case "ATE":
                      $query="SELECT *
                           FROM {$MyPHD}ticket
                           WHERE seq_ticket_id=$seq_ticket_id";

                   $result=mysql_query($query) or die (mysql_error());

                   $row = mysql_fetch_array($result);
                   $fecha_ultimo_estado=date("$Date_format H:i:s",strtotime($row['fecha_ultimo_estado']));
                   echo "<p><span class='error'>$Ticket_created: <strong># $seq_ticket_id</strong></span> <br>
                   $State:  <strong>{$_SESSION['PHD_ATE']} $By ({$row['update_oper']}) - $fecha_update</strong><br><br>";
                   if (strlen($sigo_ticket____)>1)
                     {echo " <input class='boton' type='button' name='s_adjunto' value='{$sigo_ticket____}' onClick='window.location=\"abro_adjunto.php?file={$sigo_ticket_____}\"' /></p>";
                     }
                      break;
            }
    }

else 
        {if($_SESSION['PHD_NIVEL']>5)
                 { echo "$State: <strong>{$_SESSION['PHD_PAS']} $By ({$row['update_oper']}) - $fecha_update</strong>
                   <div style='text-align:right; margin-right:20px'><p>";
                   ## Verifico si puede acceder al ticket o no.
                   // Verify that if cant access to the ticket or not.
           
                   $query="SELECT count(*) as cuantos
                           FROM {$MyPHD}ticket
                           WHERE seq_ticket_id=$seq_ticket_id AND $Filtro_ticket";

                   $result=mysql_query($query) or die (mysql_error());

                   $row = mysql_fetch_array($result);
                   if ($row['cuantos']>0)
                         { $ancho_editar=36+(strlen($seq_ticket_id)*7);
                           echo "$Ticket: <input class='boton_editar' style='width: {$ancho_editar}px;' type='button' value='# $seq_ticket_id' onclick=window.open('ticket_modif.php?modificar=$seq_ticket_id')>";
                         }
                   else
                         {echo "$Ticket: <strong># $seq_ticket_id</strong>";
                         }
                   if (strlen($sigo_ticket____)>1)
                     {echo " <input class='boton' type='button' name='s_adjunto' value='{$sigo_ticket____}' onClick='window.location=\"abro_adjunto.php?file={$sigo_ticket_____}\"' />";
                     }
                   echo "</p></div>";

                 }
           else
                 {$query="SELECT *
                           FROM {$MyPHD}ticket
                           WHERE seq_ticket_id=$seq_ticket_id";

                   $result=mysql_query($query) or die (mysql_error());

                   $row = mysql_fetch_array($result);
                   $fecha_ultimo_estado=date("$Date_format H:i:s",strtotime($row['fecha_ultimo_estado']));
                   echo "<p><span class='error'>$Ticket_created: <strong># $seq_ticket_id</strong></span>
                   <br>
                   $State: <strong>{$row['estado']}
                   $By ({$row['operador_ultimo_estado']}) - $fecha_ultimo_estado</strong>
                   ";
                   if (strlen($sigo_ticket____)>1)
                     {echo " <input class='boton' type='button' name='s_adjunto' value='{$sigo_ticket____}' onClick='window.location=\"abro_adjunto.php?file={$sigo_ticket_____}\"' /></p>";
                     }
                 }
         }


## Busco los comentarios de la solicitud
// Search the request comments

$query="SELECT tkt.*, ope.ape_y_nom as ope_ape_y_nom, usu.ape_y_nom as usu_ape_y_nom
        FROM {$MyPHD}sigo_ticket tkt
        LEFT JOIN {$MyPHD}operador ope ON tkt.operador_id=ope.operador_id
        LEFT JOIN {$MyPHD}usuario usu ON tkt.usuario_id=usu.usuario_id
        WHERE seq_ticket_id='$seq_ticket_id'
        AND visible='S' AND LENGTH(comentario)>0";

$result=mysql_query($query) or die (mysql_error());
$q_registros=mysql_num_rows($result);

if ($q_registros>0)
        {echo "<h3>$Comments</h3>";
        
         while($row = mysql_fetch_array($result))
                {foreach($row as $clave => $valor)
                        {$row[$clave]=trim(htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1"));
                        }
                 $fecha=date("$Date_format H:i:s",strtotime($row['fecha']));
                 $comentario=str_replace(chr(10),"<br>",str_replace(chr(13),"",$row['comentario']));
                 echo "<p>
                 <strong>$fecha</strong> $By ({$row['usuario_id']}{$row['operador_id']}) {$row['usu_ape_y_nom']}{$row['ope_ape_y_nom']}
                 <br />
                 <div style='padding:5px' class='caja_texto'> $comentario </div>
                 </p> ";
                }
        }

if (isset($_POST['comentario']))
        {$comentario="";
          echo "<br /><strong>$Comment:</strong> <br /> <textarea name='comentario' rows='5' cols='150'>$comentario</textarea>
         <script language='javascript'>
         document.solicitud.comentario.focus();
         </script>";
        }

    
echo "</div>

<br />
      <table border='0' cellspacing='1' cellpadding='2' width='90%'>
      <tr>";
      if ($estado=="PEN" and $_SESSION['PHD_NIVEL']>4)
          {echo "
              <td align='right'>
               <input class='boton_guardar' style='width: {$ancho_abrir}px;' type='submit' value='$Open_ticket' name='actualizar'>
              </td>
              <td align='right'>
               <input class='boton_cancelar' style='width: {$ancho_cancelar}px;' type='submit' value='$Cancel $Request' name='actualizar'>
              </td>
             ";
          }

      elseif ($estado=="PAS"  and $_SESSION['PHD_NIVEL']<5 and !isset($control))
          {if (isset($_POST['comentario']))
                {echo "<td align='right'>
                <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$Save' name='guardar'>
                </td>";
                }
           else
                {echo " 
                <td align='right'>
                <input class='boton_editar' style='width: {$ancho_agregar}px;' type='submit' value='$Add_comment' name='comentario'>
                </td>";
                }
           }
echo          "
              <td align='right'>
               <input class='boton_salir' style='width: {$ancho_cerrar}px;' type='button' value='$Close' onclick='window.close()'>
              </td>
             </tr>
           </table>
    </form>
$control
</body>
</html>";
?>

