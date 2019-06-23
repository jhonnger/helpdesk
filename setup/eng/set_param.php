<?PHP
/*
    Nombre: set_param.php
    Autor: Julio Tuozzo - jtuozzo@p-hd.com.ar
    Función: Configura los parámetros generales del sistema
    Ver: 2.00
*/

session_start();

if (!isset($_SESSION['PARAM']))
    {include('setup_head.inc');
     echo "<p class='danger'>INVALID CALL</p>";
     exit();
    }

require('../../config.inc.php');
require('../../include/lang.inc');

$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());
## Inicializo $mensaje que es donde voy a colocar los mensajes de error en caso de existir.

$mensaje='<br />';

## Primero verfico que se haya ingresado por "guardar", si no es así
## muestro la vista para pedir los datos

if(!isSet($_POST[guardar]))
     {
        $validez_psw=60;
        $dias_psw=90;
        $max_lines_screen=40;
        $max_lines_export=60000;
        $max_dif_min=10;
        $max_attach=120000;
        $from_user_request="admin@p-hd.com.ar";
        $from_user_psw="admin@p-hd.com.ar";
        $contact_default="";
        $process_default="";
        $state_default="";
        $state_alert="";
        $main_screen_state="";
        $date_format="DMA";
        $PEN="Loaded";
        $PAS="Proccessed";
        $CAN="Canceled";
        $assign_ticket_chk="";
        

        include('set_param.inc');
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
            $$variable="<br /><span class='danger'><small>$Upper_than_cero</small></span>";
          }

    }
if ($_POST['max_attach']>16000000)
    { $OK=false;
      $max_attach_err="<br /><span class='danger'><small>$High_than_16m</small></span>";
    }

if (!ereg('^.+@.+\\..+$',$from_user_request))

   	    {$OK=false;
         $from_user_request_err="<br /> <span class='danger'><small>$No_valid_e_mail</small></span>";
	    }

if (!ereg('^.+@.+\\..+$',$from_user_psw))

   	    {$OK=false;
         $from_user_psw_err="<br /> <span class='danger'><small>$No_valid_e_mail</small></span>";
	    }


if (strlen($_POST['PAS'])<1)
    {$PAS_err="<br /><span class='danger'><small>$Cant_blank_value</small></span>";
     $OK=false;
    }

if (strlen($_POST['PEN'])<1)
    {$PEN_err="<br /><span class='danger'><small>$Cant_blank_value</small></span>";
     $OK=false;
    }

if (strlen($_POST['CAN'])<1)
    {$CAN_err="<br /><span class='danger'><small>$Cant_blank_value</small></span>";
     $OK=false;
    }

if (!$OK)
    { $mensaje=$Correct_err_to_cont;
      require('set_param.inc');
      exit();
    }




$query="INSERT INTO parametros VALUES
        ($validez_psw,
         $dias_psw,
         $max_lines_screen,
         $max_lines_export,
         $max_dif_min,
         $max_attach,
         '$assign_ticket',
         '$from_user_request',
         '$from_user_psw',
         '$contact_default',
         '$process_default',
         '$state_default',
         '$state_alert',
         '$main_screen_state',
         '$date_format',
         '$PEN',
         '$PAS',
         '$CAN',
         'SETUP',
  	      NOW(),
         'SETUP',
  	      NOW())";

if (!mysql_query($query))
    {$mensaje="<h2 class='danger'>Insert script error</h2>
     MySQL error: ".mysql_error();
     require('set_param.inc');
     exit();

    }

session_destroy();
header("Location: index.php");
?>
