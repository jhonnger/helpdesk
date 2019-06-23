<?PHP
/*
    Nombre: ticket_modif.inc
    Autor: Julio Tuozzo 
    Función: Formulario de modificación de ticket de mesa de ayuda
    Function: Update ticket form.
    Ver: 2.00

*/

$ancho_guardar=22+(strlen($Save)*8);
$ancho_salir=22+(strlen($Close)*8);
include('head.inc');


## Traigo las funciones JavaScript
// Get JavaSript functions.

include('f_subtipo_JS.inc');
include('f_fecha_JS.inc');

//$fecha=date("F j Y H:i:s");
//echo $fecha;
//exit();

## Inicio el formulario de carga de tickets
// Inicializing the load ticket form.

echo

"<body>
<a href='http://www.p-hd.com.ar'><img src='./images/phd_150_20.gif' border='0' alt='PHD Help Desk' /></a>
<form enctype='multipart/form-data' name='ticket' method='post' action=ticket_modif.php onsubmit='document.ticket.fecha_sigo.value=f_fecha();'>

    <TABLE border='0' width='95%' cellpadding='1' cellspacing='1' align='center'>
     <tr>
      <td colspan=3> <h3>$Ticket: # $seq_ticket_id </h3></td>
     </tr>
     <tr>
      <td align='left'> $Date: <b>$fecha</b>
        <INPUT type='hidden' name='fecha' value='$fecha'>
        <INPUT type='hidden' name='fecha_sigo' value='$fecha_sigo'>
        <INPUT type='hidden' name='seq_ticket_id' value='$seq_ticket_id'>
      </td>
      <td align='center'>$Operator: <b>$operador / $operador_ape_y_nom / $operador_sector_id</b> </td>
      <INPUT type='hidden' name='operador' value='$operador'>
      <INPUT type='hidden' name='operador_ape_y_nom' value='$operador_ape_y_nom'>
      <INPUT type='hidden' name='operador_sector_id' value='$operador_sector_id'>
      <td align='right'>$Contact: <b>$contacto</b><INPUT type='hidden' name='contacto' value='$contacto'></td>
    </tr>
    </TABLE>
    <center class=error>$mensaje</center>

    <TABLE class=borde_fino width='95%' cellpadding='1' cellspacing='0' align='center' >
     <tr>
      <td colspan='3'><b> $User_information </b></td>
     </tr>
     <tr>
      <td>Usuario: <b>$usuario</b> <INPUT type='hidden' name='usuario' value='$usuario'> </td>
      <td> $Last_and_first_name: <b>$ape_y_nom</b><INPUT type='hidden' name='ape_y_nom' value='$ape_y_nom'> </td>
      <td>$Area: <b>$area_id</b> <INPUT type='hidden' name='area_id' value='$area_id'> </td>
     </tr>

     <tr>
       <td colspan='3'>
        <TABLE  width='100%' cellpadding='2' cellspacing='1' align='center' >
         <tr>
          <td> $Floor: <INPUT type='text' name='piso' value='$piso' size='4' maxlength='4' > </td>
          <td>$Phone: <INPUT type='text' name='planta' value='$planta' size='30' maxlength='30' > </td>
          <td>$Elec_mail: <INPUT type='text' name='e_mail' value='$e_mail' size='45' maxlength='60' > </td>
         <td><b>$nombre_area</b></td>
        </tr>
       </TABLE>
       </td>
      </tr>
     </table>
        
    <table border='0' width='95%' cellpadding='3' cellspacing='2' align='center' >
     <tr> <td colspan='3'> <b> Datos del ticket </b> </td> </tr>
     <tr> <td valign='top'> $Incident: </td>
      <td class=caja_texto>
        $_SESSION[MOD_PHD_INCIDENTE]
      </td>
     </tr>
     <tr>
        <td";

        if (strlen($nombre_adjunto)>0)
             { echo ">   $Attached_file:</td><td> <b>$nombre_adjunto</b>
                        <input class='boton_bold' type='submit' value='$Download' name='adjunto'>
                        <input type='hidden' name='nombre_adjunto' value='$nombre_adjunto'> ";
             }
        else
            {echo "colspan='2'>";

            }
echo " </td>
    </tr>

   <tr> <td valign='top'> $Comment: ";

if ($_SESSION['PHD_SEQ_SOLICITUD_ID']>0)
        {echo "<br>
         <br>$User_visible <input type='checkbox' $visible_check name='visible' value='S'/> ";
        }

       echo " </td>
      <td>
        <TEXTAREA name='comentario' rows='5' cols='130'>$comentario</TEXTAREA>
      </td>
     </tr>
     <tr>";

