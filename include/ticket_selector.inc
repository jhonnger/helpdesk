<?PHP
/*
    Nombre: ticket_selector.inc
    Autor: Julio Tuozzo
    Función: Cabecera de selección de tickets
    Function: Ticket selection header.
    Ver: 2.12
*/

echo "<div id='contenido'>
<form  class='consulta' method='post' action='$_SERVER[PHP_SELF]'>
$Assigned_to: <select name='asignado_a'>
    <option></option> \n";

## Busco en la tabla 'operador' lo operadores.
// Search in the table 'operador' the operators.

        $query="SELECT operador_id, ape_y_nom
                FROM {$MyPHD}operador
                WHERE sector_id='$_SESSION[PHD_SECTOR_ID]' OR privado='N'
                ORDER BY operador_id";
        $result_00=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result_00))
            {if ($row['operador_id']==$_SESSION['PHD_MAIN_CONS']['asignado_a'])
                    {$selected='selected';
                    }
             else
                    {$selected='';
                    }

            echo "<OPTION $selected value='$row[operador_id]'> $row[operador_id] </option> \n";
	        }

echo "</select>
&nbsp; &nbsp;
$Sector: <select name='asignado_a_sector'>
    <option></option> \n";

## Busco los sectores.
// Search the the sectors.

        $query="SELECT DISTINCT sector_id, nombre
                FROM {$MyPHD}sector
                ORDER BY sector_id";
        $result_00=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result_00))
            {if ($row['sector_id']==$_SESSION['PHD_MAIN_CONS']['asignado_a_sector'])
                    {$selected="selected='selected'";
                    }
             else
                    {$selected='';
                    }

              echo "<OPTION $selected value='$row[sector_id]'> $row[sector_id] </OPTION> \n";
	        }
echo "</select>

&nbsp; &nbsp;

$State:  <select name='estado'>
         <option>  </option>";

## Busco en la tabla 'atributo' los estados
// Search in the table 'atributo' the states

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$State'
                ORDER BY valor";
        $result_00=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result_00))
            {if ($row['valor']==$_SESSION['PHD_MAIN_CONS']['estado'])
                    {$selected="selected='selected'";
                    }
             else
                    {$selected='';
                    }

              echo "<option $selected value='{$row['valor']}' > {$row['valor']} </option> \n";
	        }

echo
"   </select>
&nbsp; &nbsp; &nbsp; $Input_by:
<select name='operador'>
    <option></option> \n";

## Busco en la tabla 'operador' lo operadores.
// Search in the table 'operador' the operators.

        $query="SELECT operador_id, ape_y_nom
                FROM {$MyPHD}operador
                WHERE sector_id='$_SESSION[PHD_SECTOR_ID]' OR privado='N'
                ORDER BY operador_id";
        $result_00=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result_00))
            {if ($row['operador_id']==$_SESSION['PHD_MAIN_CONS']['operador_id'])
                    {$selected="selected='selected'";
                    }
             else
                    {$selected='';
                    }

              echo "<option $selected value='$row[operador_id]'> $row[operador_id] </option> \n";
	        }


echo "</select>
&nbsp;&nbsp;
$Sector: <select name='operador_sector_id'>
    <option></option> \n";

## Busco en los sectores.
// Search the sectors.

        $query="SELECT sector_id, nombre
                FROM {$MyPHD}sector
                ORDER BY sector_id";
        $result_00=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result_00))
            {if ($row['sector_id']==$_SESSION['PHD_MAIN_CONS'][sector_id])
                    {$selected="selected='selected'";
                    }
             else
                    {$selected='';
                    }

              echo "<option $selected value='$row[sector_id]'> $row[sector_id] </option> \n";
	        }
echo "</select>
&nbsp; &nbsp;
<input class='boton_lupa' style='width: 30px; cursor:pointer' type='submit' value='' name='buscar' />
</form>
";

?>

