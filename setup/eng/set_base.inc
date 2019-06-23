<?PHP
/*
    Name: set_base.inc
    Autor: Julio Tuozzo
    Función: Configure the access variables of phd.inc
    Ver: 2.12
*/

include('setup_head.inc');
echo "
<p class='now'>Data base access parameters.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje
<p>\$Host: <input type='text' name='host' value='$Host' size='20' maxlength='40'> &nbsp; &nbsp; Name of the MySQL data base server.</p>

<p>\$Usuario: <input type='text' name='usuario' value='$Usuario' size='20' maxlength='40'> &nbsp; &nbsp; User whereupon <b>PHD Help Desk</b> will connect to the MySQL data base.</p>

<p>\$Contrasena: <input type='text' name='contrasena' value='$Contrasena' size='20' maxlength='40'> &nbsp; &nbsp; User's password.</p>

<p>\$Base: <input type='text' name='base' value='$Base' size='20' maxlength='40'> &nbsp; &nbsp; Data base name.</p>

<p><span style='color:#FF0000; font-weight: bold;'>IMPORTANT:</span>
These values already must be created in the data base <b>MySQL</b>, otherwise it will not be able to continue advancing in <b>PHD Help Desk</b> installation. <br />
The variables are stored in the file <b><i>config.inc.php</i></b> that is  in <i><b>/phd_2_12/</b></i>, in case of being necessary in the future to modify them, you will edit manually <b><i>config.inc.php</i></b> and writing the new values.</p>

<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Save values' name='b_base'></p>
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancel' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
