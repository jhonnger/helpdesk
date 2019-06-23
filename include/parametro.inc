<?PHP
/*
    Nombre: parametro.inc
    Autor: Julio Tuozzo
    Función: Vista de administración de parámetros generales de PHD Help Desk.
    Function: PHD Help Desk's General parameters administration view.
    Ver: 2.12

*/

$opcion=$Parameters_admin;
require('head.inc');
## Formulario de ingreso de parámetros.
// Parameters data input form.

echo "<body>";
require('menu.inc');
echo "<div id='contenido'>
    <div class='error'> $mensaje </div>
<form method='post' action='$_SERVER[PHP_SELF]' >

  <table class='caja_texto' border='0' width='90%' cellpadding='4' cellspacing='4' align='center'>
    <tr>
      <td>validez_psw:</td>
      <td><input type='text' name='validez_psw' value='$validez_psw' size='3' maxlength='3'>  $validez_psw_err </td>
      <td> $Explain_validez_psw</td>
    </tr>
    <tr>
      <td>dias_psw:</td>
      <td><input type='text' name='dias_psw' value='$dias_psw' size='3' maxlength='3'> $dias_psw_err</td>
      <td>$Explain_dias_psw</td>
    </tr>
    <tr>
      <td>max_lines_screen:</td>
      <td><input type='text' name='max_lines_screen' value='$max_lines_screen' size='3' maxlength='3'> $max_lines_screen_err</td>
      <td>$Explain_max_lines_screen</td>
    </tr>
    <tr>
      <td>max_lines_export:</td>
      <td><input type='text' name='max_lines_export' value='$max_lines_export' size='6' maxlength='6'> $max_lines_export_err</td>
      <td>$Explain_max_lines_export</td>
    </tr>
    <tr>
      <td>max_dif_min:</td>
      <td><input type='text' name='max_dif_min' value='$max_dif_min' size='5' maxlength='5'> $max_dif_min_err</td>
      <td>$Explain_max_dif_min</td>
    </tr>
    <tr>
       <td>max_attach:</td>
       <td><input type='text' name='max_attach' value='$max_attach' size='8' maxlength='8'> $max_attach_err</td>
       <td>$Explain_max_attach</td>
    </tr>
    <tr>
       <td>assign_ticket:</td>
       <td><input type='checkbox' name='assign_ticket' value='S' $assign_ticket_chk /> </td>
       <td>$Explain_assign_ticket</td>
    </tr>
    <tr>
       <td>from_user_request:</td>
       <td colspan='2'><input type='text' name='from_user_request' value='$from_user_request' size='50' maxlength='60'> &nbsp;
         $Explain_from_user_request $from_user_request_err</td>
    </tr>
    <tr>
       <td>from_user_psw:</td>
       <td colspan='2'><input type='text' name='from_user_psw' value='$from_user_psw' size='50' maxlength='60'> &nbsp;
         $Explain_from_user_psw $from_user_psw_err</td>
    </tr>


    <tr>
       <td>state_alert:</td>
       <td colspan='2'> <select name='state_alert'>
       <option value=''>$None</option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$State' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$state_alert)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<option $selected value='{$row['valor']}'> {$row['valor']} </option> \n";
	        }


echo  "</select>
       &nbsp;
         $Explain_state_alert</td>
    </tr>

    <tr>
       <td>date_format:</td>
       <td colspan='2'>
            <select name='date_format'>
               <option $DMA_selected value='DMA'>$DMA</option>
               <option $MDA_selected value='MDA'>$MDA</option>
               <option $AMD_selected value='AMD'>$AMD</option>
            </select>
       &nbsp;
             $Explain_date_format</td>
    </tr>

    <tr>
       <td>main_screen_state:</td>
       <td colspan='2'> <select name='main_screen_state'>
       <option value=''>$None</option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$State' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$main_screen_state)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<option $selected value='{$row['valor']}'> {$row['valor']} </option> \n";
	        }


echo  "</select>
       &nbsp;
         $Explain_main_screen_state</td>
    </tr>


  </table>

  <h3>$Default_values</h3>

  <table class='caja_texto' border='0' width='90%' cellpadding='4' cellspacing='1' align='center'>
    <tr>
      <td>$Contact:</td>
      <td> <select name='contact_default'>
       <option value=''>$None</option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Contact' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$contact_default)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<option $selected value='{$row['valor']}'> {$row['valor']} </option> \n";
	        }


echo  "</select>
      </td>
      <td>$Process:</td>
      <td> <select name='process_default'>
       <option value=''>$None</option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$Process' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$process_default)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<option $selected value='{$row['valor']}'> {$row['valor']} </option> \n";
	        }


echo  "</select>
     </td>
      <td>$State:</td>
      <td> <select name='state_default'>
       <option value=''>$None</option>";

        $query="SELECT valor
                FROM {$MyPHD}atributo
                WHERE atributo='$State' AND activo='S'
                ORDER BY valor";
        $result=mysql_query($query) or die (mysql_error());

        while ($row = mysql_fetch_array($result))
            { if ($row['valor']==$state_default)
                {$selected='selected';
                }
            else
                {$selected='';
                }
            echo "<option $selected value='{$row['valor']}'> {$row['valor']} </option> \n";
	        }

$ancho_guardar=22+(strlen($Save)*8);
$ancho_cancelar=22+(strlen($Cancel)*8);

echo  "</select>
      </td>
   </tr>

 </table>

<H3>$Request_states</h3>
  <table class='caja_texto' border='0' width='90%' cellpadding='4' cellspacing='4' align='center'>

    <tr>
      <td>ATE:</td>
      <td><input type='text' name='ATE' value='$ATE' size='20' maxlength='20'> </td>
      <td> Estado de solicitud cuando ha sido atendido el ticket.</td><!-- CAMBIO -->
    </tr>

    <tr>
      <td>PEN:</td>
      <td><input type='text' name='PEN' value='$PEN' size='20' maxlength='20'>  $PEN_err </td>
      <td> $Explain_PEN</td>
    </tr>

    <tr>
      <td>PAS:</td>
      <td><input type='text' name='PAS' value='$PAS' size='20' maxlength='20'>  $PAS_err </td>
      <td> $Explain_PAS</td>
    </tr>

    <tr>
      <td>CAN:</td>
      <td><input type='text' name='CAN' value='$CAN' size='20' maxlength='20'>  $CAN_err </td>
      <td> $Explain_CAN</td>
    </tr>

  </table>

 <br />
  <table class='caja_texto' border='0' width='90%' cellpadding='4' cellspacing='1' align='center'>
    <tr>
      <td style='text-align:right'> <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$Save' name='guardar'></td>
      <td style='text-align:right'> <input class='boton_cancelar' style='width: {$ancho_cancelar}px;' type='button' value='$Cancel' onclick='window.location=\"index.php\"'></td>

   </tr>
 </table>
</form>
</div>
</body>
</html>";
?>

