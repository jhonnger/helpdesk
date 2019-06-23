<?PHP
/*
    Nombre: ticket_insert.inc
    Autores: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Formulario de ingreso de ticket de mesa de ayuda.
    Function: Form of entrance of ticket of help desk.
    Ver: 2.12
*/

$opcion=$New_ticket;
$ancho_guardar=23+(strlen($Save)*9);
$ancho_salir=23+(strlen($Exit)*9);
require('head.inc');

## Inicio el formulario de carga de tickets
// Start the load tiket form.
echo
"<body>";
require('menu.inc');

## Funcion JavaScript que verifica que al salir del formulario
## esten vacíos los campos usuario e incidente por si apretó
## el botón "Cerrar" por error.

// Javascript function  that verifies that when leaving the form
// the fields 'user' and 'incident' are empty in case the button 'Cerrar' (Close)
// tightened by error

echo
"
<SCRIPT LANGUAGE='JavaScript'>
window.onbeforeunload = function(e)
        {	if (verifico_vacio())
                {return '$Are_data_loaded';
	            }
        };
    
    function verifico_vacio()
        { var c_usuario=document.ticket.usuario.value;
          var c_inci=document.ticket.incidente.value;
          if ((c_usuario.length>0 || c_inci.length>0) && document.ticket.guardar.value!='Wait...')
            {return true

            }
        else
            {return false
            }
        }

</script>\n";

require('f_subtipo_JS.inc');
require('f_fecha_JS.inc');
require('f_usuario_AJAX.inc');

echo "
<script language='JavaScript'>
window.onload = function ()
        { document.getElementById('disp_fecha').innerHTML = document.ticket.fecha.value= document.ticket.fecha_ultimo_estado.value=f_fecha();
          document.getElementById('usuario').onblur = valida_usuario;
          document.getElementById('area_id').onblur = valida_area;
          valida_area();
        }
</script>

<div id='contenido'>
<form enctype='multipart/form-data' name='ticket' method='post' action='$_SERVER[PHP_SELF]'>
    <table border='0' width='95%' cellpadding='1' cellspacing='1' align='center'>
     <tr>
      <td align='left'> $Date: <strong id='disp_fecha'>$fecha</strong> <INPUT type='hidden' name='fecha' value='$fecha'> </td>
      <td align='center'>$Operator: <strong>$operador - $operador_ape_y_nom</strong> </td>";
    
echo
"     <td align='right'>
        $Contact: <SELECT name='contacto'>
            <option></option>";

    $query="SELECT valor
            FROM {$MyPHD}atributo
            WHERE atributo='$Contact' AND activo='S'
            ORDER BY valor";
    $result=mysql_query($query) or die (mysql_error());
    
    while ($row = mysql_fetch_array($result))
       { if ($row['valor']==$contacto)
            {$selected='selected';
            }
        else
            {$selected='';
            }
         echo "<OPTION $selected> {$row['valor']} </OPTION> \n";
	   }
echo
"    </select>
     </td>
    </tr>
    </table>
    <div id='mensaje' class='error'>$mensaje</div>

    <table class='borde_fino' width='95%' cellpadding='1' cellspacing='0' align='center' >
     <tr>
      <td colspan='3'><strong> $User_information </strong></td>
     </tr>
     <tr>
      <td>
      $User: <input type='text' name='usuario' id='usuario' value='$usuario' size='15' maxlength='15' onblur='f_actualizo_fechas()' />&nbsp;
       <input class='boton_lupa' style='cursor:pointer' title='$Search $User' type='button' value= '' onclick=window.open('usr_busco.php','','width=500,height=390,scrollbars=1,resizable=1,toolbar=0,location=0,menubar=0,status=0,directories=0') />
      </td>
      <td> $Last_and_first_name: <INPUT type='text' name='ape_y_nom' id='ape_y_nom' value='$ape_y_nom' size='45' maxlength='50' > </td>
      <td> $Area: <input type='text' name='area_id' id='area_id' value='$area_id' size='15' maxlength='15' > </td>
     </tr>";

## Pido el resto de los datos
// Get the rest of the data

