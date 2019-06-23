<?PHP
/*
    Nombre: set_base.inc
    Autor: Julio Tuozzo
    Función: Configura las variables de acceso a la base de datos en config.inc.php
    Ver: 2.12
*/

include('setup_head.inc');
echo "
<p class='now'>Par&aacute;metros de acceso a la base de datos.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje
<p>\$Host: <input type='text' name='host' value='$Host' size='20' maxlength='40'> &nbsp; &nbsp; Nombre del servidor de la base de datos MySQL.</p>

<p>\$Usuario: <input type='text' name='usuario' value='$Usuario' size='20' maxlength='40'> &nbsp; &nbsp; Usuario con que <b>PHD Help Desk</b> se conectará a la base de datos.</p>

<p>\$Contrasena: <input type='text' name='contrasena' value='$Contrasena' size='20' maxlength='40'> &nbsp; &nbsp; Contrase&ntilde;a del usuario.</p>

<p>\$Base: <input type='text' name='base' value='$Base' size='20' maxlength='40'> &nbsp; &nbsp; Nombre de la base de datos.</p>

<p><span style='color:#FF0000; font-weight: bold;'>IMPORTANTE:</span>
Estos valores ya deben estar creados en la base de datos <b>MySQL</b>, de lo contrario no podrá seguir avanzando en la instalaci&oacute;n de <b>PHD Help Desk</b>. <br />
Las variables se almacenan en el archivo <i><b>config.inc.php</b></i>, en caso de ser necesario en un futuro modificarlas podr&aacute; hacerlo editando  <i><b>config.inc.php</b></i> escribiendo los nuevos valores manualmente.</p>

<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Guardar valores' name='b_base'></p>
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancelar' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
