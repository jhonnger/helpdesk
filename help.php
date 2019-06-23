<?PHP
/*
    Nombre: help.php
    Autor: Julio Tuozzo.
    Función: Ventana de ayuda.
    Function: Help Window.
    Versión: 2.12
*/


require('config.inc.php');
require($Include.'lang.inc');
$ancho_cerrar=24+(strlen($Close)*8);
require($Include.'head.inc');
echo "<body>


<img src='./images/phd_150_20.gif' border='0' alt='PHD Help Desk'> <br />
<small style='font-family: Arial, Helvetica, sans-serif;'>$Version</small>
<h4 class='menu'>
<p><a href='$PHD_home_url' target='_blank'  >$PHD_home</a></p>
<p><a href='$User_guide_url' target='_blank'  >$User_guide</a></p>
<p><a href='$FAQ_url' target='_blank'  >FAQ</a>
<hr /></p>
<p><a href='$Registry_url' target='_blank' >$Registry</a></p>
<p><a href='$Users_forum_url' target='_blank' >$Users_forum</a></p>
<hr />
</p>
<p><a href='$Check_last_version_url' target='_blank' >$Check_last_version</a></p>
</h4>
<hr />
<br />
<div style='text-align:center'>
    <input class='boton_salir' style='width: {$ancho_cerrar}px;' type='button' name='button' value='$Close' onClick=window.close();>
 </div></body>
</html>
";

?>

