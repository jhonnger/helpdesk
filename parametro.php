<?PHP
/*
    Nombre: parametro.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Controlador del archivo de parámetros
    Function: Paramters file controler.
    Ver: 2.12
    
*/
session_start();
require('config.inc.php');
require($Include.'lang.inc');

if (!isset($_SESSION['PHD_NIVEL']) or $_SESSION['PHD_NIVEL']<20)
    {require($Include.'login.inc');
     exit();
    }


$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());
## Inicializo $mensaje que es donde voy a colocar los mensajes de error en caso de existir.
// Inicializing $mensaje that is where going to place the messages of error in case of existing.

$mensaje='<br />';

## Primero verfico que se haya ingresado por "guardar", si no es así
## muestro la vista para pedir los datos
// At first check that has been entered by “guardar”, if it is not thus
// show the view for data input.

if(!isSet($_POST[guardar]))
	  {$query="SELECT * FROM {$MyPHD}parametros";
       $result=mysql_query($query) or die(mysql_error());
       $q_filas=mysql_num_rows($result);

        if($q_filas!=1)
	           {$mensaje=str_replace("%1%", $q_filas,$Err_parameters_file);
                require('head.inc');
                echo "<body>
                       <script languaje='JavaScript'>
                        window.alert('$mensaje');
                        window.location='index.php';
                        </script> \n
                       </body>
                      </html>";
   	            exit();
               }

        $row=mysql_fetch_array($result);

        $validez_psw=$row['validez_psw'];
        $dias_psw=$row['dias_psw'];
        $max_lines_screen=$row['max_lines_screen'];
        $max_lines_export=$row['max_lines_export'];
        $max_dif_min=$row['max_dif_min'];
        $max_attach=$row['max_attach'];
        $from_user_request=$row['from_user_request'];
        $from_user_psw=$row['from_user_psw'];
        $contact_default=$row['contact_default'];
        $process_default=$row['process_default'];
        $state_default=$row['state_default'];
        $state_alert=$row['state_alert'];
        $main_screen_state=$row['main_screen_state'];
        $PEN=$row['PEN'];
        $PAS=$row['PAS'];
        $CAN=$row['CAN'];
        $date_format=$row['date_format'];
        $aux_date="{$row['date_format']}_selected";
        $$aux_date="selected='selected'";
        $assign_ticket_chk=$row['assign_ticket']=="S"?"checked='checked'":"";
        $ATE=$row['ATE'];//

        require($Include.'parametro.inc');
	    exit();
       }
else
    ## Inicializo las variables con los valores que vienen del formulario
    // Set the variables with the form values.
    {if (get_magic_quotes_gpc())
            { foreach($_POST as $clave => $valor)
                  {$_POST[$clave]=stripslashes($_POST[$clave]);
                  }
            }

       foreach($_POST as $clave => $valor)
             {$_POST[$clave]=trim(htmlentities($_POST[$clave],ENT_QUOTES,"ISO-8859-1"));
             }
       $validez_psw=$_POST['validez_psw'];
       $dias_psw=$_POST['dias_psw'];
       $max_lines_screen=$_POST['max_lines_screen'];
       $max_lines_export=$_POST['max_lines_export'];
       $max_dif_min=$_POST['max_dif_min'];
       $max_attach=$_POST['max_attach'];
       $from_user_request=$_POST['from_user_request'];
       $from_user_psw=$_POST['from_user_psw'];
       $contact_default=$_POST['contact_default'];
       $process_default=$_POST['process_default'];
       $state_default=$_POST['state_default'];
       $state_alert=$_POST['state_alert'];
       $main_screen_state=$_POST['main_screen_state'];
       $PEN=$_POST['PEN'];
       $PAS=$_POST['PAS'];
       $CAN=$_POST['CAN'];
       $date_format=$_POST['date_format'];
       $aux_date="{$_POST['date_format']}_selected";
       $$aux_date="selected='selected'";
       $assign_ticket=$_POST['assign_ticket']=="S"?"S":"N";
       $ATE=$_POST['ATE'];//POSIBLE ERROR


    }

