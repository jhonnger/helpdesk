<?PHP
/*
    Nombre: atributo_list.inc
    Autor: Julio Tuozzo
    Función: Vista de la lista de atributos de los casos.
    Function: Tickets attributes list view.
    Ver: 2.00

*/

$ancho=22+(strlen($Filter)*8);
require('head.inc');
echo "<body>

<form method='post' action='$_SERVER[PHP_SELF]' style='text-align:center'>
    $Class_attribute: <SELECT name='atributo'>
              <option></option>
              <OPTION $opt_contact> $Contact </OPTION>
              <OPTION $opt_state> $State </OPTION>
              <OPTION $opt_process> $Process </OPTION>
              <OPTION $opt_type> $Type </OPTION>";

        $query="SELECT valor
            FROM {$MyPHD}atributo
            WHERE atributo='$Type' AND activo='S'
            ORDER BY valor";
    $result=mysql_query($query) or die (mysql_error());

    while ($row = mysql_fetch_array($result))
       { if ($_SESSION[ATRIBUTO][atributo]==$row[valor])
            {$opt_selected="selected";
            }
         else
            {$opt_selected="";
            }

         echo "<OPTION value='$row[valor]' $opt_selected> $Subtype_of $row[valor] </OPTION> \n";
	   }


echo "
          </SELECT>
&nbsp; &nbsp;
    $Active: <select name='activo'>
        <option></option>
        <option value='S' $S_selected> $Yes </option>
        <option value='N' $N_selected> $No </option>
   </select> &nbsp; &nbsp;
   <input class='boton_filtrar' style='width: {$ancho}px;' type='submit' value='$Filter' name='filtrar'>
</form>";

    require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                                  // Line that shows <Prev | 1 2 3 ..... | Prox>

echo "<FORM method='post' action='atributo.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' target='_parent' >

    <TABLE border='0' align='center' cellspacing='1' cellpadding='2' width='80%'>
    <tr>
     <th width='15%'> $Change_active </th>
  	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=atributo&sentido=$sen_atributo>   $Class_attribute </a> $arr_atributo </th>
	 <th> $Value </th>
	 <th> <a href=$_SERVER[PHP_SELF]?pagina=1&q_registros=$q_registros&orden=activo&sentido=$sen_activo> $Active </a> $arr_activo  </th>
    </tr>";


    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $J=0;
    $atributo_ant='';

    $query="SELECT seq_atrib_id, IF(EXISTS(SELECT * FROM {$MyPHD}atributo b WHERE a.atributo=b.valor),CONCAT('_____',atributo),atributo) as atributo, valor, activo
    FROM {$MyPHD}atributo a $condicion
    ORDER BY $orden $sentido, atributo, valor
    LIMIT $desde_reg, $_SESSION[PHD_MAX_LINES_SCREEN]";

    $result=mysql_query($query) or die (mysql_error());

    while ($row = mysql_fetch_array($result))
	{  $activo= ($row[activo]=='S') ? "<img src='./images/ok.gif' border='0' alt='$Yes' />" : "<img src='./images/cancelar.gif' border='0' alt='$No' />" ;
      $atributo=str_replace("_____","$Subtype_of ",$row['atributo']);
      $ancho_editar=26+(strlen($row[seq_atrib_id])*8);
      if ($atributo!=$atributo_ant)
            {$atributo_ant=$atributo;
             $J++;
             $J=$J % 2;
             echo "<tr $color[$J]>
             <td> <input class='boton_editar' style='width: {$ancho_editar}px;' type='submit' value=$row[seq_atrib_id] name='activo' > </td>
             <td><b>$atributo_ant</b>";
             }
       else
            {echo "<tr $color[$J]>
             <td> <input class='boton_editar' style='width: {$ancho_editar}px;' type='submit' value=$row[seq_atrib_id] name='activo'> </td>
             <td>";

            }

echo
"</td>
       <td> $row[valor]  </td>
       <td> $activo  </td>";

	}

echo "</table>
    </form>
    <strong>$Total: $q_registros</strong>";

require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>
echo "</body>
</html>";


?>

