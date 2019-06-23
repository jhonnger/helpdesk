<?PHP
/*
    Nombre: area.inc
    Autor: Julio Tuozzo
    Función: Vista de administración de áreas.
    Function: Administration areas view.
    Ver: 2.12

*/
$opcion=$Area_admin;
require('head_frame.inc');

## Formulario de ingreso de datos del área.
// Area data input form.

echo "<body>";
require('menu.inc');
echo "<div id='contenido'>
    <div class='error'> $mensaje </div>

    <form method='post' action='$_SERVER[PHP_SELF]?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros'>";

    if (isSet($_POST['area_modificar']) or $fail_modif)
        {echo "$Area_code: <strong>$area_id</strong> &nbsp; &nbsp;
         <input type='hidden' name='area_id' value='$area_id' >";
        }
    else
        {echo "$Area_code: <input type='text' name='area_id' size='15' maxlength='15' value='$area_id' > &nbsp; &nbsp;";
        }
$ancho_guardar=22+(strlen($value_guardar)*9);
$ancho_salir=22+(strlen($Exit)*10);
$ancho_cancelar=22+(strlen($Cancel)*9);
echo
"   $Name: <input type='text' name='nombre' size='50' maxlength='50' value='$nombre' >
    &nbsp; &nbsp; &nbsp;
    $Active <input type='checkbox' $active_check name='activo' value='1' />

           <TABLE border='0' cellspacing='1' cellpadding='5' width='100%'>
             <tr>
             <td width='30%'>
               <input class='boton_cancelar' style='width: {$ancho_cancelar}px;'  type='$type_cancelar' value='$Cancel' name='cancelar'>
              </td>
              <td align='center'>
               <input class='boton_guardar' style='width: {$ancho_guardar}px;' type='submit' value='$value_guardar' name='$name_guardar'>
              </td>
              <td align='right' width='30%'>
               <input class='boton_salir' style='width: {$ancho_salir}px;' type='submit' value='$Home' name='salir'>
              </td>
             </tr>
           </TABLE>
   </FORM> ";

## Muestro los datos de las áreas
// Show the areas data
echo "
 <iframe src='area_list.php?orden=$orden&sentido=$sentido&pagina=$pagina&q_registros=$q_registros' onLoad='this.style.height=document.body.clientHeight-this.offsetTop-75;' />

    </div>
  </body>
</html>";
?>