echo    "   <td>$Attach_file: </td>
            <td><input type='file' name='sigo_adjunto' size='60' maxlength='120'> (Max. $text_max_attach)
        </td>
    </tr>

    </TABLE>



    <TABLE  width='95%' cellpadding='5' cellspacing='1' align='center' >
      <tr>
        <td>$Priority: <select name='prioridad'>";
        for ($I=5;$I>0;$I--)
            {if ($I==$prioridad)
                {$selected='selected';
                }
             else
                {$selected='';
                }
             echo "<option $selected value='$I'> $I ";
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
       <td>
        $Assigned_to: <SELECT name='asignado_a'>
            <option> </option>";

        $query="SELECT operador_id, ape_y_nom, sector_id
                FROM {$MyPHD}operador
                WHERE (nivel>0 AND
                (sector_id='$_SESSION[PHD_SECTOR_ID]' OR privado='N')) OR
                operador_id='$asignado_a'
                ORDER BY sector_id, operador_id";
        $result=mysql_query($query) or die ($No_database);

        while ($row = mysql_fetch_array($result))
            { if ($row['operador_id']==$asignado_a)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<OPTION $selected value='$row[operador_id]'> $row[operador_id] - $row[ape_y_nom] / $row[sector_id] </OPTION> \n";
	       }


## Armo la lista de opciones de proceso
## IMPORTANTE: Como la base de datos tiene atributos que hoy pueden no
## estar activos y si estar en la tabla de tickets voy a validar que el
## valor actual figure en la lista, de no ser así lo agrego, esto es lo que
## detecta la variable $existe.

// Make the list of process options
// IMPORTANT: As the data base has attributes that today can not be active
// and if to be in the table of tickets going to validate that present value
// appears in the list, otherwise add, this is what detects the variable $existe.

echo
"               </SELECT>
       </td>
       <td>";

## Solo pueden ver y cambiar el atributo privado un operador del sector que ingresó el ticket
// Only can view and change the private attribute an operator that belong to the sector has inserted the ticket.

if ($operador_sector_id==$_SESSION['PHD_SECTOR_ID'])
    {
      echo "$Private &nbsp; <input type='checkbox' $private_check name='privado' value='S' />";
    }
else
    { echo "<input type='hidden' name='privado' value='$privado' />
            $Private: ";
      if ($privado=="S")
            {echo "<b>$Yes</b>";
            }
         else
            {echo "<b>$No</b>";
            }
    }

echo
       "</td>
      </tr>

      <tr>
       <td>
        $Process: <SELECT name='proceso' >";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Process' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die ($No_database);


        $existe=false;
        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$proceso)
                {$selected='selected';
                 $existe=true;
                }
            else
                {$selected='';
                }
            echo "<OPTION $selected> {$row['valor']} </OPTION> \n";
	       }
        if (!$existe)
            {echo "<OPTION selected> $proceso </OPTION> \n";
            }
echo
"               </SELECT>
       </td>";

## Ahora armo la lista de clasificación de tipo y subtipo, primero
## armo la lista de los "tipos";
// Make the list of type and subtype, at first the type list.


echo
"      <td>
        $Type: <SELECT name='tipo' onBlur='f_sub_tipo(this);' >";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Type' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die ($No_database);

        $existe=false;
        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$tipo)
                {$selected='selected';
                 $existe=true;
                }
              else
                {$selected='';
                }
            echo "<OPTION $selected value='{$row['valor']}' > {$row['valor']} </OPTION> \n";
	        }
        if (!$existe)
            {echo "<OPTION selected> $tipo </OPTION> \n";
            }
echo
"       </SELECT>
       </td>";

## Ahora armo la lista de selección de subtipos
// make the subtype list

echo
"      <td>
        $Subtype: <SELECT name='sub_tipo'>";


      $query="SELECT b.atributo, b.valor
            FROM {$MyPHD}atributo a, {$MyPHD}atributo b
            WHERE a.valor=b.atributo and a.atributo='$Type' and a.valor='$tipo' and b.activo='S'
            ORDER BY b.atributo, b.valor";
        $result=mysql_query($query) or die ($No_database);
        $existe=false;
        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$sub_tipo)
                {$selected='selected';
                 $existe=true;
                }
              else
                {$selected='';
                }
            echo "<OPTION $selected value='{$row['valor']}' > {$row['valor']} </OPTION> \n";
	        }
        if (!$existe)
            {echo "<OPTION selected> $sub_tipo </OPTION> \n";
            }
echo
"      </SELECT>
       </td>
      </tr>";


## Armo la lista de opciones de estado del ticket
// make the state option list.

echo
    "<tr>
       <td>
        $State: <SELECT name='estado' onChange='document.ticket.fecha_ultimo_estado.value=f_fecha();'>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$State' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die ($No_database);

        $existe=false;
        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$estado)
                {$selected='selected';
                 $existe=true;
                }
            else
                {$selected='';
                }
            echo "<OPTION $selected value='{$row['valor']}'> {$row['valor']} </OPTION> \n";
	        }
        if (!$existe)
            {echo "<OPTION selected> $estado </OPTION> \n";
            }

