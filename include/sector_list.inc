<?PHP
/*
    Nombre: sector_list.inc
    Autor: Julio Tuozzo
    Función: Vista de listado de sectores.
    Function: Sectors list view.
    Ver: 2.00
    
*/
$ancho=22+(strlen($Filter)*8);
require('head.inc');
echo "
    <body class=fondo>
    <form method='post' action='$_SERVER[PHP_SELF]' style='text-align:center'>
    $Sector: <input type='text' name='sector_id' size='10' maxlength='15' value='{$_SESSION[SECTOR][sector_id]}'> &nbsp; &nbsp;
    $Name: <input type='text' name='nombre' size='35' maxlength='50' value='{$_SESSION[SECTOR][nombre]}' >  &nbsp; &nbsp;
    $Active: <select name='activo'>
        <option></option>
        <option value='S' $S_selected> $Yes </option>
        <option value='N' $N_selected> $No </option>
   </select> &nbsp; &nbsp;
   <input class='boton_filtrar' style='width: {$ancho}px;' type='submit' value='$Filter' name='filtrar'>
</form>";
require('ant_123_prox.inc');  ## Línea que muestra <Ant | 1 2 3..... | Prox>
                              // Line that shows <Prev | 1 2 3 ..... | Prox>

echo "    <form method='post' action='sector.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' target='_parent'>
    <TABLE border='0' align='center' cellspacing='1' cellpadding='2' width='80%'>
    <tr>
     <th nowrap> <a href=$_SERVER[PHP_SELF]?orden=sector_id&sentido=$sen_sector_id&pagina=1&q_registros=$q_registros>$Sector </a> $arr_sector_id</th>
	 <th> <a href=$_SERVER[PHP_SELF]?orden=nombre&sentido=$sen_nombre&pagina=1&q_registros=$q_registros> $Name </a> $arr_nombre</th>
	 <th> <a href=$_SERVER[PHP_SELF]?orden=activo&sentido=$sen_activo&pagina=1&q_registros=$q_registros> $Active </a> $arr_activo </th>
    </tr>";
    
  
    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $J=0;
    $atributo_ant='';
    while ($row = mysql_fetch_array($result))
 	      {## Formateo los datos
           // Formating data

           foreach($row as $clave => $valor)
                {$row[$clave]=htmlentities($row[$clave],ENT_QUOTES,"ISO-8859-1");
                }

            $activo= ($row[activo]=='S') ? "<img src='./images/ok.gif' border='0' alt='$Yes' />" : "<img src='./images/cancelar.gif' border='0' alt='$No' />" ;
           $J++;
           $J=$J % 2;
           $ancho_editar=26+(strlen($row[sector_id])*8);
           echo "<tr $color[$J]>
           <td> <input class='boton_editar' style='width: {$ancho_editar}px;' type='submit' value='$row[sector_id]' name='sector_modificar' > </td>
           <td> $row[nombre]  </td>
           <td> $activo  </td>";

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
