<?PHP
/*
    Nombre: usuario.inc
    Autor: Julio Tuozzo
    Función: Vista de administración de usuarios de los casos
    Function: Administration of ticket's users view
    Ver: 2.00
*/


## Formulario de ingreso de datos del usuario.
// User data input form.
$opcion=$Users_admin;

require('head_frame.inc');
echo "<body>";
require('menu.inc');
echo "<div id='contenido'>
    <div class='error'> $mensaje </div>
    <FORM method='post' action='$_SERVER[PHP_SELF]?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' >";

## Valido si dibujo el formulario para dar de alta de usuarios o para
## modificarlos
// Check if drawing the form to insert users or for to modify them

    if (isSet($_POST['usr_modificar']) or $fail_modif)
        {echo "$User: <b>$usuario_id</b> &nbsp; &nbsp;
        <input type='hidden' name='usuario_id' value=$usuario_id >";
         $value_guardar=$Modif;
         $name_guardar='modificar';
         $boton_genero_clave="<input class='boton' type='submit' name='genero' value='$Gener_new_pswd' onclick='this.value=\"Wait...\"' />";
         $tipo_cancelo='submit'; // esta variable hace que aparezca el botón "cancelar"
        }
    else
        { echo "$User: <input type='text' name='usuario_id' size='15' maxlength='15' value='$usuario_id' >  &nbsp; &nbsp;";
         $value_guardar=$Save;
         $name_guardar='guardar';
         $tipo_cancelo='hidden';
        }
$ancho_guardar=22+(strlen($value_guardar)*8);
$ancho_salir=25+(strlen($Home)*9);
$ancho_cancelar=22+(strlen($Cancel)*8);

    echo "$Last_and_first_name: <input type='text' name='ape_y_nom' size='50' maxlength='50' value='$ape_y_nom'>  &nbsp; &nbsp;
        &nbsp;
         $boton_genero_clave
           <br /><br />
          $Elec_mail: <input type='text' name='e_mail' size='60' maxlength='60' value='$e_mail'>  &nbsp; &nbsp;
          $Floor: <input type='text' name='piso' size='4' maxlength='4' value='$piso'>  &nbsp; &nbsp;
          $Phone: <input type='text' name='planta' size='30' maxlength='30' value='$planta'><br />
          <br />

          $Area: <select name='area_id'>
              <option>  </option>";
    $query="SELECT area_id, nombre
            FROM {$MyPHD}area
            WHERE activo='S'
            ORDER BY area_id";

    $result=mysql_query($query) or die (mysql_error());

    while ($row = mysql_fetch_array($result))
       { if ($row['area_id']==$area_id)
            {$selected='selected';
            }
        else
            {$selected='';
            }
         echo "<option $selected value='$row[area_id]'> $row[area_id] -  $row[nombre] </option> \n";
	   }



echo    "</select>
        &nbsp; &nbsp; &nbsp;
        $Active <input type='checkbox' $active_check name='activo' value='1' />
         <br />
           <TABLE border='0' cellspacing='1' cellpadding='5' width='100%'>
             <tr>
              <td width='30%'>
              <input class='boton_cancelar' style='width: {$ancho_cancelar}px;' type='$tipo_cancelo' value='$Cancel' name='cancelar'>
              </td>
              <td align='center'>
               <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$value_guardar' name='$name_guardar'>
              </td>
              <td align='right' width='30%'>
               <input class='boton_salir' style='width: {$ancho_salir}px;' type='submit' value='$Home' name='salir'>
              </td>
             </tr>
           </TABLE>

   </FORM>";

## Muestro los datos de los usuarios
// Show the users data
echo "
 <iframe src='usuario_list.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' onLoad='this.style.height=document.body.clientHeight-this.offsetTop-85;' />


  </body>
</html>";

?>

