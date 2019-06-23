<?PHP
/*
    Nombre: solic_list.inc
    Autor: Julio Tuozzo 
    Función: Lista de solicitudes por pantalla
    Function: screen request list.
    Ver: 2.00

*/

## Calculo desde que registro muestro en función de la página
// Calculate since registry show based on the page.

$desde_reg=($pagina-1)*$_SESSION[PHD_MAX_LINES_SCREEN];

## Hago la consulta
// make query

$query="SELECT seq_solicitud_id, fecha, usuario_id, ape_y_nom, area, incidente, estado, planta, e_mail
        FROM {$MyPHD}solicitud WHERE
        $condicion ORDER BY $orden $sentido LIMIT $desde_reg, $_SESSION[PHD_MAX_LINES_SCREEN]";
//echo $query;

$result=mysql_query($query) or die (mysql_error());


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


$_aux_estado="$_SESSION[PHD_SOL_ESTADO]"."_sel";
$$_aux_estado="selected";


/*
    Nombre: head.inc
    Autor: Julio Tuozzo
    Función: HEAD de las páginas
    Function: Page's Head.
    Ver: 1.43

*/

echo
"<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Transitional//EN' 'http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd'>
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='en' lang='en'>
<head>
  <meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1'>
  <meta http-equiv='refresh' content='30' />
  <title>PHD Help Desk &nbsp; ($_SESSION[PHD_OPERADOR]) - $_SESSION[PHD_APE_Y_NOM] / $_SESSION[PHD_SECTOR_ID] </title>
  <LINK REL=STYLESHEET TYPE='text/css' HREF='phd.css' TITLE='estilo'>
  <link rel='shortcut icon' href='favicon.ico' />
  $frames
</head> \n";



echo "<body>";
require($menu);
echo"<div id='contenido'>
<form method='post' action='$_SERVER[PHP_SELF]?dummy=foo$op_user' >

        $Support_request # <input type='text' name='seq_solicitud_id' value='$_SESSION[PHD_SEQ_SOLICITUD_ID]' size='6' maxlength='6'> &nbsp; &nbsp;
        $State: <select name='estado'>
           
           <option $ATE_sel value='ATE'> {$_SESSION['PHD_ATE']}
           <option $PEN_sel value='PEN'> {$_SESSION['PHD_PEN']}
           <option $PAS_sel value='PAS'> {$_SESSION['PHD_PAS']}
           <option $CAN_sel value='CAN'> {$_SESSION['PHD_CAN']}
        </select>
        &nbsp; &nbsp;
        $Input_date $From: <INPUT type='text' name='fecha_desde' value='$_SESSION[PHD_SOL_FECHA_DESDE]' size='10' maxlength='10' > ($Date_text) &nbsp; &nbsp;

     $To: <input type='text' name='fecha_hasta' value='$_SESSION[PHD_SOL_FECHA_HASTA]' size='10' maxlength='10' > ($Date_text)

    &nbsp; &nbsp; &nbsp; &nbsp; <input class='boton_lupa' type='submit' value='' name='buscar' style='width: 30px; cursor:pointer' >
    </form>
    <div class=error> $mensaje </div>
    <hr>";

include('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>

echo "

   <form method='post' action='solic_modif.php?dummy=foo$op_user' target='_blank'>

    <table border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
 	 <th nowrap='nowrap'> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=seq_solicitud_id&sentido=$sen_seq_solicitud_id$op_user>$Request </a> $arr_seq_solicitud_id
	 <th nowrap='nowrap'> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=fecha&sentido=$sen_fecha$op_user>$Date</a> $arr_fecha";

if($_GET['op']!="user")
      {

     echo "<th nowrap='nowrap'> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=usuario_id&sentido=$sen_usuario_id$op_user>$User</a> $arr_usuario_id
	       <th nowrap='nowrap'> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=ape_y_nom&sentido=$sen_ape_y_nom$op_user>$Last_and_first_name</a> $arr_ape_y_nom
	       <th nowrap='nowrap'> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=area&sentido=$sen_area$op_user>$Area</a> $arr_area";

      }

echo   "<th nowrap='nowrap'> $Reason_request
	 <th nowrap='nowrap'> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=estado&sentido=$sen_estado$op_user>$State</a> $arr_estado
    </tr>";


    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $J=0;
    while ($row = mysql_fetch_array($result))
	{ $J++;
	  $Col=$J % 2;
	  $fecha=date("$Date_format H:i:s",strtotime($row['fecha']));
	  
	  $incidente=str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row['incidente'],ENT_QUOTES,"ISO-8859-1")));


      switch($row['estado'])
            {case "PEN":
                $estado=$_SESSION['PHD_PEN'];
                break;
            case "PAS":
                $estado=$_SESSION['PHD_PAS'];
                break;
            case "CAN":
                $estado=$_SESSION['PHD_CAN'];
                break;
            case "ATE":
                $estado=$_SESSION['PHD_ATE'];
                break;
            }

      $ancho_editar=26+(strlen($row['seq_solicitud_id'])*7);
      echo "<tr $color[$Col]>
      <td> <input class='boton_editar' style='width: {$ancho_editar}px;' type='submit' value={$row['seq_solicitud_id']} name='modificar' target='_blank'> </td>
      <td> $fecha";

if($_GET['op']!="user")
      {echo "
          <td> $row[usuario_id]
          <td nowrap> $row[ape_y_nom]
          <td> $row[area]";
      }
echo  "
      <td> $incidente
      <td> $estado";

	}

echo "</table> </form>

<b> $Total_request: $q_registros</b> <p>";


include('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>

echo
"  </body>
</html>";


?>
