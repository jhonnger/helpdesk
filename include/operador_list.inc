<?PHP
/*
    Nombre: operador_list.inc
    Autor: Julio Tuozzo
    Función: Vista de la lista de operadores del sistema.
    Function: Sistem operators administration list view.
    Ver: 2.12
*/
$ancho=22+(strlen($Filter)*8);
require('head.inc');
echo "
    <body>
    <form method='post' action='$_SERVER[PHP_SELF]'>
    $Operator: <input type='text' name='operador_id' size='10' maxlength='15' value='{$_SESSION[OPERADOR][operador_id]}'> &nbsp; &nbsp;
    $Last_and_first_name: <input type='text' name='ape_y_nom' size='35' maxlength='50' value='{$_SESSION[OPERADOR][ape_y_nom]}' >  &nbsp; &nbsp;
    $Sector: <select name='sector_id'>
           <option>  </option>";
    $query="SELECT sector_id, nombre
            FROM {$MyPHD}sector
            ORDER BY sector_id";

    $result=mysql_query($query) or die (mysql_error());

    while ($row = mysql_fetch_array($result))
       {if ($row['sector_id']==$_SESSION[OPERADOR][sector_id])
            {$selected='selected';
            }
        else
            {$selected='';
            }
         echo "<option $selected > $row[sector_id]  </option> \n";
	   }

if (isset($_SESSION[OPERADOR][nivel]))
    { $aux_selec="_{$_SESSION[OPERADOR][nivel]}";
      $$aux_selec="'selected'";
    }


echo    "</select>
        &nbsp; &nbsp;

    $Access_level:
          <select name='nivel'>
              <option></option>
              <OPTION $_10 value='10'> $Operator </OPTION>
              <OPTION $_20 value='20'> $Administrator </OPTION>
              <OPTION $_0 value='0'> $No_access </OPTION>
          </SELECT> &nbsp; &nbsp;
   <input class='boton_filtrar' style='width: {$ancho}px;' type='submit' value='$Filter' name='filtrar'>
</form>";

    require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>

$query="SELECT *  FROM {$MyPHD}operador $condicion ORDER BY $orden $sentido, operador_id LIMIT $desde_reg, $_SESSION[PHD_MAX_LINES_SCREEN]";
$result=mysql_query($query) or die (mysql_error());

echo " <form method='post' action='operador.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' target='_parent'>
    <table border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
  	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=operador_id&sentido=$sen_operador_id> $Operator </a> $arr_operador_id  </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=ape_y_nom&sentido=$sen_ape_y_nom> $Last_and_first_name </a> $arr_ape_y_nom </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=sector_id&sentido=$sen_sector_id> $Sector </a> $arr_sector_id </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=nivel&sentido=$sen_nivel> $Access_level </a> $arr_nivel </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=privado&sentido=$sen_privado> $Private </a> $arr_privado </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=avisar_asignado&sentido=$sen_avisar_asignado> $Alert_assign </a> $arr_avisar_asignado </th>
	  <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=avisar_solicitud&sentido=$sen_avisar_solicitud> $Alert_user_request </a> $arr_avisar_solicitud </th>
    </tr>";
    
  
    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $J=0;
    while ($row = mysql_fetch_array($result))
	{ ## Le doy forma al vector de los datos
      // Formating the data vector.

      foreach($row as $clave => $valor)
           {$row[$clave]=htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1");
           }
      $J++;
	  $J=$J % 2;
      switch ($row[nivel])
            {case 20:
                $t_nivel="<h2>$Administrator</h2>";
                break;
             case 10:
                $t_nivel="<h3>$Operator</h3>";
                break;
             case 0:
                $t_nivel="<h3 style='text-align:left' class='error'> $No_access </h3>";
                break;
             default:
                $t_nivel="<p class='error'> $Err_level_access </p>";
             }
      if ($row[privado]=='S')
            {$t_privado="<img src='./images/ok.gif' border='0' alt='$Yes' />";
            }
      else
            {$t_privado="";
            }

      if ($row[avisar_asignado]=='S')
            {$t_avisar_asignado="<img src='./images/ok.gif' border='0' alt='$Yes' />";
            }
      else
            {$t_avisar_asignado="";
            }

      if ($row[avisar_solicitud]=='S')
            {$t_avisar_solicitud="<img src='./images/ok.gif' border='0' alt='$Yes' />";
            }
      else
            {$t_avisar_solicitud="";
            }
      $ancho_editar=26+(strlen($row['operador_id'])*8);
	  echo "<tr $color[$J]>
      <td> <input class='boton_editar' style='width: {$ancho_editar}px;'  type='submit' value={$row['operador_id']} name='modificar'> </td>
      <td> $row[ape_y_nom]  </td>
      <td> $row[sector_id]  </td>
      <td> $t_nivel  </td>
      <td> $t_privado  </td>
      <td> $t_avisar_asignado  </td>
      <td> $t_avisar_solicitud  </td>";

	}    

echo "</table>
    </form>
<strong>$Total: $q_registros</strong>";

require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>

echo    "
  </body>
</html>";


?>

