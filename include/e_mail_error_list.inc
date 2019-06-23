<?PHP
/*
    Nombre: e_mail_error_list.inc
    Autor: Julio Tuozzo
    Función: Vista de la lista de errores de envío de e-mails.
    Function: Send e-mail errors list view.
    Ver: 2.12
*/

$opcion=$E_mail_error_log;
$ancho_eliminar=22+(strlen($Erase_log)*7);
$ancho_salir=22+(strlen($Home)*7);

require('head.inc');
echo "<body>";
require('menu.inc');
echo "<div id='contenido'>";


echo " <form method='post' action='{$_SERVER['PHP_SELF']}?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros'>
       <div class='caja' style='text-align:center'> <input class='boton_eliminar' style='width: {$ancho_eliminar}px;' type='submit' value='$Erase_log' name='eliminar' onclick='return confirm(\"$Are_you_sure_erase_log\")'/>
               <span style='position:absolute; right:50px'> <input class='boton_salir' style='width: {$ancho_salir}px;' type='submit' value='$Home' name='inicio' />
               </span>
    </div> <br />";
require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>
echo "
    <table border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
  	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=insert_datetime&sentido=$sen_insert_datetime> $Date </a> $arr_insert_datetime  </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=from_name&sentido=$sen_from_name> $Sender </a> $arr_from_name </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=from_e_mail&sentido=$sen_from_e_mail> $Elec_mail </a> $arr_from_e_mail </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=to_name&sentido=$sen_to_name> $Receiver </a> $arr_to_name </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=to_e_mail&sentido=$sen_to_e_mail> $Elec_mail </a> $arr_to_e_mail </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=subject&sentido=$sen_subject> $Subject </a> $arr_subject </th>
	 <th nowrap='nowrap'> $Body  </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=error_message&sentido=$sen_error_message> $Error_message </a> $arr_error_message </th>
    </tr>";
    
  
    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $J=0;
    while ($row = mysql_fetch_array($result))
	{ ## Le doy forma al vector de los datos
      // Formating the data vector.

      foreach($row as $clave => $valor)
           {//$row[$clave]=htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1"); Saco esto por ahora para que se vea el cuerpo del correo
           }
      $J++;
	  $J=$J % 2;
      $fecha=date("$Date_format H:i:s",strtotime($row['insert_datetime']));
	  echo "<tr $color[$J]>
      <td nowrap='nowrap'> $fecha </td>
      <td> {$row['from_name']} </td>
      <td> {$row['from_e_mail']} </td>
      <td> {$row['to_name']} </td>
      <td> {$row['to_e_mail']} </td>
      <td> {$row['subject']} </td>
      <td> {$row['body']} </td>
      <td> {$row['error_message']} </td>
        </tr>";
        

	}    

echo "</table>
    </form>
<strong>$Total: $q_registros</strong>";

require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>

echo    "</div>
  </body>
</html>";


?>

