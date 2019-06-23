<?PHP
/*
    Nombre: login.php
    Autor: Julio Tuozzo
    Función: Validación de operador y contraseña.
    Function: operator and password validation.
    Ver: 2.12
    
*/
session_start();
## Blanqueo variables globales.
// Unset global variables.

foreach($_SESSION as $clave => $valor)
     { $hay_phd=strpos("AUX".$clave,"PHD_");
       if($hay_phd)
            {unset($_SESSION[$clave]);
            }
     }

require('config.inc.php');
require($Include.'lang.inc');
require('funciones.inc.php');
require('./securimage/securimage.php');


$Conect=mysql_connect($Host,$Usuario,$Contrasena) or die (mysql_error());
$Uso=mysql_select_db($Base) or die (mysql_error());

## Pregunto si pidió generar la contraseña
// Ask about the password generation

if(isset($_POST['genera']))
    {require($Include.'opr_self_clave.inc');
    }

## Verfico que se haya ingresado por "submit", si no es así
## pido usuario y contraseña
// Check that has been entered by “submit”, if it is not thus
// request operator and password

if(!isSet($_POST[submit]))
	  {require($Include.'login.inc');
	   exit();
      }
    
if (strlen($_POST[operador])==0)        ## Verifico que haya ingresado el operador.
	   {$mensaje=$Err_input_operator;          // Verify that the operator has entered.
    	 require($Include.'login.inc');
    	 exit();
    	}

if (strlen($_POST[contrasenia])==0) ## Verifico que haya ingresado al contraseña.
	       {$mensaje=$Err_input_passwd;        // Verify that the password has entered.
	        require($Include.'login.inc');
	        exit();
	       }


## Busco el operador en la tabla correspondiente
// Search the operator in the table

$operador=trim(strip_tags($_POST[operador]));
$query="SELECT * FROM {$MyPHD}operador WHERE operador_id='$operador'";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
	   {$mensaje=$Oper_not_autorized;
	    require($Include.'login.inc');
	    exit();
	   }

### Ahora verifico la contraseña
$md5_contrasenia=md5($_POST['contrasenia']);
$query="SELECT * FROM {$MyPHD}operador WHERE operador_id='$operador' AND contrasenia='$md5_contrasenia'";
$result=mysql_query($query) or die (mysql_error());;
$q_filas=mysql_num_rows($result);

if ($q_filas!=1)
 	        {$mensaje=$Invalid_passwd;
	         require($Include.'login.inc');
	         exit();
	        }

$data=mysql_fetch_array($result);
if ($data['nivel']<1)
		       {$mensaje=$Oper_not_autorized;
                require($Include.'login.inc');
		        exit();
		       }

## Operador y contraseña válidos busco los parámetros de la aplicación e
## inicializo las variables globales.
// Operator and password valid, search the software parameters and initialize
// the global variables.

$query="SELECT * FROM {$MyPHD}parametros";
$result=mysql_query($query) or die(mysql_error());
$q_filas=mysql_num_rows($result);

if($q_filas!=1)
        	{$mensaje=str_replace("%1%", $q_filas,$Err_parameters_file);
        	 require($Include.'login.inc');
        	 exit();
            }

$row=mysql_fetch_array($result);

$_SESSION['PHD_OPERADOR']=$data['operador_id'];
$_SESSION['PHD_APE_Y_NOM']=$data['ape_y_nom'];
$_SESSION['PHD_NIVEL']=$data['nivel'];
$_SESSION['PHD_SECTOR_ID']=$data['sector_id'];
$_SESSION['PHD_E_MAIL']= $row['from_user_psw'];
$_SESSION['PHD_VALIDEZ_PSW']=$row['validez_psw'];
$_SESSION['PHD_DIAS_PSW']=$row['dias_psw'];
$_SESSION['PHD_MAX_LINES_SCREEN']=$row['max_lines_screen'];
$_SESSION['PHD_MAX_LINES_EXPORT']=$row['max_lines_export'];
$_SESSION['PHD_MAX_DIF_MIN']=$row['max_dif_min'];
$_SESSION['PHD_MAX_ATTACH']=$row['max_attach'];
$_SESSION['PHD_ASSIGN_TICKET']=$row['assign_ticket'];
$_SESSION['PHD_FROM_USER_REQUEST']=$row['from_user_request'];
$_SESSION['PHD_CONTACT_DEFAULT']=$row['contact_default'];
$_SESSION['PHD_PROCESS_DEFAULT']=$row['process_default'];
$_SESSION['PHD_STATE_DEFAULT']=$row['state_default'];
$_SESSION['PHD_STATE_ALERT']=$row['state_alert'];
$_SESSION['PHD_MAIN_SCREEN_STATE']=$row['main_screen_state'];
$_SESSION['PHD_PEN']=$row['PEN'];
$_SESSION['PHD_PAS']=$row['PAS'];
$_SESSION['PHD_CAN']=$row['CAN'];
$_SESSION['PHD_ATE']=$row['ATE'];//
$_SESSION['PHD_DATE_FORMAT']=$row['date_format'];

## Verifico que no haya caducado la contraseña, de ser asi pido
## el cambio, si esta todo OK entro a la aplicacion.
// Verify that it has not expired the password, to be thus request
// the change, if this whole OK enter to the application.

if (strtotime($data['expira_clave'])<time())
            { ## Antes de llamar a la pantalla de cambio de clave bajo el nivel de
              ## ejecución para que no entre a ningún lado hasta que no la cambie.
              // Before calling to the screen of change of key under the level of
              // execution so that not between a no side until it does not change it.
              
              $_SESSION['PHD_CLAVE_CHG']=$_SESSION['PHD_NIVEL'];
              $_SESSION['PHD_NIVEL']=5;
              header("Location: clave_chg.php");
            }
else
            { header("Location: index.php"); // Todo OK, voy al index
            }
	
?>
