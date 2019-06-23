<?PHP
/*
    Nombre: novedades_list.inc
    Autor: Julio Tuozzo
    Función: Consulta de novedades por pantalla
    Function: News consult by screen.
    Ver: 2.12

*/
## Calculo desde que registro muestro en función de la página
// Calculate since registry show based on the page.

$desde_reg=($pagina-1)*$_SESSION[PHD_MAX_LINES_SCREEN];

## Hago la consulta
// make query

$query="{$_SESSION['PHD_NEWS_QUERY']}
		ORDER BY $orden $sentido LIMIT $desde_reg, $_SESSION[PHD_MAX_LINES_SCREEN]";

$result=mysql_query($query) or die (mysql_error());


require('head.inc');

echo "<body>";
require('menu.inc');
echo "<div id='contenido'>";
require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                             // Line that shows <Prev | 1 2 3 ..... | Prox>
echo "$titulo
   <form method='post' action='ticket_modif.php' target='_blank'>

    <table border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
 	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=seq_ticket_id&sentido=$sen_seq_ticket_id>$Ticket </a> $arr_seq_ticket_id </th> 
 	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=tipo&sentido=$sen_tipo>$Type </a> $arr_tipo </th> 

 	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=insert_datetime&sentido=$sen_insert_datetime>$Date </a> $arr_insert_datetime </th>
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=insert_oper&sentido=$sen_insert_oper>$Operator</a> $arr_insert_oper </th>
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=insert_user&sentido=$sen_insert_user>$User</a> $arr_insert_user </th>
	 <th nowrap> $Incident / $Comment </th> 
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=campo_cambiado&sentido=$sen_campo_cambiado>$Modified_field</a> $arr_campo_cambiado </th>
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=valor_anterior&sentido=$sen_valor_anterior>$Previous_value</a> $arr_valor_anterior </th>
     <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=valor_actual&sentido=$sen_valor_actual>$New_value</a> $arr_valor_actual </th>
    </tr>";

    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $Col=$J=0;
    $ticket_ant="";
    while ($row = mysql_fetch_array($result))
	{ if($ticket_ant!=$row['insert_datetime'].$row['seq_ticket_id'])
	  		{$ticket_ant=$row['insert_datetime'].$row['seq_ticket_id'];
	  		 $J++;
		  	 $Col=$J % 2;
		  	 $fecha=date("$Date_format H:i:s",strtotime($row['insert_datetime']));
		  	 $ancho=26+(strlen($row['seq_ticket_id'])*8);
    	     if($row['tipo']=="$New")
      				{$tipo="<img src='./images/nuevo.png' alt='$New' /> {$row['tipo']}";
					}
      		 else
      				{$tipo=" {$row['tipo']} <img src='./images/go-next.gif' alt='$Follow_up' />";
					}
			 echo "<tr $color[$Col]>
			 <td> <input class='boton_editar' type='submit' style='width: {$ancho}px;' value={$row['seq_ticket_id']} name='modificar' target='_blank'> </td>
      		 <td nowrap='nowrap'> $tipo </td>
      		 <td> $fecha </td>
      		 <td> {$row['insert_oper']} </td>
      		 <td> {$row['insert_user']} </td>";
			}
	  else		
	  		{echo "<tr $color[$Col]>
			  <td> </td>
      		 <td > </td>
      		 <td>  </td>
      		 <td>  </td>
      		 <td>  </td>";
		
			}
  	  $disp_incidente=str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row['incidente'],ENT_QUOTES,"ISO-8859-1")));		  
      echo "<td>$disp_incidente</td>
      <td >{$row['campo_cambiado']} </td>
      <td>{$row['valor_anterior']} </td>
      <td> {$row['valor_actual']} </td>
	       </tr>";

	}

echo "</table> </form> <br />";


require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
echo
"</div>
  </body>
</html>";


?>
