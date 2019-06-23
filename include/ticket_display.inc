<?PHP
/*
    Nombre: ticket_display.inc
    Autor: Julio Tuozzo
    Función:  formulario que muestra los tickets por pantalla
    Function: Form that print tickets by screen.
    Ver: 2.00

*/

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

require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                             // Line that shows <Prev | 1 2 3 ..... | Prox>
echo "$titulo
   <form method='post' action='ticket_modif.php' target='_blank'>

    <table border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
 	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=seq_ticket_id&sentido=$sen_seq_ticket_id>$Ticket </a> $arr_seq_ticket_id
 	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=prioridad&sentido=$sen_prioridad>$Priority </a> $arr_prioridad
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=fecha&sentido=$sen_fecha>$Date</a> $arr_fecha
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=usuario_id&sentido=$sen_usuario_id>$User</a> $arr_usuario_id
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=ape_y_nom&sentido=$sen_ape_y_nom>$Last_and_first_name</a> $arr_ape_y_nom
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=area_id&sentido=$sen_area_id>$Area</a> $arr_area_id
	 <th nowrap> $Incident
	 <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=estado&sentido=$sen_estado>$State</a> $arr_estado
     <th nowrap> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=fecha_ultimo_estado&sentido=$sen_fecha_ultimo_estado>$Last_state_date</a> $arr_fecha_ultimo_estado
    </tr>";


    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $J=0;
    while ($row = mysql_fetch_array($result))
	{ $J++;
	  $Col=$J % 2;
	  $fecha=date("$Date_format H:i:s",strtotime($row['fecha']));
	  $fecha_ultimo_estado=date("$Date_format H:i:s",strtotime($row['fecha_ultimo_estado']));

	  $a_incidente=explode(" ",$_SESSION[PHD_INCIDENTE]);
	  $q_palabras=count($a_incidente);
	  $disp_ape_y_nom=str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row['ape_y_nom'],ENT_QUOTES,"ISO-8859-1")));
	  $disp_incidente=str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row['incidente'],ENT_QUOTES,"ISO-8859-1")));
	  for ($I=0; $I<$q_palabras; $I++)
          {$disp_incidente=str_replace($a_incidente[$I],"<span class='resalto'>".$a_incidente[$I]."</span>",$disp_incidente);
          }
      $ancho=26+(strlen($row['seq_ticket_id'])*8);
	  echo "<tr $color[$Col]>
      <td> <input class='boton_editar' type='submit' style='width: {$ancho}px;' value={$row['seq_ticket_id']} name='modificar' target='_blank'> </td>
      <td class='p_$row[prioridad]'> $row[prioridad]
      <td> $fecha
      <td> $row[usuario_id]
      <td nowrap> $disp_ape_y_nom
      <td> $row[area_id]
      <td> $disp_incidente";

## Veo si hay comentarios en el ticket
// Verify if there are comments in the ticket

    $query_0="SELECT fecha, operador_id, usuario_id, comentario
            FROM {$MyPHD}sigo_ticket
            WHERE seq_ticket_id={$row['seq_ticket_id']}
            ORDER BY seq_sigo_ticket_id";

    $result_0=mysql_query($query_0) or die (mysql_error());
    while ($row_0 = mysql_fetch_array($result_0))
       {if (strlen($row_0[comentario])>0)
          { $b_fecha=date("$Date_format H:i",strtotime($row_0['fecha']));
       	    $a_comentario=explode(" ",$_SESSION[PHD_COMENTARIO_Q]);
       	    $q_palabras=count($a_comentario);
            $disp_comentario=str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row_0['comentario'],ENT_QUOTES,"ISO-8859-1")));
        	for ($I=0; $I<$q_palabras; $I++)
                {$disp_comentario=str_replace($a_comentario[$I],"<span class='resalto'>".$a_comentario[$I]."</span>",$disp_comentario);
        }

            echo " <br> <b> $b_fecha  - $row_0[operador_id] $row_0[usuario_id]</b> - $disp_comentario";
          }
       }

echo
"     <td> $row[estado]
      <td> $fecha_ultimo_estado";
	}

echo "</table> </form>

<b> $Total_tkt: $q_registros</b> <p>";


require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
echo
"</div>
  </body>
</html>";

?>
