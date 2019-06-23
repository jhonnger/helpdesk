<?PHP
/*
    Nombre: user_login.inc
    Autor: Julio Tuozzo jtuozzo@p-hd.com.ar
    Función: Formulario de ingreso de usuario y contraseña
    Function: Form of user entrance and password
    Ver: 2.00
*/

include('head.inc');
echo "<body>
<h5>$Version</h5>

<br style='line-height:9;'/>

<div style='text-align:center'>
<a href='http://www.p-hd.com.ar'><img SRC='./images/phd_400_55.gif' border='0' alt='PHD Help Desk'></a>
<h2>$User_request_access</h2>
</div>
<br style='line-height:2.8;'/>

<div id='login'>

   <h3 style='text-align:center'>$Log_in</h3><br />

   <form method='post' action='user_login.php' >
	$User: &nbsp; &nbsp; <input type='text' name='usuario' value='$usuario'  size='20' maxlength='18' /> <br /> <br />
    $Password: <input type='password' name='contrasenia' size='20' maxlength='16' /> <br /> <br />
    <input class='boton' type='submit' value='$Enter' name='submit'>

</div>

<p style='text-align:center' id='forgot_text'><a href='#' onfocus=\"document.getElementById('forgot').style.visibility='visible'; document.getElementById('forgot_text').style.visibility='hidden';
document.getElementById('error').style.visibility='hidden'; \">$Forgot_password</a></p>
<p class='error' id='error'> $mensaje </p>
<p style='visibility:hidden; text-align:center; font-weight:bold;' id='forgot'>
<img id='captcha' src='./securimage/securimage_show.php' alt='CAPTCHA Image' /><br /><br />
$Input_the_code <input type='text' name='captcha' size='4' maxlength='4' />
 $And_press  <input type='submit' class='boton' name='genera'  value='$Gener_new_pswd' onclick='this.value=\"Wait...\"' />  </p>

</form>
$js_muestro_captcha
</body>

</html>";
?>