## Validación del contenido del formulario
// Form content validation

$OK=true;
$I=0;
foreach ($_POST as $variable=>$valor)
    { $caso_variable=$variable;
      $caso_variable[0]=strtoupper($variable[0]);
      $$caso_variable=$valor;
      $I++;
      if ((!is_numeric($valor) or $valor<1) and $I<7)
          { $OK=false;

            $variable=$variable."_err";
            $$variable="<br /><span class='error'><small>$Upper_than_cero</small></span>";
          }

    }
if ($_POST['max_attach']>16000000)
    { $OK=false;
      $max_attach_err="<br /><span class='error'><small>$High_than_16m</small></span>";
    }

if (!preg_match('#^.+@.+\\..+$#',$from_user_request))

   	    {$OK=false;
         $from_user_request_err="<br /> <span class='error'><small>$No_valid_e_mail</small></span>";
	    }

if (!preg_match('#^.+@.+\\..+$#',$from_user_psw))

   	    {$OK=false;
         $from_user_psw_err="<br /> <span class='error'><small>$No_valid_e_mail</small></span>";
	    }


if (strlen($_POST['PAS'])<1)
    {$PAS_err="<br /><span class='error'><small>$Cant_blank_value</small></span>";
     $OK=false;
    }

if (strlen($_POST['PEN'])<1)
    {$PEN_err="<br /><span class='error'><small>$Cant_blank_value</small></span>";
     $OK=false;
    }

if (strlen($_POST['CAN'])<1)
    {$CAN_err="<br /><span class='error'><small>$Cant_blank_value</small></span>";
     $OK=false;
    }

if (!$OK)
    { $mensaje=$Correct_err_to_cont;
      require($Include.'parametro.inc');
      exit();
    }

$query="UPDATE {$MyPHD}parametros SET
       validez_psw=$validez_psw,
       dias_psw=$dias_psw,
       max_lines_screen=$max_lines_screen,
       max_lines_export=$max_lines_export,
       max_dif_min=$max_dif_min,
       max_attach=$max_attach,
       assign_ticket='$assign_ticket',
       from_user_request='$from_user_request',
       from_user_psw='$from_user_psw',
       contact_default='$contact_default',
       process_default='$process_default',
       state_default='$state_default',
       state_alert='$state_alert',
       main_screen_state='$main_screen_state',
       date_format='$date_format',
       PEN='$PEN',
       PAS='$PAS',
       CAN='$CAN',
  	   update_oper='$_SESSION[PHD_OPERADOR]',
  	   update_datetime=NOW(),
       ATE = '$ATE'";

     $update=mysql_query($query) or die (mysql_error());
     
     $_SESSION['PHD_VALIDEZ_PSW']=$validez_psw;
     $_SESSION['PHD_DIAS_PSW']=$dias_psw;
     $_SESSION['PHD_MAX_LINES_SCREEN']=$max_lines_screen;
     $_SESSION['PHD_MAX_LINES_EXPORT']=$max_lines_export;
     $_SESSION['PHD_MAX_DIF_MIN']=$max_dif_min;
     $_SESSION['PHD_MAX_ATTACH']=$max_attach;
     $_SESSION['PHD_ASSIGN_TICKET']=$assign_ticket;
     $_SESSION['PHD_FROM_USER_REQUEST']=$from_user_request;
     $_SESSION['PHD_CONTACT_DEFAULT']=$contact_default;
     $_SESSION['PHD_PROCESS_DEFAULT']=$process_default;
     $_SESSION['PHD_STATE_DEFAULT']=$state_default;
     $_SESSION['PHD_STATE_ALERT']=$state_alert;
     $_SESSION['PHD_MAIN_SCREEN_STATE']=$main_screen_state;
     $_SESSION['PHD_PEN']=$PEN;
     $_SESSION['PHD_PAS']=$PAS;
     $_SESSION['PHD_CAN']=$CAN;
     $_SESSION['PHD_DATE_FORMAT']=$date_format;
     $_SESSION['PHD_ATE']=$ATE;//

     header("Location: index.php");
?>
