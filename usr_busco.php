<?PHP
/*
    Nombre: usr_busco.php
    Autor: Julio Tuozzo
    Función: Busco un usuario y lo devuelve a la ventana padre.
    Function: Search for a user and it gives back to the window father to it.
    Versión: 2.12
*/


## Verifico que se encuentre validado el usuario, si no es asi lo
## dirijo a la pantalla de login.
// Verify that one is validated the user, if it is not therefore
// redirect to the screen of login.

session_start();
require('config.inc.php');
require($Include.'lang.inc');
if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<6)
    {require($Include.'login.inc');
     exit();
    }

## Me conecto con la base de datos para poder buscar
## al usuario
// Connect with the database to search the user´s data.


$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());
$ape_y_nom=htmlentities(trim(strip_tags($_POST['ape_y_nom'])),ENT_QUOTES,"ISO-8859-1");

$ancho_cerrar=24+(strlen($Close)*8);
$ancho_buscar=24+(strlen($Search)*8);

require($Include.'head.inc');
echo"  <body class='fondo'>

<div style='text-align:center'>
<i>$Enter_last_name.</i><BR /><BR />
<form method='post' action='$_SERVER[PHP_SELF]' >
    $Last_and_first_name: <input type='text' name='ape_y_nom' size='40' maxlength='40' value='$ape_y_nom'>
                       <input class='boton_buscar' style='width: {$ancho_buscar}px;' type='submit' name='buscar_usr' value='$Search'> <br />

</form>
</div>";

## Veo si se posteó el formulario para hacer la búsqueda.
// Check if post the form to become the search.

if (isset($_POST['buscar_usr']))
    {require($Include.'usr_busco.inc');
    }

echo "<br />
<div style='text-align:center'>
    <input class='boton_salir' style='width: {$ancho_cerrar}px;' type='button' name='button' value='$Close' onClick=window.close();>
 </div>
";


echo "
</body>
</html>";

?>
