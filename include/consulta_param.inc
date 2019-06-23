<?PHP
/*
    Nombre: consulta_param.inc.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Parámetros de la consulta
    Function: Query parameters.
    Ver: 2.12
*/


$ancho_salir=23+(strlen($Exit)*9);
$ancho_consultar=23+(strlen($Consult)*9);

require('head.inc');
echo"<body>";
require('menu.inc');

## Traigo las funciones JavaScript
// Get the JavaScript functions.
$subtipo_blank=true;
require('f_subtipo_JS.inc');


## Dibujo la pantalla de consulta general
// Drawing the screen of general consultation

echo

"<div id='contenido'>$mensaje
<form name='ticket' method='post' action='$_SERVER[PHP_SELF]'>
<input type='hidden' name='ape_y_nom' />
<table class='consulta' border='0' width='95%' cellpadding='3' cellspacing='3' align='center'>
<tr>
<td>
$Ticket #: </td> <td> <INPUT type='text' name='ticket' size='8' maxlength='8' />
</td>
</tr>
<tr>
<td>
$Input_date $From:  </td> <td> <INPUT type='text' name='fecha_desde' size='10' maxlength='10' > ($Date_text) &nbsp;&nbsp; &nbsp; &nbsp;
$To: <INPUT type='text' name='fecha_hasta' size='10' maxlength='10' > ($Date_text)
</td>
</tr>
<tr>
<td>
$Input_by:  </td> <td> <select name='operador'>
    <option></option> \n";

## Busco en la tabla 'operador' lo operadores.
// Search in the table 'operador' the operators.

        $query="SELECT operador_id, ape_y_nom
                FROM {$MyPHD}operador
                WHERE sector_id='$_SESSION[PHD_SECTOR_ID]' OR privado='N'
                ORDER BY operador_id";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION value='$row[operador_id]'> $row[operador_id] - $row[ape_y_nom] </OPTION> \n";
	        }
    

echo "</select>
&nbsp;&nbsp; &nbsp; &nbsp;
$Sector: <select name='operador_sector_id'>
    <option></option> \n";

## Busco en los sectores.
// Search the sectors.

        $query="SELECT sector_id, nombre
                FROM {$MyPHD}sector
                ORDER BY sector_id";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION value='$row[sector_id]'> $row[sector_id] - $row[nombre] </OPTION> \n";
	        }
echo "</select>
</td>
</tr>
<tr>
<td>
$Contact: </td> <td>  <select name='contacto'>
          <option>  </option>";

## Busco en la tabla 'atributo' los contactos.
// Search in the table 'atributo' the contacts.

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Contact'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION > $row[valor] </OPTION> \n";
	        }

echo
"   <option> Web </option>
    </select>
</td>
</tr>
<tr>
<td>
$User:  </td> <td> <input type='text' name='usuario' size='15' maxlength='15'>
<INPUT  class='boton_lupa' title='$Search $User' type='button' value= '' onclick=window.open('usr_busco.php','','width=500,height=390,scrollbars=1,resizable=1,toolbar=0,location=0,menubar=0,status=0,directories=0')>

&nbsp;&nbsp; &nbsp; &nbsp;
$Area: <select name='area_id'>
    <option></option> \n";

## Busco en la tabla 'area''.
// Search in the table 'area'.

        $query="SELECT area_id, nombre
                FROM  {$MyPHD}area
                ORDER BY area_id";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<option value='$row[area_id]'> $row[area_id] - $row[nombre] </option> \n";
	        }
echo "</select>
</td>
</tr>
<tr>
<td>

$Assigned_to: </td> <td> <select name='asignado_a'>
    <option></option> \n";

## Busco en la tabla 'operador' lo operadores.
// Search in the table 'operador' the operators.

        $query="SELECT operador_id, ape_y_nom
                FROM {$MyPHD}operador
                WHERE sector_id='$_SESSION[PHD_SECTOR_ID]' OR privado='N'
                ORDER BY operador_id";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION value='$row[operador_id]'> $row[operador_id] - $row[ape_y_nom] </OPTION> \n";
	        }

echo "</select>
&nbsp;&nbsp; &nbsp; &nbsp;
$Sector: <select name='asignado_a_sector'>
    <option></option> \n";

## Busco los sectores.
// Search the the sectors.

        $query="SELECT DISTINCT sector_id, nombre
                FROM {$MyPHD}sector
                ORDER BY sector_id";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION value='$row[sector_id]'> $row[sector_id] - $row[nombre] </OPTION> \n";
	        }
echo "</select>

</td>
</tr>
<tr>
<td>

$Priority: </td> <td>  <select name='prioridad'>
           <option></option>";
        for ($I=5;$I>0;$I--)
            {echo "<option value='$I'> $I ";
             switch ($I)
                {
                   case 5:
                   print "- $High";
                   break;
                   case 3:
                   print "- $Medium";
                   break;
                   case 1:
                   print "- $Low";
                   break;
                }
             echo "</OPTION> \n";
            }

echo   "</select>
</td>
</tr>
<tr>
<td>
$Incident: </td> <td>  <input type='text' name='incidente' size='80' maxlength='100' >
</td>
</tr>

<tr>
<td>
$Comment: </td> <td>  <input type='text' name='comentario' size='80' maxlength='100' >
</td>
</tr>


<tr>
<td>
$Process: </td> <td>  <SELECT name='proceso'>
          <OPTION>  </OPTION>";

## Busco en la tabla 'atributo' los procesos.
// Search in the table 'atributo' the processes.

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Process'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION > {$row['valor']} </OPTION> \n";
	        }

echo
"   </SELECT>

</td>
</tr>
<tr>
<td>
$Type:  </td> <td> <SELECT name='tipo' onBlur='f_sub_tipo(this);'>
      <OPTION>  </OPTION>";

## Busco en la tabla de atributos los tipos de incidentes.
// Search in the table of attributes the types of incidents.

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Type'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION value='$row[valor]'> $row[valor] </OPTION> \n";
	        }

## Ahora armo la lista de selección de subtipos.
// Make the subtype list.

echo
"    </select>
&nbsp;&nbsp; &nbsp; &nbsp;
$Subtype: <select name='sub_tipo'>  </select>

</td>
</tr>
<tr>
<td>
$State:  </td> <td> <SELECT name='estado'>
         <OPTION>  </OPTION>";

## Busco en la tabla 'atributo' los estados
// Search in the table 'atributo' the states

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$State'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            {echo "<OPTION > {$row['valor']} </OPTION> \n";
	        }

echo
"   </SELECT>

&nbsp;&nbsp; &nbsp; &nbsp;

$Last_state_date $From: <INPUT type='text' name='fecha_ue_desde' size='10' maxlength='10' > ($Date_text)
&nbsp;&nbsp; &nbsp; &nbsp;
$To: <INPUT type='text' name='fecha_ue_hasta' size='10' maxlength='10' > ($Date_text)
 </td>
</tr>
</table>

<table class='consulta' border='0' width='95%' cellpadding='5' cellspacing='3' align='center'>
<tr>
<td style='text-align: center;'><input class='boton_bold' type='reset' value='$Clean'></td>
<td style='text-align: center;'><input class='boton_filtrar' style='width: {$ancho_consultar}px;' type='submit' value='$Consult' name='buscar'></td>
<td style='text-align: center;'><input class='boton_bold' type='submit' value='$Export' name='exportar'></td>
<td style='text-align: center;'><input class='boton_salir' style='width: {$ancho_salir}px;' type='button' value='$Home' onclick='window.location=\"index.php\"';>
</td>
</tr>
</table>

  </form>
</div>
 </body>
</html>";

?>
