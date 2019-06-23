<?PHP
/*
    Nombre: menu.inc
    Autor: Julio Tuozzo jtuozzo@p-hd.com.ar
    Función: Línea del menú principal
    Function: Main menu line
    Ver: 2.12
*/

echo "
<script type='text/javascript' src='menu_ie6.js'></script>
<table border='0' align='center' cellspacing='0' cellpadding='0' width='100%'  id='encabezado'>
<tr>
<td  width='180'><img src='./images/phd_150_20.gif' border='0' alt='Help Desk Grupo Carita Feliz' title='Help Desk Grupo Carita Feliz'/></td>
<td style='text-align:center; vertical-align:bottom'>$opcion</td>
<td style='text-align:right; vertical-align:bottom'>
    <h4 class='menu'><a href='#' onclick=\"window.open('help.php','','width=250,height=390,scrollbars=0,resizable=1,toolbar=0,location=0,menubar=0,status=0,directories=0')\">$Help</a></h4>

</td>
</tr>
</table>


<div id='menu'>
<ul>
    <li><a href='index.php'>$Home</a></li>
    <li><a href='ticket_insert.php'>$New_ticket</a></li>
    <li><a href='#'>$Consults</a>
	   <ul>
	    <li><a href='novedades.php'>$News</a></li>
	    <li><a href='consulta.php'>$Advanced_query</a></li>
	   </ul> 
    </li>
	<li><a href='solic_list.php'>$Management_requests</a></li>
    <li><a href='clave_chg.php'>$Passwd_change</a></li>";
if ($_SESSION['PHD_NIVEL']==20)
    {echo "<li><a href='#'>$Administration</a>
      <ul>
        <li><a href='area.php'>$Areas</a></li>
        <li><a href='usuario.php'>$Users</a></li>
        <li><a href='carga_usuario_area.php'>$Load_users</a></li>
        <li><a href='atributo.php'>$Attributes</a></li>
        <li><a href='parametro.php'>$Parameters</a></li>
        <li><a href='sector.php'>$Sectors</a></li>
        <li><a href='operador.php'>$Operators</a></li>
        <li><a href='e_mail_error.php'>$E_mail_error_log</a></li>
      </ul>
    </li>";
    }
echo "<li style='float:right; margin-right:30px'><a href='login.php'>$Exit</a></li>
</ul>
</div>";


?>

