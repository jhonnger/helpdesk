<?PHP
/*
    Nombre: c_screen.inc
    Autor: Julio Tuozzo
    Función: Consulta de tickets por pantalla
    Function: Ticket consult by screen.
    Ver: 2.00

*/
## Calculo desde que registro muestro en función de la página
// Calculate since registry show based on the page.

$opcion=$Advanced_query;
$desde_reg=($pagina-1)*$_SESSION[PHD_MAX_LINES_SCREEN];

## Hago la consulta
// make query

$query="SELECT seq_ticket_id, fecha, usuario_id, ape_y_nom, area_id, incidente,
        estado, fecha_ultimo_estado, prioridad
        FROM {$MyPHD}ticket
        $condicion ORDER BY $orden $sentido LIMIT $desde_reg, $_SESSION[PHD_MAX_LINES_SCREEN]";

$result=mysql_query($query) or die (mysql_error());


require('head.inc');

echo "<body>";
if($menu=="no")
    {$ancho_salir=22+(strlen($Close)*8);
     echo "<div style='text-align:center'>
            <form method='post'>
            <input class='boton_salir' style='width: {$ancho_salir}px;' type='button' name='button' value='$Close' onClick='window.close()' />
           </form>
           </div>";
    }
else
    {require('menu.inc');
    }

echo "<div id='contenido'>";
require('ticket_display.inc');

?>
