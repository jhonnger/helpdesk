<?PHP
/*
    Nombre: set_admin.inc
    Autor: Julio Tuozzo
    Función: Create the operator with administrator permission
    Ver: 2.12
*/

include('setup_head.inc');
echo "<p class='now'>Operator with administrator level creation.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje
<p>Operator code: <input type='text' name='operador' value='$operador' size='15' maxlength='15'> </p>

<p>Last and first name: <input type='text' name='ape_y_nom' value='$ape_y_nom' size='40' maxlength='40'> </p>

<p>Password: <input type='password' name='contrasenia' size='20' maxlength='20'></p>

<p>Retype password: <input type='password' name='reingresa' size='20' maxlength='20'></p>

<p>E-mail: <input type='text' name='e_mail' value='$e_mail' size='50' maxlength='60'></p>

<p>Sector code: <input type='text' name='sector_id' value='$sector_id' size='15' maxlength='15'> &nbsp; &nbsp;
sector name: <input type='text' name='sector_nombre' value='$sector_nombre' size='50' maxlength='50'>
</p>

<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Create operator' name='b_admin'></p>
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancel' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
