<?PHP
/*
    Nombre: set_mail.inc
    Autor: Julio Tuozzo
    Función: SMTP server variables configure.
    Ver: 2.12
*/

include('setup_head.inc');
echo "
<p class='now'>E mail server parameters.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje
<p>\$Mail_host: <input type='text' name='host' value='$Mail_host' size='60' maxlength='60'> &nbsp; &nbsp; SMTP server.</p>

<p>\$Mail_usuario: <input type='text' name='usuario' value='$Mail_usuario' size='60' maxlength='60'> &nbsp; &nbsp; SMTP server user.</p>

<p>\$Mail_clave: <input type='text' name='clave' value='$Mail_clave' size='20' maxlength='40'> &nbsp; &nbsp; user´s password.</p>

<p>\$Mail_port: <input type='text' name='port' value='$Mail_port' size='5' maxlength='5'> &nbsp; &nbsp; Port.</p>

<p>These variables are stored in the <i><b>config.inc.php</b></i> file, that placed in <i><b>/phd_2_12</b></i>, in case of necesary change this values in the future you can modify it editing the file  <i><b>config.inc.php</b></i> and write the new values in the variables.</p>

<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Save values' name='b_mail'></p>
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancel' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
