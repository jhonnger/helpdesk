<?PHP
/*
    Nombre: user_menu.inc
    Autor: Julio Tuozzo jtuozzo@p-hd.com.ar
    Función: Línea del menú de usuarios
    Function: users menu line
    Ver: 2.12
*/

echo "
<script type='text/javascript' src='menu_ie6.js'></script>
<table border='0' align='center' cellspacing='0' cellpadding='0' width='100%'>
<tr>
<td  width='180'><a href='http://www.p-hd.com.ar'><img src='./images/phd_150_20.gif' border='0' alt='Help Desk' /></a></td>
<td style='text-align:center; vertical-align:bottom'>$opcion</td>
<td style='text-align:right; vertical-align:bottom'><h5>$Version</h5></td>
</tr>
</table>


<div id='menu'>
<ul>
    <li><a href='user_request.php'>$New_request</a></li>
    <li><a href='solic_list.php?op=user'>$See_my_request</a></li>
    <li><a href='user_clave_chg.php'>$Passwd_change</a></li>
    <li style='float:right; margin-right:30px'><a href='user_login.php'>$Exit</a></li>
</ul>
</div>";

?>

