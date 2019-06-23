<?PHP
/*
    Nombre: usr_gen_clave.inc
    Autor: Julio Tuozzo
    Función: Genera una nueva contraseña para el usuario
    Function: create a new user password
    Ver: 2.12
*/

## Inicializo las variables y genero la contraseña
// Inicializing variables and create password

if (get_magic_quotes_gpc())
    { foreach($_POST as $clave => $valor)
      {$_POST[$clave]=stripslashes($_POST[$clave]);
      }
    }

foreach($_POST as $clave => $valor)
     {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
     }

$usuario_id=$_POST['usuario_id'];
$e_mail=$_POST['e_mail'];
$ape_y_nom=$_POST['ape_y_nom'];
$contrasenia=generapwd();
$md5=md5($contrasenia);


if (strlen($e_mail)<5)                    ## Verifico que tenga un e-mail para enviar la contraseña
	   {$mensaje=$No_e_mail_usr;          // Verify that the user has e-mail to send te password
       }

else
        {## hago la actualización de la contraseña
        // Update the password.

        $query="UPDATE {$MyPHD}usuario
                SET
                contrasenia='$md5',
                cambia_clave='S',
                update_oper='{$_SESSION[PHD_OPERADOR]}',
                update_user=null,
        		update_datetime=NOW()
		        WHERE
		        usuario_id='$usuario_id'";

        $update=mysql_query($query) or die (mysql_error());

        ## Envio correo con la contraseña al usuario.
        // Send mail with the users password.

        $link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/user_request.php";

        $e_mensaje_html.="$Body_new_pswd_1 <br />";
        $e_mensaje_html.="$Body_new_pswd_2 <strong>$usuario_id</strong> $Body_new_pswd_3 <strong>$contrasenia</strong> <br /> <br />";
        $e_mensaje_html.="$Body_new_pswd_4 <br /><br />";
        $e_mensaje_html.="$Access_at: <a href='$link'>$link</a>";



        $manda_mail=send_e_mail($_SESSION['PHD_APE_Y_NOM'],$_SESSION['PHD_E_MAIL'],$ape_y_nom,$e_mail,$Subject_new_pswd,$e_mensaje_html);

        if(strlen($manda_mail)<1)
            { $mensaje="$Mail_sent ($usuario_id) $ape_y_nom. <br />";
              $mensaje.="$Was_sended_to: $e_mail <br />";
              $mensaje.="$New_pswd_assigned $contrasenia";
            }
        else
            {$mensaje="$No_mail_sent ($usuario_id) $ape_y_nom. <br />";
             $mensaje.="$Mail_srv_err: <em>\"$manda_mail\"</em><br />";
             $mensaje.="$Try_e_mail: $e_mail  <br />";
             $mensaje.="$New_pswd_assigned $contrasenia";
            }
       }

$piso=$planta=$e_mail=$ape_y_nom=$usuario_id='';
?>
