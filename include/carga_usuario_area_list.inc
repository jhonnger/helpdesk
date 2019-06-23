<?PHP
/*
    Nombre: carga_usuario_area_list.inc
    Autor: Julio Tuozzo
    Función: Vista de la lista de usuarios y areas
    Function: users and areas list view.
    Ver: 2.12
*/

$opcion=$Load_users;
$ancho_eliminar=22+(strlen($Cancel_file)*7);
$ancho_salir=22+(strlen($Home)*9);
$ancho_cargar=22+(strlen($Load)*9);

require('head.inc');
echo "<body>";
require('menu.inc');
echo "<div id='contenido'>";


echo " <form method='post' action='{$_SERVER['PHP_SELF']}?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros'>

	   <div class='caja' style='text-align:center'>
			<span style='position:absolute; left:50px'>
			   <input class='boton_eliminar' style='width: {$ancho_eliminar}px;' type='submit' value='$Cancel_file' name='eliminar' onclick='return confirm(\"$Are_you_sure_cancel_file\")'/>
		    </span>
    	<input class='boton_guardar' style='width: {$ancho_cargar}px;' type='submit' value='$Load' name='procesar' onclick='return confirm(\"$Are_you_sure_load_file\")'/>

               <span style='position:absolute; right:50px'> 
			   		<input class='boton_salir' style='width: {$ancho_salir}px;' type='submit' value='$Home' name='inicio' />
               </span>
               <br />$Explain_load
    </div> <br />";
    
require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>
echo "
    <table border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
  	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=usuario_id&sentido=$sen_usuario_id> $User </a> $arr_usuario_id  </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=ape_y_nom&sentido=$sen_ape_y_nom> $Last_and_first_name </a> $arr_ape_y_nom </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=e_mail&sentido=$sen_e_mail> $Elec_mail </a> $arr_e_mail </th> 
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=piso&sentido=$sen_piso> $Floor </a> $arr_piso </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=planta&sentido=$sen_planta> $Phone </a> $arr_planta </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=area_id&sentido=$sen_area_id> $Area_code </a> $arr_area_id </th>
	 <th nowrap='nowrap'> <a href={$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=nombre&sentido=$sen_nombre> $Name $Area </a> $arr_nombre </th>
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
	  echo "<tr $color[$J]>
      <td nowrap='nowrap'> {$row['usuario_id']} </td>
      <td> {$row['ape_y_nom']} </td>
      <td> {$row['e_mail']} </td>
      <td> {$row['piso']} </td>
      <td> {$row['planta']} </td>
      <td> {$row['area_id']} </td>
      <td> {$row['nombre']} </td>
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