echo
    " <tr>
       <td colspan='3'>
        <table  width='100%' cellpadding='2' cellspacing='1' align='center' >
         <tr>
          <td> $Floor: <INPUT type='text' name='piso' id='piso' value='$piso' size='4' maxlength='4' > </td>
          <td>$Phone: <INPUT type='text' name='planta' id='planta' value='$planta' size='30' maxlength='30' > </td>
          <td>$Elec_mail: <INPUT type='text' name='e_mail' id='e_mail' value='$e_mail' size='45' maxlength='60' > </td>
         <td ><strong><div id='nombre_area'>$nombre_area</div></strong></td>
        </tr>
       </table>
       </td>
      </tr>

      <tr>
        <td colspan='3' align='center' class='error' ><span id='alert'></span>
        </td>
       </tr>

   </table>
        
    <table border='0' width='95%' cellpadding='3' cellspacing='1' align='center' >
     <tr> <td colspan='2'> <strong> $Ticket_information </strong> </td>
          
     </tr>
     <tr> <td valign='top'> $Incident: </td>
      <td>
        <TEXTAREA name='incidente' rows='4' cols='130'>$incidente</TEXTAREA>
      </td>
     </tr>
     <tr> <td valign='top'> $Comment: </td>
      <td>
        <TEXTAREA name='comentario' rows='4' cols='130'>$comentario</TEXTAREA>
      </td>
     </tr>
    <tr>
    <td>$Attach_file: </td>
            <td><input type='file' name='adjunto' size='60' maxlength='120'> (Max. $text_max_attach)
        </td>
    </tr>
    </table>

<br />
<table  width='95%' cellpadding='3' cellspacing='1' align='center' >
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
       <td colspan=>
        $Assigned_to: <SELECT name='asignado_a'>
            <option> </option>";

        $query="SELECT operador_id, ape_y_nom, sector_id
                FROM {$MyPHD}operador
                WHERE nivel>0 AND
                (sector_id='$_SESSION[PHD_SECTOR_ID]' OR privado='N')
                ORDER BY sector_id, operador_id";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['operador_id']==$asignado_a)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<OPTION $selected value='$row[operador_id]'> $row[operador_id] - $row[ape_y_nom] / $row[sector_id]  </OPTION> \n";
	       }

echo
"               </SELECT>
       </td>
       <td>$Private &nbsp; <input type='checkbox' $private_check name='privado' value='S' />
       </td>
      </tr>
      <tr>
       <td>
        $Process: <SELECT name='proceso'>
                  <option></option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Process' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$proceso)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<OPTION $selected> {$row['valor']} </OPTION> \n";
	       }

echo
"               </SELECT>
       </td>";

## Ahora armo la lista de clasificación de tipo y subtipo, primero
## armo la lista de los "tipos";
// Make the list of classification of type and subtype, at first
// make the list of the “types”;

echo
"      <td>
        $Type: <SELECT name='tipo' onBlur='f_sub_tipo(this);' >
                <option></option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Type' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$tipo)
                {$selected='selected';
                }
              else
                {$selected='';
                }
            echo "<OPTION $selected value='{$row['valor']}' > {$row['valor']} </OPTION> \n";
	        }

echo
"       </SELECT>
       </td>";

## Ahora armo la lista de selección de subtipos.
// Make the subtype list.

echo
"      <td>
        $Subtype: <SELECT name='sub_tipo'>";

        $query="SELECT b.atributo, b.valor
            FROM {$MyPHD}atributo a, {$MyPHD}atributo b
            WHERE a.valor=b.atributo and a.atributo='$Type' and a.valor='$tipo' and b.activo='S'
            ORDER BY b.atributo, b.valor";
        $result=mysql_query($query) or die (mysql_error());
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


#### Armo la lista de opciones de estado del ticket

echo
    "<tr>
       <td>
        $State: <SELECT name='estado' onChange='document.ticket.fecha_ultimo_estado.value=f_fecha();'>
                 <option></option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$State' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$estado)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<OPTION $selected value='{$row['valor']}'> {$row['valor']} </OPTION> \n";
	        }

echo
"        </select>
        </td>
        <td colspan='2'>

       $Last_state_date: <input type='text' name='fecha_ultimo_estado' value='$fecha_ultimo_estado' size='19' maxlength='19' >

        </td>
       </tr>
      </table>
      <p>

      <table class='borde_fino' border='0' cellspacing='0' cellpadding='0' width='95%' align='center'>
             <tr>
              <td align='right'>
               <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$Save' name='guardar' onclick='this.value=\"Wait...\"'>
              </td>
              <td align='right'>
               <input class='boton_salir' style='width: {$ancho_salir}px;' type='button' value='$Home' name='Salir'
               onClick='window.location=\"index.php\";'>
              </td>
             </tr>
           </table>


    </form>
 </div> ";
    ## Verifico si tengo número de ticket anterior para informarlo al operador
    // Verify if exists the previous ticket number to inform it yo the operator.

    if ($_SESSION['PHD_SEQ_TICKET_ID']>0)
        {echo "<SCRIPT LANGUAGE='JavaScript'> \n
         window.alert('$Ticket_was_stored #$_SESSION[PHD_SEQ_TICKET_ID]')
         </SCRIPT>\n";
         $_SESSION['PHD_SEQ_TICKET_ID']=0;
        }

echo "
</body>
</html>";
?>

