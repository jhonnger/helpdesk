<?PHP
/*
    Nombre: usr_self_clave.inc
    Autor: Julio Tuozzo
    Función: Auto genera una nueva contraseña para el usuario
    Function: self create a new user password
    Ver: 2.12
*/

$js_muestro_captcha="<script language='JavaScript'>
                     document.getElementById('forgot').style.visibility='visible';
                     document.getElementById('forgot_text').style.visibility='hidden';
                     </script>";


if (strlen($_POST['usuario'])==0)        ## Verifico que haya ingresado el usuario.
	   {$mensaje=$No_user;               // Verify that the user has entered.
    	 include('user_login.inc');
    	 exit();
    	}

$usuario=trim(strip_tags($_POST['usuario']));

## Busco el usuario en la tabla, verifico que tenga un e-mail
// Search the user in the tables, verify that has an e-mail.

$query="SELECT * FROM {$MyPHD}usuario WHERE usuario_id='$usuario'";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
	   {$mensaje=$User_not_exists;
	    include('user_login.inc');
	    exit();
	   }

$row=mysql_fetch_array($result);
$e_mail=$row['e_mail'];
$ape_y_nom=$row['ape_y_nom'];

if (strlen($e_mail)<5)                    ## Verifico que tenga un e-mail para enviar la contraseña
	   {$mensaje=$No_e_mail_usr;          // Verify that the user has e-mail to send te password
    	 include('user_login.inc');
    	 exit();
    	}

$securimage = new Securimage();
if ($securimage->check($_POST['captcha']) == false  and  isset($_SESSION['securimage_code_value']))   ## Verifico el captcha
        {$mensaje=$Error_captcha;                     // Captcha verifying
         include('user_login.inc');
    	 exit();
        }


$contrasenia=generapwd();
$md5=md5($contrasenia);
## hago la actualización de la contraseña
// Update the password.

$query="UPDATE {$MyPHD}usuario
        SET
        contrasenia='$md5',
        cambia_clave='S',
        update_user='$usuario',
        update_oper=null,
		update_datetime=NOW()
		WHERE
		usuario_id='$usuario'";

$update=mysql_query($query) or die (mysql_error());
$js_muestro_captcha="";

## Envio correo con la contraseña al usuario. 
// Send mail with the users password.
$query="SELECT * FROM {$MyPHD}parametros";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
        	{$mensaje=str_replace("%1%", $q_filas,$Err_parameters_file);
        	 require($Include.'user_login.inc');
        	 exit();
            }

$row=mysql_fetch_array($result);


$link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/user_request.php";

$e_mensaje_html.="$Body_new_pswd_1 <br /> <br />";
$e_mensaje_html.="$Body_new_pswd_2 <strong>$usuario</strong> $Body_new_pswd_3 <strong>$contrasenia</strong> <br /> <br />";
$e_mensaje_html.="$Body_new_pswd_4 <br /><br />";
$e_mensaje_html.="$Access_at: <a href='$link'>$link</a>";

$manda_mail=send_e_mail($New_pswd,$row['from_user_psw'],$ape_y_nom,$e_mail, $Subject_new_pswd,$e_mensaje_html);

if(strlen($manda_mail)<1)
       { $mensaje="$Mail_sent ($usuario) $ape_y_nom. <br />";
         $mensaje.="$Was_sended_to: $e_mail";
       }
else
       {$mensaje="$No_mail_sent $usuario. <br />";
        $mensaje.="$Mail_srv_err: <em>\"$manda_mail\"</em><br />";
        $mensaje.="$Try_e_mail: $e_mail";
       }

?>
