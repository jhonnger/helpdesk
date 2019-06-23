<?PHP
/*
    Nombre: novedades_param.inc.php
    Autor: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Parámetros de la consulta de novedades 
    Function: News parameters.
    Ver: 2.12
*/


$ancho_salir=22+(strlen($Home)*8);
$ancho_consultar=22+(strlen($Consult)*8);

require('head.inc');
echo"<body>";
require('menu.inc');


## Dibujo la pantalla
// Drawing the screen

echo

"<div id='contenido'>$mensaje
<form name='novedades' method='post' action='$_SERVER[PHP_SELF]'>
<div class='consulta'>
$News $From:  </td> <td> <INPUT type='text' name='fecha_desde' size='10' maxlength='10' value='$fecha_desde'> ($Date_text) &nbsp;&nbsp; &nbsp; &nbsp;
$To: <INPUT type='text' name='fecha_hasta' size='10' maxlength='10' value='$fecha_hasta' > ($Date_text)
&nbsp; &nbsp; &nbsp; 
<input class='boton_filtrar' style='width: {$ancho_consultar}px;' type='submit' value='$Consult' name='buscar'>
<span style='position:absolute; right:50px'> <input class='boton_salir' style='width: {$ancho_salir}px;' type='button' value='$Home' onclick='window.location=\"index.php\"'> </span>
</div>
</form>
</body>
</html>";

?>
