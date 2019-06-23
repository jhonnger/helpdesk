<?PHP
/*
    Nombre: opr_ins.inc
    Autor: Julio Tuozzo
    Función: Valida los datos del operador y lo da de alta en la base
    Function: Operator data validation and input in the database.
    Ver: 2.12
*/

## Preparo los datos para insertarlos
// Prepare the data before insert

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
$e_mail=$_POST['e_mail'];
$user=$_SESSION['PHD_OPERADOR'];
$sector_id=$_POST['sector_id'];

   switch ($_POST['nivel'])
            {case $Administrator:
                $_20='selected';
                $nivel=20;
                break;
             case $Operator:
                $_10='selected';
                $nivel=10;
                break;
             default:
                $_0='selected';
                $nivel=0;
            }

    if ($_POST[privado]=="1")
        {$privado="S";
         $private_check="checked";
        }
    else
        {$privado="N";
         $private_check="";
        }

    if ($_POST[avisar_asignado]=="1")
        {$avisar_asignado="S";
         $avisar_asignado_check="checked";
        }
    else
        {$avisar_asignado="N";
         $avisar_asignado_check="";
        }

     if ($_POST[avisar_solicitud]=="1")
        {$avisar_solicitud="S";
         $avisar_solicitud_check="checked";
        }
    else
        {$avisar_solicitud="N";
         $avisar_solicitud_check="";
        }


## Valido datos antes de darlos de alta
// Valid data before insert in the database.

    if (strlen($operador)<1)
    	{$mensaje=$Err_input_operator;
        }

    elseif (strlen($ape_y_nom)<1)
   	    {$mensaje=$No_last_name;
	    }

    elseif (!preg_match('#^.+@.+\\..+$#',$e_mail))
   	    {$mensaje=$No_valid_e_mail;
	    }

    elseif (strlen($sector_id)<1)
   	    {$mensaje=$No_sector;
	    }

        else
        {
	       $query="SELECT * FROM {$MyPHD}operador WHERE operador_id='$operador'";
	       $result=mysql_query($query) or die (mysql_error());
	       $q_filas=Mysql_num_rows($result);
	
           if ($q_filas>0)
	           {$mensaje=$Oper_exists;
	           }
	       else

##  Lo doy de alta en la base
// Input in the database
	           {
                $ape_y_nom=mysql_real_escape_string(html_entity_decode($ape_y_nom,ENT_QUOTES,"ISO-8859-1"));
                ## Genero la contrasenia
                // Create the password
                $contrasenia=generapwd();
                $md5=md5($contrasenia);
                ## Armo el insert y lo ejecuto
                // Make the insert and execute it


                       $query="INSERT INTO {$MyPHD}operador VALUES ('$operador',
					   '$ape_y_nom',
					   '$sector_id',
					   '$e_mail',
					   '$md5',
					   '$privado',
                       $nivel,
					   DATE_SUB(NOW(),INTERVAL 1 DAY), 
					   '$avisar_asignado',
					   '$avisar_solicitud',
					   '$user',
					   NOW(),
					   '$user',
					   NOW())";

    	       $insert=mysql_query($query) or die (mysql_error());

               
               ## Envio correo con la contraseña al operador. Si no se puede enviar
               ## el correo se muestra un mensaje con la contraseña para que el
               ## administrador la informe al usuario.

               // Send mail with the password to the operator. If it is not possible to be sent
               // the mail a message with the password is displayed to the administrator to
               // report the operator.


               $link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"));
               
               $e_mensaje_html="$Body_new_oper_1 <br />";
               $e_mensaje_html.="$Body_new_pswd_2 <strong>$operador</strong> $Body_new_pswd_3 <strong>$contrasenia</strong> <br /><br />";
               $e_mensaje_html.="$Body_new_pswd_4 <br /><br />";
               $e_mensaje_html.="$Access_at: <a href='$link'>$link</a>";
               

                $manda_mail=send_e_mail($_SESSION['PHD_APE_Y_NOM'],$_SESSION['PHD_E_MAIL'],$ape_y_nom,$e_mail, $Subject_new_oper,  $e_mensaje_html);

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
               $_20=$_10=$_0=$e_mail=$ape_y_nom=$avisar_solicitud_check=$avisar_asignado_check=$operador='';

      	     }
          }



?>
