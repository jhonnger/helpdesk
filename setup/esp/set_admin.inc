<?PHP
/*
    Nombre: set_admin.inc
    Autor: Julio Tuozzo
    Función: Formulario de alta el operador con permisos de administrador en la base
    Ver: 2.12
*/

include('setup_head.inc');
echo "
<p class='now'>Alta de operador con permiso de administrador.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje
<p>C&oacute;digo del operador: <input type='text' name='operador' value='$operador' size='15' maxlength='15'> </p>

<p>Apellido y Nombre: <input type='text' name='ape_y_nom' value='$ape_y_nom' size='40' maxlength='40'> </p>

<p>Contrase&ntilde;a: <input type='password' name='contrasenia' size='20' maxlength='20'></p>

<p>Reingrese contrase&ntilde;a: <input type='password' name='reingresa' size='20' maxlength='20'></p>

<p>Correo electr&oacute;nico: <input type='text' name='e_mail' value='$e_mail' size='50' maxlength='60'></p>

<p>C&oacute;digo del sector al que pertenece: <input type='text' name='sector_id' value='$sector_id' size='15' maxlength='15'> &nbsp; &nbsp;
nombre del sector: <input type='text' name='sector_nombre' value='$sector_nombre' size='50' maxlength='50'>
</p>

<p style='text-align:center'> <input class='boton_bold'  type='submit' value='Crear operador' name='b_admin'></p>
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancelar' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
