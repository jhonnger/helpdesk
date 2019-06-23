<?PHP
/*
    Nombre: opr_self_clave.inc
    Autor: Julio Tuozzo
    Función: Auto genera una nueva contraseña para el operador
    Function: self create a new operator password
    Ver: 2.12
*/

$js_muestro_captcha="<script language='JavaScript'>
                     document.getElementById('forgot').style.visibility='visible';
                     document.getElementById('forgot_text').style.visibility='hidden';
                     </script>";


if (strlen($_POST['operador'])==0)        ## Verifico que haya ingresado el operador.
	   {$mensaje=$Err_input_operator;        // Verify that the operator has entered.
    	 include('login.inc');
    	 exit();
    	}

$operador=trim(strip_tags($_POST['operador']));

## Busco el operador en la tabla, verifico que tenga un e-mail
// Search the user in the tables, verify that has an e-mail.

$query="SELECT * FROM {$MyPHD}operador WHERE operador_id='$operador'";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
	   {$mensaje=$Oper_not_autorized;
	    include('login.inc');
	    exit();
	   }

$row=mysql_fetch_array($result);
$e_mail=$row['e_mail'];
$ape_y_nom=$row['ape_y_nom'];

if (strlen($e_mail)<5)                    ## Verifico que tenga un e-mail para enviar la contraseña
	   {$mensaje=$No_e_mail_usr;          // Verify that the user has e-mail to send te password
    	 include('login.inc');
    	 exit();
    	}

$securimage = new Securimage();
if ($securimage->check($_POST['captcha']) == false and  isset($_SESSION['securimage_code_value']))   ## Verifico el captcha
        {$mensaje=$Error_captcha;                     // Captcha verifying
         include('login.inc');
    	 exit();
        }


$contrasenia=generapwd();
$md5=md5($contrasenia);

## hago la actualización de la contraseña
// Update the password.

$query="UPDATE {$MyPHD}operador
        SET
        contrasenia='$md5',
        expira_clave=DATE_SUB(NOW(),INTERVAL 1 DAY),
        update_oper='$operador',
		update_datetime=NOW()
		WHERE
		operador_id='$operador'";

$update=mysql_query($query) or die (mysql_error());
$js_muestro_captcha="";

## Envio correo con la contraseña al operador.
// Send mail with the operators password.

$query="SELECT * FROM {$MyPHD}parametros";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
        	{$mensaje=str_replace("%1%", $q_filas,$Err_parameters_file);
        	 require($Include.'login.inc');
        	 exit();
            }

$row=mysql_fetch_array($result);

$link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/index.php";


$e_mensaje_html.="$Body_new_pswd_1 <br /> <br />";
$e_mensaje_html.="$Body_new_pswd_2 <strong>$operador</strong> $Body_new_pswd_3 <strong>$contrasenia</strong> <br /> <br />";
$e_mensaje_html.="$Body_new_pswd_4 <br /><br />";
$e_mensaje_html.="$Access_at: <a href='$link'>$link</a>";

$manda_mail=send_e_mail($New_pswd,$row['from_user_psw'],$ape_y_nom,$e_mail,$Subject_new_pswd,$e_mensaje_html);

if(strlen($manda_mail)<1)
       { $mensaje="$Mail_sent ($operador) $ape_y_nom. <br />";
         $mensaje.="$Was_sended_to: $e_mail";
       }
else
       {$mensaje="$No_mail_sent ($operador) $ape_y_nom. <br />";
        $mensaje.="$Mail_srv_err: <em>\"$manda_mail\"</em><br />";
        $mensaje.="$Try_e_mail: $e_mail";
       }

?>
