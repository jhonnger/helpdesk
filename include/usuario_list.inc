<?PHP
/*
    Nombre: usuario_list.inc
    Autor: Julio Tuozzo
    Función: Vista de la lista de usuarios de los casos
    Function: Ticket's users list view.
    Ver: 2.00
*/

$ancho=22+(strlen($Filter)*8);
require('head.inc');
    echo "<body>

<form method='post' action='$_SERVER[PHP_SELF]'>
    $User: <input type='text' name='usuario_id' size='10' maxlength='15' value='{$_SESSION[USUARIO][usuario_id]}'> &nbsp; &nbsp;
    $Last_and_first_name: <input type='text' name='ape_y_nom' size='30' maxlength='50' value='{$_SESSION[USUARIO][ape_y_nom]}' >  &nbsp; &nbsp;
    $Area: <select name='area_id'>
           <option>  </option>";
    $query="SELECT area_id, nombre
            FROM {$MyPHD}area
            ORDER BY area_id";

    $result=mysql_query($query) or die (mysql_error());

    while ($row = mysql_fetch_array($result))
       { $area_nombre=substr($row[nombre],0,25);
         if ($row['area_id']==$_SESSION[USUARIO][area_id])
            {$selected='selected';
            }
        else
            {$selected='';
            }
         echo "<option $selected value='$row[area_id]'> $row[area_id] - $area_nombre </option> \n";
	   }

if (isset($_SESSION[USUARIO][activo]))
    { $_sele="{$_SESSION[USUARIO][activo]}"."_selected";
      $$_sele="'selected'";
    }


echo    "</select>
        &nbsp; &nbsp;
        
    $Active: <select name='activo'>
        <option></option>
        <option value='S' $S_selected> $Yes </option>
        <option value='N' $N_selected> $No </option>
   </select> &nbsp; &nbsp;
   <input class='boton_filtrar' style='width: {$ancho}px;' type='submit' value='$Filter' name='filtrar'>
</form>";

$query="SELECT * FROM {$MyPHD}usuario $condicion ORDER BY $orden $sentido LIMIT $desde_reg, $_SESSION[PHD_MAX_LINES_SCREEN]";
$result=mysql_query($query) or die (mysql_error());

require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>

## Muestro los datos de los operadores
// Show the operator data.

echo "<FORM method='post' action='usuario.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' target='_parent'>
    <TABLE border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
  	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=usuario_id&sentido=$sen_usuario_id> $User </a> $arr_usuario_id </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=ape_y_nom&sentido=$sen_ape_y_nom>$Last_and_first_name</a> $arr_ape_y_nom </th>
	 <th>  <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=area_id&sentido=$sen_area_id>$Area</a> $arr_area_id </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=activo&sentido=$sen_activo> $Active </a> $arr_activo </th>
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
      if ($row[activo]=='S')
            {$t_activo="<img src='./images/ok.gif' border='0' alt='$Yes' />";
            }
      else
            {$t_activo="<img src='./images/cancelar.gif' border='0' alt='$No' />";
            }
      $ancho_editar=26+(strlen($row[usuario_id])*8);
	  echo "<tr $color[$J]>
      <td> <input class='boton_editar' style='width: {$ancho_editar}px;' type='submit' value='$row[usuario_id]' name='usr_modificar'> </td>
      <td> $row[ape_y_nom]  </td>
      <td> $row[area_id]  </td>
      <td> $t_activo  </td>";

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

