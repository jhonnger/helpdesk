<?PHP
/*
    Nombre: set_tables.inc
    Autor: Julio Tuozzo
    Función: Creation of the tables in the data base.
    Ver: 2.12
*/


include('setup_head.inc');
echo "<p class='now'>Create tables in the data base.</p>
<form method='post' action='$_SERVER[PHP_SELF]' >
$mensaje";
if (!isset($mensaje))
    {echo "<h2 class='danger'>IMPORTANT:</h2>
     <p class='now'>This process will create the following tables in the data base <i><b>$Base</b></i>: area, atributo,  e_mail_error, ticket, hist_pass, operador, parametros, sector, sigo_ticket, solicitud, usuario.<br />
    Be sure that the user <i><b>$Usuario</b></i> has permissions to make CREATE TABLE in the base and that does not exist tables with these names.</p>
    <p style='text-align:center'> <input class='boton_bold'  type='submit' value='Create tables' name='b_tables'></p>";
    }
echo "
<p style='text-align:right'> <input class='boton_bold' type='button' value='Cancel' onclick='window.location=\"index.php\"'></p>

</form>
</body>
</html>";
?>
