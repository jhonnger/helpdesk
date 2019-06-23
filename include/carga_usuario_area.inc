<?PHP
/*
    Nombre: carga_usuario_area.inc
    Autores: Julio Tuozzo / jtuozzo@p-hd.com.ar
    Función: Formulario de ingreso del archivo con los usuarios y áreas.
    Function: Form of entrance users and areas file.
    Ver: 2.12
*/

$opcion=$Load_users;
$ancho_cargar=22+(strlen($Load)*9);
$ancho_inicio=22+(strlen($Home)*10);
require('head.inc');

## Inicio el formulario de carga de tickets
// Start the load tiket form.
echo
"<body>";
require('menu.inc');

echo "
<div id='contenido'>
<div class='caja' style='text-align:center'> $proceso_ok
<h3 style='text-align:center'>$Load_csv_file</h3>
<em>$File_content: \"$User\",\"$Last_and_first_name\",\"$Elec_mail\",\"$Floor\",\"$Phone\",\"$Area_code\",\"$Name $Area\"</em><br />
<span class='error'>$mensaje</span><br />

<form enctype='multipart/form-data' name='usuario_area' method='post' action='$_SERVER[PHP_SELF]'>
$Field_delimiter: <select name='delimitador'>
	<option value=','>$Comma (,)</option>
	<option value=';'>$Semicolon (;)</option>
	<option value='\\t'>$Tab </option>
</select>
&nbsp; &nbsp; 
$Attach_file: <input type='file' name='archivo_csv' size='60' maxlength='120'> (Max. $text_max_attach)
<br />
<br />
	<input class='boton_guardar' style='width: {$ancho_cargar}px;' type='submit' value='$Load' name='cargar' onclick='this.value=\"Wait...\"' />
	<span style='position:absolute; right:30px'><input class='boton_salir' style='width: {$ancho_inicio}px;' type='submit' value='$Home' name='inicio' /></span>
    </form>
 </div>
</div> 
</body>
</html>";
?>

