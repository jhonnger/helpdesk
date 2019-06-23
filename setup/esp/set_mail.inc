<?PHP
/*
    Nombre: set_mail.inc
    Autor: Julio Tuozzo
    Función: Configura las variables de conexión con el servidor SMTP.
    Ver: 2.12
*/

include('setup_head.inc');
echo "
<p class='now'>Par&aacute;metros del servidor para enviar correo electr&oacute;nico.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje
<p>\$Mail_host: <input type='text' name='host' value='$Mail_host' size='60' maxlength='60'> &nbsp; &nbsp; Nombre del servidor SMTP para enviar correo.</p>

<p>\$Mail_usuario: <input type='text' name='usuario' value='$Mail_usuario' size='60' maxlength='60'> &nbsp; &nbsp; Usuario del  servidor.</p>

<p>\$Mail_clave: <input type='text' name='clave' value='$Mail_clave' size='20' maxlength='40'> &nbsp; &nbsp; Clave del usuario.</p>

<p>\$Mail_port: <input type='text' name='port' value='$Mail_port' size='5' maxlength='5'> &nbsp; &nbsp; Puerto de acceso.</p>

<p>Las variables se almacenan en el archivo <i><b>config.inc.php</b></i>, en caso de ser necesario en un futuro modificarlas podr&aacute; hacerlo editando  <i><b>config.inc.php</b></i> escribiendo los nuevos valores manualmente.</p>

<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Guardar valores' name='b_mail'></p>
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancelar' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
