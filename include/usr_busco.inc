<?PHP
/*
    Nombre: usr_busco.inc
    Autor: Julio Tuozzo.
    Función: Busqueda de usuario.
    Function: Search of user.
    Versión: 2.00
*/

$query="SELECT usuario_id, ape_y_nom, area_id FROM {$MyPHD}usuario
        WHERE ape_y_nom like '%$ape_y_nom%'
        AND activo='S'
        ORDER BY ape_y_nom";
$result=mysql_query($query) or die (mysql_error());
$q_registros=mysql_num_rows($result);

$max_reg=$_SESSION[PHD_MAX_LINES_SCREEN]*2;

if ($q_registros>$max_reg)
    {echo "<SCRIPT LANGUAGE='JavaScript'> \n
     window.alert('$Err_max_row_1 $q_registros $Err_max_row_2 $max_reg, $Err_max_row_3');
    </SCRIPT>\n";
     }

elseif($q_registros==0)

    {echo "<p class='error'>$No_user_found '$ape_y_nom'</p>";
    }
else

    {echo  "<hr />";

     ## Muestro los datos de los usuarios
     // Show the user's data.

     echo "

    <form method='post' name='f_usr_busco'>
    <table border='0' cellspacing='1' cellpadding='2' width='100%'>
    <tr>
  	 <th> $User </th>
	 <th> $Last_and_first_name </th>
	 <th> $Area </th>
    </tr>";
    
  
    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $J=0;
    while ($row = mysql_fetch_array($result))
	{ $J++;
	  $J=$J % 2;
	  echo "<tr $color[$J]>
      <td> 
      <INPUT class='boton_bold' type='button' value='$row[usuario_id]' onclick='window.opener.document.ticket.usuario.value =\"$row[usuario_id]\";
                        window.opener.document.ticket.usuario.focus();
                        window.opener.document.ticket.ape_y_nom.value=\"\";window.close();'> </td>
      <td> $row[ape_y_nom]  </td>
      <td> $row[area_id]  </td>
      </tr>";

	}    

echo "</table>
 </form>";
}

?>

