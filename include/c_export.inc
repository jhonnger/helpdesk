<?PHP
/*
    Nombre: c_export.php
    Autor: Julio Tuozzo
    Función: Exportación de la consulta
    Function: Query export.
    Ver: 2.05

*/

## Verfico que la cantidad de filas no supere el máximo que se puede exportar.
// Verify that the amount of rows does not upper than the maximum that can be exported.

if ($q_registros>$_SESSION[PHD_MAX_LINES_EXPORT])
    {$mensaje="<SCRIPT LANGUAGE='JavaScript'> \n
     window.alert('$Err_max_row_1 $q_registros $Err_max_row_2 $_SESSION[PHD_MAX_LINES_EXPORT]');
     window.close();
     </SCRIPT>\n";
     require('consulta_param.inc');
     exit();
    }


$query="select seq_ticket_id, prioridad, fecha, operador_id, operador_sector_id, contacto,usuario_id,  area_id, ape_y_nom, piso, planta, e_mail, asignado_a,  asignado_a_sector, incidente, proceso,  tipo, sub_tipo, estado, fecha_ultimo_estado, operador_ultimo_estado
from {$MyPHD}ticket
$condicion ORDER BY seq_ticket_id";

$result=mysql_query($query) or die (mysql_error());
$q_column=mysql_num_fields($result);

## Envio el header del archivo
// Send the file header


header("Content-type: application/vnd.ms-excel");
header("Content-Disposition: attachment; filename=\"q_phd.xls\"");

echo "<table border='1'>
        <tr>
            <td colspan='22'>$titulo </td>
        </tr>
        <tr>
            <td colspan='22'> </td>
        </tr>
        <tr>
            <th> #$Ticket</th>
            <th>$Priority</th>
            <th>$Date</th>
            <th>$Operator</th>
            <th>$Operator $Sector</th>
            <th>$Contact</th>
            <th>$User</th>
            <th>$User $Area</th>
            <th>$Last_and_first_name</th>
            <th>$Floor</th>
            <th>$Phone</th>
            <th>$Elec_mail</th>
            <th>$Assigned_to</th>
            <th>$Assigned_to $Sector</th>
            <th>$Incident</th>
            <th>$Comment</th>
            <th>$Process</th>
            <th>$Type</th>
            <th>$Subtype</th>
            <th>$State</th>
            <th>$Last_state_date</th>
            <th>$Last_state_oper</th>
        </tr>";


## Recorro el query y lo mando.
// Send the query

while ($row = mysql_fetch_array($result))
	{
	  foreach ($row as $indice=>$valor)
        { $row[$indice]=str_replace(chr(10),"<br />",str_replace(chr(13),"",htmlentities($row[$indice],ENT_QUOTES,"ISO-8859-1")));
        }

       $q_tickets="<td valign='top'>$row[seq_ticket_id]</td>
                   <td valign='top'>$row[prioridad]</td>
                   <td valign='top'>$row[fecha]</td>
                   <td valign='top'>$row[operador_id]</td>
                   <td valign='top'>$row[operador_sector_id]</td>
                   <td valign='top'>$row[contacto]</td>
                   <td valign='top'>$row[usuario_id]</td>
                   <td valign='top'>$row[area_id]</td>
                   <td valign='top'>$row[ape_y_nom]</td>
                   <td valign='top'>$row[piso]</td>
                   <td valign='top'>$row[planta]</td>
                   <td valign='top'>$row[e_mail]</td>
                   <td valign='top'>$row[asignado_a]</td>
                   <td valign='top'>$row[asignado_a_sector]</td>
                   <td valign='top'>$row[incidente]</td><td>";

## Veo si hay cometarios en el ticket

     $query_0="SELECT fecha, operador_id, comentario
            FROM {$MyPHD}sigo_ticket
            WHERE seq_ticket_id={$row['seq_ticket_id']}
            ORDER BY seq_sigo_ticket_id";

     $result_0=mysql_query($query_0) or die (mysql_error());
     while ($row_0 = mysql_fetch_array($result_0))
       {if (isSet($row_0[operador_id]) and strlen($row_0[comentario])>0)
          {foreach ($row_0 as $indice=>$valor)
                    {$row_0[$indice]=str_replace(chr(10),"<br />",str_replace(chr(13),"",htmlentities($row_0[$indice],ENT_QUOTES,"ISO-8859-1")));

                    }

            $b_fecha=date("$Date_format H:i",strtotime($row_0['fecha']));
            $q_tickets.= "<b>$b_fecha - $row_0[operador_id] </b> $row_0[comentario] <br />";
          }
       }


      $q_tickets.="</td>
                    <td valign='top'>$row[proceso]</td>
                    <td valign='top'>$row[tipo]</td>
                    <td valign='top'>$row[sub_tipo]</td>
                    <td valign='top'>$row[estado]</td>
                    <td valign='top'>$row[fecha_ultimo_estado]</td>
                    <td valign='top'>$row[operador_ultimo_estado]</td>
                </tr>";
        echo $q_tickets;

   }
echo "</table>";
?>

