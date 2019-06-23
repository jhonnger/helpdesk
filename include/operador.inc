<?PHP
/*
    Nombre: operador.inc
    Autor: Julio Tuozzo
    Función: Vista de administración de operadores del sistema
    Function: Sistem operators administration view.
    Ver: 2.12
*/

$opcion=$Oper_admin;
require('head_frame.inc');
echo "<body>";
require('menu.inc');
echo "<div id='contenido'>
    <div class='error'> $mensaje </div>

    <form method='post' action='$_SERVER[PHP_SELF]?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros'' >";
 
## Valido si dibujo el formulario para dar de alta operadores o para
## modificarlos
// Check if drawing the form to insert operators or for to modify them

    if (isSet($_POST['modificar']))
        {echo "$Operator: <b>$operador</b> &nbsp; &nbsp;
        <input type='hidden' name='operador' value=$operador >";
         $guardar=$Modif;
         $tipo_genero_clave='submit'; // esta variable hace que se vea el botón de generar contraseña
         $tipo_cancelo='submit'; // esta variable hace que aparezca el botón "cancelar"
        }
    else
        { echo "$Operator: <input type='text' name='operador' size='15' maxlength='15' value=$operador >  &nbsp; &nbsp;";
         $guardar=$Save;
         $tipo_genero_clave='hidden';
         $tipo_cancelo='hidden';
        }

    echo "$Last_and_first_name: <input type='text' name='ape_y_nom' size='40' maxlength='40' value='$ape_y_nom'>  &nbsp; &nbsp;
          <input class='boton' type='$tipo_genero_clave' name='genero' value='$Gener_new_pswd' onclick='this.value=\"Wait...\"' />
           <br /><br />
          $Elec_mail: <input type='text' name='e_mail' size='50' maxlength='60' value='$e_mail'>  &nbsp; &nbsp;

          $Access_level:
          <SELECT name='nivel'>
              <OPTION $_10> $Operator </OPTION>
              <OPTION $_20> $Administrator </OPTION>
              <OPTION $_0> $No_access </OPTION>
          </SELECT>
          
          <br /> <br />
          
          $Sector: <select name='sector_id'>
              <option>  </option>";
    $query="SELECT sector_id, nombre
            FROM {$MyPHD}sector
            WHERE activo='S'
            ORDER BY sector_id";

    $result=mysql_query($query) or die (mysql_error());

    while ($row = mysql_fetch_array($result))
       { if ($row['sector_id']==$sector_id)
            {$selected='selected';
            }
        else
            {$selected='';
            }
         echo "<option $selected value='$row[sector_id]'> $row[sector_id] -  $row[nombre] </option> \n";
	   }

$ancho_guardar=22+(strlen($guardar)*8);
$ancho_salir=22+(strlen($Exit)*8);
$ancho_cancelar=22+(strlen($Cancel)*8);

echo    "</select>
        &nbsp; &nbsp; &nbsp;
        $Private <input type='checkbox' $private_check name='privado' value='1' />
        &nbsp; &nbsp; &nbsp;
        $Alert_assign <input type='checkbox' $avisar_asignado_check name='avisar_asignado' value='1' />
        &nbsp; &nbsp; &nbsp;
        $Alert_user_request <input type='checkbox' $avisar_solicitud_check name='avisar_solicitud' value='1' />
         <br />
           <TABLE border='0' cellspacing='1' cellpadding='5' width='100%'>
             <tr>
              <td width='30%'>
              <input  class='boton_cancelar' style='width: {$ancho_cancelar}px;' type='$tipo_cancelo' value='$Cancel' name='cancelar'>
              </td>
              <td align='center'>
               <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$guardar' name='$guardar' onclick='this.value=\"Wait...\"' />
              </td>
              <td align='right' width='30%'>
               <input class='boton_salir' style='width: {$ancho_salir}px;' type='submit' value='$Home' name='salir'>
              </td>
             </tr>
           </table>
   </form>";

## Muestro los datos de los operadores
// Show the operator data.

echo "
 <iframe src='operador_list.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' onLoad='this.style.height=document.body.clientHeight-this.offsetTop-95;' />

  </body>
</html>";
?>