echo
"        </SELECT>
        </td>
        <td>

       $Last_state_date: <INPUT type='text' name='fecha_ultimo_estado' value='$fecha_ultimo_estado' size='19' maxlength='19' >

        </td>
        <td>
        $estado $By: <b>$operador_ultimo_estado</b>

        <INPUT type='hidden' name='operador_ultimo_estado' value='$operador_ultimo_estado'>
        </td>
       </tr>
      </TABLE>
      <p>
      <TABLE border='0' cellspacing='1' cellpadding='2' width='100%'>
             <tr>
              <td align='right'>
               <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$Save' name='guardar' onclick='this.value=\"Wait...\"' />
              </td>
              <td align='right'>
               <input class='boton_salir' style='width: {$ancho_salir}px;' type='button' name='button' value='$Close' onClick='window.close()' />
              </td>
             </tr>
           </TABLE>
 ";

echo "</FORM>";

## Cargo el vector con los datos del seguimiento del ticket
// Load the vector with the follow up data.

      $query="SELECT seq_sigo_ticket_id, fecha, operador_id, usuario_id, campo_cambiado, valor_anterior, valor_actual, comentario, nombre_adjunto
       FROM {$MyPHD}sigo_ticket WHERE seq_ticket_id=$seq_ticket_id";
      $result=mysql_query($query) or die ($No_database);
      $I=0;
      while ($row = mysql_fetch_array($result))
        {$sigo_ticket[$I]['seq_sigo_ticket_id']=$row['seq_sigo_ticket_id'];
         $sigo_ticket[$I]['fecha']=date("$Date_format H:i:s",strtotime($row['fecha']));
         $sigo_ticket[$I]['operador']=$row['operador_id'];
         $sigo_ticket[$I]['usuario']=$row['usuario_id'];
         $sigo_ticket[$I]['campo_cambiado']=$row['campo_cambiado'];
         $sigo_ticket[$I]['valor_anterior']=$row['valor_anterior'];
         $sigo_ticket[$I]['valor_actual']=$row['valor_actual'];
         $sigo_ticket[$I]['comentario']=str_replace(chr(10),"<br>",str_replace(chr(13),"",htmlentities($row['comentario'],ENT_QUOTES,"ISO-8859-1")));
         $sigo_ticket[$I]['nombre_adjunto']=$row['nombre_adjunto'];
         $I++;
        }

## Si corresponde, muestro el seguimiento del ticket
// If it correspond, show the follow up of the ticket.

if (count($sigo_ticket)>0)
    {echo "<hr />
            <b> $Tkt_follow_up </b>
            <TABLE border='0' cellspacing='1' cellpadding='2' width='100%'>
            <tr>
	           <th>$Date</th>
	           <th>$Operator</th>
	           <th>$User</th>
	           <th>$Modified_field</th>
	           <th>$Previous_value</th>
               <th>$New_value</th>
               <th>$Comment</th>
               <th>$Attached_file</th>
            </tr>";
    $color[0]='class=b_linea_1';
    $color[1]='class=b_linea_2';
    $renglon_ant="";
    $J=0;
    for ($I=0; $I<count($sigo_ticket); $I++)
        {if ($renglon_ant<>$sigo_ticket[$I]['fecha'].$sigo_ticket[$I]['operador'])
                       { $J++;
                         $J=$J % 2;
                         echo "<tr $color[$J]>
                             <td>{$sigo_ticket[$I]['fecha']}</td>
                             <td>{$sigo_ticket[$I]['operador']}</td>
                             <td>{$sigo_ticket[$I]['usuario']}</td>";
                        $renglon_ant=$sigo_ticket[$I]['fecha'].$sigo_ticket[$I]['operador'];
                       }
                 else
                       {echo "<tr $color[$J]>
                              <td></td>
                              <td></td>
                              <td></td>";
                       }
echo "          <td>{$sigo_ticket[$I]['campo_cambiado']}</td>
                <td>{$sigo_ticket[$I]['valor_anterior']}</td>
                <td>{$sigo_ticket[$I]['valor_actual']}</td>
                <td>{$sigo_ticket[$I]['comentario']}</td>
                <td>";
                if (strlen($sigo_ticket[$I]['nombre_adjunto'])>1)
                     {echo "<input class='boton' type='button' name='s_adjunto' value='{$sigo_ticket[$I]['nombre_adjunto']}' onClick='window.location=\"abro_adjunto.php?file={$sigo_ticket[$I]['seq_sigo_ticket_id']}\"' />";
                     }
echo            "</td>

                </tr>";
        }
    }
echo "</table>


</body>
</html>";
?>

