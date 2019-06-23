<?PHP
/*
    Nombre: user_request.inc
    Autor: Julio Tuozzo
    Función: Ingreso de solicitud de soporte
    Function: Input of support request.
    Ver: 2.00
*/
$opcion="<h2>$Support_request</h2>";
$ancho_guardar=22+(strlen($Save)*8);

## Verifico si tengo número de solicitud anterior para informarlo al operador
// Verify if exists the previous ticket number to inform it yo the operator.

if ($_SESSION['PHD_SEQ_SOLICITUD_ID']>0)
    {  $Request_was_send=str_replace("%1%", " #$_SESSION[PHD_SEQ_SOLICITUD_ID] ",$Request_was_send );
       $mensaje=$Request_was_send;
       $_SESSION['PHD_SEQ_SOLICITUD_ID']=0;
    }


require('head.inc');

## Inicio el formulario de carga solicitudes
// Start the load request form.

echo "<body>";
require('user_menu.inc');
## Traigo las funciones JavaScript
// Get the JavaScript functions.
require('f_fecha_JS.inc');

echo "
<script language='JavaScript'>
window.onload = function ()
        { document.getElementById('disp_fecha').innerHTML = document.solicitud.fecha.value= f_fecha();
        }
</script>

<div id='contenido'>
    <div id='mensaje' class='error'>$mensaje</div>
    <form enctype='multipart/form-data' name='solicitud' method='post' action='$_SERVER[PHP_SELF]' style='line-height:2.0;' >
     $Date: <strong id='disp_fecha'>$fecha</strong> <INPUT type='hidden' name='fecha' value='$fecha'>

   <div class='borde_fino'>
     <strong> $User_information </strong> <br />
      $User: <strong> {$_SESSION['PHD_OPERADOR']} </strong> &nbsp; &nbsp; 
      $Last_and_first_name: <strong> {$_SESSION['PHD_APE_Y_NOM']} </strong> &nbsp; &nbsp; &nbsp; &nbsp;
      $Area: <strong> ({$_SESSION['PHD_AREA_ID']}) - {$_SESSION['PHD_AREA_NOMBRE']}</strong> <br />

      $Floor: <INPUT type='text' name='piso' id='piso' value='{$_SESSION['PHD_PISO']}' size='4' maxlength='4' > &nbsp; &nbsp; &nbsp;
      $Phone: <INPUT type='text' name='planta' id='planta' value='{$_SESSION['PHD_TELEFONO']}' size='30' maxlength='30' > &nbsp; &nbsp; &nbsp;
      $Elec_mail: <INPUT type='text' name='e_mail' id='e_mail' value='{$_SESSION['PHD_E_MAIL']}' size='45' maxlength='60' >

    </div>
        
    <div class='borde_fino'>
    <strong> $Reason_request </strong>
    <TABLE border='0' width='95%' cellpadding='3' cellspacing='1' align='center' >
     <tr> <td valign='top'> $Detail: </td>
      <td>
        <TEXTAREA name='incidente' rows='6' cols='130' >$incidente</TEXTAREA>
      </td>
     </tr>
    <tr>
    <td>$Attach_file: </td>
            <td><input type='file' name='adjunto' size='60' maxlength='120'> (Max. $text_max_attach)
        </td>
    </tr>
    </table>
    </div>
<br />
<div style='text-align:center'>
    <input class='boton_guardar' style='width: {$ancho_guardar}px;'  type='submit' value='$Save' name='guardar' onclick='this.value=\"Wait...\"'>
</div>

    </form>
</div>
</body>
</html>";
?>

