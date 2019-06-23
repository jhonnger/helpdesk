<?PHP
/*
    Nombre: set_tables.inc
    Autor: Julio Tuozzo
    Función: Creación de tablas en la base de datos
    Ver: 2.12
*/

include('setup_head.inc');
echo "<p class='now'>Creaci&oacute;n de las tablas en la base de datos.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje";
if (!isset($mensaje))
    {echo "<h2 class='danger'>IMPORTANTE:</h2>
     <p class='now'>Este proceso creará las siguientes tablas en la base <i><b>$Base</b></i>: area, atributo, e_mail_error, hist_pass, operador, parametros, sector, sigo_ticket, ticket, solicitud, usuario.<br />
    Asegúrese que el usuario <i><b>$Usuario</b></i> posea permisos para realizar CREATE TABLE en la base y que no existan tablas con estos nombres.</p>
    <p style='text-align:center'> <input class='boton_bold'  type='submit' value='Crear tablas' name='b_tables'></p>";
    }
echo "
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancelar' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";

?>
