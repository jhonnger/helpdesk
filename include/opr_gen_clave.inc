<?PHP
/*
    Nombre: opr_gen_clave.inc
    Autor: Julio Tuozzo
    Función: Genera una nueva contraseña para el operador
    Function: create a new operator password
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

$operador=$_POST['operador'];
$ape_y_nom=$_POST['ape_y_nom'];
$contrasenia=generapwd();
$e_mail=$_POST['e_mail'];
$md5=md5($contrasenia);
## hago la actualización de la contraseña
// Update the password.

$query="UPDATE {$MyPHD}operador
        SET
        contrasenia='$md5',
        expira_clave=DATE_SUB(NOW(),INTERVAL 1 DAY),
        update_oper='{$_SESSION['PHD_OPERADOR']}',
		update_datetime=NOW()
		WHERE
		operador_id='$operador'";

$update=mysql_query($query) or die (mysql_error());

## Envio correo con la contraseña al operador. Si no se puede enviar
## el correo se muestra un mensaje con la contraseña para que el
## administrador la informe al usuario.
// Send mail with the password to the operator. If cannot be sent
// the mail it shows a message with the password so that
// administrator the report to the operator.
$link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/index.php";

$e_mensaje_html.="$Body_new_pswd_1 <br />";
$e_mensaje_html.="$Body_new_pswd_2 <strong>$operador</strong> $Body_new_pswd_3 <strong>$contrasenia</strong> <br /> <br />";
$e_mensaje_html.="$Body_new_pswd_4 <br /><br />";
$e_mensaje_html.="$Access_at: <a href='$link'>$link</a>"; 

$manda_mail=send_e_mail($_SESSION['PHD_APE_Y_NOM'],$_SESSION['PHD_E_MAIL'],$ape_y_nom,$e_mail, $Subject_new_pswd, $e_mensaje_html);

if(strlen($manda_mail)<1)
          { $mensaje="$Mail_sent $operador. <br />";
            $mensaje.="$New_pswd_assigned $contrasenia";
          }
else
          { $mensaje="$No_mail_sent $operador. <br />";
            $mensaje.="$Mail_srv_err: <em>\"$manda_mail\"</em><br />";
            $mensaje.="$New_pswd_assigned $contrasenia";
          }


// Blanqueo variables
$_20=$_10=$_0=$e_mail=$ape_y_nom=$operador='';
?>